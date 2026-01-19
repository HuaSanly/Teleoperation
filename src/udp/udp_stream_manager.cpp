#include "udp/udp_stream_manager.hpp"
#include "udp/gf256.hpp"
#include "utils/teleop_logger.hpp"
#include <array>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <cerrno>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <mutex>

#include "rclcpp/rclcpp.hpp"
#include <inttypes.h>

namespace trb
{
    namespace udp
    {

        namespace
        {
            inline rclcpp::Logger udp_logger()
            {
                return rclcpp::get_logger("teleop_robot_bridge.udp");
            }

            inline void logHeaderOnce(const VideoPacketHeaderV2 &h, uint64_t idx)
            {
                trb::utils::TeleopLogger::instance().udpHeaderOnce(
                    idx,
                    static_cast<uint8_t>(h.Type),
                    h.PacketSeqNum,
                    static_cast<uint64_t>(h.Timestamp),
                    h.FrameId,
                    h.FragmentIndex,
                    h.TotalFragments,
                    h.PayloadLength,
                    h.FramePayloadLength,
                    h.FecTableId);
            }

            inline uint32_t coveredSources(uint16_t total_fragments, uint8_t k)
            {
                if (k == 0)
                {
                    return 0;
                }
                return (static_cast<uint32_t>(total_fragments) / static_cast<uint32_t>(k)) * static_cast<uint32_t>(k);
            }

            inline double usToMs(int64_t us)
            {
                return (us >= 0) ? (static_cast<double>(us) / 1000.0) : -1.0;
            }

            struct V2FecParams
            {
                uint8_t groups{0};
                uint8_t r{0};
            };

            struct V2FecTable
            {
                std::array<uint8_t, 256> groups_by_n{};
                std::array<uint8_t, 256> r_by_n{};
                bool loaded{false};
                std::string source_path;
            };

            inline bool parseIntAfterColon(const std::string &s, size_t &pos, int &out)
            {
                const size_t colon = s.find(':', pos);
                if (colon == std::string::npos)
                {
                    return false;
                }
                size_t i = colon + 1;
                while (i < s.size() && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n'))
                {
                    ++i;
                }
                bool neg = false;
                if (i < s.size() && s[i] == '-')
                {
                    neg = true;
                    ++i;
                }
                if (i >= s.size() || s[i] < '0' || s[i] > '9')
                {
                    return false;
                }
                long v = 0;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9')
                {
                    v = v * 10 + (s[i] - '0');
                    ++i;
                }
                out = static_cast<int>(neg ? -v : v);
                pos = i;
                return true;
            }

            inline bool loadV2FecTableFromJsonText(const std::string &text, V2FecTable &out, rclcpp::Logger logger)
            {
                // This is a lightweight parser tailored for config/UDP_VIDEO_FEC_TABLE_V1(1).json.
                // Expected entries under "plans": [{"n":0,"groupCount":1,"parityCount":0}, ...]
                out.groups_by_n.fill(0);
                out.r_by_n.fill(0);

                size_t pos = 0;
                int parsed = 0;
                while (true)
                {
                    const size_t n_key = text.find("\"n\"", pos);
                    if (n_key == std::string::npos)
                    {
                        break;
                    }
                    pos = n_key + 3;

                    int n = 0;
                    if (!parseIntAfterColon(text, pos, n))
                    {
                        break;
                    }

                    const size_t g_key = text.find("\"groupCount\"", pos);
                    if (g_key == std::string::npos)
                    {
                        break;
                    }
                    pos = g_key + 12;
                    int group_count = 0;
                    if (!parseIntAfterColon(text, pos, group_count))
                    {
                        break;
                    }

                    const size_t p_key = text.find("\"parityCount\"", pos);
                    if (p_key == std::string::npos)
                    {
                        break;
                    }
                    pos = p_key + 13;
                    int parity_count = 0;
                    if (!parseIntAfterColon(text, pos, parity_count))
                    {
                        break;
                    }

                    if (n >= 0 && n < 256)
                    {
                        if (parity_count <= 0)
                        {
                            out.groups_by_n[static_cast<size_t>(n)] = 0;
                            out.r_by_n[static_cast<size_t>(n)] = 0;
                        }
                        else
                        {
                            const int g = std::max(0, std::min(255, group_count));
                            const int r = std::max(0, std::min(255, parity_count));
                            out.groups_by_n[static_cast<size_t>(n)] = static_cast<uint8_t>(g);
                            out.r_by_n[static_cast<size_t>(n)] = static_cast<uint8_t>(r);
                        }
                    }
                    ++parsed;
                }

                if (parsed <= 0)
                {
                    RCLCPP_WARN(logger, "FEC table JSON parsed 0 entries; disabling FEC table");
                    return false;
                }
                return true;
            }

            inline bool loadV2FecTableFromJsonFile(const std::filesystem::path &path, V2FecTable &out, rclcpp::Logger logger)
            {
                std::ifstream ifs(path);
                if (!ifs.is_open())
                {
                    return false;
                }
                std::string text((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
                if (text.empty())
                {
                    return false;
                }
                if (!loadV2FecTableFromJsonText(text, out, logger))
                {
                    return false;
                }
                out.source_path = path.string();
                return true;
            }

            inline const V2FecTable &getV2FecTable()
            {
                static V2FecTable table;
                static std::once_flag once;
                static std::atomic<bool> logged{false};
                std::call_once(once, []()
                               {
                                   const auto logger = rclcpp::get_logger("teleop_robot_bridge.udp");

                                   // Candidate locations (dev + common launch cwd patterns).
                                   const std::string filename = "UDP_VIDEO_FEC_TABLE_V1(1).json";
                                   std::vector<std::filesystem::path> candidates;
                                   candidates.emplace_back(std::filesystem::path("config") / filename);
                                   candidates.emplace_back(std::filesystem::path("teleop_robot_bridge") / "config" / filename);
                                   candidates.emplace_back(std::filesystem::path("src") / "teleop_robot_bridge" / "config" / filename);

                                   // Try path relative to this translation unit (useful in dev workspaces).
                                   try
                                   {
                                       const std::filesystem::path this_file(__FILE__);
                                       const auto maybe_pkg = this_file.parent_path().parent_path().parent_path();
                                       candidates.emplace_back(maybe_pkg / "config" / filename);
                                   }
                                   catch (...)
                                   {
                                   }

                                   for (const auto &p : candidates)
                                   {
                                       if (loadV2FecTableFromJsonFile(p, table, logger))
                                       {
                                           table.loaded = true;
                                           return;
                                       }
                                   }

                                   table.loaded = false; });

                if (!logged.exchange(true))
                {
                    if (table.loaded)
                    {
                        RCLCPP_INFO(udp_logger(), "Loaded FEC table from %s", table.source_path.c_str());
                    }
                    else
                    {
                        RCLCPP_WARN(udp_logger(), "Failed to load FEC table JSON; FEC will be disabled (table_id=1)");
                    }
                }
                return table;
            }

            inline bool lookupV2FecParams(uint8_t table_id, uint16_t total_fragments, V2FecParams &out)
            {
                out = V2FecParams{};
                if (table_id == 0)
                {
                    return false;
                }
                // Current implementation supports only TableId=1 (V2 implicit grouping strategy).
                if (table_id != 1)
                {
                    return false;
                }
                if (total_fragments >= 256)
                {
                    // Strategy doc provides a suggestion for N>=256 but the V2 header uses uint16.
                    // Keep it disabled for now to avoid mismatched expectations.
                    return false;
                }

                const auto &table = getV2FecTable();
                if (!table.loaded)
                {
                    return false;
                }

                const uint8_t g = table.groups_by_n[static_cast<size_t>(total_fragments)];
                const uint8_t r = table.r_by_n[static_cast<size_t>(total_fragments)];
                if (g == 0 || r == 0)
                {
                    return false;
                }
                out.groups = g;
                out.r = r;
                return true;
            }
        }

        UdpStreamManager::UdpStreamManager(const std::string &ip, int port)
            : packet_builder_(kMaxPayloadSize), ip_(ip), port_(port), is_running_(false), signaling_running_(false)
        {
            socket_ = std::make_unique<UdpSocket>(ip, port);
        }

        UdpStreamManager::~UdpStreamManager()
        {
            stop();
        }

        bool UdpStreamManager::start()
        {
            if (!socket_->open())
            {
                return false;
            }
            is_running_ = true;
            signaling_running_ = true;
            recv_thread_ = std::thread(&UdpStreamManager::recvThreadMain, this);
            signaling_thread_ = std::thread(&UdpStreamManager::signalingThreadMain, this);
            send_thread_ = std::thread(&UdpStreamManager::sendThreadMain, this);
            return true;
        }

        void UdpStreamManager::stop()
        {
            is_running_ = false;
            signaling_running_ = false;

            {
                std::lock_guard<std::mutex> lk(queue_mutex_);
                queue_.clear();
                queue_bytes_ = 0;
            }
            queue_cv_.notify_all();

            if (send_thread_.joinable())
            {
                send_thread_.join();
            }
            if (signaling_thread_.joinable())
            {
                signaling_thread_.join();
            }
            if (recv_thread_.joinable())
            {
                recv_thread_.join();
            }
        }

        void UdpStreamManager::setPacingEnabled(bool enabled)
        {
            pacing_enabled_.store(enabled);
            queue_cv_.notify_all();
        }

        void UdpStreamManager::setPacingRateBps(uint64_t pacing_bps)
        {
            pacing_bps_.store(pacing_bps);
            queue_cv_.notify_all();
        }

        void UdpStreamManager::setQueueLimits(size_t max_packets, size_t max_bytes)
        {
            queue_max_packets_.store(max_packets);
            queue_max_bytes_.store(max_bytes);
            queue_cv_.notify_all();
        }

        void UdpStreamManager::setSendNonBlocking(bool enabled)
        {
            if (socket_)
            {
                socket_->setSendNonBlocking(enabled);
            }
        }

        void UdpStreamManager::setSendBufferBytes(int bytes)
        {
            if (socket_)
            {
                socket_->setSendBufferBytes(bytes);
            }
        }

        void UdpStreamManager::setStopAfterFramesEnabled(bool enabled)
        {
            stop_after_frames_enabled_.store(enabled, std::memory_order_relaxed);
            if (!enabled)
            {
                stop_after_frames_triggered_.store(false, std::memory_order_relaxed);
                data_plane_halted_.store(false, std::memory_order_relaxed);
            }
        }

        void UdpStreamManager::setStopAfterFramesMaxFrames(uint32_t max_frames)
        {
            stop_after_frames_max_frames_.store(max_frames, std::memory_order_relaxed);
            if (max_frames == 0)
            {
                // Treat 0 as "no limit".
                stop_after_frames_triggered_.store(false, std::memory_order_relaxed);
                data_plane_halted_.store(false, std::memory_order_relaxed);
            }
        }

        void UdpStreamManager::setHeaderLogMaxPackets(uint64_t max_packets)
        {
            header_log_max_packets_.store(max_packets, std::memory_order_relaxed);
            // Reset index so changing the parameter takes effect immediately.
            debug_header_printed_.store(0, std::memory_order_relaxed);
        }

        void UdpStreamManager::setSessionId(const std::string &session_id)
        {
            session_id_ = session_id;
            packet_builder_.setSessionId(session_id);
        }

        void UdpStreamManager::setFecTableId(uint8_t table_id)
        {
            std::lock_guard<std::mutex> lk(fec_mutex_);
            fec_table_id_ = table_id;
        }

        void UdpStreamManager::sendH264Frame(const std::vector<uint8_t> &frame_data)
        {
            sendH264Frame(frame_data.data(), frame_data.size(), 0, false);
        }

        void UdpStreamManager::sendH264Frame(const uint8_t *data, size_t size)
        {
            sendH264Frame(data, size, 0, false);
        }

        void UdpStreamManager::sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us)
        {
            sendH264Frame(data, size, capture_timestamp_us, false);
        }

        void UdpStreamManager::sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us, bool keyframe)
        {
            if (!is_running_ || !handshake_success_)
            {
                return;
            }

            if (data_plane_halted_.load(std::memory_order_relaxed))
            {
                return;
            }

            const bool stop_enabled = stop_after_frames_enabled_.load(std::memory_order_relaxed);
            const uint32_t max_frames = stop_after_frames_max_frames_.load(std::memory_order_relaxed);
            // frame_id_ is the next FrameId to assign.
            if (stop_enabled && max_frames > 0 && frame_id_ >= max_frames)
            {
                return;
            }

            const uint16_t total_fragments = static_cast<uint16_t>((size + kMaxPayloadSize - 1) / kMaxPayloadSize);

            uint8_t fec_table_id = 0;
            {
                std::lock_guard<std::mutex> lk(fec_mutex_);
                fec_table_id = fec_table_id_;
            }

            V2FecParams fec_params;
            const bool fec_strategy_enabled = lookupV2FecParams(fec_table_id, total_fragments, fec_params);
            const uint8_t groups = fec_strategy_enabled ? fec_params.groups : 0;
            const uint8_t r_per_group = fec_strategy_enabled ? fec_params.r : 0;

            const uint32_t current_frame_id = frame_id_++;
            const uint64_t timestamp = getCurrentNtpTimestamp();

            uint64_t fec_compute_us = 0;
            uint32_t parity_packets = 0;

            // Cached Cauchy coefficient matrices by (k,r).
            auto getCoef = [](uint8_t k, uint8_t r) -> const std::vector<uint8_t> &
            {
                struct Cache
                {
                    std::mutex mu;
                    std::unordered_map<uint32_t, std::vector<uint8_t>> m;
                };
                static Cache cache;

                const uint32_t key = (static_cast<uint32_t>(k) << 8) | static_cast<uint32_t>(r);
                {
                    std::lock_guard<std::mutex> lk(cache.mu);
                    auto it = cache.m.find(key);
                    if (it != cache.m.end())
                    {
                        return it->second;
                    }
                }

                std::vector<uint8_t> coef;
                coef.resize(static_cast<size_t>(k) * static_cast<size_t>(r), 0);
                for (uint8_t j = 0; j < r; ++j)
                {
                    for (uint8_t i = 0; i < k; ++i)
                    {
                        const uint8_t x = i;
                        const uint8_t y = static_cast<uint8_t>(0x80u + static_cast<uint8_t>(j));
                        coef[static_cast<size_t>(j) * static_cast<size_t>(k) + static_cast<size_t>(i)] = gf256::inv(static_cast<uint8_t>(x ^ y));
                    }
                }

                std::lock_guard<std::mutex> lk(cache.mu);
                auto [it, _] = cache.m.emplace(key, std::move(coef));
                return it->second;
            };

            std::vector<uint8_t> packet;
            packet.reserve(64 + kMaxPayloadSize);

            auto enqueueSource = [&](uint16_t frag_idx)
            {
                const size_t offset = static_cast<size_t>(frag_idx) * kMaxPayloadSize;
                const size_t chunk_size = std::min(kMaxPayloadSize, size - offset);

                VideoPacketHeaderV2 header;
                header.Type = 0x01;
                header.PacketSeqNum = packet_seq_num_++;
                header.Timestamp = timestamp;
                header.FrameId = current_frame_id;
                header.FragmentIndex = frag_idx;
                header.TotalFragments = total_fragments;
                header.PayloadLength = static_cast<uint16_t>(chunk_size);
                header.FramePayloadLength = static_cast<uint32_t>(size);

                if (fec_strategy_enabled)
                {
                    header.FecTableId = fec_table_id;
                }
                else
                {
                    header.FecTableId = 0;
                }

                packet_builder_.buildVideoPacket(header, data + offset, chunk_size, packet);

                const uint64_t max_headers = header_log_max_packets_.load(std::memory_order_relaxed);
                const uint64_t idx = debug_header_printed_.fetch_add(1, std::memory_order_relaxed);
                if (max_headers == 0 || idx < max_headers)
                {
                    logHeaderOnce(header, idx);
                }

                QueueItem qi;
                qi.kind = QueueItem::Kind::Datagram;
                qi.frame_id = current_frame_id;
                qi.bytes = packet;
                qi.wire_bytes = packet.size();
                enqueueItem(std::move(qi));
            };

            if (!fec_strategy_enabled)
            {
                // No FEC: just send sources in order.
                for (uint16_t i = 0; i < total_fragments; ++i)
                {
                    enqueueSource(i);
                }
            }
            else
            {
                // FEC enabled: send sources in group-interleaved rounds,
                // and distribute parity packets evenly across rounds to reduce burst-loss sensitivity.
                const size_t symbol_bytes = static_cast<size_t>(kMaxPayloadSize);

                // Precompute per-group k and coefficient pointers.
                std::vector<uint8_t> k_by_group;
                k_by_group.resize(groups, 0);
                std::vector<const std::vector<uint8_t> *> coef_by_group;
                coef_by_group.resize(groups, nullptr);

                uint16_t rounds = 0;
                for (uint8_t g = 0; g < groups; ++g)
                {
                    uint8_t k_g = 0;
                    for (uint32_t idx = g; idx < total_fragments; idx += groups)
                    {
                        ++k_g;
                    }
                    k_by_group[g] = k_g;
                    if (k_g > 0 && r_per_group > 0)
                    {
                        coef_by_group[g] = &getCoef(k_g, r_per_group);
                    }
                    rounds = std::max<uint16_t>(rounds, static_cast<uint16_t>(k_g));
                }
                if (rounds == 0)
                {
                    rounds = 1;
                }

                auto enqueueParity = [&](uint8_t g, uint8_t p)
                {
                    const uint8_t k_g = k_by_group[g];
                    if (k_g == 0)
                    {
                        return;
                    }
                    const auto *coef_ptr = coef_by_group[g];
                    if (coef_ptr == nullptr)
                    {
                        return;
                    }

                    std::vector<uint8_t> parity(symbol_bytes, 0);
                    const uint8_t *coef_row = coef_ptr->data() + static_cast<size_t>(p) * static_cast<size_t>(k_g);

                    uint8_t local_i = 0;
                    for (uint32_t src_idx = g; src_idx < total_fragments; src_idx += groups)
                    {
                        const size_t offset = static_cast<size_t>(src_idx) * kMaxPayloadSize;
                        const size_t chunk_size = std::min(kMaxPayloadSize, size - offset);
                        const uint8_t c = coef_row[local_i++];
                        gf256::mulAdd(c, data + offset, parity.data(), chunk_size);
                    }

                    VideoPacketHeaderV2 parity_header;
                    parity_header.Type = 0x01;
                    parity_header.PacketSeqNum = packet_seq_num_++;
                    parity_header.Timestamp = timestamp;
                    parity_header.FrameId = current_frame_id;
                    parity_header.TotalFragments = total_fragments;
                    parity_header.FramePayloadLength = static_cast<uint32_t>(size);
                    parity_header.PayloadLength = static_cast<uint16_t>(symbol_bytes);
                    parity_header.FecTableId = fec_table_id;

                    const uint32_t frag_index = static_cast<uint32_t>(total_fragments) + static_cast<uint32_t>(g) + static_cast<uint32_t>(p) * static_cast<uint32_t>(groups);
                    parity_header.FragmentIndex = static_cast<uint16_t>(frag_index & 0xFFFFu);

                    packet_builder_.buildVideoPacket(parity_header, parity.data(), symbol_bytes, packet);

                    const uint64_t max_headers = header_log_max_packets_.load(std::memory_order_relaxed);
                    const uint64_t idx = debug_header_printed_.fetch_add(1, std::memory_order_relaxed);
                    if (max_headers == 0 || idx < max_headers)
                    {
                        logHeaderOnce(parity_header, idx);
                    }

                    QueueItem pq;
                    pq.kind = QueueItem::Kind::Datagram;
                    pq.frame_id = current_frame_id;
                    pq.bytes = packet;
                    pq.wire_bytes = packet.size();
                    enqueueItem(std::move(pq));
                    ++parity_packets;
                };

                const uint32_t parity_total = static_cast<uint32_t>(groups) * static_cast<uint32_t>(r_per_group);
                uint32_t parity_cursor = 0;
                uint32_t parity_acc = 0;

                const auto fec0 = std::chrono::steady_clock::now();

                for (uint16_t t = 0; t < rounds; ++t)
                {
                    // Source round: one per group if exists.
                    for (uint16_t g = 0; g < groups; ++g)
                    {
                        const uint32_t idx = static_cast<uint32_t>(g) + static_cast<uint32_t>(t) * static_cast<uint32_t>(groups);
                        if (idx < total_fragments)
                        {
                            enqueueSource(static_cast<uint16_t>(idx));
                        }
                    }

                    // Parity scheduling (even distribution across rounds).
                    // Bresenham-like: after each source round, emit 0..N parity packets.
                    parity_acc += parity_total;
                    while (parity_cursor < parity_total && parity_acc >= static_cast<uint32_t>(rounds))
                    {
                        parity_acc -= static_cast<uint32_t>(rounds);

                        const uint8_t p = static_cast<uint8_t>(parity_cursor / static_cast<uint32_t>(groups));
                        const uint8_t g = static_cast<uint8_t>(parity_cursor % static_cast<uint32_t>(groups));
                        enqueueParity(g, p);
                        ++parity_cursor;
                    }
                }

                // Flush any remaining parity.
                while (parity_cursor < parity_total)
                {
                    const uint8_t p = static_cast<uint8_t>(parity_cursor / static_cast<uint32_t>(groups));
                    const uint8_t g = static_cast<uint8_t>(parity_cursor % static_cast<uint32_t>(groups));
                    enqueueParity(g, p);
                    ++parity_cursor;
                }

                const auto fec1 = std::chrono::steady_clock::now();
                fec_compute_us += static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(fec1 - fec0).count());
            }

            if (keyframe)
            {
                const uint32_t data_pkts = static_cast<uint32_t>(total_fragments);
                const uint32_t parity_pkts = parity_packets;
                const uint32_t total_pkts = data_pkts + parity_pkts;

                trb::utils::TeleopLogger::instance().udpIFrame(
                    current_frame_id,
                    size,
                    data_pkts,
                    parity_pkts,
                    total_pkts,
                    static_cast<uint8_t>(fec_strategy_enabled ? fec_table_id : 0),
                    static_cast<uint8_t>(fec_strategy_enabled ? groups : 0),
                    static_cast<uint8_t>(fec_strategy_enabled ? r_per_group : 0));
            }

            // Frame-end marker.
            {
                constexpr size_t kVideoHeaderBytes = 26; // HeaderV2 (new) (implicit grouping)
                const uint32_t data_packets = total_fragments;
                const uint32_t protected_source_packets = fec_strategy_enabled ? data_packets : 0;

                const uint64_t data_payload_bytes = static_cast<uint64_t>(size);
                const uint64_t parity_payload_bytes = static_cast<uint64_t>(parity_packets) * static_cast<uint64_t>(kMaxPayloadSize);

                const uint64_t data_wire_bytes = static_cast<uint64_t>(data_packets) * kVideoHeaderBytes + data_payload_bytes;
                const uint64_t parity_wire_bytes = static_cast<uint64_t>(parity_packets) * (kVideoHeaderBytes + static_cast<uint64_t>(kMaxPayloadSize));

                const double payload_overhead_pct = (data_payload_bytes > 0)
                                                        ? (100.0 * static_cast<double>(parity_payload_bytes) / static_cast<double>(data_payload_bytes))
                                                        : 0.0;

                QueueItem end;
                end.kind = QueueItem::Kind::FrameEnd;
                end.frame_id = current_frame_id;
                end.capture_timestamp_us = capture_timestamp_us;
                end.enc_bytes = size;
                end.fragments = data_packets;
                end.groups = fec_strategy_enabled ? groups : 0;
                end.protected_packets = protected_source_packets;
                end.parity_pkts = parity_packets;
                end.payload_overhead_pct = payload_overhead_pct;
                end.data_wire_bytes = data_wire_bytes;
                end.wire_extra_bytes = parity_wire_bytes;
                end.fec_compute_us = fec_compute_us;
                enqueueItem(std::move(end));
            }
        }

        void UdpStreamManager::enqueueItem(QueueItem &&item)
        {
            std::unique_lock<std::mutex> lk(queue_mutex_);

            if (item.kind == QueueItem::Kind::Datagram)
            {
                queue_bytes_ += item.wire_bytes;
            }

            queue_.push_back(std::move(item));

            const size_t max_packets = queue_max_packets_.load();
            const size_t max_bytes = queue_max_bytes_.load();

            while (!queue_.empty() &&
                   ((max_packets > 0 && queue_.size() > max_packets) || (max_bytes > 0 && queue_bytes_ > max_bytes)))
            {
                dropOldestFrameLocked();
            }

            lk.unlock();
            queue_cv_.notify_one();
        }

        void UdpStreamManager::dropOldestFrameLocked()
        {
            if (queue_.empty())
            {
                return;
            }

            const uint32_t drop_frame_id = queue_.front().frame_id;
            bool seen_end = false;
            while (!queue_.empty() && queue_.front().frame_id == drop_frame_id)
            {
                QueueItem &front = queue_.front();
                if (front.kind == QueueItem::Kind::Datagram)
                {
                    if (queue_bytes_ >= front.wire_bytes)
                    {
                        queue_bytes_ -= front.wire_bytes;
                    }
                    else
                    {
                        queue_bytes_ = 0;
                    }
                }
                if (front.kind == QueueItem::Kind::FrameEnd)
                {
                    seen_end = true;
                }
                queue_.pop_front();
            }

            if (seen_end)
            {
                dropped_frames_.fetch_add(1);
            }
        }

        void UdpStreamManager::sendThreadMain()
        {
            using clock = std::chrono::steady_clock;
            auto toSteadyUs = [](const clock::time_point &tp) -> int64_t
            {
                return std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()).count();
            };

            // Pacing state (virtual clock). Ensures packets are spread out instead of burst.
            clock::time_point next_send_tp = clock::now();

            struct FrameSendStats
            {
                bool active{false};
                uint32_t frame_id{0};
                clock::time_point first_send_begin{};
                clock::time_point last_send_end{};
                uint64_t pacing_sleep_us{0};
                uint64_t send_calls_us{0};
                uint64_t send_max_us{0};
                uint32_t send_failures{0};
                uint32_t send_eagain_drops{0};
                int send_last_errno{0};
            } stats;

            while (is_running_)
            {
                QueueItem item;
                {
                    std::unique_lock<std::mutex> lk(queue_mutex_);
                    queue_cv_.wait_for(lk, std::chrono::milliseconds(10), [this]
                                       { return !queue_.empty() || !is_running_; });
                    if (!is_running_)
                    {
                        break;
                    }
                    if (queue_.empty())
                    {
                        continue;
                    }
                    item = std::move(queue_.front());
                    if (item.kind == QueueItem::Kind::Datagram)
                    {
                        if (queue_bytes_ >= item.wire_bytes)
                        {
                            queue_bytes_ -= item.wire_bytes;
                        }
                        else
                        {
                            queue_bytes_ = 0;
                        }
                    }
                    queue_.pop_front();
                }

                // If data-plane is halted, drop queued items without sending.
                if (data_plane_halted_.load(std::memory_order_relaxed))
                {
                    if (item.kind == QueueItem::Kind::FrameEnd)
                    {
                        stats = FrameSendStats{};
                    }
                    continue;
                }

                const bool pacing_enabled = pacing_enabled_.load();
                const uint64_t pacing_bps = pacing_bps_.load();
                const double rate_bytes_per_sec = (pacing_enabled && pacing_bps > 0)
                                                      ? (static_cast<double>(pacing_bps) / 8.0)
                                                      : 0.0;

                if (rate_bytes_per_sec <= 0.0)
                {
                    next_send_tp = clock::now();
                }

                if (item.kind == QueueItem::Kind::Datagram)
                {
                    if (!stats.active || stats.frame_id != item.frame_id)
                    {
                        stats = FrameSendStats{};
                        stats.active = true;
                        stats.frame_id = item.frame_id;
                    }

                    // Strict pacing: schedule each packet at next_send_tp.
                    if (rate_bytes_per_sec > 0.0)
                    {
                        auto now = clock::now();
                        if (next_send_tp < now)
                        {
                            next_send_tp = now;
                        }

                        if (next_send_tp > now)
                        {
                            std::this_thread::sleep_until(next_send_tp);
                            const auto after_sleep = clock::now();
                            const uint64_t slept_us = static_cast<uint64_t>(
                                std::chrono::duration_cast<std::chrono::microseconds>(after_sleep - now).count());
                            stats.pacing_sleep_us += slept_us;
                        }

                        // Advance virtual clock by packet serialization time.
                        const double pkt_us_d = (static_cast<double>(item.wire_bytes) * 1e6) / rate_bytes_per_sec;
                        const uint64_t pkt_us = static_cast<uint64_t>(std::max(0.0, std::ceil(pkt_us_d)));
                        next_send_tp += std::chrono::microseconds(pkt_us);
                    }

                    const auto s0 = clock::now();
                    const int rc = socket_->send(item.bytes.data(), item.bytes.size());
                    const auto s1 = clock::now();

                    if (rc >= 0)
                    {
                        sent_total_pkts_.fetch_add(1, std::memory_order_relaxed);
                    }
                    if (stats.send_calls_us == 0)
                    {
                        stats.first_send_begin = s0;
                    }
                    stats.last_send_end = s1;

                    const uint64_t us = static_cast<uint64_t>(
                        std::chrono::duration_cast<std::chrono::microseconds>(s1 - s0).count());
                    stats.send_calls_us += us;
                    stats.send_max_us = std::max(stats.send_max_us, us);
                    if (rc < 0)
                    {
                        const int e = errno;
                        // Non-blocking socket will report transient congestion as EAGAIN/EWOULDBLOCK.
                        if (e == EAGAIN || e == EWOULDBLOCK)
                        {
                            ++stats.send_eagain_drops;
                        }
                        else
                        {
                            ++stats.send_failures;
                            stats.send_last_errno = e;
                        }
                    }
                }
                else // FrameEnd
                {
                    const bool have_stats = stats.active && stats.frame_id == item.frame_id && stats.send_calls_us > 0;
                    const auto frame_end_tp = have_stats ? stats.last_send_end : clock::now();
                    const auto frame_begin_tp = have_stats ? stats.first_send_begin : frame_end_tp;

                    const uint64_t frame_total_us = static_cast<uint64_t>(
                        std::chrono::duration_cast<std::chrono::microseconds>(frame_end_tp - frame_begin_tp).count());

                    const int64_t send_begin_us = toSteadyUs(frame_begin_tp);
                    const int64_t send_end_us = toSteadyUs(frame_end_tp);
                    const int64_t upstream_us = (item.capture_timestamp_us != 0)
                                                    ? (send_begin_us - static_cast<int64_t>(item.capture_timestamp_us))
                                                    : -1;
                    const int64_t e2e_us = (item.capture_timestamp_us != 0)
                                               ? (send_end_us - static_cast<int64_t>(item.capture_timestamp_us))
                                               : -1;

                    // Match encoder cadence: print once every 30 frames.
                    if ((item.frame_id % 30) == 0)
                    {
                        const uint64_t pacing_sleep_us = have_stats ? stats.pacing_sleep_us : 0;
                        const uint64_t send_max_us = have_stats ? stats.send_max_us : 0;
                        const uint32_t send_eagain = have_stats ? stats.send_eagain_drops : 0;
                        const uint32_t send_fail = have_stats ? stats.send_failures : 0;
                        const int send_errno = have_stats ? stats.send_last_errno : 0;

                        RCLCPP_INFO(
                            udp_logger(),
                            "UDP frame=%u: e2e=%.1fms (up=%.1fms, send=%.1fms, pacing=%.1fms), pkts=%u (+fec %u), eagain=%u, fail=%u(errno=%d), sent_total=%" PRIu64 ", dropped_frames=%" PRIu64,
                            item.frame_id,
                            usToMs(e2e_us),
                            usToMs(upstream_us),
                            static_cast<double>(frame_total_us - pacing_sleep_us) / 1000.0,
                            static_cast<double>(pacing_sleep_us) / 1000.0,
                            item.fragments,
                            item.parity_pkts,
                            send_eagain,
                            send_fail,
                            send_errno,
                            sent_total_pkts_.load(std::memory_order_relaxed),
                            dropped_frames_.load());

                        if (send_eagain > 0)
                        {
                            RCLCPP_WARN(
                                udp_logger(),
                                "UDP frame=%u: dropped %u packets due to EAGAIN (kernel tx queue full)",
                                item.frame_id,
                                send_eagain);
                        }
                        if (send_max_us > 2000)
                        {
                            RCLCPP_WARN(
                                udp_logger(),
                                "UDP frame=%u: slow sendto() max=%.1fms (non-EAGAIN stalls)",
                                item.frame_id,
                                static_cast<double>(send_max_us) / 1000.0);
                        }
                    }

                    if (have_stats)
                    {
                        stats = FrameSendStats{};
                    }

                    const bool stop_enabled = stop_after_frames_enabled_.load(std::memory_order_relaxed);
                    const uint32_t max_frames = stop_after_frames_max_frames_.load(std::memory_order_relaxed);
                    if (stop_enabled && max_frames > 0 && !stop_after_frames_triggered_.load(std::memory_order_relaxed))
                    {
                        // Stop after we have finished sending FrameId == max_frames - 1.
                        if (item.frame_id + 1u >= max_frames)
                        {
                            stop_after_frames_triggered_.store(true, std::memory_order_relaxed);
                            data_plane_halted_.store(true, std::memory_order_relaxed);

                            // Best-effort: clear any already-queued data to ensure no further packets go out.
                            {
                                std::lock_guard<std::mutex> lk(queue_mutex_);
                                queue_.clear();
                                queue_bytes_ = 0;
                            }
                            queue_cv_.notify_all();

                            const uint64_t sent_total = sent_total_pkts_.load(std::memory_order_relaxed);
                            RCLCPP_WARN(
                                udp_logger(),
                                "UDP stop_after_frames triggered: max_frames=%u, last_frame=%u, sent_total_pkts=%" PRIu64 ", dropped_frames=%" PRIu64,
                                static_cast<unsigned>(max_frames),
                                static_cast<unsigned>(item.frame_id),
                                sent_total,
                                dropped_frames_.load());
                        }
                    }
                }
            }
        }

        void UdpStreamManager::recvThreadMain()
        {
            char buffer[1024];
            while (signaling_running_)
            {
                int len = socket_->receive(buffer, sizeof(buffer), 100); // 100ms timeout
                if (len > 0)
                {
                    // Control-plane: ACK
                    if (len >= 3 && buffer[0] == 'A' && buffer[1] == 'C' && buffer[2] == 'K')
                    {
                        std::lock_guard<std::mutex> lk(handshake_mutex_);
                        if (!handshake_success_)
                        {
                            handshake_success_ = true;
                            handshake_cv_.notify_all();
                            RCLCPP_INFO(udp_logger(), "UDP handshake: ACK received, streaming enabled");
                        }
                    }
                    else
                    {
                        // Data-plane: allow reusing this socket for other datagrams, e.g. pose (Type=0x02)
                        const uint8_t type = static_cast<uint8_t>(buffer[0]);
                        if (type == 0x02)
                        {
                            auto cb = pose_datagram_cb_;
                            if (cb)
                            {
                                cb(reinterpret_cast<const uint8_t *>(buffer), static_cast<size_t>(len));
                            }
                        }
                    }
                }
            }
        }

        void UdpStreamManager::setPoseDatagramCallback(std::function<void(const uint8_t *, size_t)> cb)
        {
            pose_datagram_cb_ = std::move(cb);
        }

        void UdpStreamManager::signalingThreadMain()
        {
            auto last_timeout_log = std::chrono::steady_clock::now() - std::chrono::seconds(10);
            while (signaling_running_)
            {
                if (session_id_.empty())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    continue;
                }

                if (!handshake_success_)
                {
                    // Handshake phase
                    {
                        std::string hello = packet_builder_.buildHelloMessage();
                        if (!hello.empty())
                        {
                            socket_->send(hello.c_str(), hello.size());
                        }
                    }

                    // Wait for ACK
                    std::unique_lock<std::mutex> lk(handshake_mutex_);
                    if (handshake_cv_.wait_for(lk, std::chrono::milliseconds(1000), [this]
                                               { return handshake_success_.load(); }))
                    {
                        // Per doc: FEC is pure static-table; no coefficient announce is sent.
                    }
                    else
                    {
                        // Timeout, retry loop
                        const auto now = std::chrono::steady_clock::now();
                        if (now - last_timeout_log > std::chrono::seconds(5))
                        {
                            last_timeout_log = now;
                            RCLCPP_WARN(udp_logger(), "UDP handshake: waiting for ACK (retrying HELLO)");
                        }
                    }
                }
                else
                {
                    // Keep-alive phase
                    {
                        std::string ping = packet_builder_.buildPingMessage();
                        if (!ping.empty())
                        {
                            socket_->send(ping.c_str(), ping.size());
                        }
                    }

                    std::this_thread::sleep_for(std::chrono::seconds(5));
                }
            }
        }

        uint64_t UdpStreamManager::getCurrentNtpTimestamp()
        {
            // NTP timestamp: 64-bit. High 32: seconds since 1900. Low 32: fraction.
            // Unix epoch (1970) is 2208988800 seconds after 1900.
            auto now = std::chrono::system_clock::now();
            auto duration = now.time_since_epoch();
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
            auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration) - seconds;

            uint32_t ntp_seconds = static_cast<uint32_t>(seconds.count() + 2208988800U);
            uint32_t ntp_fraction = static_cast<uint32_t>((microseconds.count() * 4294967296.0) / 1000000.0);

            return (static_cast<uint64_t>(ntp_seconds) << 32) | ntp_fraction;
        }

    } // namespace udp
} // namespace trb
