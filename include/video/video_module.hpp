#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include "video/video_stream_manager.hpp"

namespace trb::video
{

    class VideoModule
    {
    public:
        struct Config
        {
            enum class Codec : int
            {
                kH264 = 0,
                kH265 = 1,
            };

            uint32_t width{3840};
            uint32_t height{1520};
            uint32_t fps{30};
            Codec codec{Codec::kH264};

            static Config configFromRosParam(rclcpp::Node &node);
        };

        using EncodedFrameCallback = std::function<void(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)>;
        using SpsPpsCallback = std::function<void(const std::vector<uint8_t> &sps,
                                                  const std::vector<uint8_t> &pps,
                                                  const std::vector<uint8_t> &vps)>;
        using StatsSnapshot = VideoStreamManager::StatsSnapshot;

        VideoModule(rclcpp::Node &node, Config config);
        ~VideoModule();

        VideoModule(const VideoModule &) = delete;
        VideoModule &operator=(const VideoModule &) = delete;

        bool start();
        void stop();
        bool isRunning() const;

        void setEncodedFrameCallback(EncodedFrameCallback callback);
        void setSpsPpsCallback(SpsPpsCallback callback);
        bool requestKeyframe();

        bool hasSpsPps() const;
        bool getSpsPps(std::vector<uint8_t> &sps,
                       std::vector<uint8_t> &pps,
                       std::vector<uint8_t> &vps) const;
        void clearSpsPps();

        StatsSnapshot consumeStats();

        const Config &config() const { return config_; }

    private:
        void onEncodedFrame(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe);
        void updateParameterSets(const uint8_t *data, size_t size);
        bool parameterSetsReadyLocked() const;
        void emitCachedParameterSetsIfReady();

        rclcpp::Node &node_;
        rclcpp::Logger logger_;
        Config config_;
        std::unique_ptr<VideoStreamManager> manager_;

        EncodedFrameCallback encoded_callback_;
        SpsPpsCallback sps_pps_callback_;

        mutable std::mutex sps_pps_mutex_;
        std::vector<uint8_t> cached_sps_;
        std::vector<uint8_t> cached_pps_;
        std::vector<uint8_t> cached_vps_;
        std::atomic<bool> sps_pps_emitted_{false};
    };

} // namespace trb::video