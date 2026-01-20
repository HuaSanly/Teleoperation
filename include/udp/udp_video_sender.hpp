#pragma once

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "udp/udp_manager.hpp"
#include "udp/udp_packet.hpp"

namespace trb::udp
{

struct UdpVideoSenderConfig
{
    size_t max_payload_bytes{1200};

    bool fec_enabled{true};
    uint8_t fec_table_id{1};

    bool pacing_enabled{true};
    uint64_t pacing_bps{30000000};
    size_t queue_max_packets{1024};
    size_t queue_max_bytes{300000};
};

class UdpVideoSender
{
public:
    explicit UdpVideoSender(UdpVideoSenderConfig config);
    ~UdpVideoSender();

    void setSessionId(const std::string &session_id);

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
            Datagram,
            FrameEnd
        };
        Kind kind{Kind::Datagram};
        uint32_t frame_id{0};
        uint64_t capture_timestamp_us{0};
        size_t enc_bytes{0};
        uint32_t fragments{0};
        std::vector<uint8_t> bytes;
        size_t wire_bytes{0};
    };

    void sendThreadMain();
    void enqueueItem(QueueItem &&item);
    void dropOldestFrameLocked();

    uint64_t getCurrentNtpTimestamp() const;

    UdpVideoSenderConfig config_;
    UdpManager *udp_manager_{nullptr};

    std::atomic<bool> running_{false};
    std::atomic<bool> paused_{false};

    std::thread send_thread_;

    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::deque<QueueItem> queue_;
    size_t queue_bytes_{0};

    UdpPacketBuilder packet_builder_;

    uint16_t packet_seq_num_{0};
    uint32_t frame_id_{0};
};

} // namespace trb::udp
