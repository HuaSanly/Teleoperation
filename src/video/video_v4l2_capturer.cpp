#include "video/video_v4l2_capturer.hpp"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "nvbufsurface.h"

namespace trb::video
{
    namespace
    {
        const char *memoryModeName(VideoV4L2Capturer::MemoryMode mode)
        {
            switch (mode)
            {
            case VideoV4L2Capturer::MemoryMode::kDmaBuf:
                return "dmabuf";
            case VideoV4L2Capturer::MemoryMode::kMmap:
            default:
                return "mmap";
            }
        }
    }

    VideoV4L2Capturer::VideoV4L2Capturer() = default;

    VideoV4L2Capturer::~VideoV4L2Capturer()
    {
        stop();
    }

    bool VideoV4L2Capturer::initialize(const Config &config)
    {
        config_ = config;
        actual_width_ = 0;
        actual_height_ = 0;
        actual_pixel_format_ = 0;

        if (!openDevice())
            return false;

        if (!configureDevice())
        {
            closeDevice();
            return false;
        }

        return true;
    }

    bool VideoV4L2Capturer::start()
    {
        if (running_)
            return true;

        if (cam_fd_ < 0)
        {
            std::cerr << "VideoV4L2Capturer not initialized (device not opened)" << std::endl;
            return false;
        }

        if (!requestBuffers())
            return false;

        if (!streamOn())
            return false;

        running_ = true;
        return true;
    }

    void VideoV4L2Capturer::interrupt()
    {
        if (!running_)
        {
            return;
        }

        running_ = false;

        // STREAMOFF breaks poll/DQBUF quickly but keeps the mapped buffers
        // alive until the owner thread has finished consuming the last frame.
        streamOff();
    }

    void VideoV4L2Capturer::stop()
    {
        if (!running_)
        {
            closeDevice();
            return;
        }

        interrupt();
        closeDevice();
    }

    bool VideoV4L2Capturer::isRunning() const
    {
        return running_.load();
    }

    uint32_t VideoV4L2Capturer::width() const
    {
        return actual_width_;
    }

    uint32_t VideoV4L2Capturer::height() const
    {
        return actual_height_;
    }

    uint32_t VideoV4L2Capturer::pixelFormat() const
    {
        return actual_pixel_format_;
    }

    bool VideoV4L2Capturer::openDevice()
    {
        if (cam_fd_ >= 0)
            return true;

        cam_fd_ = open(config_.device_path.c_str(), O_RDWR | O_NONBLOCK);
        if (cam_fd_ < 0)
        {
            std::cerr << "Failed to open V4L2 device '" << config_.device_path
                      << "': " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        return true;
    }

    bool VideoV4L2Capturer::pollForFrame(int timeout_ms)
    {
        struct pollfd fds[1];
        fds[0].fd = cam_fd_;
        fds[0].events = POLLIN | POLLPRI | POLLERR;
        fds[0].revents = 0;

        const int pr = poll(fds, 1, timeout_ms);
        if (pr < 0)
        {
            if (errno == EINTR)
                return false;
            std::cerr << "poll failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        if (pr == 0)
            return false;

        if (!running_.load())
            return false;

        if ((fds[0].revents & (POLLERR | POLLPRI)) != 0 && (fds[0].revents & POLLIN) == 0)
        {
            std::cerr << "poll returned non-POLLIN revents=0x" << std::hex << fds[0].revents << std::dec
                      << "; attempting DQBUF anyway" << std::endl;
        }

        return (fds[0].revents & (POLLIN | POLLPRI | POLLERR)) != 0;
    }

    bool VideoV4L2Capturer::dequeue(Frame &frame, int timeout_ms)
    {
        if (!running_ || cam_fd_ < 0)
            return false;

        if (!pollForFrame(timeout_ms))
            return false;

        struct v4l2_buffer v4l2_buf;
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        v4l2_buf.memory = (config_.memory_mode == MemoryMode::kDmaBuf)
                               ? V4L2_MEMORY_DMABUF
                               : V4L2_MEMORY_MMAP;

        {
            std::lock_guard<std::mutex> lk(ioctl_mutex_);
            if (ioctl(cam_fd_, VIDIOC_DQBUF, &v4l2_buf) < 0)
            {
                if (errno == EAGAIN || errno == EINTR)
                    return false;
                if (!running_)
                    return false;
                std::cerr << "VIDIOC_DQBUF failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
                return false;
            }
        }

        if (v4l2_buf.index >= buffers_.size())
        {
            std::cerr << "VIDIOC_DQBUF returned invalid index=" << v4l2_buf.index
                      << " (buffers=" << buffers_.size() << ")" << std::endl;
            return false;
        }

        const auto &buffer = buffers_[v4l2_buf.index];
        if ((config_.memory_mode == MemoryMode::kMmap && buffer.start == nullptr) ||
            (config_.memory_mode == MemoryMode::kDmaBuf && buffer.dmabuf_fd < 0))
        {
            std::cerr << "VIDIOC_DQBUF returned uninitialized buffer index=" << v4l2_buf.index << std::endl;
            return false;
        }

        frame.v4l2_buf = v4l2_buf;
        frame.data = (config_.memory_mode == MemoryMode::kMmap)
                         ? static_cast<const uint8_t *>(buffer.start)
                         : nullptr;
        frame.size = static_cast<size_t>(v4l2_buf.bytesused);
        frame.dmabuf_fd = (config_.memory_mode == MemoryMode::kDmaBuf)
                              ? buffer.dmabuf_fd
                              : -1;
        if (config_.memory_mode == MemoryMode::kDmaBuf && frame.size == 0)
        {
            frame.size = buffer.length;
        }
        frame.timestamp_us = static_cast<uint64_t>(v4l2_buf.timestamp.tv_sec) * 1000000ULL +
                             static_cast<uint64_t>(v4l2_buf.timestamp.tv_usec);

        return (frame.data != nullptr || frame.dmabuf_fd >= 0) && frame.size != 0;
    }

    bool VideoV4L2Capturer::requeue(const struct v4l2_buffer &v4l2_buf)
    {
        if (cam_fd_ < 0)
            return false;

        struct v4l2_buffer buf = v4l2_buf;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = (config_.memory_mode == MemoryMode::kDmaBuf)
                         ? V4L2_MEMORY_DMABUF
                         : V4L2_MEMORY_MMAP;
        if (config_.memory_mode == MemoryMode::kDmaBuf)
        {
            if (buf.index >= buffers_.size() || buffers_[buf.index].dmabuf_fd < 0)
            {
                std::cerr << "VIDIOC_QBUF invalid dmabuf index=" << buf.index << std::endl;
                return false;
            }
            buf.m.fd = buffers_[buf.index].dmabuf_fd;
            buf.length = buffers_[buf.index].length;
            buf.bytesused = 0;
        }

        std::lock_guard<std::mutex> lk(ioctl_mutex_);
        if (ioctl(cam_fd_, VIDIOC_QBUF, &buf) < 0)
        {
            std::cerr << "VIDIOC_QBUF failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }
        return true;
    }

    bool VideoV4L2Capturer::configureDevice()
    {
        struct v4l2_capability cap;
        memset(&cap, 0, sizeof(cap));
        if (ioctl(cam_fd_, VIDIOC_QUERYCAP, &cap) < 0)
        {
            std::cerr << "VIDIOC_QUERYCAP failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) || !(cap.capabilities & V4L2_CAP_STREAMING))
        {
            std::cerr << "Device does not support V4L2 capture/streaming" << std::endl;
            return false;
        }

        struct v4l2_format fmt;
        memset(&fmt, 0, sizeof(fmt));
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = config_.width;
        fmt.fmt.pix.height = config_.height;
        fmt.fmt.pix.pixelformat = config_.pixel_format;
        fmt.fmt.pix.field = V4L2_FIELD_ANY;

        if (ioctl(cam_fd_, VIDIOC_S_FMT, &fmt) < 0)
        {
            std::cerr << "VIDIOC_S_FMT failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        memset(&fmt, 0, sizeof(fmt));
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (ioctl(cam_fd_, VIDIOC_G_FMT, &fmt) < 0)
        {
            std::cerr << "VIDIOC_G_FMT failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        actual_width_ = fmt.fmt.pix.width;
        actual_height_ = fmt.fmt.pix.height;
        actual_pixel_format_ = fmt.fmt.pix.pixelformat;

        std::cerr << "VideoV4L2Capturer negotiated format: "
              << actual_width_ << "x" << actual_height_
              << " pixfmt=0x" << std::hex << actual_pixel_format_ << std::dec
              << " memory=" << memoryModeName(config_.memory_mode)
              << std::endl;

        // best-effort set framerate
        if (config_.framerate != 0)
        {
            struct v4l2_streamparm sp;
            memset(&sp, 0, sizeof(sp));
            sp.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            sp.parm.capture.timeperframe.numerator = 1;
            sp.parm.capture.timeperframe.denominator = config_.framerate;
            if (ioctl(cam_fd_, VIDIOC_S_PARM, &sp) < 0)
            {
                std::cerr << "WARN: VIDIOC_S_PARM failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            }
        }

        return true;
    }

    bool VideoV4L2Capturer::requestBuffers()
    {
        if (!buffers_.empty())
            return true;

        const uint32_t count = (config_.buffer_count == 0) ? 4 : config_.buffer_count;

        if (config_.memory_mode == MemoryMode::kDmaBuf)
        {
            return requestDmaBufBuffers(count);
        }

        return requestMmapBuffers(count);
    }

    bool VideoV4L2Capturer::requestMmapBuffers(uint32_t count)
    {
        if (count == 0)
        {
            count = 4;
        }

        struct v4l2_requestbuffers rb;
        memset(&rb, 0, sizeof(rb));
        rb.count = count;
        rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        rb.memory = V4L2_MEMORY_MMAP;

        if (ioctl(cam_fd_, VIDIOC_REQBUFS, &rb) < 0)
        {
            std::cerr << "VIDIOC_REQBUFS failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        if (rb.count == 0)
        {
            std::cerr << "Driver returned 0 buffers" << std::endl;
            return false;
        }

        buffers_.resize(rb.count);

        for (uint32_t index = 0; index < rb.count; ++index)
        {
            struct v4l2_buffer buf;
            memset(&buf, 0, sizeof(buf));
            buf.index = index;
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;

            if (ioctl(cam_fd_, VIDIOC_QUERYBUF, &buf) < 0)
            {
                std::cerr << "VIDIOC_QUERYBUF failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
                return false;
            }

            buffers_[index].length = buf.length;
            buffers_[index].start = mmap(nullptr, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, cam_fd_, buf.m.offset);
            if (buffers_[index].start == MAP_FAILED)
            {
                std::cerr << "mmap failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
                buffers_[index].start = nullptr;
                return false;
            }

            if (ioctl(cam_fd_, VIDIOC_QBUF, &buf) < 0)
            {
                std::cerr << "VIDIOC_QBUF failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
                return false;
            }
        }

        return true;
    }

    bool VideoV4L2Capturer::requestDmaBufBuffers(uint32_t count)
    {
        if (count == 0)
        {
            count = 4;
        }

        if (actual_pixel_format_ != V4L2_PIX_FMT_YUYV)
        {
            std::cerr << "DMABUF capture is only supported for negotiated YUYV; actual pixfmt=0x"
                      << std::hex << actual_pixel_format_ << std::dec << std::endl;
            return false;
        }

        struct v4l2_requestbuffers rb;
        memset(&rb, 0, sizeof(rb));
        rb.count = count;
        rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        rb.memory = V4L2_MEMORY_DMABUF;

        if (ioctl(cam_fd_, VIDIOC_REQBUFS, &rb) < 0)
        {
            std::cerr << "VIDIOC_REQBUFS DMABUF failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        if (rb.count == 0)
        {
            std::cerr << "Driver returned 0 DMABUF buffers" << std::endl;
            return false;
        }

        buffers_.resize(rb.count);

        for (uint32_t index = 0; index < rb.count; ++index)
        {
            NvBufSurfaceCreateParams params;
            memset(&params, 0, sizeof(params));
            params.gpuId = 0;
            params.width = actual_width_;
            params.height = actual_height_;
            params.layout = NVBUF_LAYOUT_PITCH;
            params.colorFormat = NVBUF_COLOR_FORMAT_YUYV;
            params.memType = NVBUF_MEM_SURFACE_ARRAY;
            params.isContiguous = true;

            NvBufSurface *surface = nullptr;
            if (NvBufSurfaceCreate(&surface, 1, &params) != 0 || !surface)
            {
                std::cerr << "NvBufSurfaceCreate YUYV capture buffer failed at index=" << index << std::endl;
                return false;
            }
            surface->numFilled = 1;

            buffers_[index].surface = surface;
            buffers_[index].dmabuf_fd = static_cast<int>(surface->surfaceList[0].bufferDesc);
            buffers_[index].length = surface->surfaceList[0].dataSize;

            struct v4l2_buffer buf;
            memset(&buf, 0, sizeof(buf));
            buf.index = index;
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_DMABUF;
            buf.m.fd = buffers_[index].dmabuf_fd;
            buf.length = buffers_[index].length;

            // Some UVC drivers require QUERYBUF with the imported fd before QBUF.
            (void)ioctl(cam_fd_, VIDIOC_QUERYBUF, &buf);

            memset(&buf, 0, sizeof(buf));
            buf.index = index;
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_DMABUF;
            buf.m.fd = buffers_[index].dmabuf_fd;
            buf.length = buffers_[index].length;

            if (ioctl(cam_fd_, VIDIOC_QBUF, &buf) < 0)
            {
                std::cerr << "VIDIOC_QBUF DMABUF failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
                return false;
            }
        }

        return true;
    }

    bool VideoV4L2Capturer::streamOn()
    {
        enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (ioctl(cam_fd_, VIDIOC_STREAMON, &type) < 0)
        {
            std::cerr << "VIDIOC_STREAMON failed: " << strerror(errno) << " (" << errno << ")" << std::endl;
            return false;
        }

        return true;
    }

    void VideoV4L2Capturer::streamOff()
    {
        if (cam_fd_ < 0)
            return;

        enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        (void)ioctl(cam_fd_, VIDIOC_STREAMOFF, &type);
    }

    void VideoV4L2Capturer::closeDevice()
    {
        if (cam_fd_ >= 0 && !buffers_.empty())
        {
            struct v4l2_requestbuffers rb;
            memset(&rb, 0, sizeof(rb));
            rb.count = 0;
            rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            rb.memory = (config_.memory_mode == MemoryMode::kDmaBuf)
                            ? V4L2_MEMORY_DMABUF
                            : V4L2_MEMORY_MMAP;
            (void)ioctl(cam_fd_, VIDIOC_REQBUFS, &rb);
        }

        for (auto &b : buffers_)
        {
            if (b.start && b.start != MAP_FAILED)
                munmap(b.start, b.length);
            if (b.surface)
                NvBufSurfaceDestroy(reinterpret_cast<NvBufSurface *>(b.surface));
            b.start = nullptr;
            b.length = 0;
            b.surface = nullptr;
            b.dmabuf_fd = -1;
        }
        buffers_.clear();

        if (cam_fd_ >= 0)
        {
            close(cam_fd_);
            cam_fd_ = -1;
        }
    }

} // namespace trb::video
