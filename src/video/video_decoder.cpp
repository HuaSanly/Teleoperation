#include "video/video_decoder.hpp"

#include <algorithm>
#include <cstring>
#include <fcntl.h>

#include <linux/videodev2.h>

#include <ros/ros.h>

#include "NvBuffer.h"
#include "NvVideoDecoder.h"

namespace trb::video
{

namespace
{
uint32_t safePoolSize(uint32_t v)
{
    return std::max<uint32_t>(2, v);
}

std::string fourccToString(uint32_t fourcc)
{
    char s[5] = {
        static_cast<char>(fourcc & 0xFF),
        static_cast<char>((fourcc >> 8) & 0xFF),
        static_cast<char>((fourcc >> 16) & 0xFF),
        static_cast<char>((fourcc >> 24) & 0xFF),
        0};
    return std::string(s);
}
} // namespace

VideoDecoder::VideoDecoder(VideoDecoderConfig config)
    : config_(std::move(config))
{
}

VideoDecoder::~VideoDecoder()
{
    stop();
}

bool VideoDecoder::start()
{
    if (running_)
    {
        return true;
    }

    auto *dec = NvVideoDecoder::createVideoDecoder("video_decoder", O_NONBLOCK);
    if (!dec)
    {
        ROS_ERROR("VideoDecoder: failed to create NvVideoDecoder");
        return false;
    }

    decoder_ = dec;

    if (!configureDecoder())
    {
        destroyDecoder();
        return false;
    }

    running_ = true;
    return true;
}

void VideoDecoder::stop()
{
    if (!running_)
    {
        return;
    }

    destroyDecoder();
    running_ = false;
}

bool VideoDecoder::decode(const uint8_t *data, size_t size, uint64_t timestamp_us, DecodedFrame &out)
{
    out = DecodedFrame{};

    if (!running_ || !decoder_ || !data || size == 0)
    {
        return false;
    }

    auto *dec = static_cast<NvVideoDecoder *>(decoder_);

    reclaimOutputBuffers();
    if (free_output_indices_.empty())
    {
        ROS_WARN_THROTTLE(2.0, "VideoDecoder output buffers exhausted");
        return false;
    }

    const uint32_t out_index = free_output_indices_.back();
    free_output_indices_.pop_back();

    NvBuffer *out_buf = dec->output_plane.getNthBuffer(out_index);
    if (!out_buf || out_buf->planes[0].data == nullptr)
    {
        free_output_indices_.push_back(out_index);
        return false;
    }

    const size_t copy_bytes = std::min<size_t>(size, out_buf->planes[0].length);
    std::memcpy(out_buf->planes[0].data, data, copy_bytes);
    out_buf->planes[0].bytesused = static_cast<uint32_t>(copy_bytes);

    v4l2_buffer v4l2_out;
    v4l2_plane out_planes[MAX_PLANES];
    std::memset(&v4l2_out, 0, sizeof(v4l2_out));
    std::memset(out_planes, 0, sizeof(out_planes));
    v4l2_out.index = out_index;
    v4l2_out.m.planes = out_planes;
    v4l2_out.m.planes[0].bytesused = out_buf->planes[0].bytesused;

    if (dec->output_plane.qBuffer(v4l2_out, nullptr) < 0)
    {
        free_output_indices_.push_back(out_index);
        return false;
    }

    reclaimOutputBuffers();

    if (!capture_configured_)
    {
        v4l2_event ev;
        std::memset(&ev, 0, sizeof(ev));
        if (dec->dqEvent(ev, 0) == 0 && ev.type == V4L2_EVENT_RESOLUTION_CHANGE)
        {
            v4l2_format fmt;
            std::memset(&fmt, 0, sizeof(fmt));
            if (dec->capture_plane.getFormat(fmt) < 0)
            {
                return false;
            }

            ROS_INFO("VideoDecoder capture format: %ux%u fourcc=%s planes=%u",
                     fmt.fmt.pix_mp.width,
                     fmt.fmt.pix_mp.height,
                     fourccToString(fmt.fmt.pix_mp.pixelformat).c_str(),
                     fmt.fmt.pix_mp.num_planes);

            const uint32_t cap_w = fmt.fmt.pix_mp.width;
            const uint32_t cap_h = fmt.fmt.pix_mp.height;
            if (dec->setCapturePlaneFormat(V4L2_PIX_FMT_NV12M, cap_w, cap_h) < 0)
            {
                return false;
            }

            int min_bufs = 0;
            if (dec->getMinimumCapturePlaneBuffers(min_bufs) < 0)
            {
                min_bufs = 0;
            }
            const uint32_t cap_bufs = std::max<uint32_t>(safePoolSize(config_.pool_size), static_cast<uint32_t>(std::max(0, min_bufs)));

            if (dec->capture_plane.setupPlane(V4L2_MEMORY_MMAP, cap_bufs, true, false) < 0)
            {
                return false;
            }

            if (dec->capture_plane.setStreamStatus(true) < 0)
            {
                return false;
            }

            capture_fd_by_index_.assign(dec->capture_plane.getNumBuffers(), -1);
            for (uint32_t i = 0; i < dec->capture_plane.getNumBuffers(); ++i)
            {
                NvBuffer *buf = dec->capture_plane.getNthBuffer(i);
                if (buf && buf->planes[0].fd >= 0)
                {
                    capture_fd_by_index_[i] = buf->planes[0].fd;
                }

                v4l2_buffer v4l2_cap;
                v4l2_plane cap_planes[MAX_PLANES];
                std::memset(&v4l2_cap, 0, sizeof(v4l2_cap));
                std::memset(cap_planes, 0, sizeof(cap_planes));
                v4l2_cap.index = i;
                v4l2_cap.m.planes = cap_planes;
                if (dec->capture_plane.qBuffer(v4l2_cap, nullptr) < 0)
                {
                    return false;
                }
            }

            capture_configured_ = true;
        }
    }

    if (!capture_configured_)
    {
        return false;
    }

    v4l2_buffer v4l2_cap;
    v4l2_plane cap_planes[MAX_PLANES];
    std::memset(&v4l2_cap, 0, sizeof(v4l2_cap));
    std::memset(cap_planes, 0, sizeof(cap_planes));
    v4l2_cap.m.planes = cap_planes;

    NvBuffer *cap_buf = nullptr;
    if (dec->capture_plane.dqBuffer(v4l2_cap, &cap_buf, nullptr, 10) < 0)
    {
        return false;
    }

    const uint32_t cap_index = v4l2_cap.index;
    if (cap_index >= capture_fd_by_index_.size())
    {
        dec->capture_plane.qBuffer(v4l2_cap, nullptr);
        return false;
    }

    const int fd = capture_fd_by_index_[cap_index];
    if (fd < 0)
    {
        dec->capture_plane.qBuffer(v4l2_cap, nullptr);
        return false;
    }

    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        fd_to_capture_index_[fd] = cap_index;
        in_use_fds_.insert(fd);
    }

    out.fd = fd;
    out.width = config_.width;
    out.height = config_.height;
    out.timestamp_us = timestamp_us;
    return true;
}

void VideoDecoder::releaseFd(int fd)
{
    if (fd < 0)
    {
        return;
    }

    auto *dec = static_cast<NvVideoDecoder *>(decoder_);
    if (!dec)
    {
        return;
    }

    uint32_t cap_index = 0;
    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        auto it = fd_to_capture_index_.find(fd);
        if (it == fd_to_capture_index_.end())
        {
            return;
        }
        cap_index = it->second;
        fd_to_capture_index_.erase(it);
        in_use_fds_.erase(fd);
    }

    v4l2_buffer v4l2_cap;
    v4l2_plane cap_planes[MAX_PLANES];
    std::memset(&v4l2_cap, 0, sizeof(v4l2_cap));
    std::memset(cap_planes, 0, sizeof(cap_planes));
    v4l2_cap.index = cap_index;
    v4l2_cap.m.planes = cap_planes;
    dec->capture_plane.qBuffer(v4l2_cap, nullptr);
}

bool VideoDecoder::isRunning() const
{
    return running_;
}

bool VideoDecoder::configureDecoder()
{
    auto *dec = static_cast<NvVideoDecoder *>(decoder_);
    if (!dec)
    {
        return false;
    }

    if (config_.width == 0 || config_.height == 0)
    {
        ROS_ERROR("VideoDecoder: invalid width/height");
        return false;
    }

    if (dec->subscribeEvent(V4L2_EVENT_RESOLUTION_CHANGE, 0, 0) < 0)
    {
        ROS_ERROR("VideoDecoder: subscribeEvent failed");
        return false;
    }

    const uint32_t max_input = config_.width * config_.height * 2;
    if (dec->setOutputPlaneFormat(V4L2_PIX_FMT_MJPEG, max_input) < 0)
    {
        ROS_ERROR("VideoDecoder: setOutputPlaneFormat MJPEG failed");
        return false;
    }

    dec->setFrameInputMode(1);

    if (config_.max_perf_mode)
    {
        dec->setMaxPerfMode(1);
    }

    const uint32_t out_bufs = safePoolSize(config_.pool_size);
    if (dec->output_plane.setupPlane(V4L2_MEMORY_MMAP, out_bufs, true, false) < 0)
    {
        ROS_ERROR("VideoDecoder: output_plane setup failed");
        return false;
    }

    if (dec->output_plane.setStreamStatus(true) < 0)
    {
        ROS_ERROR("VideoDecoder: stream on failed");
        return false;
    }

    free_output_indices_.clear();
    for (uint32_t i = 0; i < dec->output_plane.getNumBuffers(); ++i)
    {
        free_output_indices_.push_back(i);
    }

    capture_configured_ = false;
    return true;
}

void VideoDecoder::destroyDecoder()
{
    auto *dec = static_cast<NvVideoDecoder *>(decoder_);
    if (dec)
    {
        dec->output_plane.setStreamStatus(false);
        dec->capture_plane.setStreamStatus(false);
        delete dec;
    }

    decoder_ = nullptr;

    std::lock_guard<std::mutex> lk(pool_mutex_);
    free_output_indices_.clear();
    capture_fd_by_index_.clear();
    fd_to_capture_index_.clear();
    in_use_fds_.clear();
    capture_configured_ = false;
}

bool VideoDecoder::reclaimOutputBuffers()
{
    auto *dec = static_cast<NvVideoDecoder *>(decoder_);
    if (!dec)
    {
        return false;
    }

    bool reclaimed = false;
    while (true)
    {
        v4l2_buffer v4l2_out;
        v4l2_plane out_planes[MAX_PLANES];
        std::memset(&v4l2_out, 0, sizeof(v4l2_out));
        std::memset(out_planes, 0, sizeof(out_planes));
        v4l2_out.m.planes = out_planes;

        NvBuffer *buffer = nullptr;
        const int ret = dec->output_plane.dqBuffer(v4l2_out, &buffer, nullptr, 0);
        if (ret < 0)
        {
            break;
        }

        free_output_indices_.push_back(v4l2_out.index);
        reclaimed = true;
    }

    return reclaimed;
}

uint32_t VideoDecoder::clampBufferCount(uint32_t v) const
{
    return safePoolSize(v);
}

} // namespace trb::video
