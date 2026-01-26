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

    send_thread_ = std::thread(&UdpVideoSender::sendThreadMain, this);

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

    if (send_thread_.joinable())
    {
        send_thread_.join();
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

    const size_t max_payload = config_.max_payload_bytes;
    const uint16_t total_fragments = static_cast<uint16_t>((size + max_payload - 1) / max_payload);

    const uint32_t current_frame_id = frame_id_++;
    const uint64_t timestamp = getCurrentNtpTimestamp();

    std::vector<uint8_t> packet;
    packet.reserve(32 + max_payload);

    const bool fec_enabled = config_.fec_enabled;
    const uint8_t fec_table_id = config_.fec_table_id;

    V2FecParams fec_params;
    const bool fec_strategy_enabled = fec_enabled && lookupV2FecParams(fec_table_id, total_fragments, fec_params);
    const uint8_t groups = fec_strategy_enabled ? fec_params.groups : 0;
    const uint8_t r_per_group = fec_strategy_enabled ? fec_params.r : 0;

    double packet_ms = 0.0;
    double fec_ms = 0.0;
    auto enqueueSource = [&](uint16_t frag_idx)
    {
        const auto t0 = std::chrono::steady_clock::now();
        const size_t offset = static_cast<size_t>(frag_idx) * max_payload;
        const size_t chunk_size = std::min(max_payload, size - offset);

        VideoPacketHeaderV2 header;
        header.Type = 0x01;
        header.PacketSeqNum = packet_seq_num_++;
        header.Timestamp = timestamp;
        header.FrameId = current_frame_id;
        header.FragmentIndex = frag_idx;
        header.TotalFragments = total_fragments;
        header.PayloadLength = static_cast<uint16_t>(chunk_size);
        header.FramePayloadLength = static_cast<uint32_t>(size);
        header.FecTableId = fec_strategy_enabled ? fec_table_id : 0;
        header.KeyframeFlag = keyframe ? 1 : 0;

        packet_builder_.buildVideoPacket(header, data + offset, chunk_size, packet);

        QueueItem qi;
        qi.kind = QueueItem::Kind::Datagram;
        qi.frame_id = current_frame_id;
        qi.bytes = packet;
        qi.wire_bytes = packet.size();
        enqueueItem(std::move(qi));
        const auto t1 = std::chrono::steady_clock::now();
        packet_ms += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 1000.0;
    };

    if (!fec_strategy_enabled)
    {
        for (uint16_t i = 0; i < total_fragments; ++i)
        {
            enqueueSource(i);
        }
    }
    else
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

            const auto t0 = std::chrono::steady_clock::now();
            std::vector<uint8_t> parity(symbol_bytes, 0);
            const uint8_t *coef_row = coef_ptr->data() + static_cast<size_t>(p) * static_cast<size_t>(k_g);

            uint8_t local_i = 0;
            for (uint32_t src_idx = g; src_idx < total_fragments; src_idx += groups)
            {
                const size_t offset = static_cast<size_t>(src_idx) * max_payload;
                const size_t chunk_size = std::min(max_payload, size - offset);
                const uint8_t c = coef_row[local_i++];
                gf256::mulAdd(c, data + offset, parity.data(), chunk_size);
            }
            const auto t1 = std::chrono::steady_clock::now();
            fec_ms += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 1000.0;

            const auto packet_t0 = std::chrono::steady_clock::now();
            VideoPacketHeaderV2 parity_header;
            parity_header.Type = 0x01;
            parity_header.PacketSeqNum = packet_seq_num_++;
            parity_header.Timestamp = timestamp;
            parity_header.FrameId = current_frame_id;
            parity_header.TotalFragments = total_fragments;
            parity_header.FramePayloadLength = static_cast<uint32_t>(size);
            parity_header.PayloadLength = static_cast<uint16_t>(symbol_bytes);
            parity_header.FecTableId = fec_table_id;
            parity_header.KeyframeFlag = keyframe ? 1 : 0;

            const uint32_t frag_index = static_cast<uint32_t>(total_fragments) + static_cast<uint32_t>(g) + static_cast<uint32_t>(p) * static_cast<uint32_t>(groups);
            parity_header.FragmentIndex = static_cast<uint16_t>(frag_index & 0xFFFFu);

            packet_builder_.buildVideoPacket(parity_header, parity.data(), symbol_bytes, packet);

            QueueItem pq;
            pq.kind = QueueItem::Kind::Datagram;
            pq.frame_id = current_frame_id;
            pq.bytes = packet;
            pq.wire_bytes = packet.size();
            enqueueItem(std::move(pq));
            const auto packet_t1 = std::chrono::steady_clock::now();
            packet_ms += std::chrono::duration_cast<std::chrono::microseconds>(packet_t1 - packet_t0).count() / 1000.0;
        };

        const uint32_t parity_total = static_cast<uint32_t>(groups) * static_cast<uint32_t>(r_per_group);
        uint32_t parity_cursor = 0;
        uint32_t parity_acc = 0;

        for (uint16_t t = 0; t < rounds; ++t)
        {
            for (uint16_t g = 0; g < groups; ++g)
            {
                const uint32_t idx = static_cast<uint32_t>(g) + static_cast<uint32_t>(t) * static_cast<uint32_t>(groups);
                if (idx < total_fragments)
                {
                    enqueueSource(static_cast<uint16_t>(idx));
                }
            }

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

        while (parity_cursor < parity_total)
        {
            const uint8_t p = static_cast<uint8_t>(parity_cursor / static_cast<uint32_t>(groups));
            const uint8_t g = static_cast<uint8_t>(parity_cursor % static_cast<uint32_t>(groups));
            enqueueParity(g, p);
            ++parity_cursor;
        }
    }

    QueueItem end;
    end.kind = QueueItem::Kind::FrameEnd;
    end.frame_id = current_frame_id;
    end.capture_timestamp_us = capture_timestamp_us;
    end.enc_bytes = size;
    end.fragments = total_fragments;
    end.packet_ms = packet_ms;
    end.fec_ms = fec_ms;
    enqueueItem(std::move(end));

    (void)keyframe;
}

void UdpVideoSender::enqueueItem(QueueItem &&item)
{
    std::unique_lock<std::mutex> lk(queue_mutex_);

    if (item.kind == QueueItem::Kind::Datagram)
    {
        queue_bytes_ += item.wire_bytes;
    }

    queue_.push_back(std::move(item));

    const size_t max_packets = config_.queue_max_packets;
    const size_t max_bytes = config_.queue_max_bytes;

    if ((max_packets > 0 && queue_.size() > static_cast<size_t>(max_packets * 0.9)) ||
        (max_bytes > 0 && queue_bytes_ > static_cast<size_t>(max_bytes * 0.9)))
    {
        ROS_WARN_THROTTLE(2.0, "UDP video queue high-water: packets=%zu/%zu bytes=%zu/%zu",
                          queue_.size(),
                          max_packets,
                          queue_bytes_,
                          max_bytes);
    }

    while (!queue_.empty() &&
           ((max_packets > 0 && queue_.size() > max_packets) || (max_bytes > 0 && queue_bytes_ > max_bytes)))
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
    size_t dropped_packets = 0;
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
            ++dropped_packets;
        }
        queue_.pop_front();
    }

    ROS_WARN_THROTTLE(2.0, "UDP video drop frame=%u packets=%zu (queue full)",
                      drop_frame_id,
                      dropped_packets);
}

void UdpVideoSender::sendThreadMain()
{
    using clock = std::chrono::steady_clock;

    clock::time_point next_send_tp = clock::now();

    struct FrameStats
    {
        bool active{false};
        uint32_t frame_id{0};
        clock::time_point first_send{};
        clock::time_point last_send{};
        uint64_t pacing_sleep_us{0};
        double packet_ms{0.0};
        double fec_ms{0.0};
    } stats;

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
            queue_.pop_front();
        }

        const bool pacing_enabled = config_.pacing_enabled;
        const uint64_t pacing_bps = config_.pacing_bps;
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
                stats = FrameStats{};
                stats.active = true;
                stats.frame_id = item.frame_id;
            }

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

                const double pkt_us_d = (static_cast<double>(item.wire_bytes) * 1e6) / rate_bytes_per_sec;
                const uint64_t pkt_us = static_cast<uint64_t>(std::max(0.0, std::ceil(pkt_us_d)));
                next_send_tp += std::chrono::microseconds(pkt_us);
            }

            if (udp_manager_)
            {
                if (udp_manager_->isHandshakeReady())
                {
                    udp_manager_->sendToRemote(item.bytes.data(), item.bytes.size());
                }
            }

            const auto now = clock::now();
            if (stats.first_send.time_since_epoch().count() == 0)
            {
                stats.first_send = now;
            }
            stats.last_send = now;
        }
        else
        {
            if (stats.active && stats.frame_id == item.frame_id)
            {
                stats.packet_ms = item.packet_ms;
                stats.fec_ms = item.fec_ms;
                const uint64_t frame_us = static_cast<uint64_t>(
                    std::chrono::duration_cast<std::chrono::microseconds>(stats.last_send - stats.first_send).count());
                if ((item.frame_id % 30) == 0)
                {
                    ROS_INFO("UDP video frame=%u: packets=%u, send=%.1fms, packet=%.1fms, fec=%.1fms, pacing=%.1fms",
                             item.frame_id,
                             item.fragments,
                             static_cast<double>(frame_us - stats.pacing_sleep_us) / 1000.0,
                             stats.packet_ms,
                             stats.fec_ms,
                             static_cast<double>(stats.pacing_sleep_us) / 1000.0);
                }
                stats = FrameStats{};
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
