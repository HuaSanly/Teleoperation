#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "udp/fec_executor.hpp"
#include "udp/udp_packet.hpp"

namespace trb::udp
{

class UdpManager;

struct UdpVideoSenderConfig
{
    size_t max_payload_bytes{1200};
    bool pacing_enabled{true};
    size_t queue_max_bytes{300000};
    int pacing_target_bps{0};
    bool fec_enabled{true};
    uint8_t fec_table_id{1};
    int fec_threads{0};
    int send_threads{1};
};

class UdpVideoSender
{
public:
    explicit UdpVideoSender(UdpVideoSenderConfig config);
    ~UdpVideoSender();

    struct SendStats
    {
        uint64_t sent_frames{0};
        uint64_t dropped_frames{0};
        uint64_t sent_packets{0};
    };

    void setSessionId(const std::string &session_id);

    SendStats getSendStats() const;

    bool start(UdpManager *udp_manager);
    void stop();

    void pause();
    void resume();

    void sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us, bool keyframe);

private:
    struct QueueItem
    {
        enum class Kind
        {
            Frame,
            Datagram
        };

        Kind kind{Kind::Frame};
        uint32_t frame_id{0};
        std::vector<uint8_t> bytes;
        size_t wire_bytes{0};
        uint64_t capture_timestamp_us{0};
        size_t enc_bytes{0};
        uint16_t fragments{0};
        uint64_t frame_duration_us{0};
        bool keyframe{false};
    };

    void enqueueItem(QueueItem &&item);
    void dropOldestFrameLocked();
    void sendThreadMain();
    uint64_t getCurrentNtpTimestamp() const;

    UdpVideoSenderConfig config_{};
    UdpPacketBuilder packet_builder_;
    UdpManager *udp_manager_{nullptr};

    std::atomic<bool> running_{false};
    std::atomic<bool> paused_{false};

    std::vector<std::thread> send_threads_;
    std::unique_ptr<FecExecutor> fec_executor_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::deque<QueueItem> queue_;
    size_t queue_bytes_{0};

    std::mutex pacing_mutex_;
    double pacing_budget_bytes_{0.0};
    std::chrono::steady_clock::time_point pacing_last_tp_{};

    uint32_t frame_id_{0};
    std::atomic<uint16_t> packet_seq_num_{0};
    uint64_t last_capture_ts_us_{0};
    std::atomic<uint64_t> dropped_frames_since_log_{0};
    std::atomic<uint64_t> sent_frames_{0};
    std::atomic<uint64_t> dropped_frames_{0};
    std::atomic<uint64_t> sent_packets_{0};
};

} // namespace trb::udp
