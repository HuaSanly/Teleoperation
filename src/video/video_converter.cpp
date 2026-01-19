#include "video/video_converter.hpp"
#include <cstring>
#include <unordered_map>
#include <atomic>
#include <algorithm>
#include <chrono>
#include <cinttypes>

#include "rclcpp/rclcpp.hpp"

#include <linux/videodev2.h>

// Jetson Multimedia API headers
// Ensure these are available in your include path (e.g. /usr/src/jetson_multimedia_api/include)
#include "NvJpegDecoder.h"
#include "nvbufsurface.h"
#include "NvBuffer.h"
#include "nvbufsurftransform.h"

namespace trb::video
{

    namespace
    {
        inline rclcpp::Logger conv_logger()
        {
            return rclcpp::get_logger("teleop_robot_bridge.video.converter");
        }
    }

    VideoConverter::VideoConverter() = default;

    VideoConverter::~VideoConverter()
    {
        destroyBuffers();
    }

    bool VideoConverter::initialize(const Config &config)
    {
        RCLCPP_INFO(conv_logger(), "VideoConverter: init v2");
        config_ = config;

        jpeg_decoder_.reset(NvJPEGDecoder::createJPEGDecoder("jpegdec"));
        if (!jpeg_decoder_)
        {
            std::cerr << "Failed to create NvJPEGDecoder" << std::endl;
            return false;
        }

        // Match decoder output memory type to our pre-allocated buffers.
        jpeg_decoder_->setMemType(NVBUF_MEM_SURFACE_ARRAY);

        // We are providing external buffers (NvBufSurface)
        jpeg_decoder_->setUseExternalBuffer(true);

        // Configure transform session (used for YUV422 -> NV12).
        {
            NvBufSurfTransformConfigParams transform_config;
            memset(&transform_config, 0, sizeof(transform_config));
            if (config_.transform_compute_mode == 1)
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
                          << ((config_.transform_compute_mode == 1) ? "GPU" : (config_.transform_compute_mode == 2) ? "VIC"
                                                                                                                    : "DEFAULT")
                          << ")" << std::endl;
            }

            RCLCPP_INFO(
                conv_logger(),
                "VideoConverter: transform compute=%s, dec_layout=%s, out_layout=%s",
                ((config_.transform_compute_mode == 1) ? "GPU" : (config_.transform_compute_mode == 2) ? "VIC"
                                                                                                       : "DEFAULT"),
                ((config_.decode_surface_layout == 1) ? "BLOCK_LINEAR" : "PITCH"),
                ((config_.output_surface_layout == 1) ? "BLOCK_LINEAR" : "PITCH"));
        }

        // Allocate output NvBufSurface pool (NV12) for NVENC input.
        NvBufSurfaceCreateParams out_params;
        memset(&out_params, 0, sizeof(out_params));
        out_params.gpuId = 0;
        out_params.width = config_.width;
        out_params.height = config_.height;
        out_params.layout = (config_.output_surface_layout == 1) ? NVBUF_LAYOUT_BLOCK_LINEAR : NVBUF_LAYOUT_PITCH;
        out_params.colorFormat = NVBUF_COLOR_FORMAT_NV12;
        out_params.memType = NVBUF_MEM_SURFACE_ARRAY;
        out_params.isContiguous = true;

        surfaces_.resize(config_.buffer_pool_size, nullptr);
        dmabuf_fds_.assign(config_.buffer_pool_size, -1);

        // Allocate decode NvBufSurface pool (YUV422) to ensure decoder uses external buffers.
        const uint32_t decode_pool_size = std::max<uint32_t>(1u, std::min<uint32_t>(config_.buffer_pool_size, 4u));
        NvBufSurfaceCreateParams dec_params;
        memset(&dec_params, 0, sizeof(dec_params));
        dec_params.gpuId = 0;
        dec_params.width = config_.width;
        dec_params.height = config_.height;
        // If decode_surface_layout is not set by caller, fall back to legacy surface_layout.
        const int32_t dec_layout = (config_.decode_surface_layout == 1) ? 1 : ((config_.surface_layout == 1) ? 1 : 0);
        dec_params.layout = (dec_layout == 1) ? NVBUF_LAYOUT_BLOCK_LINEAR : NVBUF_LAYOUT_PITCH;
        dec_params.colorFormat = NVBUF_COLOR_FORMAT_YUV422;
        dec_params.memType = NVBUF_MEM_SURFACE_ARRAY;
        dec_params.isContiguous = true;

        decode_surfaces_.resize(decode_pool_size, nullptr);
        decode_dmabuf_fds_.assign(decode_pool_size, -1);

        {
            std::lock_guard<std::mutex> lk(pool_mutex_);
            while (!free_indices_.empty())
                free_indices_.pop();
            fd_to_index_.clear();

            while (!free_decode_indices_.empty())
                free_decode_indices_.pop();
            decode_fd_to_index_.clear();
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

            {
                std::lock_guard<std::mutex> lk(pool_mutex_);
                free_indices_.push(i);
                fd_to_index_.emplace(dmabuf_fds_[i], i);
            }
        }

        for (size_t i = 0; i < decode_pool_size; ++i)
        {
            NvBufSurface *surf = nullptr;
            if (NvBufSurfaceCreate(&surf, 1, &dec_params) != 0)
            {
                std::cerr << "Failed to create decode NvBufSurface " << i << std::endl;
                return false;
            }
            decode_surfaces_[i] = surf;
            decode_dmabuf_fds_[i] = surf->surfaceList[0].bufferDesc;

            std::lock_guard<std::mutex> lk(pool_mutex_);
            free_decode_indices_.push(i);
            decode_fd_to_index_.emplace(decode_dmabuf_fds_[i], i);
        }

        if (!logged_mode_.exchange(true))
        {
            std::cout << "VideoConverter: mode=decode(YUV422)->transform(NV12), out_pool=" << config_.buffer_pool_size
                      << ", dec_pool=" << decode_pool_size << std::endl;
        }

        return true;
    }

    void VideoConverter::destroyBuffers()
    {
        {
            std::lock_guard<std::mutex> lk(pool_mutex_);
            while (!free_indices_.empty())
                free_indices_.pop();
            fd_to_index_.clear();

            while (!free_decode_indices_.empty())
                free_decode_indices_.pop();
            decode_fd_to_index_.clear();
        }
        for (void *surf : surfaces_)
        {
            if (surf)
            {
                NvBufSurfaceDestroy((NvBufSurface *)surf);
            }
        }

        for (void *surf : decode_surfaces_)
        {
            if (surf)
            {
                NvBufSurfaceDestroy((NvBufSurface *)surf);
            }
        }

        surfaces_.clear();
        dmabuf_fds_.clear();

        decode_surfaces_.clear();
        decode_dmabuf_fds_.clear();
        jpeg_decoder_.reset();
    }

    void VideoConverter::setCallback(OutputCallback callback)
    {
        callback_ = std::move(callback);
    }

    void VideoConverter::releaseFd(int dmabuf_fd)
    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        auto it = fd_to_index_.find(dmabuf_fd);
        if (it != fd_to_index_.end())
        {
            free_indices_.push(it->second);
            return;
        }

        auto it2 = decode_fd_to_index_.find(dmabuf_fd);
        if (it2 != decode_fd_to_index_.end())
        {
            free_decode_indices_.push(it2->second);
            return;
        }

        // Not in our pool, so it must be a dynamic buffer from decoder.
        NvBufSurface *surf = nullptr;
        if (NvBufSurfaceFromFd(dmabuf_fd, (void **)&surf) == 0 && surf)
        {
            NvBufSurfaceDestroy(surf);
        }
    }

    void VideoConverter::processFrame(const uint8_t *data, size_t size, uint64_t timestamp_us)
    {
        if (!jpeg_decoder_ || dmabuf_fds_.empty())
            return;

        auto transform_to_nv12 = [&](NvBufSurface *src, int src_fd, uint32_t w, uint32_t h, size_t out_idx) -> bool
        {
            if (!src)
            {
                std::cerr << "VideoConverter: null src surface" << std::endl;
                return false;
            }
            NvBufSurface *dst = reinterpret_cast<NvBufSurface *>(surfaces_[out_idx]);
            if (!dst)
                return false;

            src->numFilled = 1;
            dst->numFilled = 1;

            NvBufSurfTransformParams tparams;
            memset(&tparams, 0, sizeof(tparams));
            // Full-frame colorspace conversion: avoid crop flags/rects to keep the fast path.
            // Do not set any optional flags (crop/filter/flip). This keeps the call minimal
            // and lets the backend pick the default fast path.
            // Explicitly set filter flag so the requested filter is honored.
            tparams.transform_flag = NVBUFSURF_TRANSFORM_FILTER;
            tparams.src_rect = nullptr;
            tparams.dst_rect = nullptr;
            tparams.transform_filter = NvBufSurfTransformInter_Nearest;

            const int tret = NvBufSurfTransform(src, dst, &tparams);
            if (tret != 0)
            {
                std::cerr << "VideoConverter: NvBufSurfTransform(YUV422->NV12) failed ret=" << tret
                          << " src_fd=" << src_fd << " w=" << w << " h=" << h << std::endl;
                return false;
            }
            return true;
        };

        size_t out_idx = 0;
        size_t dec_idx = 0;
        {
            std::lock_guard<std::mutex> lk(pool_mutex_);
            if (free_indices_.empty())
            {
                // Encoder is still using all buffers; drop this frame to avoid reuse hazards.
                static std::atomic<uint64_t> drop_count{0};
                const uint64_t d = drop_count.fetch_add(1) + 1;
                if (d <= 5 || (d % 300 == 0))
                {
                    std::cerr << "VideoConverter: buffer pool empty, dropping frame (drops=" << d
                              << ", pool_size=" << dmabuf_fds_.size() << ")" << std::endl;
                }
                return;
            }
            if (free_decode_indices_.empty())
            {
                // Decoder buffer pool empty; drop to keep latency bounded.
                return;
            }

            out_idx = free_indices_.front();
            free_indices_.pop();

            dec_idx = free_decode_indices_.front();
            free_decode_indices_.pop();
        }

        const int out_fd = dmabuf_fds_[out_idx];
        const int dec_fd = decode_dmabuf_fds_[dec_idx];

        uint32_t pixfmt = 0;
        uint32_t width = 0;
        uint32_t height = 0;

        // Decode MJPEG into YUV422 external buffer, then transform to NV12 for encoder.
        const auto t_decode0 = std::chrono::steady_clock::now();
        int fd = dec_fd;
        int ret = jpeg_decoder_->decodeToFd(fd, (unsigned char *)data, size, pixfmt, width, height);
        const auto t_decode1 = std::chrono::steady_clock::now();

        if (ret < 0)
        {
            std::cerr << "Failed to decode JPEG" << std::endl;
            releaseFd(out_fd);
            releaseFd(dec_fd);
        }
        else
        {
            // Decoder might still allocate a new buffer if it can't use external.
            // Accept it, transform from that FD, and destroy it via releaseFd().
            const int src_fd = fd;
            const bool used_external_decode_buffer = (src_fd == dec_fd);

            // Fast path: if the decoder used our external buffer (src_fd == dec_fd),
            // avoid NvBufSurfaceFromFd() overhead and use the already-known surface pointer.
            // Slow path: if decoder allocated its own buffer, map it once and destroy it after transform.
            NvBufSurface *src_surf = nullptr;
            NvBufSurface *dynamic_src_surf = nullptr;
            if (used_external_decode_buffer)
            {
                src_surf = reinterpret_cast<NvBufSurface *>(decode_surfaces_[dec_idx]);
            }
            else
            {
                if (NvBufSurfaceFromFd(src_fd, (void **)&dynamic_src_surf) != 0 || !dynamic_src_surf)
                {
                    std::cerr << "VideoConverter: NvBufSurfaceFromFd(dynamic src) failed" << std::endl;
                    releaseFd(out_fd);
                    releaseFd(dec_fd);
                    return;
                }
                src_surf = dynamic_src_surf;
            }

            static std::atomic<bool> logged_pixfmt{false};
            if (!logged_pixfmt.exchange(true))
            {
                RCLCPP_INFO(
                    conv_logger(),
                    "VideoConverter: decoder pixfmt=0x%x, w=%u h=%u (expect YUV422M=0x%x, YUV420M=0x%x)",
                    pixfmt,
                    width,
                    height,
                    V4L2_PIX_FMT_YUV422M,
                    V4L2_PIX_FMT_YUV420M);
            }

            if (pixfmt != V4L2_PIX_FMT_YUV422M && pixfmt != V4L2_PIX_FMT_YUV420M)
            {
                std::cerr << "VideoConverter: unsupported pixfmt from decoder: 0x" << std::hex << pixfmt << std::dec << std::endl;
                releaseFd(out_fd);
                releaseFd(dec_fd);
                if (dynamic_src_surf)
                    NvBufSurfaceDestroy(dynamic_src_surf);
                return;
            }

            const auto t_xform0 = std::chrono::steady_clock::now();
            const bool ok = transform_to_nv12(src_surf, src_fd, width, height, out_idx);
            const auto t_xform1 = std::chrono::steady_clock::now();

            static std::atomic<uint64_t> perf_count{0};
            static std::atomic<uint64_t> perf_dynamic_src{0};
            if (!used_external_decode_buffer)
            {
                perf_dynamic_src.fetch_add(1);
            }
            const uint64_t n = perf_count.fetch_add(1) + 1;
            if (n <= 5 || (n % 30 == 0))
            {
                const int64_t decode_us = std::chrono::duration_cast<std::chrono::microseconds>(t_decode1 - t_decode0).count();
                const int64_t xform_us = std::chrono::duration_cast<std::chrono::microseconds>(t_xform1 - t_xform0).count();

                const uint64_t dyn = perf_dynamic_src.load();
                const uint64_t tot = perf_count.load();

                const auto &src_sp = src_surf->surfaceList[0];
                const auto &dst_sp = reinterpret_cast<NvBufSurface *>(surfaces_[out_idx])->surfaceList[0];

                RCLCPP_INFO(
                    conv_logger(),
                    "VideoConverter perf: decode=%.2fms, yuv->nv12=%.2fms, pixfmt=0x%x, wh=%ux%u, ext_dec=%d, dyn_src=%llu/%llu, src(layout=%d fmt=%d pitch=%d), dst(layout=%d fmt=%d pitch=%d)",
                    static_cast<double>(decode_us) / 1000.0,
                    static_cast<double>(xform_us) / 1000.0,
                    pixfmt,
                    width,
                    height,
                    used_external_decode_buffer ? 1 : 0,
                    static_cast<unsigned long long>(dyn),
                    static_cast<unsigned long long>(tot),
                    static_cast<int>(src_sp.layout),
                    static_cast<int>(src_sp.colorFormat),
                    static_cast<int>(src_sp.pitch),
                    static_cast<int>(dst_sp.layout),
                    static_cast<int>(dst_sp.colorFormat),
                    static_cast<int>(dst_sp.pitch));
            }

            // Return decode buffer to pool.
            releaseFd(dec_fd);
            if (dynamic_src_surf)
                NvBufSurfaceDestroy(dynamic_src_surf);

            if (!ok)
            {
                releaseFd(out_fd);
                return;
            }

            bool taken = false;
            if (callback_)
            {
                taken = callback_(out_fd, timestamp_us);
            }
            if (!taken)
            {
                releaseFd(out_fd);
            }
        }
    }

} // namespace trb::video
