#include "udp/udp_manager.hpp"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <thread>

#include "rclcpp/rclcpp.hpp"

namespace trb::udp
{
    namespace
    {
        enum class SendAttemptResult
        {
            kSent,
            kWouldBlock,
            kDropped,
        };

        constexpr uint32_t kAudioStreamKey = 1;
        constexpr uint32_t kVideoStreamKey = 2;
        constexpr uint32_t kTelemetryStreamKey = 3;
        constexpr uint8_t kAudioPriority = 0;
        constexpr uint8_t kVideoPriority = 2;
        constexpr uint8_t kTelemetryPriority = 3;
 
        const char *pacingModeToString(UdpManager::PacingMode mode)
        {
            switch (mode)
            {
            case UdpManager::PacingMode::WebRtcLike:
                return "webrtc_like";
            case UdpManager::PacingMode::Legacy:
            default:
                return "legacy";
            }
        }

        WebRtcLikePacer::Config makeWebRtcLikePacerConfig(const UdpManager::Config &config)
        {
            WebRtcLikePacer::Config pacer_config;
            pacer_config.enabled = config.pacing_enabled;
            pacer_config.pacing_bps = config.pacing_bps;
            pacer_config.send_burst_interval_ms = config.pacing_send_burst_interval_ms;
            pacer_config.max_burst_bytes = config.pacing_max_burst_bytes;
            pacer_config.max_debt_ms = config.pacing_max_debt_ms;
            pacer_config.queue_time_limit_ms = config.pacing_queue_time_limit_ms;
            pacer_config.max_drain_multiplier = config.pacing_max_drain_multiplier;
            return pacer_config;
        }

        int defaultSendBufferBytes(const UdpManager::Config &config)
        {
            constexpr uint64_t kTargetQueueMs = 50;
            constexpr uint64_t kMinSendBufferBytes = 256 * 1024;
            constexpr uint64_t kMaxSendBufferBytes = 1024 * 1024;
            constexpr uint64_t kFallbackSendBufferBytes = 512 * 1024;

            if (config.pacing_enabled && config.pacing_bps > 0)
            {
                const auto target_bytes = static_cast<uint64_t>(
                    (static_cast<long double>(config.pacing_bps) * static_cast<long double>(kTargetQueueMs)) /
                    (8.0L * 1000.0L));
                return static_cast<int>(std::clamp(target_bytes, kMinSendBufferBytes, kMaxSendBufferBytes));
            }
            return static_cast<int>(kFallbackSendBufferBytes);
        }

        uint64_t nowSteadyUs()
        {
            return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(
                                            std::chrono::steady_clock::now().time_since_epoch())
                                            .count());
        }

        uint64_t nowUnixMs()
        {
            return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                            std::chrono::system_clock::now().time_since_epoch())
                                            .count());
        }

        rclcpp::Logger logger()
        {
            return rclcpp::get_logger("teleop_robot_bridge.udp.manager");
        }
    } // namespace

    UdpManager::UdpManager(const Config &config)
        : config_(config),
          packet_codec_(config.max_payload_bytes),
          control_({config.control_enabled, config.control_hello_interval_sec,
                    config.control_ping_interval_sec, config.control_peer_lost_timeout_sec})
    {
        socket_ = std::make_unique<UdpSocket>(config.remote_ip, config.remote_port, config.bind_ip, config.bind_port);
        fec_encoder_ = std::make_unique<FecV2>();
        packet_codec_.setDeviceId(config_.device_id);
    }

    UdpManager::~UdpManager()
    {
        stop();
    }

    bool UdpManager::start()
    {
        if (state_.running.exchange(true))
        {
            return true;
        }

        if (!socket_->open())
        {
            state_.running.store(false);
            return false;
        }

        socket_->setSendNonBlocking(config_.send_nonblocking);
        socket_->setRecvTimeoutMs(config_.recv_timeout_ms);

        const int requested_send_buffer = config_.send_buffer_bytes > 0
                                              ? config_.send_buffer_bytes
                                              : defaultSendBufferBytes(config_);
        socket_->setSendBufferBytes(requested_send_buffer);
        const int actual_send_buffer = socket_->sendBufferBytes();
        RCLCPP_INFO(logger(), "UDP send socket: nonblocking=%d sndbuf_requested=%d sndbuf_kernel=%d mode=%s",
                    config_.send_nonblocking ? 1 : 0,
                    requested_send_buffer,
                    actual_send_buffer,
                    config_.send_buffer_bytes > 0 ? "configured" : "auto-low-latency");
        if (actual_send_buffer > 0 && actual_send_buffer < requested_send_buffer)
        {
            RCLCPP_WARN(logger(), "UDP send socket buffer below requested size: requested=%d kernel=%d; "
                                 "check net.core.wmem_max or set udp.send.buffer_bytes explicitly",
                        requested_send_buffer, actual_send_buffer);
        }

        if (fec_encoder_ && config_.fec_table_id != 0)
        {
            uint8_t preload_groups = 0;
            uint8_t preload_r_per_group = 0;
            (void)fec_encoder_->getParams(config_.fec_table_id, 1, preload_groups, preload_r_per_group);
        }

        send_queue_.setLimits(config_.queue_max_packets, config_.queue_max_bytes);
        webrtc_like_pacer_.setConfig(makeWebRtcLikePacerConfig(config_));
        webrtc_like_pacer_.reset();

        control_.start(
            [this](const std::string &message) {
                if (!message.empty())
                {
                    socket_->send(message.data(), message.size());
                }
            },
            [this]() { return packet_codec_.buildHelloMessage(); },
            [this]() { return packet_codec_.buildPingMessage(); });

        RCLCPP_INFO(logger(), "UdpManager config: remote=%s:%d pacing_mode=%s pacing_enabled=%d pacing_bps=%lu",
                    config_.remote_ip.c_str(), config_.remote_port,
                    pacingModeToString(config_.pacing_mode),
                    config_.pacing_enabled ? 1 : 0,
                    static_cast<unsigned long>(config_.pacing_bps));
        RCLCPP_INFO(logger(), "UdpManager pacing: burst=%ums max_burst=%zu max_debt=%ums qlimit=%ums drain=%.2f account_audio=%d batch=%u",
                    config_.pacing_send_burst_interval_ms,
                    config_.pacing_max_burst_bytes,
                    config_.pacing_max_debt_ms,
                    config_.pacing_queue_time_limit_ms,
                    config_.pacing_max_drain_multiplier,
                    config_.pacing_account_audio ? 1 : 0,
                    config_.pacing_max_packets_per_batch);
        RCLCPP_INFO(logger(), "UdpManager config: queue_max_bytes=%zu queue_max_packets=%zu fec_table_id=%d fec_input_queue_max_frames=%zu",
                    config_.queue_max_bytes, config_.queue_max_packets,
                    static_cast<int>(config_.fec_table_id),
                    config_.fec_input_queue_max_frames);

        recv_thread_ = std::thread(&UdpManager::recvThreadMain, this);
        send_thread_ = std::thread(&UdpManager::sendThreadMain, this);
        fec_thread_ = std::thread(&UdpManager::fecThreadMain, this);
        RCLCPP_INFO(logger(), "UdpManager started (async FEC mode)");
        return true;
    }

    void UdpManager::stop()
    {
        if (!state_.running.exchange(false))
        {
            return;
        }

        control_.stop();
        send_queue_.stop();

        {
            std::lock_guard<std::mutex> lock(input_mutex_);
            input_queue_.clear();
        }
        input_cv_.notify_all();

        if (fec_thread_.joinable())
        {
            fec_thread_.join();
        }
        if (send_thread_.joinable())
        {
            send_thread_.join();
        }

        socket_->close();

        if (recv_thread_.joinable())
        {
            recv_thread_.join();
        }
        RCLCPP_INFO(logger(), "UdpManager stopped");
    }

    void UdpManager::setSessionId(const std::string &session_id)
    {
        session_id_ = session_id;
        packet_codec_.setSessionId(session_id);
    }

    void UdpManager::resetSession()
    {
        if (!state_.running.load())
        {
            return;
        }
        {
            std::lock_guard<std::mutex> lock(input_mutex_);
            input_queue_.clear();
        }
        send_queue_.clear();
        webrtc_like_pacer_.reset();
        control_.resetHandshake();
        packet_seq_num_.store(0);
        frame_id_.store(0);
        audio_group_id_.store(0);
        audio_seq_num_.store(0);
        telemetry_group_id_.store(0);
        telemetry_seq_num_.store(0);
        RCLCPP_INFO(logger(), "UdpManager session reset (queues cleared, handshake rolled back)");
    }

    void UdpManager::setDatagramCallback(const std::function<void(const uint8_t *, size_t)> &callback)
    {
        datagram_callback_ = callback;
    }

    void UdpManager::setPacingEnabled(bool enabled)
    {
        config_.pacing_enabled = enabled;
        webrtc_like_pacer_.setConfig(makeWebRtcLikePacerConfig(config_));
    }

    void UdpManager::setPacingRateBps(uint64_t bps)
    {
        config_.pacing_bps = bps;
        webrtc_like_pacer_.setConfig(makeWebRtcLikePacerConfig(config_));
    }

    void UdpManager::setQueueLimits(size_t max_packets, size_t max_bytes)
    {
        config_.queue_max_packets = max_packets;
        config_.queue_max_bytes = max_bytes;
        send_queue_.setLimits(max_packets, max_bytes);
    }

    void UdpManager::setFecTableId(uint8_t table_id)
    {
        config_.fec_table_id = table_id;
    }

    bool UdpManager::isHandshakeReady() const
    {
        if (!config_.control_enabled)
        {
            return true;
        }
        return control_.handshakeReady();
    }

    void UdpManager::sendAudioPacket(const uint8_t *data, size_t size, uint64_t timestamp_ntp)
    {
        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        if (!state_.running.load())
        {
            return;
        }
        if (config_.control_enabled && !control_.handshakeReady())
        {
            return;
        }
        if (!data || size == 0)
        {
            return;
        }

        constexpr size_t kAudioHeaderBytes = 11;
        if (config_.max_payload_bytes <= kAudioHeaderBytes || size > (config_.max_payload_bytes - kAudioHeaderBytes))
        {
            RCLCPP_WARN_THROTTLE(logger(), steady_clock, 1000,
                                 "Audio packet too large for configured UDP payload budget: %zu bytes", size);
            return;
        }

        AudioPacketHeaderV2 header;
        header.Type = kAudioPacketType;
        header.Seq = audio_seq_num_.fetch_add(1);
        header.TimestampNtp = timestamp_ntp;

        QueueItem item;
        item.kind = QueueItem::Kind::Datagram;
        item.stream = QueueItem::Stream::Audio;
        item.group_id = audio_group_id_.fetch_add(1);
        item.packet_seq = header.Seq;
        item.stream_key = kAudioStreamKey;
        item.priority = kAudioPriority;
        item.pacing_accounted = config_.pacing_account_audio;
        item.enqueue_steady_us = nowSteadyUs();
        packet_codec_.buildAudioPacket(header, data, size, item.bytes);
        item.wire_bytes = item.bytes.size();
        send_queue_.push(std::move(item));
    }

    void UdpManager::sendRobotTelemetry(const telemetry::RobotTelemetrySnapshot &snapshot)
    {
        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        if (!state_.running.load())
        {
            return;
        }
        if (config_.control_enabled && !control_.handshakeReady())
        {
            return;
        }

        TelemetryPacketHeaderV1 header;
        header.Type = kRobotTelemetryLowRateType;
        header.Seq = telemetry_seq_num_.fetch_add(1);
        header.TxTimestampMs = nowUnixMs();
        header.SessionId = session_id_;
        header.DeviceId = config_.device_id;

        QueueItem item;
        item.kind = QueueItem::Kind::Datagram;
        item.stream = QueueItem::Stream::Other;
        item.group_id = telemetry_group_id_.fetch_add(1);
        item.packet_seq = header.Seq;
        item.stream_key = kTelemetryStreamKey;
        item.priority = kTelemetryPriority;
        item.pacing_accounted = true;
        item.enqueue_steady_us = nowSteadyUs();
        packet_codec_.buildRobotTelemetryPacket(header, snapshot, item.bytes);

        if (config_.max_payload_bytes > 0 && item.bytes.size() > config_.max_payload_bytes)
        {
            RCLCPP_WARN_THROTTLE(logger(), steady_clock, 1000,
                                 "Robot telemetry packet too large for configured UDP payload budget: %zu bytes",
                                 item.bytes.size());
            return;
        }

        item.wire_bytes = item.bytes.size();
        send_queue_.push(std::move(item));
    }

    void UdpManager::sendRobotJointTelemetry(const telemetry::RobotJointTelemetrySnapshot &snapshot)
    {
        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        if (!state_.running.load())
        {
            return;
        }
        if (config_.control_enabled && !control_.handshakeReady())
        {
            return;
        }

        TelemetryPacketHeaderV1 header;
        header.Type = kRobotTelemetryHighRateType;
        header.Seq = telemetry_seq_num_.fetch_add(1);
        header.TxTimestampMs = nowUnixMs();
        header.SessionId = session_id_;
        header.DeviceId = config_.device_id;

        QueueItem item;
        item.kind = QueueItem::Kind::Datagram;
        item.stream = QueueItem::Stream::Other;
        item.group_id = telemetry_group_id_.fetch_add(1);
        item.packet_seq = header.Seq;
        item.stream_key = kTelemetryStreamKey;
        item.priority = kTelemetryPriority;
        item.pacing_accounted = true;
        item.enqueue_steady_us = nowSteadyUs();
        packet_codec_.buildRobotJointTelemetryPacket(header, snapshot, item.bytes);

        if (config_.max_payload_bytes > 0 && item.bytes.size() > config_.max_payload_bytes)
        {
            RCLCPP_WARN_THROTTLE(logger(), steady_clock, 1000,
                                 "Robot joint telemetry packet too large for configured UDP payload budget: %zu bytes",
                                 item.bytes.size());
            return;
        }

        item.wire_bytes = item.bytes.size();
        send_queue_.push(std::move(item));
    }

    void UdpManager::sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us, bool keyframe)
    {
        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        if (!state_.running.load())
        {
            return;
        }
        if (config_.control_enabled && !control_.handshakeReady())
        {
            return;
        }
        if (!data || size == 0)
        {
            return;
        }

        InputFrame frame;
        frame.data.assign(data, data + size);
        frame.capture_timestamp_us = capture_timestamp_us;
        frame.ntp_timestamp = currentNtpTimestamp();
        frame.enqueue_steady_us = nowSteadyUs();
        frame.keyframe = keyframe;

        size_t dropped_count = 0;
        {
            std::lock_guard<std::mutex> lock(input_mutex_);
            const size_t max_input_queue_frames = std::max<size_t>(1, config_.fec_input_queue_max_frames);
            while (input_queue_.size() >= max_input_queue_frames)
            {
                auto victim = std::find_if(input_queue_.begin(), input_queue_.end(), [](const InputFrame &queued_frame) {
                    return !queued_frame.keyframe;
                });
                if (victim == input_queue_.end())
                {
                    victim = input_queue_.begin();
                }
                input_queue_.erase(victim);
                ++dropped_count;
            }
            input_queue_.push_back(std::move(frame));
        }
        input_cv_.notify_one();

        video_input_frames_.fetch_add(1, std::memory_order_relaxed);
        video_input_bytes_.fetch_add(size, std::memory_order_relaxed);
        if (dropped_count > 0)
        {
            video_input_drops_.fetch_add(dropped_count, std::memory_order_relaxed);
            RCLCPP_WARN_THROTTLE(logger(), steady_clock, 1000,
                                 "FEC input queue full (max=%zu frames), dropped %zu frames (non-keyframe preferred)",
                                 config_.fec_input_queue_max_frames, dropped_count);
        }
    }

    void UdpManager::fecThreadMain()
    {
        RCLCPP_INFO(logger(), "FEC thread started in low-latency mode (no frame smoothing)");
        while (state_.running.load())
        {
            InputFrame frame;
            {
                std::unique_lock<std::mutex> lock(input_mutex_);
                if (!input_cv_.wait_for(lock, std::chrono::milliseconds(50), [this]() {
                        return !input_queue_.empty() || !state_.running.load();
                    }))
                {
                    continue;
                }
                if (!state_.running.load())
                {
                    break;
                }
                if (input_queue_.empty())
                {
                    continue;
                }
                frame = std::move(input_queue_.front());
                input_queue_.pop_front();
            }

            if (frame.capture_timestamp_us > 0)
            {
                const auto now_us = static_cast<int64_t>(nowSteadyUs());
                const int64_t cap_to_fec_us = now_us - static_cast<int64_t>(frame.capture_timestamp_us);
                if (cap_to_fec_us >= 0)
                {
                    cap_to_fec_us_total_.fetch_add(static_cast<uint64_t>(cap_to_fec_us), std::memory_order_relaxed);
                    cap_to_fec_samples_.fetch_add(1, std::memory_order_relaxed);
                }
                if (frame.enqueue_steady_us > 0)
                {
                    const int64_t fec_wait_us = now_us - static_cast<int64_t>(frame.enqueue_steady_us);
                    if (fec_wait_us >= 0)
                    {
                        fec_internal_wait_us_total_.fetch_add(static_cast<uint64_t>(fec_wait_us), std::memory_order_relaxed);
                        fec_internal_wait_samples_.fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }

            processFrame(frame);
        }
    }

    void UdpManager::processFrame(const InputFrame &frame)
    {
        static std::atomic<uint32_t> last_fec_frame_id{UINT32_MAX};
        const uint8_t *data = frame.data.data();
        const size_t size = frame.data.size();
        const size_t max_payload = packet_codec_.maxPayloadBytes();
        if (max_payload == 0)
        {
            return;
        }
        const uint16_t total_fragments = static_cast<uint16_t>((size + max_payload - 1) / max_payload);
        const uint32_t current_frame_id = frame_id_.fetch_add(1);
        const uint64_t timestamp = frame.ntp_timestamp;

        const uint32_t previous_frame_id = last_fec_frame_id.exchange(current_frame_id);
        if (previous_frame_id != UINT32_MAX && current_frame_id != previous_frame_id + 1)
        {
            RCLCPP_WARN(logger(), "[FEC] FrameId gap! prev=%u curr=%u (expected %u)",
                        previous_frame_id, current_frame_id, previous_frame_id + 1);
        }

        uint8_t groups = 0;
        uint8_t r_per_group = 0;
        const bool fec_enabled = fec_encoder_ && fec_encoder_->getParams(config_.fec_table_id, total_fragments, groups, r_per_group);

        auto enqueue_source = [&](uint16_t fragment_index) {
            const size_t offset = static_cast<size_t>(fragment_index) * max_payload;
            const size_t chunk_size = std::min(max_payload, size - offset);

            VideoPacketHeaderV2 header;
            header.Type = kVideoPacketType;
            header.PacketSeqNum = packet_seq_num_.fetch_add(1);
            header.Timestamp = timestamp;
            header.FrameId = current_frame_id;
            header.FragmentIndex = fragment_index;
            header.TotalFragments = total_fragments;
            header.PayloadLength = static_cast<uint16_t>(chunk_size);
            header.FramePayloadLength = static_cast<uint32_t>(size);
            header.FecTableId = fec_enabled ? config_.fec_table_id : 0;
            header.KeyframeFlag = frame.keyframe ? 1 : 0;

            QueueItem item;
            item.kind = QueueItem::Kind::Datagram;
            item.stream = QueueItem::Stream::Video;
            item.group_id = current_frame_id;
            item.packet_seq = header.PacketSeqNum;
            item.stream_key = kVideoStreamKey;
            item.priority = kVideoPriority;
            item.pacing_accounted = true;
            item.is_keyframe = frame.keyframe;
            item.is_fec_parity = false;
            item.enqueue_steady_us = nowSteadyUs();
            item.frame_capture_steady_us = frame.capture_timestamp_us;
            packet_codec_.buildVideoPacket(header, data + offset, chunk_size, item.bytes);
            item.wire_bytes = item.bytes.size();
            send_queue_.push(std::move(item));
        };

        if (!fec_enabled)
        {
            for (uint16_t index = 0; index < total_fragments; ++index)
            {
                enqueue_source(index);
            }
        }
        else
        {
            const size_t symbol_bytes = max_payload;
            std::vector<std::vector<uint8_t>> parity_buffers;
            fec_encoder_->buildParity(data, size, total_fragments, groups, r_per_group, symbol_bytes, parity_buffers);

            auto enqueue_parity = [&](uint8_t group, uint8_t parity) {
                const size_t parity_index = static_cast<size_t>(parity) * static_cast<size_t>(groups) + static_cast<size_t>(group);
                if (parity_index >= parity_buffers.size() || parity_buffers[parity_index].empty())
                {
                    return;
                }
                const auto &parity_payload = parity_buffers[parity_index];

                VideoPacketHeaderV2 header;
                header.Type = kVideoPacketType;
                header.PacketSeqNum = packet_seq_num_.fetch_add(1);
                header.Timestamp = timestamp;
                header.FrameId = current_frame_id;
                header.TotalFragments = total_fragments;
                header.FramePayloadLength = static_cast<uint32_t>(size);
                header.PayloadLength = static_cast<uint16_t>(parity_payload.size());
                header.KeyframeFlag = frame.keyframe ? 1 : 0;
                header.FecTableId = config_.fec_table_id;
                const uint32_t fragment_index = static_cast<uint32_t>(total_fragments) + static_cast<uint32_t>(group) +
                                                static_cast<uint32_t>(parity) * static_cast<uint32_t>(groups);
                header.FragmentIndex = static_cast<uint16_t>(fragment_index & 0xFFFFu);

                QueueItem item;
                item.kind = QueueItem::Kind::Datagram;
                item.stream = QueueItem::Stream::Video;
                item.group_id = current_frame_id;
                item.packet_seq = header.PacketSeqNum;
                item.stream_key = kVideoStreamKey;
                item.priority = kVideoPriority;
                item.pacing_accounted = true;
                item.is_keyframe = frame.keyframe;
                item.is_fec_parity = true;
                item.enqueue_steady_us = nowSteadyUs();
                item.frame_capture_steady_us = frame.capture_timestamp_us;
                packet_codec_.buildVideoPacket(header, parity_payload.data(), parity_payload.size(), item.bytes);
                item.wire_bytes = item.bytes.size();
                send_queue_.push(std::move(item));
            };

            for (uint16_t index = 0; index < total_fragments; ++index)
            {
                enqueue_source(index);
            }

            for (uint8_t parity = 0; parity < r_per_group; ++parity)
            {
                for (uint8_t group = 0; group < groups; ++group)
                {
                    enqueue_parity(group, parity);
                }
            }
        }

        QueueItem end;
        end.kind = QueueItem::Kind::GroupEnd;
        end.stream = QueueItem::Stream::Video;
        end.group_id = current_frame_id;
        end.stream_key = kVideoStreamKey;
        end.priority = kVideoPriority;
        end.pacing_accounted = false;
        end.enqueue_steady_us = nowSteadyUs();
        end.frame_capture_steady_us = frame.capture_timestamp_us;
        send_queue_.push(std::move(end));

        const uint32_t packets_this_frame = fec_enabled
                                                ? (static_cast<uint32_t>(total_fragments) + static_cast<uint32_t>(groups) * static_cast<uint32_t>(r_per_group))
                                                : static_cast<uint32_t>(total_fragments);
        fec_output_packets_.fetch_add(packets_this_frame, std::memory_order_relaxed);
    }

    void UdpManager::recvThreadMain()
    {
        std::vector<uint8_t> buffer(2048, 0);

        while (state_.running.load())
        {
            if (!config_.enable_receive)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            const int length = socket_->receive(buffer.data(), buffer.size());
            if (length <= 0)
            {
                continue;
            }

            if (length >= 3 && buffer[0] == 'A' && buffer[1] == 'C' && buffer[2] == 'K')
            {
                control_.onAckReceived();
                state_.handshake_ready.store(true);
                continue;
            }

            control_.onPeerActivity();
            if (datagram_callback_)
            {
                datagram_callback_(buffer.data(), static_cast<size_t>(length));
            }
        }
    }

    void UdpManager::sendThreadMain()
    {
        pacer_.reset();
        webrtc_like_pacer_.reset();
        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);

        struct FrameStats
        {
            uint32_t frame_id{0};
            uint64_t packets{0};
            uint64_t capture_steady_us{0};
            uint64_t last_send_done_us{0};
        } current;

        uint32_t last_sent_frame_id = UINT32_MAX;

        auto flush_frame = [&]() {
            if (current.packets == 0)
            {
                current = FrameStats{};
                return;
            }
            send_queue_.clearProtectedVideoGroup(current.frame_id);
            if (last_sent_frame_id != UINT32_MAX && current.frame_id != last_sent_frame_id + 1)
            {
                RCLCPP_WARN(logger(), "[UDP-SEND] FrameId gap! prev=%u curr=%u (expected %u, missed %u frames)",
                            last_sent_frame_id, current.frame_id, last_sent_frame_id + 1,
                            current.frame_id - last_sent_frame_id - 1);
            }
            last_sent_frame_id = current.frame_id;
            udp_sent_video_frames_.fetch_add(1, std::memory_order_relaxed);
            if (current.capture_steady_us > 0 && current.last_send_done_us >= current.capture_steady_us)
            {
                udp_video_end_to_end_us_total_.fetch_add(current.last_send_done_us - current.capture_steady_us,
                                                         std::memory_order_relaxed);
                udp_video_end_to_end_samples_.fetch_add(1, std::memory_order_relaxed);
            }
            current = FrameStats{};
        };

        auto send_datagram = [&](QueueItem &item, uint64_t pacing_us) -> SendAttemptResult {
            const uint64_t dequeue_steady_us = nowSteadyUs();
            if (item.stream == QueueItem::Stream::Video && current.packets == 0)
            {
                current.frame_id = item.group_id;
                current.capture_steady_us = item.frame_capture_steady_us;
                send_queue_.setProtectedVideoGroup(item.group_id);
            }
            if (item.stream == QueueItem::Stream::Video && item.enqueue_steady_us > 0 && dequeue_steady_us >= item.enqueue_steady_us)
            {
                udp_video_queue_delay_us_total_.fetch_add(dequeue_steady_us - item.enqueue_steady_us,
                                                          std::memory_order_relaxed);
                udp_video_queue_delay_samples_.fetch_add(1, std::memory_order_relaxed);
            }

            const auto send_start = std::chrono::steady_clock::now();
            errno = 0;
            const int sent = socket_->send(item.bytes.data(), item.bytes.size());
            const int send_errno = errno;
            const auto send_end = std::chrono::steady_clock::now();

            if (sent < 0)
            {
                if (send_errno == EAGAIN || send_errno == EWOULDBLOCK || send_errno == ENOBUFS)
                {
                    udp_send_block_events_.fetch_add(1, std::memory_order_relaxed);
                    RCLCPP_WARN_THROTTLE(logger(), steady_clock, 1000,
                                         "UDP send backpressure: stream=%d bytes=%zu errno=%d (%s); requeueing packet",
                                         static_cast<int>(item.stream), item.bytes.size(), send_errno, std::strerror(send_errno));
                    return SendAttemptResult::kWouldBlock;
                }

                udp_send_drop_packets_.fetch_add(1, std::memory_order_relaxed);
                RCLCPP_WARN_THROTTLE(logger(), steady_clock, 1000,
                                     "UDP send failed: stream=%d bytes=%zu errno=%d (%s); dropping packet",
                                     static_cast<int>(item.stream), item.bytes.size(), send_errno, std::strerror(send_errno));
                return SendAttemptResult::kDropped;
            }
            if (static_cast<size_t>(sent) != item.bytes.size())
            {
                udp_send_drop_packets_.fetch_add(1, std::memory_order_relaxed);
                RCLCPP_WARN_THROTTLE(logger(), steady_clock, 1000,
                                     "UDP send short write: stream=%d bytes=%zu sent=%d; dropping packet",
                                     static_cast<int>(item.stream), item.bytes.size(), sent);
                return SendAttemptResult::kDropped;
            }

            if (item.stream == QueueItem::Stream::Video)
            {
                current.packets += 1;
                current.last_send_done_us = static_cast<uint64_t>(
                    std::chrono::duration_cast<std::chrono::microseconds>(send_end.time_since_epoch()).count());
                udp_sent_video_packets_.fetch_add(1, std::memory_order_relaxed);
                udp_sent_video_bytes_.fetch_add(item.bytes.size(), std::memory_order_relaxed);
                udp_video_pacing_us_total_.fetch_add(pacing_us, std::memory_order_relaxed);
                udp_video_send_syscall_us_total_.fetch_add(static_cast<uint64_t>(
                                                               std::chrono::duration_cast<std::chrono::microseconds>(send_end - send_start).count()),
                                                           std::memory_order_relaxed);
            }
            return SendAttemptResult::kSent;
        };

        auto handle_queue_item = [&](QueueItem &item, uint64_t pacing_us) -> SendAttemptResult {
            if (item.kind == QueueItem::Kind::GroupEnd)
            {
                if (item.stream == QueueItem::Stream::Video)
                {
                    flush_frame();
                }
                return SendAttemptResult::kDropped;
            }
            if (item.kind != QueueItem::Kind::Datagram)
            {
                return SendAttemptResult::kDropped;
            }
            return send_datagram(item, pacing_us);
        };

        auto update_pacer_stats = [&](size_t queue_bytes) {
            const auto stats = webrtc_like_pacer_.stats(queue_bytes, std::chrono::steady_clock::now());
            udp_pacer_debt_us_.store(stats.debt_us, std::memory_order_relaxed);
            udp_pacer_expected_queue_us_.store(stats.expected_queue_us, std::memory_order_relaxed);
            udp_pacer_adjusted_bps_.store(stats.adjusted_pacing_bps, std::memory_order_relaxed);
        };

        if (config_.pacing_mode == PacingMode::Legacy)
        {
            while (state_.running.load())
            {
                QueueItem item;
                if (!send_queue_.pop(item, 20))
                {
                    continue;
                }
                if (item.kind == QueueItem::Kind::GroupEnd)
                {
                    if (item.stream == QueueItem::Stream::Video)
                    {
                        flush_frame();
                    }
                    continue;
                }
                if (item.kind != QueueItem::Kind::Datagram)
                {
                    continue;
                }

                const auto pace_start = std::chrono::steady_clock::now();
                pacer_.pace(item.wire_bytes, config_.pacing_enabled, config_.pacing_bps);
                const auto pace_end = std::chrono::steady_clock::now();
                const uint64_t pacing_us = static_cast<uint64_t>(
                    std::chrono::duration_cast<std::chrono::microseconds>(pace_end - pace_start).count());
                const SendAttemptResult send_result = handle_queue_item(item, pacing_us);
                if (send_result == SendAttemptResult::kWouldBlock && item.kind == QueueItem::Kind::Datagram)
                {
                    send_queue_.requeueFront(std::move(item));
                    (void)socket_->waitWritable(2);
                }
            }
            return;
        }

        uint64_t pending_video_pacing_us = 0;
        while (state_.running.load())
        {
            SendQueue::ItemMeta next_meta;
            if (!send_queue_.peekPrioritized(next_meta, 20))
            {
                continue;
            }

            auto queue_status = send_queue_.status();
            const bool next_packet_accounted = next_meta.pacing_accounted && config_.pacing_enabled;
            const auto wait_start = std::chrono::steady_clock::now();
            const auto wait_for = webrtc_like_pacer_.timeUntilNextSend(queue_status.bytes, next_packet_accounted, wait_start);
            update_pacer_stats(queue_status.bytes);
            if (wait_for.count() > 0)
            {
                send_queue_.waitForDataFor(wait_for);
                const auto wait_end = std::chrono::steady_clock::now();
                const uint64_t waited_us = static_cast<uint64_t>(
                    std::chrono::duration_cast<std::chrono::microseconds>(wait_end - wait_start).count());
                pending_video_pacing_us = std::min<uint64_t>(pending_video_pacing_us + waited_us, 1000000ULL);
                continue;
            }

            const uint32_t max_batch_packets = std::max<uint32_t>(1, config_.pacing_max_packets_per_batch);
            uint32_t processed_items = 0;
            bool send_would_block = false;
            while (state_.running.load() && processed_items < max_batch_packets)
            {
                QueueItem item;
                if (!send_queue_.popPrioritized(item, 0))
                {
                    break;
                }
                ++processed_items;

                const QueueItem::Stream item_stream = item.stream;
                const size_t item_wire_bytes = item.wire_bytes;
                const bool item_pacing_accounted = item.pacing_accounted && config_.pacing_enabled;
                const uint64_t pacing_us = item_stream == QueueItem::Stream::Video ? pending_video_pacing_us : 0;
                send_would_block = false;
                const SendAttemptResult send_result = handle_queue_item(item, pacing_us);
                if (send_result == SendAttemptResult::kWouldBlock && item.kind == QueueItem::Kind::Datagram)
                {
                    // Keep the send path simple: preserve order, back off in the pacer,
                    // and let the queue's backlog/capacity policy decide what to evict.
                    send_queue_.requeueFront(std::move(item));
                    queue_status = send_queue_.status();
                    webrtc_like_pacer_.onBlocked(item_wire_bytes,
                                                 queue_status.bytes,
                                                 std::chrono::steady_clock::now());
                    update_pacer_stats(queue_status.bytes);
                    send_would_block = true;
                }
                if (item_stream == QueueItem::Stream::Video)
                {
                    pending_video_pacing_us = 0;
                }

                if (send_result == SendAttemptResult::kSent)
                {
                    queue_status = send_queue_.status();
                    webrtc_like_pacer_.onPacketSent(item_wire_bytes,
                                                    item_pacing_accounted,
                                                    queue_status.bytes,
                                                    std::chrono::steady_clock::now());
                    update_pacer_stats(queue_status.bytes);
                }

                SendQueue::ItemMeta following_meta;
                if (!send_queue_.peekPrioritized(following_meta, 0))
                {
                    break;
                }
                if (send_would_block)
                {
                    break;
                }
                queue_status = send_queue_.status();
                const bool following_accounted = following_meta.pacing_accounted && config_.pacing_enabled;
                const auto next_wait = webrtc_like_pacer_.timeUntilNextSend(queue_status.bytes, following_accounted,
                                                                           std::chrono::steady_clock::now());
                update_pacer_stats(queue_status.bytes);
                if (next_wait.count() > 0)
                {
                    break;
                }
            }
        }
    }

    UdpManager::VideoStatsSnapshot UdpManager::consumeVideoStats()
    {
        VideoStatsSnapshot snapshot;
        const auto queue_snapshot = send_queue_.snapshot();

        snapshot.input_frames = video_input_frames_.exchange(0, std::memory_order_relaxed);
        snapshot.input_bytes = video_input_bytes_.exchange(0, std::memory_order_relaxed);
        snapshot.input_drops = video_input_drops_.exchange(0, std::memory_order_relaxed);
        snapshot.queue_drops = queue_snapshot.dropped_video_groups;
        snapshot.send_block_events = udp_send_block_events_.exchange(0, std::memory_order_relaxed);
        snapshot.send_drop_packets = udp_send_drop_packets_.exchange(0, std::memory_order_relaxed);
        snapshot.fec_output_packets = fec_output_packets_.exchange(0, std::memory_order_relaxed);
        snapshot.sent_frames = udp_sent_video_frames_.exchange(0, std::memory_order_relaxed);
        snapshot.sent_packets = udp_sent_video_packets_.exchange(0, std::memory_order_relaxed);
        snapshot.sent_bytes = udp_sent_video_bytes_.exchange(0, std::memory_order_relaxed);
        snapshot.cap_to_fec_us_total = cap_to_fec_us_total_.exchange(0, std::memory_order_relaxed);
        snapshot.cap_to_fec_samples = cap_to_fec_samples_.exchange(0, std::memory_order_relaxed);
        snapshot.fec_internal_wait_us_total = fec_internal_wait_us_total_.exchange(0, std::memory_order_relaxed);
        snapshot.fec_internal_wait_samples = fec_internal_wait_samples_.exchange(0, std::memory_order_relaxed);
        snapshot.send_queue_delay_us_total = udp_video_queue_delay_us_total_.exchange(0, std::memory_order_relaxed);
        snapshot.send_queue_delay_samples = udp_video_queue_delay_samples_.exchange(0, std::memory_order_relaxed);
        snapshot.pacing_us_total = udp_video_pacing_us_total_.exchange(0, std::memory_order_relaxed);
        snapshot.send_syscall_us_total = udp_video_send_syscall_us_total_.exchange(0, std::memory_order_relaxed);
        snapshot.end_to_end_us_total = udp_video_end_to_end_us_total_.exchange(0, std::memory_order_relaxed);
        snapshot.end_to_end_samples = udp_video_end_to_end_samples_.exchange(0, std::memory_order_relaxed);
        snapshot.pacer_debt_us = udp_pacer_debt_us_.load(std::memory_order_relaxed);
        snapshot.pacer_expected_queue_us = udp_pacer_expected_queue_us_.load(std::memory_order_relaxed);
        snapshot.pacer_adjusted_bps = udp_pacer_adjusted_bps_.load(std::memory_order_relaxed);
        snapshot.queue_packets = queue_snapshot.packets;
        snapshot.queue_bytes = queue_snapshot.bytes;
        return snapshot;
    }

    uint64_t UdpManager::currentNtpTimestamp() const
    {
        const auto now = std::chrono::system_clock::now();
        const auto duration = now.time_since_epoch();
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration) - seconds;
        const uint32_t ntp_seconds = static_cast<uint32_t>(seconds.count() + 2208988800U);
        const uint32_t ntp_fraction = static_cast<uint32_t>((microseconds.count() * 4294967296.0) / 1000000.0);
        return (static_cast<uint64_t>(ntp_seconds) << 32) | ntp_fraction;
    }

} // namespace trb::udp