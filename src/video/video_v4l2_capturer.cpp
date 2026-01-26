#include "video/video_v4l2_capturer.hpp"

#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <poll.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>

#include <ros/ros.h>

namespace trb::video
{

namespace
{
int xioctl(int fd, unsigned long request, void *arg)
{
    int r = 0;
    do
    {
        r = ::ioctl(fd, request, arg);
    } while (r == -1 && errno == EINTR);
    return r;
}

uint64_t nowSteadyUs()
{
    const auto now = std::chrono::steady_clock::now();
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count());
}
} // namespace

VideoV4L2Capturer::VideoV4L2Capturer(VideoV4L2Config config)
    : config_(std::move(config))
{
}

VideoV4L2Capturer::~VideoV4L2Capturer()
{
    stop();
}

bool VideoV4L2Capturer::start()
{
    if (streaming_)
    {
        return true;
    }

    ROS_INFO("V4L2: starting capture device=%s %ux%u@%u fmt=%s buffers=%d",
             config_.device.c_str(),
             config_.width,
             config_.height,
             config_.fps,
             config_.pixel_format.c_str(),
             config_.buffer_count);

    if (!openDevice())
    {
        return false;
    }

    if (!setFormat())
    {
        stop();
        return false;
    }

    if (!setFrameRate())
    {
        ROS_WARN("V4L2: failed to set fps=%u", config_.fps);
    }

    if (!requestBuffers())
    {
        stop();
        return false;
    }

    if (!queueAllBuffers())
    {
        stop();
        return false;
    }

    const v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (xioctl(fd_, VIDIOC_STREAMON, const_cast<v4l2_buf_type *>(&type)) < 0)
    {
        ROS_ERROR("V4L2: VIDIOC_STREAMON failed: %s", ::strerror(errno));
        stop();
        return false;
    }

    streaming_ = true;
    return true;
}

void VideoV4L2Capturer::stop()
{
    if (fd_ < 0)
    {
        return;
    }

    if (streaming_)
    {
        const v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        xioctl(fd_, VIDIOC_STREAMOFF, const_cast<v4l2_buf_type *>(&type));
        streaming_ = false;
    }

    unmapBuffers();

    ::close(fd_);
    fd_ = -1;
}

bool VideoV4L2Capturer::dequeue(V4L2Frame &frame)
{
    if (!streaming_ || fd_ < 0)
    {
        return false;
    }

    pollfd pfd;
    pfd.fd = fd_;
    pfd.events = POLLIN;
    const int poll_rc = ::poll(&pfd, 1, 1000);
    if (poll_rc <= 0)
    {
        return false;
    }

    v4l2_buffer buf;
    std::memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (xioctl(fd_, VIDIOC_DQBUF, &buf) < 0)
    {
        if (errno == EAGAIN)
        {
            return false;
        }
        ROS_WARN("V4L2: VIDIOC_DQBUF failed: %s", ::strerror(errno));
        return false;
    }

    if (buf.index >= buffers_.size())
    {
        ROS_WARN("V4L2: DQBUF index out of range: %u", buf.index);
        return false;
    }

    frame.index = buf.index;
    frame.data = static_cast<const uint8_t *>(buffers_[buf.index].start);
    frame.bytes_used = buf.bytesused;
    frame.timestamp_us = nowSteadyUs();
    return true;
}

void VideoV4L2Capturer::requeue(uint32_t index)
{
    if (!streaming_ || fd_ < 0)
    {
        return;
    }

    if (index >= buffers_.size())
    {
        return;
    }

    v4l2_buffer buf;
    std::memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = index;

    if (xioctl(fd_, VIDIOC_QBUF, &buf) < 0)
    {
        ROS_WARN("V4L2: VIDIOC_QBUF failed: %s", ::strerror(errno));
    }
}

bool VideoV4L2Capturer::isRunning() const
{
    return streaming_;
}

bool VideoV4L2Capturer::openDevice()
{
    if (config_.device.empty())
    {
        ROS_ERROR("V4L2: device path is empty");
        return false;
    }

    fd_ = ::open(config_.device.c_str(), O_RDWR | O_NONBLOCK, 0);
    if (fd_ < 0)
    {
        ROS_ERROR("V4L2: open(%s) failed: %s", config_.device.c_str(), ::strerror(errno));
        return false;
    }
    return true;
}

bool VideoV4L2Capturer::setFormat()
{
    v4l2_format fmt;
    std::memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = config_.width;
    fmt.fmt.pix.height = config_.height;
    fmt.fmt.pix.pixelformat = toFourcc(config_.pixel_format);
    fmt.fmt.pix.field = V4L2_FIELD_ANY;

    if (xioctl(fd_, VIDIOC_S_FMT, &fmt) < 0)
    {
        ROS_ERROR("V4L2: VIDIOC_S_FMT failed: %s", ::strerror(errno));
        return false;
    }

    config_.width = fmt.fmt.pix.width;
    config_.height = fmt.fmt.pix.height;
    return true;
}

bool VideoV4L2Capturer::setFrameRate()
{
    if (config_.fps == 0)
    {
        return true;
    }

    v4l2_streamparm parm;
    std::memset(&parm, 0, sizeof(parm));
    parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    parm.parm.capture.timeperframe.numerator = 1;
    parm.parm.capture.timeperframe.denominator = config_.fps;

    return xioctl(fd_, VIDIOC_S_PARM, &parm) == 0;
}

bool VideoV4L2Capturer::requestBuffers()
{
    v4l2_requestbuffers req;
    std::memset(&req, 0, sizeof(req));
    req.count = static_cast<uint32_t>(std::max(2, config_.buffer_count));
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (xioctl(fd_, VIDIOC_REQBUFS, &req) < 0)
    {
        ROS_ERROR("V4L2: VIDIOC_REQBUFS failed: %s", ::strerror(errno));
        return false;
    }

    if (req.count == 0)
    {
        ROS_ERROR("V4L2: no buffers available");
        return false;
    }

    buffers_.resize(req.count);
    for (uint32_t i = 0; i < req.count; ++i)
    {
        v4l2_buffer buf;
        std::memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (xioctl(fd_, VIDIOC_QUERYBUF, &buf) < 0)
        {
            ROS_ERROR("V4L2: VIDIOC_QUERYBUF failed: %s", ::strerror(errno));
            return false;
        }

        void *start = ::mmap(nullptr, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, buf.m.offset);
        if (start == MAP_FAILED)
        {
            ROS_ERROR("V4L2: mmap failed: %s", ::strerror(errno));
            return false;
        }

        buffers_[i].start = start;
        buffers_[i].length = buf.length;
    }

    return true;
}

bool VideoV4L2Capturer::queueAllBuffers()
{
    for (uint32_t i = 0; i < buffers_.size(); ++i)
    {
        v4l2_buffer buf;
        std::memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (xioctl(fd_, VIDIOC_QBUF, &buf) < 0)
        {
            ROS_ERROR("V4L2: VIDIOC_QBUF failed: %s", ::strerror(errno));
            return false;
        }
    }
    return true;
}

void VideoV4L2Capturer::unmapBuffers()
{
    for (auto &buf : buffers_)
    {
        if (buf.start != nullptr)
        {
            ::munmap(buf.start, buf.length);
            buf.start = nullptr;
            buf.length = 0;
        }
    }
    buffers_.clear();
}

uint32_t VideoV4L2Capturer::toFourcc(const std::string &format)
{
    if (format == "mjpeg" || format == "mjpg")
    {
        return V4L2_PIX_FMT_MJPEG;
    }
    if (format == "yuyv" || format == "yuy2")
    {
        return V4L2_PIX_FMT_YUYV;
    }

    return V4L2_PIX_FMT_MJPEG;
}

} // namespace trb::video
