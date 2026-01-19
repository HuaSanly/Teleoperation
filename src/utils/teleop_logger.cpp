#include "utils/teleop_logger.hpp"

#include <cstdio>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

#include <unistd.h>

namespace trb::utils
{

    namespace
    {
        inline rclcpp::Logger udp_logger()
        {
            return rclcpp::get_logger("teleop_robot_bridge.udp");
        }

        constexpr const char *kTopicUdpIFrame = "udp_iframe";
        constexpr const char *kTopicUdpHeaderOnce = "udp_header_once";
        constexpr const char *kTopicUdpHandshake = "udp_handshake";
        constexpr const char *kTopicUdpFrameEnd = "udp_frame_end";
        constexpr const char *kTopicH264SpsPps = "h264_sps_pps";

        static std::string base64Encode(const uint8_t *data, size_t size)
        {
            static const char kB64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            std::string out;
            out.reserve(((size + 2) / 3) * 4);

            size_t i = 0;
            while (i + 3 <= size)
            {
                const uint32_t v = (static_cast<uint32_t>(data[i]) << 16) |
                                   (static_cast<uint32_t>(data[i + 1]) << 8) |
                                   (static_cast<uint32_t>(data[i + 2]));
                out.push_back(kB64[(v >> 18) & 0x3F]);
                out.push_back(kB64[(v >> 12) & 0x3F]);
                out.push_back(kB64[(v >> 6) & 0x3F]);
                out.push_back(kB64[v & 0x3F]);
                i += 3;
            }

            const size_t rem = size - i;
            if (rem == 1)
            {
                const uint32_t v = (static_cast<uint32_t>(data[i]) << 16);
                out.push_back(kB64[(v >> 18) & 0x3F]);
                out.push_back(kB64[(v >> 12) & 0x3F]);
                out.push_back('=');
                out.push_back('=');
            }
            else if (rem == 2)
            {
                const uint32_t v = (static_cast<uint32_t>(data[i]) << 16) |
                                   (static_cast<uint32_t>(data[i + 1]) << 8);
                out.push_back(kB64[(v >> 18) & 0x3F]);
                out.push_back(kB64[(v >> 12) & 0x3F]);
                out.push_back(kB64[(v >> 6) & 0x3F]);
                out.push_back('=');
            }
            return out;
        }

        static FILE *openAppendFile(const std::string &path, rclcpp::Logger logger)
        {
            if (path.empty())
            {
                RCLCPP_WARN(logger, "File logging enabled but path is empty; disabling file sink");
                return nullptr;
            }

            try
            {
                const std::filesystem::path p(path);
                if (p.has_parent_path())
                {
                    std::filesystem::create_directories(p.parent_path());
                }
            }
            catch (const std::exception &e)
            {
                RCLCPP_WARN(logger, "Failed to create log directory for %s: %s", path.c_str(), e.what());
            }

            FILE *f = std::fopen(path.c_str(), "a");
            if (!f)
            {
                RCLCPP_WARN(logger, "Failed to open log file %s for append", path.c_str());
                return nullptr;
            }

            // Line-buffered: flush on each newline.
            std::setvbuf(f, nullptr, _IOLBF, 0);
            return f;
        }

        static std::string makePerRunLogFilePath(const std::string &path_or_dir, rclcpp::Logger logger)
        {
            std::filesystem::path dir;
            if (path_or_dir.empty())
            {
                return {};
            }

            try
            {
                const std::filesystem::path p(path_or_dir);
                if (std::filesystem::is_directory(p))
                {
                    dir = p;
                }
                else
                {
                    // Backward compatibility: if a file path is provided, use its parent directory.
                    dir = p.has_parent_path() ? p.parent_path() : std::filesystem::path(".");
                }
                std::filesystem::create_directories(dir);
            }
            catch (const std::exception &e)
            {
                RCLCPP_WARN(logger, "Failed to prepare log directory for %s: %s", path_or_dir.c_str(), e.what());
                return {};
            }

            using clock = std::chrono::system_clock;
            const auto now = clock::now();
            const std::time_t tt = clock::to_time_t(now);

            const auto us_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
            const auto us_part = static_cast<long>(us_since_epoch.count() % 1000000);
            std::tm tm{};
#if defined(_WIN32)
            localtime_s(&tm, &tt);
#else
            localtime_r(&tt, &tm);
#endif

            std::ostringstream name;
            name << "trb_" << std::put_time(&tm, "%Y%m%d_%H%M%S")
                 << "_" << std::setw(6) << std::setfill('0') << us_part
                 << "_" << static_cast<long>(::getpid()) << ".log";
            return (dir / name.str()).string();
        }

        static void closeFile(FILE *f)
        {
            if (f)
            {
                std::fclose(f);
            }
        }

        static uint32_t topicBit(const std::string &t)
        {
            if (t == kTopicUdpIFrame)
            {
                return static_cast<uint32_t>(TeleopLogger::FileTopic::UdpIFrame);
            }
            if (t == kTopicUdpHeaderOnce)
            {
                return static_cast<uint32_t>(TeleopLogger::FileTopic::UdpHeaderOnce);
            }
            if (t == kTopicUdpHandshake)
            {
                return static_cast<uint32_t>(TeleopLogger::FileTopic::UdpHandshake);
            }
            if (t == kTopicUdpFrameEnd)
            {
                return static_cast<uint32_t>(TeleopLogger::FileTopic::UdpFrameEnd);
            }
            if (t == kTopicH264SpsPps)
            {
                return static_cast<uint32_t>(TeleopLogger::FileTopic::H264SpsPps);
            }
            return 0;
        }

    } // namespace

    TeleopLogger &TeleopLogger::instance()
    {
        static TeleopLogger inst;
        return inst;
    }

    TeleopLogger::TeleopLogger() = default;

    void TeleopLogger::configureFileLogging(bool enabled, const std::string &path, uint32_t topic_mask)
    {
        std::lock_guard<std::mutex> lk(file_mutex_);

        file_topic_mask_.store(topic_mask, std::memory_order_relaxed);
        file_enabled_.store(enabled, std::memory_order_relaxed);
        file_path_ = path;

        if (!enabled)
        {
            closeFile(reinterpret_cast<FILE *>(file_));
            file_ = nullptr;
            return;
        }

        // Each run uses a fresh file under the target directory.
        closeFile(reinterpret_cast<FILE *>(file_));
        file_ = nullptr;

        const auto logger = rclcpp::get_logger("teleop_robot_bridge.logging");
        const std::string per_run_path = makePerRunLogFilePath(file_path_, logger);
        if (per_run_path.empty())
        {
            RCLCPP_WARN(logger, "Failed to create per-run log file path from '%s'; disabling file sink", file_path_.c_str());
            file_enabled_.store(false, std::memory_order_relaxed);
            return;
        }

        file_path_ = per_run_path;
        file_ = openAppendFile(file_path_, logger);
        if (file_)
        {
            RCLCPP_INFO(logger, "File logging enabled: %s", file_path_.c_str());
        }
    }

    uint32_t TeleopLogger::fileTopicsFromStrings(const std::vector<std::string> &topics, rclcpp::Logger logger)
    {
        uint32_t mask = 0;
        for (const auto &t : topics)
        {
            const uint32_t bit = topicBit(t);
            if (bit == 0)
            {
                RCLCPP_WARN(logger, "Unknown logging.file.topics entry: %s (supported: %s,%s,%s,%s,%s)",
                            t.c_str(),
                            kTopicUdpIFrame,
                            kTopicUdpHeaderOnce,
                            kTopicUdpHandshake,
                            kTopicUdpFrameEnd,
                            kTopicH264SpsPps);
                continue;
            }
            mask |= bit;
        }
        return mask;
    }

    void TeleopLogger::h264SpsPps(uint64_t capture_ts_us,
                                  uint32_t frame_id,
                                  uint8_t nal_unit_type,
                                  const uint8_t *nal,
                                  size_t nal_size)
    {
        if (!shouldWrite(FileTopic::H264SpsPps))
        {
            return;
        }

        if (!nal || nal_size == 0)
        {
            return;
        }

        const char *kind = (nal_unit_type == 7) ? "SPS" : (nal_unit_type == 8) ? "PPS"
                                                                               : "NAL";

        std::lock_guard<std::mutex> lk(file_mutex_);
        std::ostringstream oss;
        oss << nowString() << " [" << kTopicH264SpsPps << "] "
            << "ts_us=" << capture_ts_us
            << " frame_id=" << frame_id
            << " nal_type=" << static_cast<unsigned>(nal_unit_type)
            << " kind=" << kind
            << " bytes=" << nal_size
            << " b64=" << base64Encode(nal, nal_size);
        writeLineLocked(oss.str());
    }

    bool TeleopLogger::shouldWrite(FileTopic topic) const
    {
        if (!file_enabled_.load(std::memory_order_relaxed))
        {
            return false;
        }
        const uint32_t mask = file_topic_mask_.load(std::memory_order_relaxed);
        return (mask & static_cast<uint32_t>(topic)) != 0;
    }

    std::string TeleopLogger::nowString()
    {
        using clock = std::chrono::system_clock;
        const auto now = clock::now();
        const std::time_t tt = clock::to_time_t(now);

        std::tm tm{};
#if defined(_WIN32)
        localtime_s(&tm, &tt);
#else
        localtime_r(&tt, &tm);
#endif

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void TeleopLogger::writeLineLocked(const std::string &line)
    {
        if (!file_enabled_.load(std::memory_order_relaxed))
        {
            return;
        }

        if (!file_)
        {
            file_ = openAppendFile(file_path_, rclcpp::get_logger("teleop_robot_bridge.logging"));
        }
        FILE *f = reinterpret_cast<FILE *>(file_);
        if (!f)
        {
            return;
        }

        std::fputs(line.c_str(), f);
        std::fputc('\n', f);
    }

    void TeleopLogger::udpHeaderOnce(uint64_t idx,
                                     uint8_t type,
                                     uint16_t seq,
                                     uint64_t ts,
                                     uint32_t frame_id,
                                     uint16_t frag_index,
                                     uint16_t total_frags,
                                     uint16_t payload_len,
                                     uint32_t frame_len,
                                     uint8_t fec_table_id)
    {
        if (idx < 8)
        {
            RCLCPP_INFO(
                udp_logger(),
                "UDP hdr[%lu]: type=0x%02X seq=%u ts=%lu frame=%u frag=%u/%u paylen=%u frame_len=%u fec(table=%u)",
                static_cast<unsigned long>(idx),
                static_cast<unsigned>(type),
                static_cast<unsigned>(seq),
                static_cast<unsigned long>(ts),
                static_cast<unsigned>(frame_id),
                static_cast<unsigned>(frag_index),
                static_cast<unsigned>(total_frags),
                static_cast<unsigned>(payload_len),
                static_cast<unsigned>(frame_len),
                static_cast<unsigned>(fec_table_id));
        }

        if (!shouldWrite(FileTopic::UdpHeaderOnce))
        {
            return;
        }

        std::lock_guard<std::mutex> lk(file_mutex_);
        std::ostringstream oss;
        oss << nowString() << " [" << kTopicUdpHeaderOnce << "] "
            << "idx=" << idx
            << " type=0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned>(type) << std::dec
            << " seq=" << seq
            << " ts=" << ts
            << " frame=" << frame_id
            << " frag=" << frag_index << "/" << total_frags
            << " paylen=" << payload_len
            << " frame_len=" << frame_len
            << " fec.table=" << static_cast<unsigned>(fec_table_id);
        writeLineLocked(oss.str());
    }

    void TeleopLogger::udpIFrame(uint32_t frame_id,
                                 size_t enc_bytes,
                                 uint32_t data_pkts,
                                 uint32_t parity_pkts,
                                 uint32_t total_pkts,
                                 uint8_t fec_table_id,
                                 uint8_t groups,
                                 uint8_t r)
    {
        RCLCPP_INFO(
            udp_logger(),
            "I-frame: frame_id=%u enc_bytes=%zu data_pkts=%u parity_pkts=%u total_pkts=%u fec(table=%u groups=%u r=%u)",
            static_cast<unsigned>(frame_id),
            enc_bytes,
            static_cast<unsigned>(data_pkts),
            static_cast<unsigned>(parity_pkts),
            static_cast<unsigned>(total_pkts),
            static_cast<unsigned>(fec_table_id),
            static_cast<unsigned>(groups),
            static_cast<unsigned>(r));

        if (!shouldWrite(FileTopic::UdpIFrame))
        {
            return;
        }

        std::lock_guard<std::mutex> lk(file_mutex_);
        std::ostringstream oss;
        oss << nowString() << " [" << kTopicUdpIFrame << "] "
            << "frame_id=" << frame_id
            << " enc_bytes=" << enc_bytes
            << " data_pkts=" << data_pkts
            << " parity_pkts=" << parity_pkts
            << " total_pkts=" << total_pkts
            << " fec.table=" << static_cast<unsigned>(fec_table_id)
            << " groups=" << static_cast<unsigned>(groups)
            << " r=" << static_cast<unsigned>(r);
        writeLineLocked(oss.str());
    }

    void TeleopLogger::udpHandshake(const std::string &msg)
    {
        RCLCPP_INFO(udp_logger(), "%s", msg.c_str());

        if (!shouldWrite(FileTopic::UdpHandshake))
        {
            return;
        }

        std::lock_guard<std::mutex> lk(file_mutex_);
        std::ostringstream oss;
        oss << nowString() << " [" << kTopicUdpHandshake << "] " << msg;
        writeLineLocked(oss.str());
    }

    void TeleopLogger::udpFrameEnd(uint32_t frame_id,
                                   uint64_t capture_ts_us,
                                   size_t enc_bytes,
                                   uint32_t data_pkts,
                                   uint32_t parity_pkts,
                                   double payload_overhead_pct,
                                   uint64_t fec_compute_us)
    {
        RCLCPP_INFO(
            udp_logger(),
            "FrameEnd: frame_id=%u cap_us=%lu enc_bytes=%zu data_pkts=%u parity_pkts=%u overhead=%.2f%% fec_us=%lu",
            static_cast<unsigned>(frame_id),
            static_cast<unsigned long>(capture_ts_us),
            enc_bytes,
            static_cast<unsigned>(data_pkts),
            static_cast<unsigned>(parity_pkts),
            payload_overhead_pct,
            static_cast<unsigned long>(fec_compute_us));

        if (!shouldWrite(FileTopic::UdpFrameEnd))
        {
            return;
        }

        std::lock_guard<std::mutex> lk(file_mutex_);
        std::ostringstream oss;
        oss << nowString() << " [" << kTopicUdpFrameEnd << "] "
            << "frame_id=" << frame_id
            << " cap_us=" << capture_ts_us
            << " enc_bytes=" << enc_bytes
            << " data_pkts=" << data_pkts
            << " parity_pkts=" << parity_pkts
            << " overhead_pct=" << std::fixed << std::setprecision(2) << payload_overhead_pct
            << " fec_us=" << fec_compute_us;
        writeLineLocked(oss.str());
    }

} // namespace trb::utils
