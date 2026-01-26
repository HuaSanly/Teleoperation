#include "video/video_recorder.hpp"

#include <chrono>
#include <filesystem>

#include <ros/ros.h>

namespace trb::video
{

VideoRecorder::VideoRecorder(VideoRecorderConfig config)
    : config_(std::move(config))
{
}

VideoRecorder::~VideoRecorder()
{
    stop();
}

bool VideoRecorder::start()
{
    if (running_.exchange(true))
    {
        return true;
    }

    if (!config_.enabled)
    {
        running_.store(false);
        return false;
    }

    const std::string path = buildOutputPath();
    if (path.empty())
    {
        running_.store(false);
        return false;
    }

    ofs_.open(path, std::ios::binary | std::ios::out);
    if (!ofs_.is_open())
    {
        ROS_ERROR("VideoRecorder: failed to open %s", path.c_str());
        running_.store(false);
        return false;
    }

    ROS_INFO("VideoRecorder: recording to %s", path.c_str());
    return true;
}

void VideoRecorder::stop()
{
    if (!running_.exchange(false))
    {
        return;
    }

    std::lock_guard<std::mutex> lk(write_mutex_);
    if (ofs_.is_open())
    {
        ofs_.flush();
        ofs_.close();
    }
}

void VideoRecorder::writeFrame(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)
{
    (void)timestamp_us;
    (void)keyframe;

    if (!running_.load() || !config_.enabled || !ofs_.is_open() || !data || size == 0)
    {
        return;
    }

    std::lock_guard<std::mutex> lk(write_mutex_);
    ofs_.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(size));
}

bool VideoRecorder::isRunning() const
{
    return running_.load();
}

std::string VideoRecorder::buildOutputPath() const
{
    std::filesystem::path dir;
    if (!config_.output_dir.empty())
    {
        dir = config_.output_dir;
    }
    else
    {
        dir = std::filesystem::current_path();
    }

    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    if (ec)
    {
        ROS_ERROR("VideoRecorder: failed to create dir %s: %s", dir.string().c_str(), ec.message().c_str());
        return {};
    }

    const auto now = std::chrono::system_clock::now();
    const auto ts = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    const std::string filename = "recording_" + std::to_string(ts) + ".h264";

    return (dir / filename).string();
}

} // namespace trb::video
