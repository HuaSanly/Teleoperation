#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>

#include "rclcpp/rclcpp.hpp"

#include "audio/audio_manager.hpp"
#include "audio/audio_receiver.hpp"

namespace trb::audio
{

    class AudioModule
    {
    public:
        using Config = AudioManager::Config;
        using EncodedPacketCallback = AudioManager::EncodedPacketCallback;

        static Config configFromRosParam(rclcpp::Node &node);

        AudioModule(rclcpp::Node &node, const Config &config);
        ~AudioModule();

        AudioModule(const AudioModule &) = delete;
        AudioModule &operator=(const AudioModule &) = delete;

        bool initialize();
        bool start();
        void stop();
        bool isRunning() const { return started_.load(std::memory_order_acquire); }

        bool isEnabled() const { return static_cast<bool>(manager_); }
        bool isConfigPublished() const { return config_published_.load(std::memory_order_acquire); }
        void markConfigPublished() { config_published_.store(true, std::memory_order_release); }
        void resetConfigPublished() { config_published_.store(false, std::memory_order_release); }
        bool isRemoteConfigReady() const { return remote_config_ready_.load(std::memory_order_acquire); }

        void setEncodedPacketCallback(EncodedPacketCallback callback);
        bool pushRemoteOpusPacket(const uint8_t *data, size_t size, uint64_t timestamp_ntp);
        bool receiveRemotePacket(uint16_t seq, const uint8_t *data, size_t size, uint64_t timestamp_ntp);
        bool applyRemoteConfig(const Config &remote_config, const std::string &config_id);
        void resetRemoteConfig(const std::string &reason = {});

        const Config &config() const { return config_; }

    private:
        rclcpp::Logger logger_;
        Config config_;
        AudioReceiver::Config receiver_config_;
        std::unique_ptr<AudioManager> manager_;
        std::unique_ptr<AudioReceiver> receiver_;
        EncodedPacketCallback encoded_cb_;
        std::atomic<bool> started_{false};
        std::atomic<bool> config_published_{false};
        std::atomic<bool> remote_config_ready_{false};
        std::string remote_config_id_;
    };

} // namespace trb::audio