#ifndef TRB_UTILS_TELEOP_LOGGER_HPP
#define TRB_UTILS_TELEOP_LOGGER_HPP

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

namespace trb::utils
{

    class TeleopLogger
    {
    public:
        enum class FileTopic : uint32_t
        {
            UdpIFrame = 1u << 0,
            UdpHeaderOnce = 1u << 1,
            UdpHandshake = 1u << 2,
            UdpFrameEnd = 1u << 3,
            H264SpsPps = 1u << 4,
            UdpScreamFeedback = 1u << 5,
            UdpScreamRate = 1u << 6,
        };

        static TeleopLogger &instance();

        // Configure optional file logging. If enabled=false, file sink is closed.
        void configureFileLogging(bool enabled, const std::string &path, uint32_t topic_mask);

        // Helpers
        static uint32_t fileTopicsFromStrings(const std::vector<std::string> &topics, rclcpp::Logger logger);

        void udpHeaderOnce(uint64_t idx,
                           uint8_t type,
                           uint16_t seq,
                           uint64_t ts,
                           uint32_t frame_id,
                           uint16_t frag_index,
                           uint16_t total_frags,
                           uint16_t payload_len,
                           uint32_t frame_len,
                           uint8_t fec_table_id,
                           uint8_t keyframe_flag);

        void udpIFrame(uint32_t frame_id,
                       size_t enc_bytes,
                       uint32_t data_pkts,
                       uint32_t parity_pkts,
                       uint32_t total_pkts,
                       uint8_t fec_table_id,
                       uint8_t groups,
                       uint8_t r);

        void udpHandshake(const std::string &msg);

        void udpFrameEnd(uint32_t frame_id,
                         uint64_t capture_ts_us,
                         size_t enc_bytes,
                         uint32_t data_pkts,
                         uint32_t parity_pkts,
                         double payload_overhead_pct,
                         uint64_t fec_compute_us);

        void udpScreamFeedbackHeader(uint16_t base_seq,
                         uint16_t ack_vector_bits,
                         uint64_t rx_timestamp_ntp);

        void udpScreamRate(uint64_t target_bps,
                   uint64_t pacing_bps);

        // H264 bitstream diagnostics: log every SPS/PPS NAL unit to the optional file sink.
        // nal_unit_type: 7 (SPS) or 8 (PPS)
        void h264SpsPps(uint64_t capture_ts_us,
                        uint32_t frame_id,
                        uint8_t nal_unit_type,
                        const uint8_t *nal,
                        size_t nal_size);

    private:
        TeleopLogger();

        bool shouldWrite(FileTopic topic) const;
        void writeLineLocked(const std::string &line);
        static std::string nowString();

        std::mutex file_mutex_;
        std::string file_path_;
        std::atomic<bool> file_enabled_{false};
        std::atomic<uint32_t> file_topic_mask_{0};

        // Lazy-opened file handle.
        void *file_{nullptr};
    };

} // namespace trb::utils

#endif // TRB_UTILS_TELEOP_LOGGER_HPP
