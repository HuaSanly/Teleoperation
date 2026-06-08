#include "video/video_decoder.hpp"

#include <algorithm>
#include <chrono>

#include "rclcpp/rclcpp.hpp"

#include "NvBufSurface.h"
#include "NvJpegDecoder.h"
#include "nvbufsurface.h"

namespace trb::video
{

namespace
{
uint64_t nowSteadyUs()
{
    const auto now = std::chrono::steady_clock::now();
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(
            now.time_since_epoch()).count());
}

size_t trimToJpegEoi(const uint8_t *data, size_t size)
{
    if (!data || size < 2)
    {
        return size;
    }

    const size_t search = std::min<size_t>(size, 1024);
    for (size_t offset = 0; offset + 1 < search; ++offset)
    {
        const size_t index = size - 2 - offset;
        if (data[index] == 0xff && data[index + 1] == 0xd9)
        {
            return index + 2;
        }
    }
    return size;
}

void destroyDecodedFd(int fd)
{
    if (fd > 0)
    {
        (void)NvBufSurf::NvDestroy(fd);
    }
}

void logDecodeFailureOnce(const uint8_t *data, size_t size, uint64_t frame_id)
{
    static std::atomic<uint64_t> failure_count{0};
    const uint64_t count = failure_count.fetch_add(1, std::memory_order_relaxed) + 1;
    if (!(count <= 5 || (count % 60 == 0)))
    {
        return;
    }

    const uint8_t b0 = size > 0 ? data[0] : 0;
    const uint8_t b1 = size > 1 ? data[1] : 0;
    RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                "VideoDecoder: decodeToFd failed frame=%lu size=%zu head=0x%02x 0x%02x failures=%lu",
                static_cast<unsigned long>(frame_id),
                size,
                static_cast<unsigned>(b0),
                static_cast<unsigned>(b1),
                static_cast<unsigned long>(count));
}
} // namespace

VideoDecoder::VideoDecoder() = default;

VideoDecoder::~VideoDecoder()
{
    shutdown();
    clearQueue();
    if (jpeg_decoder_)
    {
        jpeg_decoder_->setUseExternalBuffer(false);
        jpeg_decoder_.reset();
    }
    destroyDecodeBuffers();
}

bool VideoDecoder::initialize(const Config &config)
{
    config_ = config;
    stop_.store(false, std::memory_order_release);
    shutting_down_.store(false, std::memory_order_release);

    jpeg_decoder_.reset(NvJPEGDecoder::createJPEGDecoder("jpegdec"));
    if (!jpeg_decoder_)
    {
        RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"),
                     "VideoDecoder: failed to create NvJPEGDecoder");
        return false;
    }

    jpeg_decoder_->setMemType(NVBUF_MEM_SURFACE_ARRAY);
    jpeg_decoder_->setUseExternalBuffer(true);

    if (!allocateDecodeBuffers())
    {
        jpeg_decoder_->setUseExternalBuffer(false);
        jpeg_decoder_.reset();
        return false;
    }

    RCLCPP_INFO(rclcpp::get_logger("teleop_robot_bridge.video"),
                "VideoDecoder: using NvJPEGDecoder external decode pool for Thor MJPEG decode");
    return true;
}

bool VideoDecoder::allocateDecodeBuffers()
{
    destroyDecodeBuffers();

    const uint32_t pool_size = std::max<uint32_t>(1u, config_.capture_plane_buffers);
    NvBufSurfaceCreateParams params;
    std::memset(&params, 0, sizeof(params));
    params.gpuId = 0;
    params.width = config_.width;
    params.height = config_.height;
    params.layout = (config_.decode_surface_layout == 1) ? NVBUF_LAYOUT_BLOCK_LINEAR : NVBUF_LAYOUT_PITCH;
    params.colorFormat = NVBUF_COLOR_FORMAT_YUV422;
    params.memType = NVBUF_MEM_SURFACE_ARRAY;
    params.isContiguous = true;

    decode_surfaces_.assign(pool_size, nullptr);
    decode_dmabuf_fds_.assign(pool_size, -1);
    for (uint32_t index = 0; index < pool_size; ++index)
    {
        NvBufSurface *surface = nullptr;
        if (NvBufSurfaceCreate(&surface, 1, &params) != 0 || !surface)
        {
            RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"),
                         "VideoDecoder: NvBufSurfaceCreate decode buffer failed at index=%u", index);
            destroyDecodeBuffers();
            return false;
        }
        decode_surfaces_[index] = surface;
        decode_dmabuf_fds_[index] = surface->surfaceList[0].bufferDesc;
        free_decode_indices_.push(index);
        decode_fd_to_index_.emplace(decode_dmabuf_fds_[index], index);
    }

    RCLCPP_INFO(rclcpp::get_logger("teleop_robot_bridge.video"),
                "VideoDecoder: decode pool allocated size=%u layout=%s input=%ux%u",
                pool_size,
                config_.decode_surface_layout == 1 ? "block" : "pitch",
                config_.width,
                config_.height);
    return true;
}

void VideoDecoder::destroyDecodeBuffers()
{
    {
        std::lock_guard<std::mutex> lk(pool_mutex_);
        while (!free_decode_indices_.empty())
        {
            free_decode_indices_.pop();
        }
        decode_fd_to_index_.clear();
    }

    for (void *surface : decode_surfaces_)
    {
        if (surface)
        {
            NvBufSurfaceDestroy(reinterpret_cast<NvBufSurface *>(surface));
        }
    }
    decode_surfaces_.clear();
    decode_dmabuf_fds_.clear();
}

bool VideoDecoder::acquireDecodeBuffer(size_t &index, int &fd)
{
    std::lock_guard<std::mutex> lk(pool_mutex_);
    if (free_decode_indices_.empty())
    {
        return false;
    }
    index = free_decode_indices_.front();
    free_decode_indices_.pop();
    fd = decode_dmabuf_fds_[index];
    return fd >= 0;
}

void VideoDecoder::releaseDecodeBuffer(size_t index)
{
    std::lock_guard<std::mutex> lk(pool_mutex_);
    if (index < decode_dmabuf_fds_.size())
    {
        free_decode_indices_.push(index);
    }
}

bool VideoDecoder::submit(const uint8_t *data,
                          size_t size,
                          uint64_t frame_id,
                          uint64_t capture_timestamp_us,
                          uint64_t capture_steady_us)
{
    return submitDetailed(data, size, frame_id, capture_timestamp_us, capture_steady_us) ==
           SubmitStatus::kQueued;
}

VideoDecoder::SubmitStatus VideoDecoder::submitDetailed(const uint8_t *data,
                                                        size_t size,
                                                        uint64_t frame_id,
                                                        uint64_t capture_timestamp_us,
                                                        uint64_t capture_steady_us)
{
    if (!jpeg_decoder_ || !data || size == 0 || stop_.load(std::memory_order_acquire))
    {
        if (stop_.load(std::memory_order_acquire) || !jpeg_decoder_)
        {
            return SubmitStatus::kStopped;
        }
        return SubmitStatus::kInvalidInput;
    }

    if (size > config_.max_mjpeg_size_bytes)
    {
        RCLCPP_WARN_THROTTLE(rclcpp::get_logger("teleop_robot_bridge.video"),
                             *rclcpp::Clock::make_shared(),
                             1000,
                             "VideoDecoder: MJPEG frame too large (%zu > %u), dropping",
                             size, config_.max_mjpeg_size_bytes);
        return SubmitStatus::kFrameTooLarge;
    }

    const size_t max_queue = std::max<uint32_t>(1, config_.capture_plane_buffers);
    {
        std::lock_guard<std::mutex> lk(queue_mutex_);
        if (decoded_queue_.size() >= max_queue)
        {
            return SubmitStatus::kDecodedQueueFull;
        }
    }

    size_t decode_index = 0;
    int decode_fd = -1;
    if (!acquireDecodeBuffer(decode_index, decode_fd))
    {
        return SubmitStatus::kNoDecodeBuffer;
    }

    const auto decode_start = nowSteadyUs();
    const size_t jpeg_size = trimToJpegEoi(data, size);
    int fd = decode_fd;
    uint32_t pixfmt = 0;
    uint32_t width = 0;
    uint32_t height = 0;

    {
        std::lock_guard<std::mutex> lk(decode_mutex_);
        if (jpeg_decoder_->decodeToFd(fd,
                                      const_cast<unsigned char *>(data),
                                      static_cast<unsigned long>(jpeg_size),
                                      pixfmt,
                                      width,
                                      height) < 0)
        {
            logDecodeFailureOnce(data, jpeg_size, frame_id);
            releaseDecodeBuffer(decode_index);
            return SubmitStatus::kDecodeFailed;
        }
    }

    if (fd < 0)
    {
        releaseDecodeBuffer(decode_index);
        return SubmitStatus::kInvalidDecodedOutput;
    }

    DecodedFrame frame;
    frame.yuv_dmabuf_fd = fd;
    frame.frame_id = frame_id;
    frame.capture_timestamp_us = capture_timestamp_us;
    frame.capture_steady_us = capture_steady_us;
    frame.decode_us = nowSteadyUs() - decode_start;
    frame._cap_buf_index = static_cast<uint32_t>(decode_index);
    frame._decode_pool_fd = decode_fd;

    {
        std::lock_guard<std::mutex> lk(queue_mutex_);
        if (decoded_queue_.size() >= max_queue || stop_.load(std::memory_order_acquire))
        {
            if (fd != decode_fd)
            {
                destroyDecodedFd(fd);
            }
            releaseDecodeBuffer(decode_index);
            return stop_.load(std::memory_order_acquire)
                       ? SubmitStatus::kStopped
                       : SubmitStatus::kDecodedQueueFull;
        }
        decoded_queue_.push(frame);
    }
    queue_cv_.notify_one();

    static std::atomic<bool> logged_format{false};
    if (!logged_format.exchange(true, std::memory_order_relaxed))
    {
        RCLCPP_INFO(rclcpp::get_logger("teleop_robot_bridge.video"),
                    "VideoDecoder: first decoded MJPEG frame fd=%d pool_fd=%d external=%d pixfmt=0x%x size=%ux%u",
                    fd, decode_fd, fd == decode_fd ? 1 : 0, pixfmt, width, height);
    }

    return SubmitStatus::kQueued;
}

bool VideoDecoder::dequeueSync(DecodedFrame &out, int timeout_ms)
{
    std::unique_lock<std::mutex> lk(queue_mutex_);
    const auto ready = [this]() {
        return stop_.load(std::memory_order_acquire) || !decoded_queue_.empty();
    };

    if (timeout_ms <= 0)
    {
        if (!ready())
        {
            return false;
        }
    }
    else if (!queue_cv_.wait_for(lk, std::chrono::milliseconds(timeout_ms), ready))
    {
        return false;
    }

    if (decoded_queue_.empty())
    {
        return false;
    }

    out = decoded_queue_.front();
    decoded_queue_.pop();
    return true;
}

void VideoDecoder::shutdown()
{
    shutting_down_.store(true, std::memory_order_release);
    stop_.store(true, std::memory_order_release);
    queue_cv_.notify_all();
}

void VideoDecoder::requeueCapture(DecodedFrame &frame)
{
    if (!shutting_down_.load(std::memory_order_acquire) &&
        frame.yuv_dmabuf_fd >= 0 && frame.yuv_dmabuf_fd != frame._decode_pool_fd)
    {
        destroyDecodedFd(frame.yuv_dmabuf_fd);
    }
    if (frame._decode_pool_fd >= 0)
    {
        releaseDecodeBuffer(static_cast<size_t>(frame._cap_buf_index));
    }
    frame.yuv_dmabuf_fd = -1;
    frame._decode_pool_fd = -1;
    frame._nvbuf = nullptr;
}

void VideoDecoder::clearQueue()
{
    std::lock_guard<std::mutex> lk(queue_mutex_);
    while (!decoded_queue_.empty())
    {
        auto frame = decoded_queue_.front();
        decoded_queue_.pop();
        if (!shutting_down_.load(std::memory_order_acquire) &&
            frame.yuv_dmabuf_fd >= 0 && frame.yuv_dmabuf_fd != frame._decode_pool_fd)
        {
            destroyDecodedFd(frame.yuv_dmabuf_fd);
        }
        if (frame._decode_pool_fd >= 0)
        {
            releaseDecodeBuffer(static_cast<size_t>(frame._cap_buf_index));
        }
    }
}

} // namespace trb::video
