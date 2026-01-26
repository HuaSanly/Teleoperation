#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <vector>

#include "video/video_decoder.hpp"
#include "video/video_encoder.hpp"
#include "video/video_v4l2_capturer.hpp"

namespace trb::video
{

struct VideoProfile
{
    uint32_t width{0};
    uint32_t height{0};
    uint32_t fps{0};
};

struct VideoStreamConfig
{
    VideoProfile profile{};
    std::string device;
    std::string pixel_format;
    int v4l2_buffer_count{4};

    uint32_t decoder_pool_size{8};
    std::string decoder_out_layout{"pitch"};

    VideoEncoderConfig encoder{};
};

class VideoStreamManager
{
public:
    using EncodedFrameCallback = std::function<void(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)>;

    explicit VideoStreamManager(VideoStreamConfig config);
    ~VideoStreamManager();

    bool start();
    void stop();

    void setEncodedFrameCallback(EncodedFrameCallback cb);

    bool isRunning() const;

private:
    struct Frame
    {
        std::vector<uint8_t> data;
        uint64_t timestamp_us{0};
    };

    void captureThreadMain();
    void pipelineThreadMain();

    VideoStreamConfig config_{};
    VideoV4L2Capturer capturer_;
    VideoDecoder decoder_;
    VideoEncoder encoder_;

    std::atomic<bool> running_{false};
    std::thread capture_thread_;
    std::thread pipeline_thread_;

    std::mutex frame_mutex_;
    std::condition_variable frame_cv_;
    std::optional<Frame> latest_frame_;

    EncodedFrameCallback encoded_frame_cb_;
};

} // namespace trb::video
