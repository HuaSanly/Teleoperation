#pragma once

#include <atomic>
#include <cstdint>
#include <fstream>
#include <mutex>
#include <string>

namespace trb::video
{

struct VideoRecorderConfig
{
    bool enabled{false};
    std::string output_dir;
};

class VideoRecorder
{
public:
    explicit VideoRecorder(VideoRecorderConfig config);
    ~VideoRecorder();

    bool start();
    void stop();

    void writeFrame(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe);

    bool isRunning() const;

private:
    std::string buildOutputPath() const;

    VideoRecorderConfig config_{};
    std::atomic<bool> running_{false};
    std::ofstream ofs_;
    std::mutex write_mutex_;
};

} // namespace trb::video
