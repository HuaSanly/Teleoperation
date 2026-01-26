#pragma once

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace trb::video
{

struct VideoDecoderConfig
{
    uint32_t width{0};
    uint32_t height{0};
    uint32_t pool_size{8};
    bool max_perf_mode{false};
};

struct DecodedFrame
{
    int fd{-1};
    uint32_t width{0};
    uint32_t height{0};
    uint64_t timestamp_us{0};
};

class VideoDecoder
{
public:
    explicit VideoDecoder(VideoDecoderConfig config);
    ~VideoDecoder();

    bool start();
    void stop();

    bool decode(const uint8_t *data, size_t size, uint64_t timestamp_us, DecodedFrame &out);
    void releaseFd(int fd);

    bool isRunning() const;

private:
    bool configureDecoder();
    void destroyDecoder();
    bool reclaimOutputBuffers();
    uint32_t clampBufferCount(uint32_t v) const;

    VideoDecoderConfig config_{};
    void *decoder_{nullptr};
    bool running_{false};

    std::mutex pool_mutex_;
    std::vector<uint32_t> free_output_indices_;
    std::vector<int> capture_fd_by_index_;
    std::unordered_map<int, uint32_t> fd_to_capture_index_;
    std::unordered_set<int> in_use_fds_;

    bool capture_configured_{false};
};

} // namespace trb::video
