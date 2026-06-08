#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include "grpc/grpc_manager.hpp"

namespace trb
{

    class GrpcModule
    {
    public:
        using Config = GrpcConfig;
        using SignalingEventCallback = std::function<void(const signaling::EventMessage &)>;
        using RegisteredCallback = std::function<void()>;
        using HeartbeatFailCallback = std::function<void()>;
        using StreamEndCallback = std::function<void()>;

        struct AudioConfig
        {
            uint32_t sample_rate{48000};
            uint32_t channels{1};
            uint32_t frame_duration_ms{20};
            uint32_t samples_per_channel{960};
            uint32_t bitrate_bps{64000};
            bool opus_inband_fec_enabled{true};
            bool opus_dtx_enabled{false};
        };

        enum class Codec : int
        {
            kH264 = 0,
            kH265 = 1,
        };

        static Config configFromRosParam(rclcpp::Node &node);
        static AudioConfig audioConfigFromRosParam(rclcpp::Node &node);

        GrpcModule(rclcpp::Node &node, const Config &config);
        ~GrpcModule();

        GrpcModule(const GrpcModule &) = delete;
        GrpcModule &operator=(const GrpcModule &) = delete;

        void start();
        void stop();

        void setRegisteredCallback(RegisteredCallback callback) { on_registered_ = std::move(callback); }
        void setSignalingEventCallback(SignalingEventCallback callback) { on_event_ = std::move(callback); }
        void setHeartbeatFailCallback(HeartbeatFailCallback callback) { on_heartbeat_fail_ = std::move(callback); }
        void setStreamEndCallback(StreamEndCallback callback) { on_stream_end_ = std::move(callback); }

        bool isRegistered() const { return registered_.load(); }
        const std::string &sessionId() const;
        const Config &config() const { return config_; }

        void startEventStream();

        bool requestPair(const std::string &peer_session_id);
        bool acceptPair(const std::string &peer_session_id);
        bool rejectPair(const std::string &peer_session_id);
        bool unpair(const std::string &peer_session_id);
        bool subscribe(const std::string &publisher_session_id, bool sub_video, bool sub_pose, bool sub_audio);
        bool unsubscribe(const std::string &publisher_session_id);
        std::vector<signaling::UnpairedEndpoint> listUnpaired(signaling::RegisterRequest::EndpointType desired_role);

        bool publishVideoConfig(uint32_t width,
                                uint32_t height,
                                uint32_t fps,
                                Codec codec,
                                const std::vector<uint8_t> &sps,
                                const std::vector<uint8_t> &pps,
                                const std::vector<uint8_t> &vps,
                                bool has_fov,
                                float hfov_deg,
                                float vfov_deg,
                                float dfov_deg);

        bool publishAudioConfig(const AudioConfig &audio_config);
        bool ackAudioConfig(bool success, const std::string &message, const std::string &config_id);

    private:
        void tryRegister();
        void onRegisterRetry();
        void onHeartbeat();
        void startRegisterRetryTimer();
        void startHeartbeatTimer();

        rclcpp::Node &node_;
        rclcpp::Logger logger_;
        Config config_;
        std::unique_ptr<GrpcManager> manager_;

        std::atomic<bool> registered_{false};
        std::atomic<bool> shutting_down_{false};
        uint32_t consecutive_heartbeat_transport_failures_{0};
        rclcpp::TimerBase::SharedPtr register_retry_timer_;
        rclcpp::TimerBase::SharedPtr heartbeat_timer_;

        RegisteredCallback on_registered_;
        SignalingEventCallback on_event_;
        HeartbeatFailCallback on_heartbeat_fail_;
        StreamEndCallback on_stream_end_;
    };

} // namespace trb