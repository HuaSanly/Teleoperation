#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "telemetry/robot_telemetry_types.hpp"
#include "udp/control_plane.hpp"
#include "udp/fec_interface.hpp"
#include "udp/fec_v2.hpp"
#include "udp/packet_codec.hpp"
#include "udp/pacer.hpp"
#include "udp/send_queue.hpp"
#include "udp/udp_socket.hpp"

namespace trb::udp
{

    class UdpManager
    {
    public:
        struct VideoStatsSnapshot
        {
            uint64_t input_frames{0};
            uint64_t input_bytes{0};
            uint64_t input_drops{0};
            uint64_t queue_drops{0};
            uint64_t send_block_events{0};
            uint64_t send_drop_packets{0};
            uint64_t fec_output_packets{0};
            uint64_t sent_frames{0};
            uint64_t sent_packets{0};
            uint64_t sent_bytes{0};
            uint64_t cap_to_fec_us_total{0};
            uint64_t cap_to_fec_samples{0};
            uint64_t fec_internal_wait_us_total{0};
            uint64_t fec_internal_wait_samples{0};
            uint64_t fec_compute_us_total{0};
            uint64_t fec_compute_samples{0};
            uint64_t send_queue_delay_us_total{0};
            uint64_t send_queue_delay_samples{0};
            uint64_t tail_queue_delay_us_total{0};
            uint64_t tail_queue_delay_samples{0};
            uint64_t pacing_us_total{0};
            uint64_t send_syscall_us_total{0};
            uint64_t end_to_end_us_total{0};
            uint64_t end_to_end_samples{0};
            uint64_t pacer_debt_us{0};
            uint64_t pacer_expected_queue_us{0};
            uint64_t pacer_adjusted_bps{0};
            size_t queue_packets{0};
            size_t queue_bytes{0};
        };

        struct Config
        {
            std::string remote_ip;
            int remote_port{0};
            std::string device_id;
            std::string bind_ip{"0.0.0.0"};
            int bind_port{0};
            bool enable_receive{true};
            bool control_enabled{true};
            double control_hello_interval_sec{1.0};
            double control_ping_interval_sec{5.0};
            double control_peer_lost_timeout_sec{0.0};
            size_t max_payload_bytes{1200};
            bool send_nonblocking{true};
            int recv_timeout_ms{100};
            bool pacing_enabled{true};
            uint64_t pacing_bps{0};
            uint32_t pacing_send_burst_interval_ms{5};
            size_t pacing_max_burst_bytes{63000};
            uint32_t pacing_max_debt_ms{500};
            uint32_t pacing_queue_time_limit_ms{150};
            double pacing_max_drain_multiplier{2.0};
            bool pacing_account_audio{false};
            uint32_t pacing_max_packets_per_batch{64};
            size_t queue_max_bytes{300000};
            size_t queue_max_packets{0};
            uint8_t fec_table_id{1};
            size_t fec_input_queue_max_frames{2};
            int send_buffer_bytes{0};
        };

        struct State
        {
            std::atomic<bool> running{false};
            std::atomic<bool> handshake_ready{false};
        };

        explicit UdpManager(const Config &config);
        ~UdpManager();

        UdpManager(const UdpManager &) = delete;
        UdpManager &operator=(const UdpManager &) = delete;

        bool start();
        void stop();
        void resetSession();

        void setSessionId(const std::string &session_id);
        void setDatagramCallback(const std::function<void(const uint8_t *, size_t)> &callback);
        void setPeerLostCallback(std::function<void()> callback) { control_.setPeerLostCallback(std::move(callback)); }
        void setPacingEnabled(bool enabled);
        void setPacingRateBps(uint64_t bps);
        void setQueueLimits(size_t max_packets, size_t max_bytes);
        void setFecTableId(uint8_t table_id);

        bool isHandshakeReady() const;

        void sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us = 0, bool keyframe = false);
        void sendAudioPacket(const uint8_t *data, size_t size, uint64_t timestamp_ntp);
        void sendRobotTelemetry(const telemetry::RobotTelemetrySnapshot &snapshot);
        void sendRobotJointTelemetry(const telemetry::RobotJointTelemetrySnapshot &snapshot);
        VideoStatsSnapshot consumeVideoStats();

    private:
        struct InputFrame
        {
            std::vector<uint8_t> data;
            uint64_t capture_timestamp_us{0};
            uint64_t ntp_timestamp{0};
            uint64_t enqueue_steady_us{0};
            bool keyframe{false};
        };

        void recvThreadMain();
        void sendThreadMain();
        void fecThreadMain();
        void processFrame(const InputFrame &frame);
        uint64_t currentNtpTimestamp() const;

        Config config_;
        State state_;

        std::unique_ptr<UdpSocket> socket_;
        PacketCodec packet_codec_;
        SendQueue send_queue_;
        WebRtcLikePacer webrtc_like_pacer_;
        ControlPlane control_;
        std::unique_ptr<IFecEncoder> fec_encoder_;
        std::mutex pacing_mutex_;

        std::thread recv_thread_;
        std::thread send_thread_;
        std::thread fec_thread_;

        std::mutex input_mutex_;
        std::condition_variable input_cv_;
        std::deque<InputFrame> input_queue_;

        std::atomic<uint32_t> frame_id_{0};
        std::atomic<uint16_t> packet_seq_num_{0};
        std::atomic<uint32_t> audio_group_id_{0};
        std::atomic<uint16_t> audio_seq_num_{0};
        std::atomic<uint32_t> telemetry_group_id_{0};
        std::atomic<uint16_t> telemetry_seq_num_{0};

        std::atomic<uint64_t> video_input_frames_{0};
        std::atomic<uint64_t> video_input_bytes_{0};
        std::atomic<uint64_t> video_input_drops_{0};
        std::atomic<uint64_t> cap_to_fec_us_total_{0};
        std::atomic<uint64_t> cap_to_fec_samples_{0};
        std::atomic<uint64_t> fec_internal_wait_us_total_{0};
        std::atomic<uint64_t> fec_internal_wait_samples_{0};
        std::atomic<uint64_t> fec_compute_us_total_{0};
        std::atomic<uint64_t> fec_compute_samples_{0};
        std::atomic<uint64_t> fec_output_packets_{0};
        std::atomic<uint64_t> udp_sent_video_frames_{0};
        std::atomic<uint64_t> udp_sent_video_packets_{0};
        std::atomic<uint64_t> udp_sent_video_bytes_{0};
        std::atomic<uint64_t> udp_send_block_events_{0};
        std::atomic<uint64_t> udp_send_drop_packets_{0};
        std::atomic<uint64_t> udp_video_queue_delay_us_total_{0};
        std::atomic<uint64_t> udp_video_queue_delay_samples_{0};
        std::atomic<uint64_t> udp_video_tail_queue_delay_us_total_{0};
        std::atomic<uint64_t> udp_video_tail_queue_delay_samples_{0};
        std::atomic<uint64_t> udp_video_pacing_us_total_{0};
        std::atomic<uint64_t> udp_video_send_syscall_us_total_{0};
        std::atomic<uint64_t> udp_video_end_to_end_us_total_{0};
        std::atomic<uint64_t> udp_video_end_to_end_samples_{0};
        std::atomic<uint64_t> udp_pacer_debt_us_{0};
        std::atomic<uint64_t> udp_pacer_expected_queue_us_{0};
        std::atomic<uint64_t> udp_pacer_adjusted_bps_{0};

        std::string session_id_;
        std::function<void(const uint8_t *, size_t)> datagram_callback_;
    };

} // namespace trb::udp
