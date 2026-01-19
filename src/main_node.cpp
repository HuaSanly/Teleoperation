#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cinttypes>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <vector>
#include <functional>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "main_node.hpp"
#include "utils/teleop_logger.hpp"

namespace trb
{

    MainNode::MainNode() : Node("main_node")
    {
        this->initGrpc();
        this->signaling_client_->connect();
        this->signaling_client_->registerRobot();
        this->initVideo();
        this->initUdp();
        this->initPoseUdp();

        if (this->udp_stream_manager_ && this->signaling_client_)
        {
            this->udp_stream_manager_->setSessionId(this->signaling_client_->sessionId());
        }
    }
    // -----------------thread handles------------------

    // ------------------init methods-------------------

    void MainNode::initVideo()
    {
        if (!video_stream_manager_)
        {
            video_stream_manager_ = std::make_unique<trb::video::VideoStreamManager>(*this);
        }

        video_stream_manager_->setEncodedFrameCallback(
            [this](const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)
            {
                if (this->udp_stream_manager_)
                {
                    this->udp_stream_manager_->sendH264Frame(data, size, timestamp_us, keyframe);
                }
            });

        if (!video_stream_manager_->start())
        {
            RCLCPP_ERROR(this->get_logger(), "VideoStreamManager start failed");
        }
    }

    void MainNode::initUdp()
    {
        std::string udp_ip = this->declare_parameter<std::string>("udp_ip", "192.168.3.2");
        int udp_port = this->declare_parameter<int>("udp_port", 7778);

        // Optional: unified logging file sink (selective topics).
        const bool log_file_enabled = this->declare_parameter<bool>("logging.file.enabled", false);
        const std::string log_file_path = this->declare_parameter<std::string>("logging.file.path", "/tmp/teleop_robot_bridge.log");
        const std::vector<std::string> log_file_topics = this->declare_parameter<std::vector<std::string>>("logging.file.topics", std::vector<std::string>{});
        const uint32_t log_topic_mask = trb::utils::TeleopLogger::fileTopicsFromStrings(log_file_topics, this->get_logger());
        trb::utils::TeleopLogger::instance().configureFileLogging(log_file_enabled, log_file_path, log_topic_mask);

        const bool stop_after_frames_enabled = this->declare_parameter<bool>("udp.stop_after_frames.enabled", false);
        const int stop_after_frames_max_frames_param = this->declare_parameter<int>("udp.stop_after_frames.max_frames", 0);
        const uint32_t stop_after_frames_max_frames = static_cast<uint32_t>(std::max(0, stop_after_frames_max_frames_param));

        const int header_log_max_packets_param = this->declare_parameter<int>("udp.header_log.max_packets", 8);
        const uint64_t header_log_max_packets = static_cast<uint64_t>(std::max(0, header_log_max_packets_param));

        // FEC (V2): selected by FecTableId only. Current sender supports only table_id=1.
        const bool fec_enabled = this->declare_parameter<bool>("udp.fec.enabled", true);
        const int fec_table_id_param = this->declare_parameter<int>("udp.fec.table_id", 1);

        uint8_t fec_table_id = static_cast<uint8_t>(fec_table_id_param & 0xFF);

        // Validate table_id.
        if (fec_enabled)
        {
            if (fec_table_id == 1)
            {
                RCLCPP_INFO(
                    this->get_logger(),
                    "FEC enabled: table_id=%u (V2 implicit grouping)",
                    static_cast<unsigned>(fec_table_id));
            }
            else
            {
                RCLCPP_WARN(
                    this->get_logger(),
                    "FEC enabled but unsupported table_id=%u; disabling FEC (only table_id=1 supported)",
                    static_cast<unsigned>(fec_table_id));
                fec_table_id = 0;
            }
        }
        else
        {
            fec_table_id = 0;
        }

        // UDP pacing (smooth sending) defaults.
        // If video.encoder.bitrate is available, use it to derive a reasonable on-wire pacing rate.
        int64_t encoder_bitrate_bps = 20000000;
        this->get_parameter_or("video.encoder.bitrate", encoder_bitrate_bps, encoder_bitrate_bps);

        double overhead = 1.0;
        if (fec_table_id != 0)
        {
            // Conservative overhead estimate for pacing: assume a worst-case redundancy.
            // Roughly 1.25x payload.
            overhead *= 1.25;
        }
        // Add header overhead (V2 header is 26 bytes over a 1200B payload).
        overhead *= ((1200.0 + 26.0) / 1200.0);
        // Small safety margin for variability.
        overhead *= 1.05;

        const uint64_t default_pacing_bps = static_cast<uint64_t>(std::llround(static_cast<double>(encoder_bitrate_bps) * overhead));
        const bool pacing_enabled = this->declare_parameter<bool>("udp.pacing.enabled", true);
        const int64_t pacing_bps = this->declare_parameter<int64_t>("udp.pacing.bps", static_cast<int64_t>(default_pacing_bps));
        const int pacing_queue_max_packets = this->declare_parameter<int>("udp.pacing.queue_max_packets", 1024);
        const int pacing_queue_max_bytes = this->declare_parameter<int>("udp.pacing.queue_max_bytes", 1024 * 1024);

        const bool udp_send_nonblocking = this->declare_parameter<bool>("udp.send.nonblocking", true);
        const int udp_send_sndbuf_bytes = this->declare_parameter<int>("udp.send.sndbuf_bytes", 0);

        udp_stream_manager_ = std::make_unique<trb::udp::UdpStreamManager>(udp_ip, udp_port);
        if (!udp_stream_manager_->start())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to start UDP stream manager");
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "UDP stream manager started on %s:%d", udp_ip.c_str(), udp_port);
        }

        if (udp_stream_manager_)
        {
            udp_stream_manager_->setPacingEnabled(pacing_enabled);
            udp_stream_manager_->setPacingRateBps(pacing_bps > 0 ? static_cast<uint64_t>(pacing_bps) : 0ULL);
            udp_stream_manager_->setQueueLimits(
                pacing_queue_max_packets > 0 ? static_cast<size_t>(pacing_queue_max_packets) : 0ULL,
                pacing_queue_max_bytes > 0 ? static_cast<size_t>(pacing_queue_max_bytes) : 0ULL);

            udp_stream_manager_->setSendNonBlocking(udp_send_nonblocking);
            if (udp_send_sndbuf_bytes > 0)
            {
                udp_stream_manager_->setSendBufferBytes(udp_send_sndbuf_bytes);
            }

            udp_stream_manager_->setStopAfterFramesMaxFrames(stop_after_frames_max_frames);
            udp_stream_manager_->setStopAfterFramesEnabled(stop_after_frames_enabled);

            udp_stream_manager_->setHeaderLogMaxPackets(header_log_max_packets);
        }

        if (udp_stream_manager_)
        {
            udp_stream_manager_->setFecTableId(fec_table_id);
        }
    }

    void MainNode::initPoseUdp()
    {
        const bool enabled = this->declare_parameter<bool>("pose_udp.enabled", false);
        if (!enabled)
        {
            RCLCPP_INFO(this->get_logger(), "Pose UDP receiver disabled (pose_udp.enabled=false)");
            return;
        }

        if (!udp_stream_manager_)
        {
            RCLCPP_ERROR(this->get_logger(), "Pose UDP receiver enabled but udp_stream_manager_ is null");
            return;
        }

        trb::udp::PoseUdpReceiverConfig cfg;
        // NOTE: We reuse UdpStreamManager's socket/recv thread; these bind/timeout settings are kept
        // for backward compatibility with standalone mode, but are not used in shared-socket mode.
        cfg.bind_ip = this->declare_parameter<std::string>("pose_udp.bind_ip", cfg.bind_ip);
        cfg.bind_port = this->declare_parameter<int>("pose_udp.bind_port", cfg.bind_port);
        cfg.allowed_remote_ip = this->declare_parameter<std::string>("pose_udp.allowed_remote_ip", cfg.allowed_remote_ip);
        cfg.recv_timeout_ms = this->declare_parameter<int>("pose_udp.recv_timeout_ms", cfg.recv_timeout_ms);
        cfg.qos_depth = this->declare_parameter<int>("pose_udp.qos.depth", cfg.qos_depth);

        cfg.frame_id_hmd = this->declare_parameter<std::string>("pose_udp.frame_id.hmd", cfg.frame_id_hmd);
        cfg.frame_id_left_controller = this->declare_parameter<std::string>("pose_udp.frame_id.left_controller", cfg.frame_id_left_controller);
        cfg.frame_id_right_controller = this->declare_parameter<std::string>("pose_udp.frame_id.right_controller", cfg.frame_id_right_controller);
        cfg.frame_id_left_aim = this->declare_parameter<std::string>("pose_udp.frame_id.left_aim", cfg.frame_id_left_aim);
        cfg.frame_id_right_aim = this->declare_parameter<std::string>("pose_udp.frame_id.right_aim", cfg.frame_id_right_aim);

        cfg.publish_euler = this->declare_parameter<bool>("pose_udp.publish_euler", true);
        cfg.publish_buttons = this->declare_parameter<bool>("pose_udp.publish_buttons", true);
        cfg.publish_aim = this->declare_parameter<bool>("pose_udp.publish_aim", true);

        pose_udp_receiver_ = std::make_unique<trb::udp::PoseUdpReceiver>(*this, cfg);

        // Hook into the existing UDP receive loop.
        udp_stream_manager_->setPoseDatagramCallback(
            [this](const uint8_t *data, size_t size)
            {
                if (this->pose_udp_receiver_)
                {
                    this->pose_udp_receiver_->handleDatagram(data, size);
                }
            });

        RCLCPP_INFO(this->get_logger(), "Pose UDP receiver enabled (shared socket via UdpStreamManager)");
    }

    void MainNode::initGrpc()
    {
        // Get parameters
        std::string server_ip = this->declare_parameter<std::string>("server_ip", "127.0.0.1");
        int server_port = this->declare_parameter<int>("server_port", 8000);
        bool use_ssl = this->declare_parameter<bool>("use_ssl", false);
        std::string device_id = this->declare_parameter<std::string>("device_id", "robot_001");
        std::string token = this->declare_parameter<std::string>("token", "default_token");

        RCLCPP_INFO(this->get_logger(), "Initializing SignalingClient with IP: %s, Port: %d, SSL: %s, DeviceID: %s",
                    server_ip.c_str(), server_port, use_ssl ? "true" : "false", device_id.c_str());

        // Initialize signaling client
        signaling_client_ = std::make_shared<SignalingClient>(
            this->get_logger(),
            server_ip,
            server_port,
            token,
            device_id,
            use_ssl);

        // Create heartbeat timer (1 second interval)
        heartbeat_timer_ = this->create_wall_timer(
            std::chrono::seconds(15),
            std::bind(&MainNode::heartbeatTimerCallback, this));

        // Start event stream
        signaling_client_->startEventStream(std::bind(&MainNode::onSignalingEvent, this, std::placeholders::_1));
    }

    void MainNode::onSignalingEvent(const signaling::EventMessage &msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received EventMessage from %s", msg.sender_session_id().c_str());

        if (msg.has_pair())
        {
            const auto &pair_event = msg.pair();
            switch (pair_event.op())
            {
            case signaling::PairEvent::REQUEST:
                RCLCPP_INFO(this->get_logger(), "Pair Request from %s. Auto-accepting...", pair_event.peer_session_id().c_str());
                // Auto accept for now
                signaling_client_->acceptPair(pair_event.peer_session_id());
                break;
            case signaling::PairEvent::ACCEPT:
                RCLCPP_INFO(this->get_logger(), "Pair Accepted by %s", pair_event.peer_session_id().c_str());
                break;
            case signaling::PairEvent::REJECT:
                RCLCPP_WARN(this->get_logger(), "Pair Rejected by %s", pair_event.peer_session_id().c_str());
                break;
            case signaling::PairEvent::UNPAIR:
                RCLCPP_INFO(this->get_logger(), "Unpaired by %s", pair_event.peer_session_id().c_str());
                break;
            default:
                break;
            }
        }
        else if (msg.has_system())
        {
            const auto &sys_cmd = msg.system();
            switch (sys_cmd.action())
            {
            case signaling::SystemCommand::REQUEST_UDP_HELLO:
                RCLCPP_WARN(this->get_logger(), "Server requested UDP HELLO resend");
                // TODO: Trigger UDP HELLO resend in UdpStreamManager
                // if (udp_stream_manager_) udp_stream_manager_->forceSendHello();
                break;
            default:
                RCLCPP_INFO(this->get_logger(), "Received SystemCommand: %d", sys_cmd.action());
                break;
            }
        }
    }

    void MainNode::heartbeatTimerCallback()
    {
        if (signaling_client_)
        {
            signaling_client_->tickHeartbeat();
        }
    }

    MainNode::~MainNode()
    {
        RCLCPP_INFO(this->get_logger(), "Shutting down MainNode...");

        // 1. Cancel timers
        if (heartbeat_timer_)
        {
            heartbeat_timer_->cancel();
            heartbeat_timer_.reset();
        }

        // 2. Stop Video Pipeline (Producers)
        // This ensures no new frames are sent to UDP manager
        stopVideo();

        // 2.5 Stop Pose UDP receiver (input)
        if (udp_stream_manager_)
        {
            udp_stream_manager_->setPoseDatagramCallback(nullptr);
        }
        if (pose_udp_receiver_)
        {
            pose_udp_receiver_->stop();
            pose_udp_receiver_.reset();
        }

        // 3. Stop UDP Manager (Transport)
        if (udp_stream_manager_)
        {
            udp_stream_manager_->stop();
            udp_stream_manager_.reset();
        }

        // 4. Stop Signaling Client (Control/Events)
        if (signaling_client_)
        {
            signaling_client_->stopEventStream();
            signaling_client_.reset();
        }

        RCLCPP_INFO(this->get_logger(), "MainNode shutdown complete.");
    }

    void MainNode::stopVideo()
    {
        if (video_stream_manager_)
        {
            video_stream_manager_->stop();
            video_stream_manager_.reset();
        }
    }
}
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<trb::MainNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
