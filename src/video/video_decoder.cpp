#include "video/video_decoder.hpp"

#include <algorithm>

#include <ros/ros.h>

#include "NvBufSurface.h"
#include "NvJpegDecoder.h"

namespace trb::video
{

namespace
{
NvBufSurfaceLayout layoutFromString(const std::string &layout)
{
    if (layout == "block")
    {
        return NVBUF_LAYOUT_BLOCK_LINEAR;
    }
    return NVBUF_LAYOUT_PITCH;
}

uint32_t safePoolSize(uint32_t v)
{
    return std::max<uint32_t>(2, v);
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

    auto *dec = NvJPEGDecoder::createJPEGDecoder("video_decoder");
    if (!dec)
    {
        ROS_ERROR("VideoDecoder: failed to create NvJPEGDecoder");
        return false;
    }

    decoder_ = dec;
    running_ = true;

    if (config_.width > 0 && config_.height > 0)
    {
        ensureOutputPool(config_.width, config_.height);
    }

    return true;
}

void VideoDecoder::stop()
{
    if (!running_)
    {
        return;
    }

    destroyPool();

    if (decoder_)
    {
        delete static_cast<NvJPEGDecoder *>(decoder_);
        decoder_ = nullptr;
    }

    running_ = false;
}

bool VideoDecoder::decode(const uint8_t *data, size_t size, uint64_t timestamp_us, DecodedFrame &out)
{
    out = DecodedFrame{};

    if (!running_ || !decoder_ || !data || size == 0)
    {
        return false;
    }

    int src_fd = -1;
    uint32_t pixfmt = 0;
    uint32_t width = 0;
    uint32_t height = 0;

    auto *dec = static_cast<NvJPEGDecoder *>(decoder_);
    if (dec->decodeToFd(src_fd, const_cast<unsigned char *>(data), size, pixfmt, width, height) < 0)
    {
        ROS_WARN("VideoDecoder: decodeToFd failed");
        return false;
    }
    (void)pixfmt;

    if (!ensureOutputPool(width, height))
    {
        return false;
    }

    const int dst_fd = acquireOutputFd();
    if (dst_fd < 0)
    {
        return false;
    }

    NvBufSurf::NvCommonTransformParams params;
    params.src_top = 0;
    params.src_left = 0;
    params.src_width = width;
    params.src_height = height;
    params.dst_top = 0;
    params.dst_left = 0;
    params.dst_width = width;
    params.dst_height = height;
    params.flag = NVBUFSURF_TRANSFORM_FILTER;
    params.flip = NvBufSurfTransform_None;
    params.filter = NvBufSurfTransformInter_Nearest;

    if (NvBufSurf::NvTransform(&params, src_fd, dst_fd) != 0)
    {
        ROS_WARN("VideoDecoder: NvTransform failed");
        releaseFd(dst_fd);
        return false;
    }

    out.fd = dst_fd;
    out.width = width;
    out.height = height;
    out.timestamp_us = timestamp_us;
    return true;
}

void VideoDecoder::releaseFd(int fd)
{
    if (fd < 0)
    {
        return;
    }

    std::lock_guard<std::mutex> lk(pool_mutex_);
    auto it = in_use_.find(fd);
    if (it != in_use_.end())
    {
        in_use_.erase(it);
        free_fds_.push_back(fd);
    }
}

bool VideoDecoder::isRunning() const
{
    return running_;
}

bool VideoDecoder::ensureOutputPool(uint32_t width, uint32_t height)
{
    if (width == 0 || height == 0)
    {
        return false;
    }

    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        if ((pool_width_ == width && pool_height_ == height) && (!free_fds_.empty() || !in_use_.empty()))
        {
            return true;
        }
    }

    destroyPool();

    NvBufSurf::NvCommonAllocateParams params;
    params.memType = NVBUF_MEM_SURFACE_ARRAY;
    params.width = width;
    params.height = height;
    params.layout = layoutFromString(config_.out_layout);
    params.colorFormat = NVBUF_COLOR_FORMAT_NV12;
    params.memtag = NvBufSurfaceTag_VIDEO_CONVERT;

    const uint32_t count = safePoolSize(config_.pool_size);
    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        free_fds_.reserve(count);
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        int fd = -1;
        if (NvBufSurf::NvAllocate(&params, 1, &fd) != 0 || fd < 0)
        {
            ROS_ERROR("VideoDecoder: NvAllocate failed at index %u", i);
            break;
        }
        std::lock_guard<std::mutex> lk(pool_mutex_);
        free_fds_.push_back(fd);
    }

    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        pool_width_ = width;
        pool_height_ = height;
        return !free_fds_.empty();
    }
}

void VideoDecoder::destroyPool()
{
    std::lock_guard<std::mutex> lk(pool_mutex_);

    for (int fd : free_fds_)
    {
        NvBufSurf::NvDestroy(fd);
    }
    for (int fd : in_use_)
    {
        NvBufSurf::NvDestroy(fd);
    }

    free_fds_.clear();
    in_use_.clear();
    pool_width_ = 0;
    pool_height_ = 0;
}

int VideoDecoder::acquireOutputFd()
{
    std::lock_guard<std::mutex> lk(pool_mutex_);
    if (free_fds_.empty())
    {
        return -1;
    }

    const int fd = free_fds_.back();
    free_fds_.pop_back();
    in_use_.insert(fd);
    return fd;
}

} // namespace trb::video
