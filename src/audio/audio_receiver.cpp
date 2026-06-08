#include "audio/audio_receiver.hpp"

#include <algorithm>
#include <chrono>
#include <utility>

namespace trb::audio
{
    namespace
    {
        template <typename T>
        T declareOrGet(rclcpp::Node &node, const std::string &name, const T &default_value)
        {
            if (!node.has_parameter(name))
            {
                return node.declare_parameter<T>(name, default_value);
            }
            T value{};
            node.get_parameter(name, value);
            return value;
        }
    } // namespace

    AudioReceiver::AudioReceiver(rclcpp::Logger logger, const Config &config)
        : logger_(std::move(logger)), config_(config), throttle_clock_(std::make_shared<rclcpp::Clock>(RCL_STEADY_TIME))
    {
        initial_buffer_packets_ = std::max<uint32_t>(1, packetCountFromMs(config_.initial_buffer_ms, config_.frame_duration_ms));
        max_buffer_packets_ = std::max<uint32_t>(initial_buffer_packets_ + 1,
                                                 packetCountFromMs(config_.max_buffer_ms, config_.frame_duration_ms));
    }

    AudioReceiver::Config AudioReceiver::configFromRosParam(rclcpp::Node &node, uint32_t frame_duration_ms)
    {
        Config config;
        config.frame_duration_ms = std::max<uint32_t>(1, frame_duration_ms);
        config.initial_buffer_ms = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.receiver.initial_buffer_ms", 60)));
        config.max_buffer_ms = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.receiver.max_buffer_ms", 200)));
        config.max_sequence_gap = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.receiver.max_sequence_gap", 1000)));
        config.log_period_sec = std::max(0.1, declareOrGet<double>(node, "audio.receiver.log_period_sec", 1.0));
        return config;
    }

    void AudioReceiver::setPlaybackCallback(PlaybackCallback callback)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        playback_callback_ = std::move(callback);
    }

    bool AudioReceiver::pushPacket(uint16_t seq, const uint8_t *data, size_t size, uint64_t timestamp_ntp)
    {
        if (!data || size == 0)
        {
            return false;
        }

        std::vector<AudioRxPacket> ready_packets;
        PlaybackCallback callback;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            ++stats_.received_packets;

            if (!initialized_)
            {
                initialized_ = true;
                primed_ = false;
                expected_seq_ = seq;
            }

            const int16_t delta = seqDelta(seq, expected_seq_);
            if (delta < 0)
            {
                ++stats_.late_packets;
                maybeLogStatsLocked();
                return false;
            }
            if (static_cast<uint32_t>(delta) > config_.max_sequence_gap)
            {
                ++stats_.reset_count;
                buffer_.clear();
                primed_ = false;
                expected_seq_ = seq;
                RCLCPP_WARN(logger_, "Audio receiver sequence jump detected; resetting rx buffer to seq=%u", seq);
            }
            if (buffer_.find(seq) != buffer_.end())
            {
                ++stats_.duplicate_packets;
                maybeLogStatsLocked();
                return false;
            }

            AudioRxPacket packet;
            packet.seq = seq;
            packet.timestamp_ntp = timestamp_ntp;
            packet.payload.assign(data, data + size);
            buffer_.emplace(seq, std::move(packet));
            stats_.buffered_packets = buffer_.size();

            if (!primed_ && buffer_.size() >= initial_buffer_packets_)
            {
                primed_ = true;
            }
            if (primed_)
            {
                drainReadyLocked(ready_packets);
                maybeSkipLossLocked(ready_packets);
            }
            stats_.buffered_packets = buffer_.size();
            callback = playback_callback_;
            maybeLogStatsLocked();
        }

        bool all_delivered = true;
        for (const auto &packet : ready_packets)
        {
            if (!callback || !callback(packet.payload.data(), packet.payload.size(), packet.timestamp_ntp))
            {
                all_delivered = false;
            }
        }
        return all_delivered && !ready_packets.empty();
    }

    void AudioReceiver::reset(const std::string &reason)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_.clear();
        initialized_ = false;
        primed_ = false;
        expected_seq_ = 0;
        ++stats_.reset_count;
        stats_.buffered_packets = 0;
        if (!reason.empty())
        {
            RCLCPP_INFO(logger_, "Audio receiver reset: %s", reason.c_str());
        }
    }

    AudioReceiver::Stats AudioReceiver::stats() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        Stats snapshot = stats_;
        snapshot.buffered_packets = buffer_.size();
        return snapshot;
    }

    uint32_t AudioReceiver::packetCountFromMs(uint32_t ms, uint32_t frame_duration_ms)
    {
        const uint32_t frame_ms = std::max<uint32_t>(1, frame_duration_ms);
        return std::max<uint32_t>(1, (ms + frame_ms - 1) / frame_ms);
    }

    int16_t AudioReceiver::seqDelta(uint16_t lhs, uint16_t rhs)
    {
        return static_cast<int16_t>(lhs - rhs);
    }

    void AudioReceiver::drainReadyLocked(std::vector<AudioRxPacket> &ready_packets)
    {
        while (true)
        {
            auto it = buffer_.find(expected_seq_);
            if (it == buffer_.end())
            {
                return;
            }
            ready_packets.push_back(std::move(it->second));
            buffer_.erase(it);
            ++expected_seq_;
            ++stats_.delivered_packets;
        }
    }

    void AudioReceiver::maybeSkipLossLocked(std::vector<AudioRxPacket> &ready_packets)
    {
        while (buffer_.size() >= max_buffer_packets_ && !buffer_.empty())
        {
            auto next_it = buffer_.begin();
            const int16_t delta = seqDelta(next_it->first, expected_seq_);
            if (delta <= 0)
            {
                expected_seq_ = next_it->first;
            }
            else
            {
                stats_.lost_packets += static_cast<uint16_t>(delta);
                expected_seq_ = next_it->first;
            }
            drainReadyLocked(ready_packets);
        }
    }

    void AudioReceiver::maybeLogStatsLocked()
    {
        const auto now = std::chrono::steady_clock::now();
        if (last_log_time_ == std::chrono::steady_clock::time_point::min())
        {
            last_log_time_ = now;
            last_log_stats_ = stats_;
            return;
        }

        const double elapsed_sec = std::chrono::duration<double>(now - last_log_time_).count();
        if (elapsed_sec < config_.log_period_sec)
        {
            return;
        }

        const uint64_t rx = stats_.received_packets - last_log_stats_.received_packets;
        const uint64_t delivered = stats_.delivered_packets - last_log_stats_.delivered_packets;
        const uint64_t dup = stats_.duplicate_packets - last_log_stats_.duplicate_packets;
        const uint64_t late = stats_.late_packets - last_log_stats_.late_packets;
        const uint64_t lost = stats_.lost_packets - last_log_stats_.lost_packets;
        const bool has_activity = rx > 0 || delivered > 0 || dup > 0 || late > 0 || lost > 0;
        if (has_activity)
        {
            RCLCPP_INFO(logger_,
                        "[AUDIO-RX] rx=%.1fpps play=%.1fpps dup=%lu late=%lu lost=%lu buf=%zu/%u",
                        static_cast<double>(rx) / elapsed_sec,
                        static_cast<double>(delivered) / elapsed_sec,
                        static_cast<unsigned long>(dup),
                        static_cast<unsigned long>(late),
                        static_cast<unsigned long>(lost),
                        buffer_.size(),
                        max_buffer_packets_);
        }
        last_log_time_ = now;
        last_log_stats_ = stats_;
    }

} // namespace trb::audio