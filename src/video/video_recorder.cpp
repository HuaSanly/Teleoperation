#include "video/video_recorder.hpp"
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstring>

namespace trb::video
{
    VideoRecorder::VideoRecorder(rclcpp::Logger logger)
        : logger_(std::move(logger))
    {
    }

    VideoRecorder::~VideoRecorder()
    {
        running_ = false;
        cv_.notify_all();
        if (writer_thread_.joinable())
        {
            writer_thread_.join();
        }

        if (output_file_.is_open())
        {
            output_file_.close();
        }
    }

    bool VideoRecorder::initialize(const Config &config)
    {
        config_ = config;
        if (!config_.enabled)
        {
            RCLCPP_INFO(logger_, "Video recording disabled");
            return true;
        }

        // Treat output_dir as a directory.
        // If empty, use current working directory.
        std::filesystem::path out_dir;
        if (config_.output_dir.empty())
        {
            out_dir = std::filesystem::current_path();
        }
        else
        {
            out_dir = std::filesystem::path(config_.output_dir);
        }

        std::error_code ec;
        if (!out_dir.empty())
        {
            std::filesystem::create_directories(out_dir, ec);
            if (ec)
            {
                RCLCPP_ERROR(logger_, "Failed to create output dir: %s (%s)", out_dir.c_str(), ec.message().c_str());
                return false;
            }
        }

        output_dir_ = out_dir;

        // Single output file under the target directory.
        output_file_path_ = output_dir_ / "output.h264";

        // Truncate on start, then append frames.
        output_file_.open(output_file_path_, std::ios::binary | std::ios::out | std::ios::trunc);
        if (!output_file_.is_open())
        {
            RCLCPP_ERROR(logger_, "Failed to open %s for writing", output_file_path_.c_str());
            return false;
        }

        RCLCPP_INFO(logger_, "Video recording enabled. Output file: %s", output_file_path_.c_str());

        running_ = true;
        writer_thread_ = std::thread(&VideoRecorder::writerLoop, this);
        return true;
    }

    void VideoRecorder::writeFrame(uint64_t frame_index, const uint8_t *data, size_t size, bool keyframe)
    {
        if (!config_.enabled || !running_)
            return;

        if (!data || size == 0)
            return;

        {
            std::lock_guard<std::mutex> lock(mutex_);
            // Simple unbounded queue for now, or could limit size to avoid OOM
            if (queue_.size() > 300)
            {
                // Drop old frames if disk is too slow
                // In a real system, we might want to drop until next keyframe
                queue_.pop();
                static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
                RCLCPP_WARN_THROTTLE(logger_, steady_clock, 5000, "Recorder queue full, dropping frames");
            }

            FrameData frame;
            frame.index = frame_index;
            frame.data.assign(data, data + size);
            frame.keyframe = keyframe;
            queue_.push(std::move(frame));
        }
        cv_.notify_one();
    }

    void VideoRecorder::writerLoop()
    {
        while (running_)
        {
            FrameData frame;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this]
                         { return !queue_.empty() || !running_; });

                if (!running_ && queue_.empty())
                    break;

                if (queue_.empty())
                    continue;

                frame = std::move(queue_.front());
                queue_.pop();
            }

            if (!output_file_.is_open())
            {
                RCLCPP_ERROR(logger_, "Recorder output file is not open; dropping frame");
                continue;
            }

            if (frame.index == 0)
            {
                RCLCPP_INFO(logger_, "Writing first frame into: %s", output_file_path_.c_str());
            }

            output_file_.write(reinterpret_cast<const char *>(frame.data.data()), frame.data.size());
            if (!output_file_)
            {
                RCLCPP_ERROR(logger_, "Failed while appending to %s", output_file_path_.c_str());
                // Attempt to clear badbit to keep going.
                output_file_.clear();
            }
        }

        if (output_file_.is_open())
        {
            output_file_.flush();
        }
    }
}
