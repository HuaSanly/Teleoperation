#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

#include "telemetry/robot_telemetry_types.hpp"
#include "udp/pose_udp_receiver.hpp"
#include "udp/udp_manager.hpp"

namespace trb::udp
{

    class UdpModule
    {
    public:
        struct Config
        {
            UdpManager::Config udp;
            bool pose_enabled{false};
            PoseUdpReceiverConfig pose;
            bool direct_running_mode{false};

            static Config configFromRosParam(rclcpp::Node &node);
        };

        using AudioDatagramCallback = std::function<void(uint16_t seq, const uint8_t *data, size_t size, uint64_t timestamp_ntp)>;
        using HandshakeReadyCallback = std::function<void()>;
        using PeerLostCallback = std::function<void()>;

        UdpModule(rclcpp::Node &node, Config config);
        ~UdpModule();

        UdpModule(const UdpModule &) = delete;
        UdpModule &operator=(const UdpModule &) = delete;

        bool start(const std::string &session_id);
        void stop();
        void resetSession();

        bool isRunning() const { return udp_manager_ != nullptr; }
        bool isHandshakeReady() const;
        bool controlEnabled() const { return config_.udp.control_enabled; }

        void setAudioDatagramCallback(AudioDatagramCallback callback) { audio_callback_ = std::move(callback); }
        void setHandshakeReadyCallback(HandshakeReadyCallback callback) { on_ready_ = std::move(callback); }
        void setPeerLostCallback(PeerLostCallback callback) { on_peer_lost_ = std::move(callback); }

        void sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us, bool keyframe);
        void sendAudioPacket(const uint8_t *data, size_t size, uint64_t timestamp_ntp);
        void sendRobotTelemetry(const telemetry::RobotTelemetrySnapshot &snapshot);
        void sendRobotJointTelemetry(const telemetry::RobotJointTelemetrySnapshot &snapshot);
        UdpManager::VideoStatsSnapshot consumeVideoStats();

        const Config &config() const { return config_; }

    private:
        void onDatagram(const uint8_t *data, size_t size);
        void handshakeTimerCallback();

        rclcpp::Node &node_;
        rclcpp::Logger logger_;
        Config config_;
        std::unique_ptr<UdpManager> udp_manager_;
        std::unique_ptr<PoseUdpReceiver> pose_receiver_;
        rclcpp::TimerBase::SharedPtr handshake_timer_;
        AudioDatagramCallback audio_callback_;
        HandshakeReadyCallback on_ready_;
        PeerLostCallback on_peer_lost_;
        std::atomic<bool> ready_fired_{false};
        std::atomic<bool> shutting_down_{false};
    };

} // namespace trb::udp