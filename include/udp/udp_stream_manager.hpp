#ifndef UDP_STREAM_MANAGER_HPP
#define UDP_STREAM_MANAGER_HPP

#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <cstdint>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "udp/udp_socket.hpp"
#include "udp/udp_packet.hpp"

namespace trb
{
    namespace udp
    {

    class IScreamController;

        class UdpStreamManager
        {
        public:
            UdpStreamManager(const std::string &ip, int port);
            ~UdpStreamManager();

            bool start();
            void stop();
            void sendH264Frame(const std::vector<uint8_t> &frame_data);
            void sendH264Frame(const uint8_t *data, size_t size);

            // Timestamp is expected to be in the same domain as std::chrono::steady_clock
            // (microseconds since steady_clock epoch). This matches VideoStreamManager.
            void sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us);

            // If keyframe==true, the sender may emit extra debug logs for this frame.
            void sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us, bool keyframe);

            void setSessionId(const std::string &session_id);

            // Configure V2 FEC participation.
            // - table_id: currently only 1 is supported.
            // - table_id==0 disables FEC participation (FecTableId=0 on wire).
            void setFecTableId(uint8_t table_id);

            // Enable UDP pacing (smooth sending) and configure target rate.
            // pacing_bps is bits/sec. If disabled, sender will drain queue as fast as possible.
            void setPacingEnabled(bool enabled);
            void setPacingRateBps(uint64_t pacing_bps);

            // Queue limits for smoothing. When exceeded, oldest frames are dropped.
            void setQueueLimits(size_t max_packets, size_t max_bytes);

            // If enabled, UDP send is non-blocking (MSG_DONTWAIT). On EAGAIN, packets are dropped.
            void setSendNonBlocking(bool enabled);

            // Optional: tune socket send buffer (SO_SNDBUF).
            void setSendBufferBytes(int bytes);

            // Optional: stop data-plane sending after N video frames.
            // When enabled and max_frames>0, frames with FrameId >= max_frames will be ignored.
            // When the sender thread finishes the last frame (FrameId=max_frames-1), it prints
            // the total number of successfully-sent UDP packets so far.
            void setStopAfterFramesEnabled(bool enabled);
            void setStopAfterFramesMaxFrames(uint32_t max_frames);

            // Debug/logging: maximum number of UDP packet headers to dump (topic udp_header_once).
            // 0 means unlimited.
            void setHeaderLogMaxPackets(uint64_t max_packets);

            // Optional: receive-side demux for non-video datagrams on the same UDP socket.
            // This is used to reuse the video stream socket for pose datagrams (Type=0x02).
            void setPoseDatagramCallback(std::function<void(const uint8_t *, size_t)> cb);

            // Optional: attach an external SCReAM controller.
            void setScreamController(std::unique_ptr<IScreamController> controller);
            void setScreamEnabled(bool enabled);

        private:
            struct QueueItem
            {
                enum class Kind : uint8_t
                {
                    Datagram = 0,
                    FrameEnd = 1,
                };

                Kind kind{Kind::Datagram};
                uint32_t frame_id{0};
                uint16_t packet_seq_num{0};

                // Datagram payload (header + payload). Used when kind==Datagram.
                std::vector<uint8_t> bytes;
                size_t wire_bytes{0};

                // Frame metadata. Used when kind==FrameEnd.
                uint64_t capture_timestamp_us{0};
                size_t enc_bytes{0};
                uint32_t fragments{0};
                uint32_t groups{0};
                uint32_t protected_packets{0};
                uint32_t parity_pkts{0};
                double payload_overhead_pct{0.0};
                uint64_t data_wire_bytes{0};
                uint64_t wire_extra_bytes{0};
                uint64_t fec_compute_us{0};
            };

            void sendThreadMain();
            void enqueueItem(QueueItem &&item);
            void dropOldestFrameLocked();

            void signalingThreadMain();
            void recvThreadMain();
            uint64_t getCurrentNtpTimestamp();

            std::unique_ptr<UdpSocket> socket_;

            std::function<void(const uint8_t *, size_t)> pose_datagram_cb_;

            UdpPacketBuilder packet_builder_;

            uint8_t fec_table_id_{1};
            std::mutex fec_mutex_;

            std::string ip_;
            int port_;
            std::atomic<bool> is_running_;
            static constexpr size_t kMaxPayloadSize = 1200;

            // Video Protocol State
            uint16_t packet_seq_num_ = 0;
            uint32_t frame_id_ = 0;

            // V2 (group FEC) fields are per-frame in the doc. We keep only the configured ProfileId.

            // Signaling Protocol State
            std::string session_id_;
            std::thread signaling_thread_;
            std::thread recv_thread_;
            std::thread send_thread_;
            std::atomic<bool> signaling_running_;

            // Pacing / queue
            std::atomic<bool> pacing_enabled_{true};
            std::atomic<uint64_t> pacing_bps_{0};
            std::atomic<size_t> queue_max_packets_{1024};
            std::atomic<size_t> queue_max_bytes_{1024 * 1024};

            std::mutex queue_mutex_;
            std::condition_variable queue_cv_;
            std::deque<QueueItem> queue_;
            size_t queue_bytes_{0};
            std::atomic<uint64_t> dropped_frames_{0};

            // Data-plane packet counter since start (successful sendto() calls from send thread).
            std::atomic<uint64_t> sent_total_pkts_{0};

            // Optional: stop sending after N frames.
            std::atomic<bool> stop_after_frames_enabled_{false};
            std::atomic<uint32_t> stop_after_frames_max_frames_{0};
            std::atomic<bool> stop_after_frames_triggered_{false};
            std::atomic<bool> data_plane_halted_{false};

            // Debug: dump UDP packet headers (in producer thread).
            // Controlled by header_log_max_packets_.
            std::atomic<uint64_t> debug_header_printed_{0};
            std::atomic<uint64_t> header_log_max_packets_{8};

            std::atomic<bool> handshake_success_{false};
            std::mutex handshake_mutex_;
            std::condition_variable handshake_cv_;

            std::mutex scream_mutex_;
            std::unique_ptr<IScreamController> scream_controller_;
            std::atomic<bool> scream_enabled_{false};
        };

    } // namespace udp
} // namespace trb

#endif // UDP_STREAM_MANAGER_HPP
