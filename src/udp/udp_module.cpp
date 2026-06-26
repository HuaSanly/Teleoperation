#include "udp/udp_module.hpp"

#include <algorithm>
#include <chrono>
#include <utility>

#include "udp/packet_codec.hpp"

namespace trb::udp
{
    namespace
    {
        template <typename T>
        T declareOrGet(rclcpp::Node &node, const std::string &name, const T &default_value)
        {
            if (!node.has_parameter(name))
            {
                return node.declare_parameter<T>(name, default_value);
            }
            T value{};
            node.get_parameter(name, value);
            return value;
        }

        bool hasValidContext(rclcpp::Node &node)
        {
            const auto base = node.get_node_base_interface();
            const auto context = base ? base->get_context() : rclcpp::Context::SharedPtr{};
            return context && context->is_valid();
        }

        uint16_t readU16LE(const uint8_t *data)
        {
            return static_cast<uint16_t>(data[0]) |
                   static_cast<uint16_t>(static_cast<uint16_t>(data[1]) << 8);
        }

        uint64_t readU64LE(const uint8_t *data)
        {
            return static_cast<uint64_t>(readU16LE(data)) |
                   (static_cast<uint64_t>(readU16LE(data + 2)) << 16) |
                   (static_cast<uint64_t>(readU16LE(data + 4)) << 32) |
                   (static_cast<uint64_t>(readU16LE(data + 6)) << 48);
        }

        std::chrono::nanoseconds periodFromSeconds(double seconds)
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(std::max(0.001, seconds)));
        }
    } // namespace

    UdpModule::Config UdpModule::Config::configFromRosParam(rclcpp::Node &node)
    {
        Config config;
        config.direct_running_mode = declareOrGet<bool>(node, "debug.direct_running_mode", false);

        auto &udp = config.udp;
        udp.remote_ip = declareOrGet<std::string>(node, "udp.server_udp_ip", "");
        udp.remote_port = declareOrGet<int>(node, "udp.server_udp_port", 0);
        udp.device_id = declareOrGet<std::string>(node, "grpc.device_id", "");
        if (udp.remote_ip.empty())
        {
            udp.remote_ip = declareOrGet<std::string>(node, "udp_ip", "");
        }
        if (udp.remote_port <= 0)
        {
            udp.remote_port = declareOrGet<int>(node, "udp_port", 0);
        }
        udp.bind_ip = declareOrGet<std::string>(node, "udp.bind_ip", "0.0.0.0");
        udp.bind_port = declareOrGet<int>(node, "udp.bind_port", 0);
        udp.enable_receive = declareOrGet<bool>(node, "udp.enable_receive", true);
        udp.control_enabled = declareOrGet<bool>(node, "udp.handshake.enabled", true);
        udp.control_hello_interval_sec = declareOrGet<double>(node, "udp.handshake.interval_sec", 1.0);
        udp.control_ping_interval_sec = declareOrGet<double>(node, "udp.handshake.ping_interval_sec", 5.0);
        udp.control_peer_lost_timeout_sec = declareOrGet<double>(node, "udp.handshake.peer_lost_timeout_sec", 0.0);
        if (config.direct_running_mode && udp.control_enabled)
        {
            udp.control_enabled = false;
            RCLCPP_INFO(node.get_logger(), "Direct running mode enabled: disabling UDP handshake/control plane");
        }

        udp.recv_timeout_ms = declareOrGet<int>(node, "udp.recv_timeout_ms", 100);
        udp.max_payload_bytes = static_cast<size_t>(std::max(1, declareOrGet<int>(node, "udp.max_payload_bytes", 1200)));
        udp.send_nonblocking = declareOrGet<bool>(node, "udp.send.nonblocking", true);
        udp.send_buffer_bytes = declareOrGet<int>(node, "udp.send.buffer_bytes", declareOrGet<int>(node, "udp.send.sndbuf_bytes", 0));

        udp.pacing_enabled = declareOrGet<bool>(node, "udp.pacing.enabled", true);
        udp.pacing_bps = static_cast<uint64_t>(std::max(0, declareOrGet<int>(node, "udp.pacing.bps", 0)));
        udp.pacing_send_burst_interval_ms = static_cast<uint32_t>(std::max(0, declareOrGet<int>(node, "udp.pacing.send_burst_interval_ms", static_cast<int>(udp.pacing_send_burst_interval_ms))));
        udp.pacing_max_burst_bytes = static_cast<size_t>(std::max(0, declareOrGet<int>(node, "udp.pacing.max_burst_bytes", static_cast<int>(udp.pacing_max_burst_bytes))));
        udp.pacing_max_debt_ms = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "udp.pacing.max_debt_ms", static_cast<int>(udp.pacing_max_debt_ms))));
        udp.pacing_queue_time_limit_ms = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "udp.pacing.queue_time_limit_ms", static_cast<int>(udp.pacing_queue_time_limit_ms))));
        udp.pacing_max_drain_multiplier = std::max(1.0, declareOrGet<double>(node, "udp.pacing.max_drain_multiplier", udp.pacing_max_drain_multiplier));
        udp.pacing_account_audio = declareOrGet<bool>(node, "udp.pacing.account_audio", udp.pacing_account_audio);
        udp.pacing_max_packets_per_batch = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "udp.pacing.max_packets_per_batch", static_cast<int>(udp.pacing_max_packets_per_batch))));
        udp.queue_max_bytes = static_cast<size_t>(std::max(0, declareOrGet<int>(node, "udp.pacing.queue_max_bytes", 300000)));
        udp.queue_max_packets = static_cast<size_t>(std::max(0, declareOrGet<int>(node, "udp.pacing.queue_max_packets", 0)));

        const bool fec_enabled = declareOrGet<bool>(node, "udp.fec.enabled", true);
        const int fec_table_id = declareOrGet<int>(node, "udp.fec.table_id", 1);
        udp.fec_table_id = fec_enabled ? static_cast<uint8_t>(std::clamp(fec_table_id, 0, 255)) : 0;
        udp.fec_input_queue_max_frames = static_cast<size_t>(std::max(1, declareOrGet<int>(node, "udp.fec.input_queue_max_frames", 2)));

        config.pose_enabled = declareOrGet<bool>(node, "udp.pose_udp.enabled", declareOrGet<bool>(node, "pose_udp.enabled", false));
        auto &pose = config.pose;
        pose.bind_ip = declareOrGet<std::string>(node, "pose_udp.bind_ip", udp.bind_ip);
        pose.bind_port = declareOrGet<int>(node, "pose_udp.bind_port", 7780);
        pose.allowed_remote_ip = declareOrGet<std::string>(node, "pose_udp.allowed_remote_ip", "");
        pose.recv_timeout_ms = declareOrGet<int>(node, "pose_udp.recv_timeout_ms", udp.recv_timeout_ms);
        pose.qos_depth = declareOrGet<int>(node, "pose_udp.qos.depth", 10);
        pose.frame_id_waist = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.waist", declareOrGet<std::string>(node, "pose_udp.frame_id.waist", "vr_waist"));
        pose.frame_id_joint24 = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.joint24", declareOrGet<std::string>(node, "pose_udp.frame_id.joint24", "vr_tracking"));
        pose.frame_id_hmd = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.hmd", declareOrGet<std::string>(node, "pose_udp.frame_id.hmd", "vr_hmd"));
        pose.frame_id_left_controller = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.left_controller", declareOrGet<std::string>(node, "pose_udp.frame_id.left_controller", "vr_left_controller"));
        pose.frame_id_right_controller = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.right_controller", declareOrGet<std::string>(node, "pose_udp.frame_id.right_controller", "vr_right_controller"));
        pose.frame_id_left_foot = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.left_foot", declareOrGet<std::string>(node, "pose_udp.frame_id.left_foot", "vr_left_foot"));
        pose.frame_id_right_foot = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.right_foot", declareOrGet<std::string>(node, "pose_udp.frame_id.right_foot", "vr_right_foot"));
        pose.frame_id_left_aim = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.left_aim", declareOrGet<std::string>(node, "pose_udp.frame_id.left_aim", "vr_left_aim"));
        pose.frame_id_right_aim = declareOrGet<std::string>(node, "udp.pose_udp.frame_id.right_aim", declareOrGet<std::string>(node, "pose_udp.frame_id.right_aim", "vr_right_aim"));
        pose.publish_euler = declareOrGet<bool>(node, "udp.pose_udp.publish_euler", declareOrGet<bool>(node, "pose_udp.publish_euler", true));
        pose.publish_buttons = declareOrGet<bool>(node, "udp.pose_udp.publish_buttons", declareOrGet<bool>(node, "pose_udp.publish_buttons", true));
        pose.publish_aim = declareOrGet<bool>(node, "udp.pose_udp.publish_aim", declareOrGet<bool>(node, "pose_udp.publish_aim", true));

        return config;
    }

    UdpModule::UdpModule(rclcpp::Node &node, Config config)
        : node_(node), logger_(node.get_logger()), config_(std::move(config))
    {
    }

    UdpModule::~UdpModule()
    {
        stop();
    }

    bool UdpModule::start(const std::string &session_id)
    {
        shutting_down_.store(false, std::memory_order_release);

        if (udp_manager_)
        {
            return true;
        }

        if (config_.udp.remote_ip.empty() || config_.udp.remote_port <= 0)
        {
            RCLCPP_WARN(logger_, "UDP config missing remote_ip/remote_port; UdpModule will not start");
            return false;
        }

        RCLCPP_INFO(logger_, "UDP config loaded: remote=%s:%d pacing_enabled=%d pacing_bps=%lu",
                    config_.udp.remote_ip.c_str(), config_.udp.remote_port,
                    config_.udp.pacing_enabled ? 1 : 0,
                    static_cast<unsigned long>(config_.udp.pacing_bps));
        RCLCPP_INFO(logger_, "UDP config loaded: queue_max_bytes=%zu queue_max_packets=%zu fec_table_id=%d fec_input_queue_max_frames=%zu",
                    config_.udp.queue_max_bytes, config_.udp.queue_max_packets,
                    static_cast<int>(config_.udp.fec_table_id),
                    config_.udp.fec_input_queue_max_frames);

        udp_manager_ = std::make_unique<UdpManager>(config_.udp);
        udp_manager_->setSessionId(session_id);

        if (config_.pose_enabled)
        {
            pose_receiver_ = std::make_unique<PoseUdpReceiver>(node_, config_.pose);
        }

        udp_manager_->setDatagramCallback([this](const uint8_t *data, size_t size) { onDatagram(data, size); });
        udp_manager_->setPeerLostCallback([this]() {
            ready_fired_.store(false);
            if (on_peer_lost_)
            {
                on_peer_lost_();
            }
        });

        if (!udp_manager_->start())
        {
            RCLCPP_ERROR(logger_, "UdpManager start failed");
            udp_manager_.reset();
            pose_receiver_.reset();
            return false;
        }

        ready_fired_.store(false);
        if (!config_.udp.control_enabled)
        {
            if (on_ready_ && !ready_fired_.exchange(true))
            {
                on_ready_();
            }
        }
        else
        {
            if (!shutting_down_.load(std::memory_order_acquire) && hasValidContext(node_))
            {
                try
                {
                    handshake_timer_ = node_.create_wall_timer(periodFromSeconds(0.2), [this]() { handshakeTimerCallback(); });
                }
                catch (const rclcpp::exceptions::RCLError &ex)
                {
                    if (!shutting_down_.load(std::memory_order_acquire))
                    {
                        RCLCPP_WARN(logger_, "Skip UDP handshake timer creation: %s", ex.what());
                    }
                }
            }
        }
        return true;
    }

    void UdpModule::stop()
    {
        shutting_down_.store(true, std::memory_order_release);
        if (handshake_timer_)
        {
            handshake_timer_->cancel();
            handshake_timer_.reset();
        }
        if (udp_manager_)
        {
            udp_manager_->stop();
            udp_manager_.reset();
        }
        pose_receiver_.reset();
        ready_fired_.store(false);
    }

    void UdpModule::resetSession()
    {
        if (shutting_down_.load(std::memory_order_acquire) || !udp_manager_)
        {
            return;
        }
        udp_manager_->resetSession();
        ready_fired_.store(false);
        if (config_.udp.control_enabled)
        {
            if (!handshake_timer_)
            {
                if (!hasValidContext(node_))
                {
                    return;
                }
                try
                {
                    handshake_timer_ = node_.create_wall_timer(periodFromSeconds(0.2), [this]() { handshakeTimerCallback(); });
                }
                catch (const rclcpp::exceptions::RCLError &ex)
                {
                    if (!shutting_down_.load(std::memory_order_acquire))
                    {
                        RCLCPP_WARN(logger_, "Skip UDP handshake timer recreation: %s", ex.what());
                    }
                }
            }
            else
            {
                try
                {
                    handshake_timer_->reset();
                }
                catch (const rclcpp::exceptions::RCLError &ex)
                {
                    if (!shutting_down_.load(std::memory_order_acquire))
                    {
                        RCLCPP_WARN(logger_, "Skip UDP handshake timer reset: %s", ex.what());
                    }
                }
            }
        }
    }

    bool UdpModule::isHandshakeReady() const
    {
        return udp_manager_ && udp_manager_->isHandshakeReady();
    }

    void UdpModule::sendH264Frame(const uint8_t *data, size_t size, uint64_t capture_timestamp_us, bool keyframe)
    {
        if (udp_manager_)
        {
            udp_manager_->sendH264Frame(data, size, capture_timestamp_us, keyframe);
        }
    }

    void UdpModule::sendAudioPacket(const uint8_t *data, size_t size, uint64_t timestamp_ntp)
    {
        if (udp_manager_)
        {
            udp_manager_->sendAudioPacket(data, size, timestamp_ntp);
        }
    }

    void UdpModule::sendRobotTelemetry(const telemetry::RobotTelemetrySnapshot &snapshot)
    {
        if (udp_manager_)
        {
            udp_manager_->sendRobotTelemetry(snapshot);
        }
    }

    void UdpModule::sendRobotJointTelemetry(const telemetry::RobotJointTelemetrySnapshot &snapshot)
    {
        if (udp_manager_)
        {
            udp_manager_->sendRobotJointTelemetry(snapshot);
        }
    }

    UdpManager::VideoStatsSnapshot UdpModule::consumeVideoStats()
    {
        if (!udp_manager_)
        {
            return UdpManager::VideoStatsSnapshot{};
        }
        return udp_manager_->consumeVideoStats();
    }

    void UdpModule::onDatagram(const uint8_t *data, size_t size)
    {
        if (shutting_down_.load(std::memory_order_acquire))
        {
            return;
        }

        if (size > 11 && data[0] == kAudioPacketType)
        {
            if (audio_callback_)
            {
                const uint16_t seq = readU16LE(data + 1);
                const uint64_t timestamp_ntp = readU64LE(data + 3);
                audio_callback_(seq, data + 11, size - 11, timestamp_ntp);
            }
            return;
        }

        if (pose_receiver_)
        {
            pose_receiver_->handleDatagram(data, size);
        }
    }

    void UdpModule::handshakeTimerCallback()
    {
        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        if (shutting_down_.load(std::memory_order_acquire))
        {
            if (handshake_timer_)
            {
                handshake_timer_->cancel();
            }
            return;
        }
        if (!udp_manager_)
        {
            if (handshake_timer_)
            {
                handshake_timer_->cancel();
            }
            return;
        }
        if (udp_manager_->isHandshakeReady())
        {
            if (handshake_timer_)
            {
                handshake_timer_->cancel();
            }
            if (on_ready_ && !ready_fired_.exchange(true))
            {
                on_ready_();
            }
            return;
        }
        RCLCPP_WARN_THROTTLE(logger_, steady_clock, 2000, "Waiting for UDP handshake ACK...");
    }

} // namespace trb::udp
