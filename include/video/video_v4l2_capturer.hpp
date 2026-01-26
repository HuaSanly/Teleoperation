#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace trb::video
{

struct VideoV4L2Config
{
    std::string device;
    uint32_t width{0};
    uint32_t height{0};
    uint32_t fps{0};
    std::string pixel_format;
    int buffer_count{4};
};

struct V4L2Frame
{
    uint32_t index{0};
    const uint8_t *data{nullptr};
    size_t bytes_used{0};
    uint64_t timestamp_us{0};
};

class VideoV4L2Capturer
{
public:
    explicit VideoV4L2Capturer(VideoV4L2Config config);
    ~VideoV4L2Capturer();

    bool start();
    void stop();

    bool dequeue(V4L2Frame &frame);
    void requeue(uint32_t index);

    bool isRunning() const;

private:
    struct Buffer
    {
        void *start{nullptr};
        size_t length{0};
    };

    bool openDevice();
    bool setFormat();
    bool setFrameRate();
    bool requestBuffers();
    bool queueAllBuffers();
    void unmapBuffers();

    static uint32_t toFourcc(const std::string &format);

    VideoV4L2Config config_{};
    int fd_{-1};
    bool streaming_{false};
    std::vector<Buffer> buffers_;
};

} // namespace trb::video
