#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

namespace trb::audio
{

    struct AudioRxPacket
    {
        uint16_t seq{0};
        uint64_t timestamp_ntp{0};
        std::vector<uint8_t> payload;
    };

    class AudioReceiver
    {
    public:
        struct Config
        {
            uint32_t frame_duration_ms{20};
            uint32_t initial_buffer_ms{60};
            uint32_t max_buffer_ms{200};
            uint32_t max_sequence_gap{1000};
            double log_period_sec{1.0};
        };

        struct Stats
        {
            uint64_t received_packets{0};
            uint64_t delivered_packets{0};
            uint64_t duplicate_packets{0};
            uint64_t late_packets{0};
            uint64_t lost_packets{0};
            uint64_t reset_count{0};
            size_t buffered_packets{0};
        };

        using PlaybackCallback = std::function<bool(const uint8_t *data, size_t size, uint64_t timestamp_ntp)>;

        AudioReceiver(rclcpp::Logger logger, const Config &config);

        static Config configFromRosParam(rclcpp::Node &node, uint32_t frame_duration_ms);

        void setPlaybackCallback(PlaybackCallback callback);
        bool pushPacket(uint16_t seq, const uint8_t *data, size_t size, uint64_t timestamp_ntp);
        void reset(const std::string &reason = {});
        Stats stats() const;

    private:
        static uint32_t packetCountFromMs(uint32_t ms, uint32_t frame_duration_ms);
        static int16_t seqDelta(uint16_t lhs, uint16_t rhs);

        void drainReadyLocked(std::vector<AudioRxPacket> &ready_packets);
        void maybeSkipLossLocked(std::vector<AudioRxPacket> &ready_packets);
        void maybeLogStatsLocked();

        rclcpp::Logger logger_;
        Config config_;
        rclcpp::Clock::SharedPtr throttle_clock_;
        uint32_t initial_buffer_packets_{3};
        uint32_t max_buffer_packets_{10};

        mutable std::mutex mutex_;
        PlaybackCallback playback_callback_;
        std::map<uint16_t, AudioRxPacket> buffer_;
        bool initialized_{false};
        bool primed_{false};
        uint16_t expected_seq_{0};
        Stats stats_;
        std::chrono::steady_clock::time_point last_log_time_{std::chrono::steady_clock::time_point::min()};
        Stats last_log_stats_;
    };

} // namespace trb::audio