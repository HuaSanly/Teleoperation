#pragma once

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_set>
#include <vector>

namespace trb::video
{

struct VideoDecoderConfig
{
    uint32_t width{0};
    uint32_t height{0};
    uint32_t pool_size{8};
    std::string out_layout{"pitch"};
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
    bool ensureOutputPool(uint32_t width, uint32_t height);
    void destroyPool();
    int acquireOutputFd();

    VideoDecoderConfig config_{};
    void *decoder_{nullptr};
    bool running_{false};

    uint32_t pool_width_{0};
    uint32_t pool_height_{0};

    std::mutex pool_mutex_;
    std::vector<int> free_fds_;
    std::unordered_set<int> in_use_;
};

} // namespace trb::video
