#pragma once

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <vector>

class NvBuffer;
class NvJPEGDecoder;

namespace trb::video
{

class VideoDecoder
{
public:
    struct Config
    {
        uint32_t width = 3840;
        uint32_t height = 1520;
        uint32_t output_plane_buffers = 6;
        uint32_t capture_plane_buffers = 12;
        uint32_t max_mjpeg_size_bytes = 4 * 1024 * 1024;
        int32_t decode_surface_layout = 0;
    };

    struct DecodedFrame
    {
        int yuv_dmabuf_fd{-1};
        uint64_t frame_id{0};
        uint64_t capture_timestamp_us{0};
        uint64_t capture_steady_us{0};
        uint64_t decode_us{0};
        uint32_t _cap_buf_index{0};
        int _decode_pool_fd{-1};
        NvBuffer *_nvbuf{nullptr};
    };

    enum class SubmitStatus
    {
        kQueued,
        kStopped,
        kInvalidInput,
        kFrameTooLarge,
        kDecodedQueueFull,
        kNoDecodeBuffer,
        kDecodeFailed,
        kInvalidDecodedOutput,
    };

    VideoDecoder();
    ~VideoDecoder();

    VideoDecoder(const VideoDecoder &) = delete;
    VideoDecoder &operator=(const VideoDecoder &) = delete;

    bool initialize(const Config &config);

    bool submit(const uint8_t *data,
                size_t size,
                uint64_t frame_id,
                uint64_t capture_timestamp_us,
                uint64_t capture_steady_us);

    SubmitStatus submitDetailed(const uint8_t *data,
                                size_t size,
                                uint64_t frame_id,
                                uint64_t capture_timestamp_us,
                                uint64_t capture_steady_us);

    bool dequeueSync(DecodedFrame &out, int timeout_ms = 100);

    void requeueCapture(DecodedFrame &frame);
    void shutdown();

private:
    bool allocateDecodeBuffers();
    void destroyDecodeBuffers();
    bool acquireDecodeBuffer(size_t &index, int &fd);
    void releaseDecodeBuffer(size_t index);
    void clearQueue();

    Config config_;
    std::unique_ptr<NvJPEGDecoder> jpeg_decoder_;
    std::mutex decode_mutex_;
    std::mutex pool_mutex_;
    std::vector<void *> decode_surfaces_;
    std::vector<int> decode_dmabuf_fds_;
    std::queue<size_t> free_decode_indices_;
    std::unordered_map<int, size_t> decode_fd_to_index_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::queue<DecodedFrame> decoded_queue_;
    std::atomic<bool> stop_{false};
    std::atomic<bool> shutting_down_{false};
};

} // namespace trb::video
