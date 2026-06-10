#include "video/video_converter.hpp"
#include "video/cuda_yuv422_converter.hpp"
#include "video/nvbuf_mutex.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <iostream>

#include "rclcpp/rclcpp.hpp"

#include <linux/videodev2.h>

#include "nvbufsurface.h"
#include "NvBuffer.h"
#include "nvbufsurftransform.h"

#ifndef TRB_HAS_CUDA_CONVERTER
#define TRB_HAS_CUDA_CONVERTER 0
#endif

namespace trb::video
{

namespace
{
const char *computeModeName(int32_t mode)
{
    if (mode == 3)
    {
        return "cuda";
    }
    if (mode == 1)
    {
        return "gpu";
    }
    if (mode == 2)
    {
        return "vic";
    }
    return "default";
}

const char *layoutName(NvBufSurfaceLayout layout)
{
    switch (layout)
    {
    case NVBUF_LAYOUT_PITCH:
        return "pitch";
    case NVBUF_LAYOUT_BLOCK_LINEAR:
        return "block";
    default:
        return "unknown";
    }
}

const char *outputFormatNameFor(VideoConverter::OutputFormat format)
{
    switch (format)
    {
    case VideoConverter::OutputFormat::kYuv420:
        return "yuv420";
    case VideoConverter::OutputFormat::kNv12:
    default:
        return "nv12";
    }
}

NvBufSurfaceColorFormat outputColorFormat(VideoConverter::OutputFormat format)
{
    switch (format)
    {
    case VideoConverter::OutputFormat::kYuv420:
        return NVBUF_COLOR_FORMAT_YUV420;
    case VideoConverter::OutputFormat::kNv12:
    default:
        return NVBUF_COLOR_FORMAT_NV12;
    }
}

const NvBufSurfTransformParams& defaultTransformParams()
{
    static const NvBufSurfTransformParams params = [] {
        NvBufSurfTransformParams value;
        std::memset(&value, 0, sizeof(value));
        value.transform_flag = NVBUFSURF_TRANSFORM_FILTER;
        value.src_rect = nullptr;
        value.dst_rect = nullptr;
        value.transform_filter = NvBufSurfTransformInter_Nearest;
        return value;
    }();
    return params;
}

void logTransformFailureOnce(int ret, int src_fd, uint32_t width, uint32_t height, const char *output_format)
{
    static std::atomic<uint64_t> failure_count{0};
    const uint64_t count = failure_count.fetch_add(1) + 1;
    if (count <= 5 || (count % 300 == 0))
    {
        std::cerr << "VideoConverter: NvBufSurfTransform(decoded-yuv->" << output_format << ") failed ret=" << ret
                  << " src_fd=" << src_fd << " w=" << width << " h=" << height
                  << " failures=" << count << std::endl;
    }
}

void logCudaFailureOnce(const CudaYuv422ConverterResult &result, int src_fd, uint32_t width, uint32_t height)
{
    static std::atomic<uint64_t> failure_count{0};
    const uint64_t count = failure_count.fetch_add(1) + 1;
    if (count <= 5 || (count % 300 == 0))
    {
        std::cerr << "VideoConverter: CUDA YUV422->NV12 failed stage=" << result.error_stage
                  << " err=" << result.error_code
                  << " src_fd=" << src_fd << " w=" << width << " h=" << height
                  << " src_color=" << result.src_color_format
                  << " dst_color=" << result.dst_color_format
                  << " src_planes=" << result.src_plane_count
                  << " dst_planes=" << result.dst_plane_count
                  << " src_frame_type=" << result.src_frame_type
                  << " dst_frame_type=" << result.dst_frame_type
                  << " failures=" << count << std::endl;
    }
}

bool useCudaConverter(const VideoConverter::Config &config)
{
    return config.transform_compute_mode == 3;
}

void logSurfaceDetails(const char *prefix, NvBufSurface *surface)
{
    if (!surface || surface->numFilled == 0)
    {
        std::cerr << prefix << " surface=null" << std::endl;
        return;
    }

    const auto &sp = surface->surfaceList[0];
    const auto &pp = sp.planeParams;
    std::cerr << prefix
              << " fd=" << sp.bufferDesc
              << " size=" << sp.width << "x" << sp.height
              << " pitch_size=" << sp.pitch << "x" << sp.height
              << " layout=" << layoutName(sp.layout)
              << " color=" << static_cast<int>(sp.colorFormat)
              << " planes=" << pp.num_planes;
    for (uint32_t i = 0; i < pp.num_planes; ++i)
    {
        std::cerr << " p" << i
                  << " pitch=" << pp.pitch[i]
                  << " width=" << pp.width[i]
                  << " height=" << pp.height[i]
                  << " psize=" << pp.psize[i]
                  << " offset=" << pp.offset[i];
    }
    std::cerr << std::endl;
}

} // namespace

VideoConverter::VideoConverter() = default;

VideoConverter::~VideoConverter()
{
    destroyBuffers();
}

bool VideoConverter::initialize(const Config &config)
{
    config_ = config;

    {
        NvBufSurfTransformConfigParams transform_config;
        memset(&transform_config, 0, sizeof(transform_config));
        if (config_.transform_compute_mode == 3)
        {
            transform_config.compute_mode = NvBufSurfTransformCompute_Default;
        }
        else if (config_.transform_compute_mode == 1)
        {
            transform_config.compute_mode = NvBufSurfTransformCompute_GPU;
        }
        else if (config_.transform_compute_mode == 2)
        {
            transform_config.compute_mode = NvBufSurfTransformCompute_VIC;
        }
        else
        {
            transform_config.compute_mode = NvBufSurfTransformCompute_Default;
        }
        transform_config.gpu_id = 0;
        transform_config.cuda_stream = 0;
        const int sret = NvBufSurfTransformSetSessionParams(&transform_config);
        if (sret != 0)
        {
            std::cerr << "VideoConverter: NvBufSurfTransformSetSessionParams failed ret=" << sret
                      << " (compute_mode="
                      << computeModeName(config_.transform_compute_mode)
                      << ")" << std::endl;
        }

    }

    NvBufSurfaceCreateParams out_params;
    memset(&out_params, 0, sizeof(out_params));
    out_params.gpuId = 0;
    out_params.width = config_.width;
    out_params.height = config_.height;
    out_params.layout = (config_.output_surface_layout == 1) ? NVBUF_LAYOUT_BLOCK_LINEAR : NVBUF_LAYOUT_PITCH;
    out_params.colorFormat = outputColorFormat(config_.output_format);
    out_params.memType = NVBUF_MEM_SURFACE_ARRAY;
    out_params.isContiguous = true;

    RCLCPP_INFO(rclcpp::get_logger("teleop_robot_bridge.video"),
                "VideoConverter: output_format=%s compute=%s in=%ux%u out=%ux%u out_layout=%s pool=%u",
                outputFormatNameFor(config_.output_format),
                computeModeName(config_.transform_compute_mode),
                config_.input_width ? config_.input_width : config_.width,
                config_.input_height ? config_.input_height : config_.height,
                config_.width,
                config_.height,
                config_.output_surface_layout == 1 ? "block" : "pitch",
                config_.buffer_pool_size);

    if (useCudaConverter(config_) &&
        (config_.decode_surface_layout != 0 ||
         config_.output_format != VideoConverter::OutputFormat::kNv12 ||
         config_.output_surface_layout != 0))
    {
        RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                    "VideoConverter: CUDA prototype supports pitch-linear YUV422 input and pitch-linear NV12 output only; current dec_layout=%s output_format=%s out_layout=%s",
                    config_.decode_surface_layout == 1 ? "block" : "pitch",
                    outputFormatNameFor(config_.output_format),
                    config_.output_surface_layout == 1 ? "block" : "pitch");
    }

    if (useCudaConverter(config_) && !TRB_HAS_CUDA_CONVERTER)
    {
        RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                    "VideoConverter: compute=cuda requested, but CUDA converter was not built");
    }

    surfaces_.resize(config_.buffer_pool_size, nullptr);
    dmabuf_fds_.assign(config_.buffer_pool_size, -1);

    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        while (!free_indices_.empty())
            free_indices_.pop();
        fd_to_index_.clear();
    }

    for (size_t i = 0; i < config_.buffer_pool_size; ++i)
    {
        NvBufSurface *surf = nullptr;
        if (NvBufSurfaceCreate(&surf, 1, &out_params) != 0)
        {
            std::cerr << "Failed to create NvBufSurface " << i << std::endl;
            return false;
        }
        surfaces_[i] = surf;
        dmabuf_fds_[i] = surf->surfaceList[0].bufferDesc;

        std::lock_guard<std::mutex> lk(pool_mutex_);
        free_indices_.push(i);
        fd_to_index_.emplace(dmabuf_fds_[i], i);
    }

#if TRB_HAS_CUDA_CONVERTER
    if (useCudaConverter(config_))
    {
        cuda_converter_ = std::make_unique<CudaYuv422Converter>();
        for (void *surface : surfaces_)
        {
            auto *dst = reinterpret_cast<NvBufSurface *>(surface);
            if (dst)
            {
                dst->numFilled = 1;
                CudaYuv422ConverterResult cuda_result;
                if (!cuda_converter_->prepareOutput(dst, &cuda_result))
                {
                    logCudaFailureOnce(cuda_result, dst->surfaceList[0].bufferDesc, config_.width, config_.height);
                    RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                                "VideoConverter: failed to prepare CUDA output pool; falling back will not be automatic");
                    return false;
                }
            }
        }
        RCLCPP_INFO(rclcpp::get_logger("teleop_robot_bridge.video"),
                    "VideoConverter: CUDA output pool prepared with %zu cached EGL frame(s)",
                    surfaces_.size());
    }
#endif

    logged_mode_.store(true, std::memory_order_relaxed);

    return true;
}

void VideoConverter::destroyBuffers()
{
    if (cuda_converter_)
    {
        cuda_converter_->reset();
        cuda_converter_.reset();
    }

    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        while (!free_indices_.empty())
            free_indices_.pop();
        fd_to_index_.clear();
    }

    for (void *surf : surfaces_)
    {
        if (surf)
        {
            NvBufSurfaceDestroy(reinterpret_cast<NvBufSurface *>(surf));
        }
    }

    surfaces_.clear();
    dmabuf_fds_.clear();
}

void VideoConverter::releaseFd(int dmabuf_fd)
{
    std::lock_guard<std::mutex> lk(pool_mutex_);
    auto it = fd_to_index_.find(dmabuf_fd);
    if (it != fd_to_index_.end())
    {
        free_indices_.push(it->second);
    }
}

VideoConverter::StatsSnapshot VideoConverter::consumeStats()
{
    StatsSnapshot snapshot;
    snapshot.processed_frames = stats_processed_frames_.exchange(0);
    snapshot.malformed_frames = stats_malformed_frames_.exchange(0);
    snapshot.pool_drops = stats_pool_drops_.exchange(0);
    snapshot.failed_frames = stats_failed_frames_.exchange(0);
    snapshot.decode_us_total = stats_decode_us_total_.exchange(0);
    snapshot.transform_us_total = stats_transform_us_total_.exchange(0);
    snapshot.map_us_total = stats_map_us_total_.exchange(0);
    snapshot.transform_wait_us_total = stats_transform_wait_us_total_.exchange(0);
    snapshot.transform_call_us_total = stats_transform_call_us_total_.exchange(0);
    return snapshot;
}

const char *VideoConverter::outputFormatName() const
{
    return outputFormatNameFor(config_.output_format);
}

bool VideoConverter::transformSync(int yuv_dmabuf_fd,
                                   uint64_t timestamp_us,
                                   uint64_t decode_us,
                                   int &output_fd_out)
{
    (void)timestamp_us;
    output_fd_out = -1;

    if (yuv_dmabuf_fd < 0 || dmabuf_fds_.empty())
    {
        return false;
    }

    if (decode_us > 0)
    {
        stats_decode_us_total_.fetch_add(static_cast<int64_t>(decode_us));
    }

    size_t out_idx = 0;
    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        if (free_indices_.empty())
        {
            const uint64_t d = stats_pool_drops_.fetch_add(1) + 1;
            if (d <= 5 || (d % 300 == 0))
            {
                std::cerr << "VideoConverter: buffer pool empty, dropping frame (drops=" << d
                          << ", pool_size=" << dmabuf_fds_.size() << ")" << std::endl;
            }
            return false;
        }
        out_idx = free_indices_.front();
        free_indices_.pop();
    }

    const int out_fd = dmabuf_fds_[out_idx];

    NvBufSurface *src_surf = nullptr;
    auto map_wait_start = std::chrono::steady_clock::now();
    auto map_lock_start = map_wait_start;
    auto map_end = map_wait_start;
    {
        std::lock_guard<std::mutex> lk(getNvBufMutex());
        map_lock_start = std::chrono::steady_clock::now();
        if (NvBufSurfaceFromFd(yuv_dmabuf_fd, reinterpret_cast<void **>(&src_surf)) != 0 || !src_surf)
        {
            map_end = std::chrono::steady_clock::now();
            stats_map_us_total_.fetch_add(
                std::chrono::duration_cast<std::chrono::microseconds>(map_end - map_wait_start).count());
            std::cerr << "VideoConverter: NvBufSurfaceFromFd failed for decoded fd=" << yuv_dmabuf_fd << std::endl;
            stats_failed_frames_.fetch_add(1);
            std::lock_guard<std::mutex> pool_lk(pool_mutex_);
            free_indices_.push(out_idx);
            return false;
        }
        map_end = std::chrono::steady_clock::now();
    }
    stats_map_us_total_.fetch_add(
        std::chrono::duration_cast<std::chrono::microseconds>(map_end - map_wait_start).count());

    const auto &src_sp = src_surf->surfaceList[0];
    const uint32_t width  = src_sp.width;
    const uint32_t height = src_sp.height;

    static std::atomic<bool> warned_dimension_mismatch{false};
    const uint32_t requested_width  = (config_.input_width  > 0) ? config_.input_width  : config_.width;
    const uint32_t requested_height = (config_.input_height > 0) ? config_.input_height : config_.height;
    if ((width != requested_width || height != requested_height) &&
        !warned_dimension_mismatch.exchange(true))
    {
        RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"), 
            "VideoConverter: decoded surface dimensions differ from requested input: requested=%ux%u actual=%ux%u",
            requested_width, requested_height, width, height);
    }

    NvBufSurface *dst = reinterpret_cast<NvBufSurface *>(surfaces_[out_idx]);
    if (!dst)
    {
        stats_failed_frames_.fetch_add(1);
        std::lock_guard<std::mutex> lk(pool_mutex_);
        free_indices_.push(out_idx);
        return false;
    }

    src_surf->numFilled = 1;
    dst->numFilled = 1;

    if (!logged_surface_details_.exchange(true, std::memory_order_relaxed))
    {
        logSurfaceDetails("VideoConverter source surface:", src_surf);
        logSurfaceDetails("VideoConverter output surface:", dst);
        const auto map_wait_us =
            std::chrono::duration_cast<std::chrono::microseconds>(map_lock_start - map_wait_start).count();
        const auto map_call_us =
            std::chrono::duration_cast<std::chrono::microseconds>(map_end - map_lock_start).count();
        RCLCPP_INFO(rclcpp::get_logger("teleop_robot_bridge.video"),
                    "VideoConverter: first map wait=%ldus call=%ldus output_format=%s",
                    static_cast<long>(map_wait_us),
                    static_cast<long>(map_call_us),
                    outputFormatNameFor(config_.output_format));
    }

    const auto wait_start = std::chrono::steady_clock::now();
    int tret = 0;
    std::chrono::steady_clock::time_point call_start;
    CudaYuv422ConverterResult cuda_result;
    if (useCudaConverter(config_))
    {
        call_start = std::chrono::steady_clock::now();
#if TRB_HAS_CUDA_CONVERTER
        if (cuda_converter_)
        {
            tret = cuda_converter_->convert(src_surf, dst, &cuda_result) ? 0 : -1;
        }
        else
        {
            cuda_result.error_stage = "cuda-converter-not-initialized";
            cuda_result.error_code = -101;
            tret = -1;
        }
#else
        cuda_result.error_stage = "cuda-not-built";
        cuda_result.error_code = -100;
        tret = -1;
#endif
    }
    else
    {
        std::lock_guard<std::mutex> lk(getNvBufMutex());
        call_start = std::chrono::steady_clock::now();
        NvBufSurfTransformParams tparams = defaultTransformParams();
        tret = NvBufSurfTransform(src_surf, dst, &tparams);
    }
    const auto call_end = std::chrono::steady_clock::now();
    const auto wait_us = std::chrono::duration_cast<std::chrono::microseconds>(call_start - wait_start).count();
    const auto call_us = std::chrono::duration_cast<std::chrono::microseconds>(call_end - call_start).count();
    stats_transform_wait_us_total_.fetch_add(wait_us);
    stats_transform_call_us_total_.fetch_add(call_us);
    stats_transform_us_total_.fetch_add(wait_us + call_us);

    if (tret != 0)
    {
        if (useCudaConverter(config_))
        {
            logCudaFailureOnce(cuda_result, yuv_dmabuf_fd, width, height);
        }
        else
        {
            logTransformFailureOnce(tret, yuv_dmabuf_fd, width, height, outputFormatNameFor(config_.output_format));
        }
        stats_failed_frames_.fetch_add(1);
        std::lock_guard<std::mutex> lk(pool_mutex_);
        free_indices_.push(out_idx);
        return false;
    }

    stats_processed_frames_.fetch_add(1);
    output_fd_out = out_fd;
    return true;
}

} // namespace trb::video
