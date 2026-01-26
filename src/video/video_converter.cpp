#include "video/video_converter.hpp"

#include <algorithm>

#include <ros/ros.h>

namespace trb::video
{

VideoConverter::VideoConverter(VideoConverterConfig config)
    : config_(std::move(config))
{
}

VideoConverter::~VideoConverter()
{
    stop();
}

bool VideoConverter::start()
{
    if (running_)
    {
        return true;
    }

    if (config_.width == 0 || config_.height == 0)
    {
        ROS_ERROR("VideoConverter: invalid width/height");
        return false;
    }

    const uint32_t count = std::max<uint32_t>(2, config_.buffer_count);
    fds_.assign(count, -1);

    NvBufSurf::NvCommonAllocateParams alloc_params{};
    alloc_params.width = config_.width;
    alloc_params.height = config_.height;
    alloc_params.colorFormat = config_.out_color_format;
    alloc_params.layout = config_.out_layout;
    alloc_params.memType = config_.out_mem_type;
    alloc_params.memtag = config_.out_mem_tag;

    if (NvBufSurf::NvAllocate(&alloc_params, count, fds_.data()) != 0)
    {
        ROS_ERROR("VideoConverter: NvAllocate failed");
        fds_.clear();
        return false;
    }

    free_fds_.clear();
    for (const int fd : fds_)
    {
        if (fd >= 0)
        {
            free_fds_.push_back(fd);
        }
    }

    transform_params_.src_width = config_.width;
    transform_params_.src_height = config_.height;
    transform_params_.src_top = 0;
    transform_params_.src_left = 0;
    transform_params_.dst_width = config_.width;
    transform_params_.dst_height = config_.height;
    transform_params_.dst_top = 0;
    transform_params_.dst_left = 0;
    transform_params_.flag = static_cast<NvBufSurfTransform_Transform_Flag>(
        NVBUFSURF_TRANSFORM_CROP_SRC | NVBUFSURF_TRANSFORM_CROP_DST | NVBUFSURF_TRANSFORM_FILTER);
    transform_params_.flip = NvBufSurfTransform_None;
    transform_params_.filter = NvBufSurfTransformInter_Nearest;

    running_ = true;
    return true;
}

void VideoConverter::stop()
{
    if (!running_)
    {
        return;
    }

    for (const int fd : fds_)
    {
        if (fd >= 0)
        {
            NvBufSurf::NvDestroy(fd);
        }
    }

    fds_.clear();
    free_fds_.clear();
    running_ = false;
}

bool VideoConverter::convert(int src_fd, uint64_t timestamp_us, ConvertedFrame &out)
{
    out = ConvertedFrame{};

    if (!running_ || src_fd < 0)
    {
        return false;
    }

    int dst_fd = -1;
    {
        std::lock_guard<std::mutex> lk(mutex_);
        if (free_fds_.empty())
        {
            ROS_WARN_THROTTLE(2.0, "VideoConverter output buffers exhausted");
            return false;
        }
        dst_fd = free_fds_.back();
        free_fds_.pop_back();
    }

    if (NvBufSurf::NvTransform(&transform_params_, src_fd, dst_fd) != 0)
    {
        ROS_WARN_THROTTLE(2.0, "VideoConverter transform failed");
        std::lock_guard<std::mutex> lk(mutex_);
        free_fds_.push_back(dst_fd);
        return false;
    }

    out.fd = dst_fd;
    out.timestamp_us = timestamp_us;
    return true;
}

void VideoConverter::releaseFd(int fd)
{
    if (!running_ || fd < 0)
    {
        return;
    }

    std::lock_guard<std::mutex> lk(mutex_);
    free_fds_.push_back(fd);
}

bool VideoConverter::isRunning() const
{
    return running_;
}

} // namespace trb::video
