#pragma once

#include <string>
#include <filesystem>
#include <mutex>
#include <vector>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <queue>
#include <memory>
#include <fstream>

#include "rclcpp/rclcpp.hpp"

namespace trb::video
{
    class VideoRecorder
    {
    public:
        struct Config
        {
            bool enabled = false;
            std::string output_dir;
        };

        VideoRecorder(rclcpp::Logger logger);
        ~VideoRecorder();

        bool initialize(const Config &config);
        void writeFrame(uint64_t frame_index, const uint8_t *data, size_t size, bool keyframe);

    private:
        void writerLoop();

        rclcpp::Logger logger_;
        Config config_;

        struct FrameData
        {
            uint64_t index;
            std::vector<uint8_t> data;
            bool keyframe;
        };

        std::filesystem::path output_dir_;
        std::filesystem::path output_file_path_;
        std::ofstream output_file_;

        std::mutex mutex_;
        std::condition_variable cv_;
        std::queue<FrameData> queue_;
        std::atomic<bool> running_{false};
        std::thread writer_thread_;
    };
}
