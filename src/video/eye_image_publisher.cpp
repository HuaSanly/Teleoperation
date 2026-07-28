#include "video/eye_image_publisher.hpp"

#include <cstring>
#include <chrono>
#include <iostream>

#include <ros/ros.h>

// Jetson Multimedia API headers
#include "nvbufsurface.h"
#include "nvbufsurftransform.h"

namespace trb::video
{

EyeImagePublisher::EyeImagePublisher() = default;

EyeImagePublisher::~EyeImagePublisher()
{
    stop();
    destroyBuffers();
}

void EyeImagePublisher::stop()
{
    if (!initialized_.load())
        return;
    
    initialized_.store(false);
    // Processing is done synchronously by caller (VSM's eye_image_thread)
}

void EyeImagePublisher::destroyBuffers()
{
    for (void* surf : nv12_surfaces_)
    {
        if (surf)
        {
            NvBufSurfaceDestroy(static_cast<NvBufSurface*>(surf));
        }
    }
    nv12_surfaces_.clear();
    nv12_fds_.clear();
    
    rgb_buffers_.clear();
    initialized_.store(false);
}

bool EyeImagePublisher::initialize(ros::NodeHandle& nh, uint32_t src_width, uint32_t src_height, const Config& config)
{
    if (initialized_.load())
    {
        ROS_WARN("EyeImagePublisher already initialized");
        return true;
    }
    
    config_ = config;
    src_width_ = src_width;
    src_height_ = src_height;
    
    if (!config_.enabled)
    {
        ROS_INFO("EyeImagePublisher disabled by config");
        return true;
    }
    
    // Create ROS publishers
    left_pub_ = nh.advertise<sensor_msgs::Image>(config_.left_topic, 1);
    right_pub_ = nh.advertise<sensor_msgs::Image>(config_.right_topic, 1);
    
    // NOTE: No independent decoder - we receive NV12 from shared decoder via queue
    
    // Allocate 2 NV12 buffers (for left and right eye output after crop+scale)
    NvBufSurfaceCreateParams params;
    memset(&params, 0, sizeof(params));
    params.gpuId = 0;
    params.width = config_.output_width;
    params.height = config_.output_height;
    params.layout = NVBUF_LAYOUT_PITCH;
    params.colorFormat = NVBUF_COLOR_FORMAT_NV12;
    params.memType = NVBUF_MEM_SURFACE_ARRAY;
    params.isContiguous = true;
    
    nv12_surfaces_.resize(2, nullptr);
    nv12_fds_.resize(2, -1);
    
    for (int i = 0; i < 2; ++i)
    {
        NvBufSurface* surf = nullptr;
        if (NvBufSurfaceCreate(&surf, 1, &params) != 0)
        {
            ROS_ERROR("EyeImagePublisher: Failed to create NV12 surface %d", i);
            destroyBuffers();
            return false;
        }
        nv12_surfaces_[i] = surf;
        nv12_fds_[i] = surf->surfaceList[0].bufferDesc;
    }
    
    // Allocate RGB buffers (640 * 360 * 3 bytes each)
    const size_t rgb_size = config_.output_width * config_.output_height * 3;
    rgb_buffers_.resize(2);
    rgb_buffers_[0].resize(rgb_size);
    rgb_buffers_[1].resize(rgb_size);
    
    initialized_.store(true);
    
    ROS_INFO("EyeImagePublisher initialized (shared decoder mode): src=%ux%u, out=%ux%u, topics=[%s, %s]",
             src_width_, src_height_,
             config_.output_width, config_.output_height,
             config_.left_topic.c_str(), config_.right_topic.c_str());
    
    return true;
}

void EyeImagePublisher::processFrame(NvBufSurface* src_surface, uint64_t timestamp_us)
{
    if (!initialized_.load() || !config_.enabled || !src_surface)
        return;
    
    // Check if anyone is subscribed - skip if no subscribers
    if (left_pub_.getNumSubscribers() == 0 && right_pub_.getNumSubscribers() == 0)
        return;
    
    const uint64_t n = frame_count_.fetch_add(1);
    const auto t0 = std::chrono::steady_clock::now();
    
    // Process left eye
    if (left_pub_.getNumSubscribers() > 0)
    {
        if (cropScaleToNV12(src_surface, 0, false))
        {
            NvBufSurface* left_nv12 = static_cast<NvBufSurface*>(nv12_surfaces_[0]);
            if (convertNV12ToRGB(left_nv12, rgb_buffers_[0].data(), rgb_buffers_[0].size()))
            {
                publishImage(left_pub_, rgb_buffers_[0].data(), timestamp_us);
            }
        }
    }
    
    // Process right eye
    if (right_pub_.getNumSubscribers() > 0)
    {
        if (cropScaleToNV12(src_surface, 1, true))
        {
            NvBufSurface* right_nv12 = static_cast<NvBufSurface*>(nv12_surfaces_[1]);
            if (convertNV12ToRGB(right_nv12, rgb_buffers_[1].data(), rgb_buffers_[1].size()))
            {
                publishImage(right_pub_, rgb_buffers_[1].data(), timestamp_us);
            }
        }
    }
    
    const auto t1 = std::chrono::steady_clock::now();
    
    // Log performance occasionally
    if (n == 0 || (n % 300 == 0))
    {
        const int64_t total_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        
        ROS_INFO("EyeImagePublisher (shared decoder): frame %lu, process=%.2fms, subs=[L:%u, R:%u]",
                 static_cast<unsigned long>(n),
                 static_cast<double>(total_us) / 1000.0,
                 left_pub_.getNumSubscribers(),
                 right_pub_.getNumSubscribers());
    }
}

bool EyeImagePublisher::cropScaleToNV12(NvBufSurface* src_surf, int dst_idx, bool is_right_eye)
{
    if (dst_idx < 0 || dst_idx >= static_cast<int>(nv12_surfaces_.size()))
        return false;
    
    if (!src_surf)
    {
        ROS_ERROR("EyeImagePublisher: src_surf is null");
        return false;
    }
    
    NvBufSurface* dst_surf = static_cast<NvBufSurface*>(nv12_surfaces_[dst_idx]);
    if (!dst_surf)
        return false;
    
    src_surf->numFilled = 1;
    dst_surf->numFilled = 1;
    
    // Calculate crop region
    // For SBS format: left eye = [0, 0, width/2, height], right eye = [width/2, 0, width/2, height]
    const uint32_t half_width = src_width_ / 2;
    
    NvBufSurfTransformRect src_rect;
    src_rect.top = 0;
    src_rect.left = is_right_eye ? half_width : 0;
    src_rect.width = half_width;
    src_rect.height = src_height_;
    
    NvBufSurfTransformRect dst_rect;
    dst_rect.top = 0;
    dst_rect.left = 0;
    dst_rect.width = config_.output_width;
    dst_rect.height = config_.output_height;
    
    // Setup transform parameters with crop + scale
    NvBufSurfTransformParams tparams;
    memset(&tparams, 0, sizeof(tparams));
    tparams.transform_flag = NVBUFSURF_TRANSFORM_FILTER | NVBUFSURF_TRANSFORM_CROP_SRC | NVBUFSURF_TRANSFORM_CROP_DST;
    tparams.src_rect = &src_rect;
    tparams.dst_rect = &dst_rect;
    tparams.transform_filter = NvBufSurfTransformInter_Bilinear;

    // Hold the VIC mutex (if injected) only across the actual hardware
    // transform call -- not across map/sync/CPU NV12->RGB/publish -- so the
    // encode thread is not blocked by CPU work that does not touch the VIC.
    int ret;
    if (vic_mutex_)
    {
        std::lock_guard<std::mutex> lk(*vic_mutex_);
        ret = NvBufSurfTransform(src_surf, dst_surf, &tparams);
    }
    else
    {
        ret = NvBufSurfTransform(src_surf, dst_surf, &tparams);
    }
    if (ret != 0)
    {
        ROS_ERROR("EyeImagePublisher: NvBufSurfTransform failed ret=%d (is_right=%d)", ret, is_right_eye);
        return false;
    }

    return true;
}

bool EyeImagePublisher::convertNV12ToRGB(NvBufSurface* surf, uint8_t* rgb_out, size_t rgb_size)
{
    if (!surf)
    {
        ROS_ERROR("EyeImagePublisher: convertNV12ToRGB surf is null");
        return false;
    }
    
    // Map ALL planes to CPU (use -1 for plane index)
    if (NvBufSurfaceMap(surf, 0, -1, NVBUF_MAP_READ) != 0)
    {
        ROS_ERROR("EyeImagePublisher: NvBufSurfaceMap failed");
        return false;
    }
    
    // Sync ALL planes for CPU read
    NvBufSurfaceSyncForCpu(surf, 0, -1);
    
    const NvBufSurfaceParams& sp = surf->surfaceList[0];
    const uint8_t* y_plane = static_cast<const uint8_t*>(sp.mappedAddr.addr[0]);
    const uint8_t* uv_plane = static_cast<const uint8_t*>(sp.mappedAddr.addr[1]);
    const uint32_t y_pitch = sp.planeParams.pitch[0];
    const uint32_t uv_pitch = sp.planeParams.pitch[1];
    const uint32_t width = config_.output_width;
    const uint32_t height = config_.output_height;
    
    // NV12 to RGB conversion
    for (uint32_t row = 0; row < height; ++row)
    {
        const uint8_t* y_row = y_plane + row * y_pitch;
        const uint8_t* uv_row = uv_plane + (row / 2) * uv_pitch;
        uint8_t* out_row = rgb_out + row * width * 3;
        
        for (uint32_t col = 0; col < width; ++col)
        {
            const int y = y_row[col];
            const int u = uv_row[(col / 2) * 2] - 128;
            const int v = uv_row[(col / 2) * 2 + 1] - 128;
            
            // YUV to RGB conversion (BT.601)
            int r = y + ((359 * v) >> 8);
            int g = y - ((88 * u + 183 * v) >> 8);
            int b = y + ((454 * u) >> 8);
            
            // Clamp
            out_row[col * 3 + 0] = static_cast<uint8_t>(r < 0 ? 0 : (r > 255 ? 255 : r));
            out_row[col * 3 + 1] = static_cast<uint8_t>(g < 0 ? 0 : (g > 255 ? 255 : g));
            out_row[col * 3 + 2] = static_cast<uint8_t>(b < 0 ? 0 : (b > 255 ? 255 : b));
        }
    }
    
    NvBufSurfaceUnMap(surf, 0, -1);
    
    return true;
}

void EyeImagePublisher::publishImage(ros::Publisher& pub, const uint8_t* rgb_data, uint64_t timestamp_us)
{
    sensor_msgs::Image msg;
    msg.header.stamp.fromNSec(timestamp_us * 1000ULL);
    msg.header.frame_id = config_.frame_id;
    msg.height = config_.output_height;
    msg.width = config_.output_width;
    msg.encoding = "rgb8";
    msg.is_bigendian = false;
    msg.step = config_.output_width * 3;
    
    const size_t data_size = msg.step * msg.height;
    msg.data.assign(rgb_data, rgb_data + data_size);
    
    pub.publish(msg);
}

} // namespace trb::video
