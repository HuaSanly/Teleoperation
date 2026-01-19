#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"

namespace trb::video
{

    class VideoStreamManager
    {
    public:
        explicit VideoStreamManager(rclcpp::Node &node);
        ~VideoStreamManager();

        VideoStreamManager(const VideoStreamManager &) = delete;
        VideoStreamManager &operator=(const VideoStreamManager &) = delete;

        // Start the full video pipeline (capture -> convert -> encode -> record).
        // Returns true if startup succeeded.
        bool start();

        // Stop threads and release resources.
        void stop();

        bool isRunning() const;

        using EncodedFrameCallback = std::function<void(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)>;
        void setEncodedFrameCallback(EncodedFrameCallback callback);

    private:
        class Impl;
        std::unique_ptr<Impl> impl_;
    };

} // namespace trb::video
