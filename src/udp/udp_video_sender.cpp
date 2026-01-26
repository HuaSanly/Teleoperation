#include "udp/udp_video_sender.hpp"

#include "udp/udp_manager.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <unordered_map>
#include <vector>

#include <ros/ros.h>
#include <ros/package.h>

#include "udp/gf256.hpp"

namespace trb::udp
{

namespace
{
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

bool parseIntAfterColon(const std::string &s, size_t &pos, int &out)
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

bool loadV2FecTableFromJsonText(const std::string &text, V2FecTable &out)
{
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

    return parsed > 0;
}

bool loadV2FecTableFromJsonFile(const std::filesystem::path &path, V2FecTable &out)
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
    if (!loadV2FecTableFromJsonText(text, out))
    {
        return false;
    }
    out.source_path = path.string();
    return true;
}

const V2FecTable &getV2FecTable()
{
    static V2FecTable table;
    static std::once_flag once;
    static std::atomic<bool> logged{false};
    std::call_once(once, []()
                   {
                       const std::string filename = "UDP_VIDEO_FEC_TABLE_V1.json";
                       std::vector<std::filesystem::path> candidates;
                       const std::string pkg_path = ros::package::getPath("teleoperation_robot_bridge");
                       if (!pkg_path.empty())
                       {
                           candidates.emplace_back(std::filesystem::path(pkg_path) / "config" / filename);
                       }
                       candidates.emplace_back(std::filesystem::path("config") / filename);
                       candidates.emplace_back(std::filesystem::path("teleoperation_robot_bridge") / "config" / filename);
                       candidates.emplace_back(std::filesystem::path("src") / "teleoperation_robot_bridge" / "config" / filename);

                       for (const auto &p : candidates)
                       {
                           if (loadV2FecTableFromJsonFile(p, table))
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
            ROS_INFO("Loaded FEC table from %s", table.source_path.c_str());
        }
        else
        {
            ROS_WARN("Failed to load FEC table JSON; FEC will be disabled (table_id=1)");
        }
    }

    return table;
}

bool lookupV2FecParams(uint8_t table_id, uint16_t total_fragments, V2FecParams &out)
{
    out = V2FecParams{};
    if (table_id == 0)
    {
        return false;
    }
    if (table_id != 1)
    {
        return false;
    }
    if (total_fragments >= 256)
    {
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
} // namespace

UdpVideoSender::UdpVideoSender(UdpVideoSenderConfig config)
    : config_(std::move(config)),
      packet_builder_(config_.max_payload_bytes)
{
}

UdpVideoSender::~UdpVideoSender()
{
    stop();
}

void UdpVideoSender::setSessionId(const std::string &session_id)
{
    packet_builder_.setSessionId(session_id);
}

UdpVideoSender::SendStats UdpVideoSender::getSendStats() const
{
    SendStats stats;
    stats.sent_frames = sent_frames_.load(std::memory_order_relaxed);
    stats.dropped_frames = dropped_frames_.load(std::memory_order_relaxed);
    stats.sent_packets = sent_packets_.load(std::memory_order_relaxed);
    return stats;
}

bool UdpVideoSender::start(UdpManager *udp_manager)
{
    if (running_.exchange(true))
    {
        return true;
    }

    udp_manager_ = udp_manager;
    if (!udp_manager_)
    {
        running_.store(false);
        return false;
    }

    paused_.store(false);

    if (config_.fec_threads > 1)
    {
        fec_executor_ = std::make_unique<FecExecutor>(static_cast<size_t>(config_.fec_threads));
        fec_executor_->start();
    }

    const int threads = std::max(1, config_.send_threads);
    send_threads_.clear();
    send_threads_.reserve(static_cast<size_t>(threads));
    for (int i = 0; i < threads; ++i)
    {
        send_threads_.emplace_back(&UdpVideoSender::sendThreadMain, this);
    }

    return true;
}

void UdpVideoSender::stop()
{
    if (!running_.exchange(false))
    {
        return;
    }

    paused_.store(false);

    queue_cv_.notify_all();

    for (auto &t : send_threads_)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    send_threads_.clear();

    if (fec_executor_)
    {
        fec_executor_->stop();
        fec_executor_.reset();
    }

    {
        std::lock_guard<std::mutex> lk(queue_mutex_);
        queue_.clear();
        queue_bytes_ = 0;
    }
}

void UdpVideoSender::pause()
{
    paused_.store(true);
}

void UdpVideoSender::resume()
{
    paused_.store(false);
}

void UdpVideoSender::sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us, bool keyframe)
{
    if (!running_.load() || paused_.load() || !udp_manager_ || !udp_manager_->isHandshakeReady())
    {
        return;
    }
    if (!data || size == 0)
    {
        return;
    }

    uint64_t frame_duration_us = 33333;
    if (last_capture_ts_us_ > 0 && capture_timestamp_us > last_capture_ts_us_)
    {
        frame_duration_us = capture_timestamp_us - last_capture_ts_us_;
    }
    last_capture_ts_us_ = capture_timestamp_us;
    QueueItem frame;
    frame.kind = QueueItem::Kind::Frame;
    frame.frame_id = frame_id_++;
    frame.capture_timestamp_us = capture_timestamp_us;
    frame.enc_bytes = size;
    frame.frame_duration_us = frame_duration_us;
    frame.keyframe = keyframe;
    frame.bytes.assign(data, data + size);
    enqueueItem(std::move(frame));
}

void UdpVideoSender::enqueueItem(QueueItem &&item)
{
    std::unique_lock<std::mutex> lk(queue_mutex_);

    if (item.kind == QueueItem::Kind::Datagram)
    {
        queue_bytes_ += item.wire_bytes;
    }
    else if (item.kind == QueueItem::Kind::Frame)
    {
        queue_bytes_ += item.bytes.size();
    }

    queue_.push_back(std::move(item));

    const size_t max_bytes = config_.queue_max_bytes;

    if (max_bytes > 0 && queue_bytes_ > static_cast<size_t>(max_bytes * 0.9))
    {
        ROS_WARN_THROTTLE(2.0, "UDP video queue high-water: bytes=%zu/%zu",
                          queue_bytes_,
                          max_bytes);
    }

    while (!queue_.empty() &&
           (max_bytes > 0 && queue_bytes_ > max_bytes))
    {
        dropOldestFrameLocked();
    }

    lk.unlock();
    queue_cv_.notify_one();
}

void UdpVideoSender::dropOldestFrameLocked()
{
    if (queue_.empty())
    {
        return;
    }

    const uint32_t drop_frame_id = queue_.front().frame_id;
    size_t dropped_items = 0;
    size_t dropped_bytes = 0;
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
            dropped_bytes += front.wire_bytes;
        }
        else if (front.kind == QueueItem::Kind::Frame)
        {
            if (queue_bytes_ >= front.bytes.size())
            {
                queue_bytes_ -= front.bytes.size();
            }
            else
            {
                queue_bytes_ = 0;
            }
            dropped_bytes += front.bytes.size();
        }
        ++dropped_items;
        queue_.pop_front();
    }

    dropped_frames_since_log_.fetch_add(1, std::memory_order_relaxed);
    constexpr uint64_t kStatsModulo = 1000000000ULL;
    const uint64_t drop = dropped_frames_.fetch_add(1, std::memory_order_relaxed) + 1;
    if (drop >= kStatsModulo)
    {
        dropped_frames_.store(drop % kStatsModulo, std::memory_order_relaxed);
    }

    ROS_WARN_THROTTLE(2.0, "UDP video drop frame=%u items=%zu bytes=%zu (queue full)",
                      drop_frame_id,
                      dropped_items,
                      dropped_bytes);
}

void UdpVideoSender::sendThreadMain()
{
    using clock = std::chrono::steady_clock;
    constexpr uint64_t kStatsModulo = 1000000000ULL;

    while (running_.load())
    {
        if (paused_.load())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        QueueItem item;
        {
            std::unique_lock<std::mutex> lk(queue_mutex_);
            queue_cv_.wait_for(lk, std::chrono::milliseconds(10), [this]
                               { return !queue_.empty() || !running_.load(); });
            if (!running_.load())
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
            else if (item.kind == QueueItem::Kind::Frame)
            {
                const size_t frame_bytes = item.bytes.size();
                if (queue_bytes_ >= frame_bytes)
                {
                    queue_bytes_ -= frame_bytes;
                }
                else
                {
                    queue_bytes_ = 0;
                }
            }
            queue_.pop_front();
        }

        const bool pacing_enabled = config_.pacing_enabled;

        if (item.kind == QueueItem::Kind::Frame)
        {
            if (!udp_manager_ || !udp_manager_->isHandshakeReady())
            {
                continue;
            }

            const size_t max_payload = config_.max_payload_bytes;
            const size_t frame_size = item.bytes.size();
            if (frame_size == 0 || max_payload == 0)
            {
                continue;
            }

            const uint16_t total_fragments = static_cast<uint16_t>((frame_size + max_payload - 1) / max_payload);
            const uint64_t timestamp = getCurrentNtpTimestamp();
            const bool fec_enabled = config_.fec_enabled;
            const uint8_t fec_table_id = config_.fec_table_id;

            V2FecParams fec_params;
            const bool fec_strategy_enabled = fec_enabled && lookupV2FecParams(fec_table_id, total_fragments, fec_params);
            const uint8_t groups = fec_strategy_enabled ? fec_params.groups : 0;
            const uint8_t r_per_group = fec_strategy_enabled ? fec_params.r : 0;
            const uint32_t parity_total = fec_strategy_enabled ? static_cast<uint32_t>(groups) * static_cast<uint32_t>(r_per_group) : 0;

            constexpr size_t kHeaderBytes = 27;
            const uint64_t source_wire_bytes = static_cast<uint64_t>(frame_size) + static_cast<uint64_t>(total_fragments) * kHeaderBytes;
            const uint64_t parity_wire_bytes = fec_strategy_enabled ?
                                                  static_cast<uint64_t>(parity_total) * (kHeaderBytes + max_payload) :
                                                  0;
            const uint64_t frame_wire_bytes = source_wire_bytes + parity_wire_bytes;

            double packet_ms = 0.0;
            double fec_ms = 0.0;
            uint64_t pacing_sleep_us = 0;

            auto pacePacket = [&](size_t wire_bytes)
            {
                if (!pacing_enabled)
                {
                    return;
                }
                double rate_bytes_per_us = 0.0;
                if (config_.pacing_target_bps > 0)
                {
                    rate_bytes_per_us = static_cast<double>(config_.pacing_target_bps) / 8.0 / 1e6;
                }
                else if (item.frame_duration_us > 0 && frame_wire_bytes > 0)
                {
                    rate_bytes_per_us = static_cast<double>(frame_wire_bytes) /
                                        static_cast<double>(item.frame_duration_us);
                }
                if (rate_bytes_per_us <= 0.0)
                {
                    return;
                }

                auto now = clock::now();
                uint64_t slept_us = 0;
                {
                    std::lock_guard<std::mutex> lk(pacing_mutex_);
                    if (pacing_last_tp_.time_since_epoch().count() == 0)
                    {
                        pacing_last_tp_ = now;
                    }

                    if (now > pacing_last_tp_)
                    {
                        const double delta_us = static_cast<double>(
                            std::chrono::duration_cast<std::chrono::microseconds>(now - pacing_last_tp_).count());
                        pacing_budget_bytes_ += delta_us * rate_bytes_per_us;
                    }

                    const size_t max_burst_bytes = std::max<size_t>(config_.max_payload_bytes * 8, 4096);
                    if (pacing_budget_bytes_ > static_cast<double>(max_burst_bytes))
                    {
                        pacing_budget_bytes_ = static_cast<double>(max_burst_bytes);
                    }

                    if (pacing_budget_bytes_ < static_cast<double>(wire_bytes))
                    {
                        const double need_bytes = static_cast<double>(wire_bytes) - pacing_budget_bytes_;
                        const double need_us = need_bytes / rate_bytes_per_us;
                        slept_us = static_cast<uint64_t>(std::ceil(need_us));
                        pacing_last_tp_ = now + std::chrono::microseconds(slept_us);
                        pacing_budget_bytes_ = 0.0;
                    }
                    else
                    {
                        pacing_budget_bytes_ -= static_cast<double>(wire_bytes);
                        pacing_last_tp_ = now;
                    }
                }

                if (slept_us > 0)
                {
                    std::this_thread::sleep_for(std::chrono::microseconds(slept_us));
                    pacing_sleep_us += slept_us;
                }
            };

            std::vector<uint8_t> packet;
            packet.reserve(kHeaderBytes + max_payload);

            auto sendPacket = [&](const VideoPacketHeaderV2 &header,
                                  const uint8_t *payload,
                                  size_t payload_bytes)
            {
                const auto t0 = std::chrono::steady_clock::now();
                packet_builder_.buildVideoPacket(header, payload, payload_bytes, packet);
                const auto t1 = std::chrono::steady_clock::now();
                packet_ms += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 1000.0;

                pacePacket(packet.size());
                udp_manager_->sendToRemote(packet.data(), packet.size());

                constexpr uint64_t kStatsModulo = 1000000000ULL;
                const uint64_t pkt = sent_packets_.fetch_add(1, std::memory_order_relaxed) + 1;
                if (pkt >= kStatsModulo)
                {
                    sent_packets_.store(pkt % kStatsModulo, std::memory_order_relaxed);
                }
            };

            const auto frame_send_start = clock::now();

            for (uint16_t frag_idx = 0; frag_idx < total_fragments; ++frag_idx)
            {
                const size_t offset = static_cast<size_t>(frag_idx) * max_payload;
                const size_t chunk_size = std::min(max_payload, frame_size - offset);

                VideoPacketHeaderV2 header;
                header.Type = 0x01;
                header.PacketSeqNum = packet_seq_num_.fetch_add(1, std::memory_order_relaxed);
                header.Timestamp = timestamp;
                header.FrameId = item.frame_id;
                header.FragmentIndex = frag_idx;
                header.TotalFragments = total_fragments;
                header.PayloadLength = static_cast<uint16_t>(chunk_size);
                header.FramePayloadLength = static_cast<uint32_t>(frame_size);
                header.FecTableId = fec_strategy_enabled ? fec_table_id : 0;
                header.KeyframeFlag = item.keyframe ? 1 : 0;

                sendPacket(header, item.bytes.data() + offset, chunk_size);
            }

            if (fec_strategy_enabled && parity_total > 0)
            {
                const size_t symbol_bytes = max_payload;
                std::vector<uint8_t> k_by_group(groups, 0);
                std::vector<const std::vector<uint8_t> *> coef_by_group(groups, nullptr);

                uint16_t rounds = 0;
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

                const auto fec_start = std::chrono::steady_clock::now();
                std::vector<std::vector<uint8_t>> parity_buffers(parity_total, std::vector<uint8_t>(symbol_bytes, 0));

                auto computeParity = [&](size_t idx)
                {
                    const uint8_t p = static_cast<uint8_t>(idx / static_cast<size_t>(groups));
                    const uint8_t g = static_cast<uint8_t>(idx % static_cast<size_t>(groups));
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
                    const uint8_t *coef_row = coef_ptr->data() + static_cast<size_t>(p) * static_cast<size_t>(k_g);
                    uint8_t local_i = 0;
                    auto &parity = parity_buffers[idx];
                    for (uint32_t src_idx = g; src_idx < total_fragments; src_idx += groups)
                    {
                        const size_t offset = static_cast<size_t>(src_idx) * max_payload;
                        const size_t chunk_size = std::min(max_payload, frame_size - offset);
                        const uint8_t c = coef_row[local_i++];
                        gf256::mulAdd(c, item.bytes.data() + offset, parity.data(), chunk_size);
                    }
                };

                if (fec_executor_)
                {
                    fec_executor_->parallelFor(parity_total, computeParity);
                }
                else
                {
                    for (size_t idx = 0; idx < parity_total; ++idx)
                    {
                        computeParity(idx);
                    }
                }
                const auto fec_end = std::chrono::steady_clock::now();
                fec_ms += std::chrono::duration_cast<std::chrono::microseconds>(fec_end - fec_start).count() / 1000.0;

                for (uint32_t idx = 0; idx < parity_total; ++idx)
                {
                    const uint8_t p = static_cast<uint8_t>(idx / static_cast<uint32_t>(groups));
                    const uint8_t g = static_cast<uint8_t>(idx % static_cast<uint32_t>(groups));

                    VideoPacketHeaderV2 parity_header;
                    parity_header.Type = 0x01;
                    parity_header.PacketSeqNum = packet_seq_num_.fetch_add(1, std::memory_order_relaxed);
                    parity_header.Timestamp = timestamp;
                    parity_header.FrameId = item.frame_id;
                    parity_header.TotalFragments = total_fragments;
                    parity_header.FramePayloadLength = static_cast<uint32_t>(frame_size);
                    parity_header.PayloadLength = static_cast<uint16_t>(symbol_bytes);
                    parity_header.FecTableId = fec_table_id;
                    parity_header.KeyframeFlag = item.keyframe ? 1 : 0;

                    const uint32_t frag_index = static_cast<uint32_t>(total_fragments) + static_cast<uint32_t>(g) + static_cast<uint32_t>(p) * static_cast<uint32_t>(groups);
                    parity_header.FragmentIndex = static_cast<uint16_t>(frag_index & 0xFFFFu);

                    sendPacket(parity_header, parity_buffers[idx].data(), symbol_bytes);
                }
            }

            const auto frame_send_end = clock::now();
            const int64_t frame_us = std::chrono::duration_cast<std::chrono::microseconds>(frame_send_end - frame_send_start).count();
            const int64_t send_us = std::max<int64_t>(0, frame_us - static_cast<int64_t>(pacing_sleep_us));
            if ((item.frame_id % 30) == 0)
            {
                const uint64_t dropped = dropped_frames_since_log_.exchange(0, std::memory_order_relaxed);
                ROS_INFO("UDP video frame=%u: packets=%u, send=%.1fms, packet=%.1fms, fec=%.1fms, pacing=%.1fms, dropped=%lu",
                         item.frame_id,
                         total_fragments,
                         static_cast<double>(send_us) / 1000.0,
                         packet_ms,
                         fec_ms,
                         static_cast<double>(pacing_sleep_us) / 1000.0,
                         static_cast<unsigned long>(dropped));
            }

            const uint64_t sent = sent_frames_.fetch_add(1, std::memory_order_relaxed) + 1;
            if (sent >= kStatsModulo)
            {
                sent_frames_.store(sent % kStatsModulo, std::memory_order_relaxed);
            }
        }
    }
}

uint64_t UdpVideoSender::getCurrentNtpTimestamp() const
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration) - seconds;

    uint32_t ntp_seconds = static_cast<uint32_t>(seconds.count() + 2208988800U);
    uint32_t ntp_fraction = static_cast<uint32_t>((microseconds.count() * 4294967296.0) / 1000000.0);

    return (static_cast<uint64_t>(ntp_seconds) << 32) | ntp_fraction;
}

} // namespace trb::udp
