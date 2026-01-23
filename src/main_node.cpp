#include "main_node.hpp"

#include <algorithm>
#include <chrono>

namespace trb
{


MainNode::MainNode(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(std::move(nh)), pnh_(std::move(pnh)) //nh公有、pnh私有
{
    loadParams();
    initGrpc();
    ROS_INFO("teleoperation_robot_bridge node initialized");

    // TODO: 初始化各模块，并将 config_ 传入各模块
    // initGrpc(config_)
    // initVideo(config_)
    // initUdp(config_)
    // initPoseUdp(config_)
}
// ------------init------------
void MainNode::initGrpc()
{
    signaling_client_ = std::make_shared<SignalingClient>(
        config_.server_ip,
        config_.server_port,
        config_.token,
        config_.device_id,
        config_.use_ssl);

    signaling_client_->connect();

    tryRegister();

    if (!grpc_registered_)
    {
        register_retry_timer_ = nh_.createTimer(
            ros::Duration(config_.grpc_register_retry_sec),
            &MainNode::registerRetryTimerCallback,
            this);
        ROS_WARN("gRPC register failed, entering pending state. Will retry every %.1f seconds.", config_.grpc_register_retry_sec);
    }
}

void MainNode::initUdp()
{
    if (udp_manager_)
    {
        return;
    }

    udp_control_ready_ = false;
    ROS_INFO("Initializing UDP control plane...");

    udp::UdpConfig cfg;
    cfg.remote_ip = config_.udp_ip;
    cfg.remote_port = config_.udp_port;
    cfg.enable_receive = config_.pose_udp_enabled || config_.udp_handshake_enabled;
    cfg.control_enabled = config_.udp_handshake_enabled;
    cfg.control_hello_interval_sec = config_.udp_handshake_interval_sec;
    cfg.control_ping_interval_sec = config_.udp_ping_interval_sec;
    cfg.control_timeout_sec = config_.udp_handshake_timeout_sec;
    cfg.max_payload_bytes = static_cast<size_t>(std::max(200, config_.udp_max_payload_bytes));

    cfg.bind_ip = "0.0.0.0";
    cfg.bind_port = 0;
    cfg.allowed_remote_ip.clear();
    cfg.recv_timeout_ms = config_.pose_udp_enabled ? config_.pose_udp_recv_timeout_ms
                                                  : config_.udp_recv_timeout_ms;

    udp_manager_ = std::make_unique<udp::UdpManager>(cfg);
    if (!udp_manager_->start())
    {
        ROS_ERROR("UdpManager start failed");
        udp_manager_.reset();
        return;
    }

    udp_manager_->setSessionId(signaling_client_ ? signaling_client_->sessionId() : "");

    udp::UdpVideoSenderConfig video_cfg;
    video_cfg.max_payload_bytes = static_cast<size_t>(std::max(200, config_.udp_max_payload_bytes));
    video_cfg.pacing_enabled = config_.udp_pacing_enabled;
    video_cfg.pacing_bps = static_cast<uint64_t>(std::max(0, config_.udp_pacing_bps));
    video_cfg.queue_max_packets = static_cast<size_t>(std::max(0, config_.udp_pacing_queue_max_packets));
    video_cfg.queue_max_bytes = static_cast<size_t>(std::max(0, config_.udp_pacing_queue_max_bytes));
    video_cfg.fec_enabled = config_.udp_fec_enabled;
    video_cfg.fec_table_id = static_cast<uint8_t>(config_.udp_fec_table_id & 0xFF);

    udp_video_sender_ = std::make_unique<udp::UdpVideoSender>(video_cfg);
    udp_video_sender_->start(udp_manager_.get());
    udp_video_sender_->pause();

    if (config_.pose_udp_enabled)
    {
        udp::PoseUdpReceiverConfig pose_cfg;
        pose_cfg.frame_id_hmd = config_.pose_udp_frame_id_hmd;
        pose_cfg.frame_id_left_controller = config_.pose_udp_frame_id_left_controller;
        pose_cfg.frame_id_right_controller = config_.pose_udp_frame_id_right_controller;
        pose_cfg.frame_id_left_aim = config_.pose_udp_frame_id_left_aim;
        pose_cfg.frame_id_right_aim = config_.pose_udp_frame_id_right_aim;
        pose_cfg.publish_euler = config_.pose_udp_publish_euler;
        pose_cfg.publish_buttons = config_.pose_udp_publish_buttons;
        pose_cfg.publish_aim = config_.pose_udp_publish_aim;
        pose_cfg.queue_size = config_.pose_udp_qos_depth;

        pose_udp_receiver_ = std::make_unique<udp::PoseUdpReceiver>(nh_, pose_cfg);

        ROS_INFO("Pose UDP receiver enabled (shared UDP socket)");
    }
    else
    {
        ROS_INFO("Pose UDP receiver disabled");
    }

    udp_manager_->setDatagramCallback(
        [this](const uint8_t *data, size_t size)
        {
            if (pose_udp_receiver_)
            {
                pose_udp_receiver_->handleDatagram(data, size);
            }
        });
}

// ------------state machine------------
void MainNode::tryRegister()
{
    if (grpc_registered_ || !signaling_client_)
    {
        return;
    }

    const int rc = signaling_client_->registerRobot();
    if (rc == 0)
    {
        grpc_registered_ = true;
        setState(State::kRegistered, "grpc registered");
        initUdp();

        udp_ready_timer_ = nh_.createTimer(
            ros::Duration(0.2),
            &MainNode::udpReadyTimerCallback,
            this);

        tryEnterPairing();
    }
}

void MainNode::enterPairingState()
{
    if (state_.load() == State::kPairing)
    {
        return;
    }

    setState(State::kPairing, "grpc+udp ready, waiting for pair");

    if (udp_video_sender_)
    {
        udp_video_sender_->pause();
    }

    if (signaling_client_)
    {
        signaling_client_->startEventStream(
            [this](const signaling::EventMessage &msg)
            {
                this->onSignalingEvent(msg);
            });
    }

    if (pairing_running_)
    {
        return;
    }

    pairing_running_ = true;
    pairing_thread_ = std::thread(
        [this]
        {
            while (pairing_running_)
            {
                if (state_.load() == State::kPairing)
                {
                    if (paired_)
                    {
                        enterRunningState();
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });
}

void MainNode::enterRunningState()
{
    if (state_.load() == State::kRunning)
    {
        return;
    }

    if (!paired_)
    {
        return;
    }

    setState(State::kRunning, "grpc+udp ready");

    if (register_retry_timer_.hasStarted())
    {
        register_retry_timer_.stop();
    }

    heartbeat_timer_ = nh_.createTimer(
        ros::Duration(config_.grpc_heartbeat_sec),
        &MainNode::heartbeatTimerCallback,
        this);

    if (udp_video_sender_)
    {
        udp_video_sender_->resume();
    }
    ROS_INFO("Node entered running state.");
}

void MainNode::tryEnterPairing()
{
    if (state_.load() == State::kRunning || state_.load() == State::kPairing)
    {
        return;
    }

    if (grpc_registered_ && udp_control_ready_)
    {
        enterPairingState();
    }
}

void MainNode::setState(State next, const std::string &reason)
{
    if (state_.load() == next)
    {
        return;
    }

    const State prev = state_.load();
    state_.store(next);
    ROS_INFO("State transition: %s -> %s (%s)", stateToString(prev), stateToString(next), reason.c_str());
}

// ------------callback------------
void MainNode::onSignalingEvent(const signaling::EventMessage &msg)
{
    ROS_INFO("Received EventMessage from %s", msg.sender_session_id().c_str());

    if (msg.has_pair())
    {
        const auto &pair_event = msg.pair();
        switch (pair_event.op())
        {
        case signaling::PairEvent::REQUEST:
            ROS_INFO("Pair Request from %s. Auto-accepting...", pair_event.peer_session_id().c_str());
            if (signaling_client_ && signaling_client_->acceptPair(pair_event.peer_session_id()) == 0)
            {
                std::lock_guard<std::mutex> lock(paired_mutex_);
                paired_peer_session_id_ = pair_event.peer_session_id();
                paired_ = true;
            }
            break;
        case signaling::PairEvent::ACCEPT:
            ROS_INFO("Pair Accepted by %s", pair_event.peer_session_id().c_str());
            {
                std::lock_guard<std::mutex> lock(paired_mutex_);
                paired_peer_session_id_ = pair_event.peer_session_id();
                paired_ = true;
            }
            break;
        case signaling::PairEvent::REJECT:
            ROS_WARN("Pair Rejected by %s", pair_event.peer_session_id().c_str());
            paired_ = false;
            break;
        case signaling::PairEvent::UNPAIR:
            ROS_INFO("Unpaired by %s", pair_event.peer_session_id().c_str());
            {
                std::lock_guard<std::mutex> lock(paired_mutex_);
                paired_peer_session_id_.clear();
                paired_ = false;
            }
            if (state_.load() == State::kRunning)
            {
                setState(State::kPairing, "unpaired");
                if (udp_video_sender_)
                {
                    udp_video_sender_->pause();
                }
            }
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
            ROS_WARN("Server requested UDP HELLO resend");
            // TODO: Trigger UDP HELLO resend
            break;
        default:
            ROS_INFO("Received SystemCommand: %d", static_cast<int>(sys_cmd.action()));
            break;
        }
    }
}

void MainNode::heartbeatTimerCallback(const ros::TimerEvent &event)
{
    (void)event;
    if (signaling_client_)
    {
        signaling_client_->tickHeartbeat();
    }
}

void MainNode::registerRetryTimerCallback(const ros::TimerEvent &event)
{
    (void)event;
    tryRegister();
}

void MainNode::udpReadyTimerCallback(const ros::TimerEvent &event)
{
    (void)event;
    if (!udp_manager_)
    {
        return;
    }

    if (udp_manager_->isHandshakeReady())
    {
        if (!udp_control_ready_)
        {
            udp_control_ready_ = true;
            ROS_INFO("UDP control ready.");
        }
        if (udp_ready_timer_.hasStarted())
        {
            udp_ready_timer_.stop();
        }
        tryEnterPairing();
    }
    else if (udp_control_ready_)
    {
        udp_control_ready_ = false;
        if (state_.load() == State::kRunning)
        {
            setState(State::kRegistered, "udp control lost");
            if (udp_video_sender_)
            {
                udp_video_sender_->pause();
            }
        }
    }
}
void MainNode::loadParams()
{
    // Signaling
    pnh_.param<std::string>("server_ip", config_.server_ip, "127.0.0.1");
    pnh_.param<int>("server_port", config_.server_port, 8000);
    pnh_.param<bool>("use_ssl", config_.use_ssl, false);
    pnh_.param<std::string>("device_id", config_.device_id, "robot_001");
    pnh_.param<std::string>("token", config_.token, "default_token");
    pnh_.param<double>("grpc/register_retry_sec", config_.grpc_register_retry_sec, 3.0);
    pnh_.param<double>("grpc/heartbeat_sec", config_.grpc_heartbeat_sec, 15.0);

    // UDP
    pnh_.param<std::string>("udp_ip", config_.udp_ip, "192.168.3.2");
    pnh_.param<int>("udp_port", config_.udp_port, 7778);
    pnh_.param<int>("udp/recv_timeout_ms", config_.udp_recv_timeout_ms, 100);
    pnh_.param<bool>("udp/pacing/enabled", config_.udp_pacing_enabled, true);
    pnh_.param<int>("udp/pacing/bps", config_.udp_pacing_bps, 30000000);
    pnh_.param<int>("udp/pacing/queue_max_packets", config_.udp_pacing_queue_max_packets, 1024);
    pnh_.param<int>("udp/pacing/queue_max_bytes", config_.udp_pacing_queue_max_bytes, 300000);
    pnh_.param<bool>("udp/handshake/enabled", config_.udp_handshake_enabled, true);
    pnh_.param<double>("udp/handshake/interval_sec", config_.udp_handshake_interval_sec, 1.0);
    pnh_.param<double>("udp/handshake/ping_interval_sec", config_.udp_ping_interval_sec, 5.0);
    pnh_.param<double>("udp/handshake/timeout_sec", config_.udp_handshake_timeout_sec, 10.0);
    pnh_.param<int>("udp/max_payload_bytes", config_.udp_max_payload_bytes, 1200);

    pnh_.param<bool>("udp/fec/enabled", config_.udp_fec_enabled, true);
    pnh_.param<int>("udp/fec/table_id", config_.udp_fec_table_id, 1);

    // Pose UDP
    pnh_.param<bool>("pose_udp/enabled", config_.pose_udp_enabled, false);
    pnh_.param<int>("pose_udp/recv_timeout_ms", config_.pose_udp_recv_timeout_ms, 100);
    pnh_.param<int>("pose_udp/qos/depth", config_.pose_udp_qos_depth, 10);
    pnh_.param<std::string>("pose_udp/frame_id/hmd", config_.pose_udp_frame_id_hmd, "vr_hmd");
    pnh_.param<std::string>("pose_udp/frame_id/left_controller", config_.pose_udp_frame_id_left_controller, "vr_left_controller");
    pnh_.param<std::string>("pose_udp/frame_id/right_controller", config_.pose_udp_frame_id_right_controller, "vr_right_controller");
    pnh_.param<std::string>("pose_udp/frame_id/left_aim", config_.pose_udp_frame_id_left_aim, "vr_left_aim");
    pnh_.param<std::string>("pose_udp/frame_id/right_aim", config_.pose_udp_frame_id_right_aim, "vr_right_aim");
    pnh_.param<bool>("pose_udp/publish_euler", config_.pose_udp_publish_euler, true);
    pnh_.param<bool>("pose_udp/publish_buttons", config_.pose_udp_publish_buttons, true);
    pnh_.param<bool>("pose_udp/publish_aim", config_.pose_udp_publish_aim, true);

    // Video
    if (!pnh_.getParam("video/profile", config_.video_profile))
    {
        config_.video_profile = {3840, 1520, 30};
    }
    pnh_.param<std::string>("video/device", config_.video_device, "/dev/video0");
    pnh_.param<std::string>("video/pixel_format", config_.video_pixel_format, "mjpeg");
    pnh_.param<int>("video/v4l2/buffer_count", config_.video_v4l2_buffer_count, 3);

    pnh_.param<int>("video/converter/buffer_pool_size", config_.video_converter_buffer_pool_size, 8);
    pnh_.param<std::string>("video/converter/compute", config_.video_converter_compute, "vic");
    pnh_.param<std::string>("video/converter/dec_layout", config_.video_converter_dec_layout, "block");
    pnh_.param<std::string>("video/converter/out_layout", config_.video_converter_out_layout, "pitch");

    pnh_.param<int>("video/encoder/bitrate", config_.video_encoder_bitrate, 40000000);
    pnh_.param<bool>("video/encoder/intra_refresh/enabled", config_.video_encoder_intra_refresh_enabled, true);
    pnh_.param<int>("video/encoder/intra_refresh/interval_slices", config_.video_encoder_intra_refresh_interval_slices, 1);
    pnh_.param<bool>("video/encoder/low_freq_idr/enabled", config_.video_encoder_low_freq_idr_enabled, true);
    pnh_.param<int>("video/encoder/low_freq_idr/interval_sec", config_.video_encoder_low_freq_idr_interval_sec, 3);
    pnh_.param<int>("video/encoder/idr_interval", config_.video_encoder_idr_interval, 90);
    pnh_.param<int>("video/encoder/idr_interval_gops", config_.video_encoder_idr_interval_gops, 90);
    pnh_.param<int>("video/encoder/force_idr_every_n", config_.video_encoder_force_idr_every_n, 0);
    pnh_.param<int>("video/encoder/qp_range_i_min", config_.video_encoder_qp_range_i_min, 10);
    pnh_.param<int>("video/encoder/qp_range_i_max", config_.video_encoder_qp_range_i_max, 40);
    pnh_.param<int>("video/encoder/qp_range_p_min", config_.video_encoder_qp_range_p_min, 10);
    pnh_.param<int>("video/encoder/qp_range_p_max", config_.video_encoder_qp_range_p_max, 40);
    pnh_.param<int>("video/encoder/output_plane_buffers", config_.video_encoder_output_plane_buffers, 3);
    pnh_.param<int>("video/encoder/capture_plane_buffers", config_.video_encoder_capture_plane_buffers, 3);
    pnh_.param<bool>("video/encoder/max_perf_mode", config_.video_encoder_max_perf_mode, false);
    pnh_.param<std::string>("video/encoder/hw_preset", config_.video_encoder_hw_preset, "ultrafast");
    pnh_.param<std::string>("video/encoder/rate_control", config_.video_encoder_rate_control, "cbr");
    pnh_.param<int>("video/encoder/peak_bitrate", config_.video_encoder_peak_bitrate, 40000000);
    pnh_.param<int>("video/encoder/virtual_buffer_size", config_.video_encoder_virtual_buffer_size, 200000);
    pnh_.param<int>("video/encoder/num_reference_frames", config_.video_encoder_num_reference_frames, 1);
    pnh_.param<int>("video/encoder/num_b_frames", config_.video_encoder_num_b_frames, 0);
    pnh_.param<int>("video/encoder/insert_sps_pps_at_idr", config_.video_encoder_insert_sps_pps_at_idr, 1);

    // Recording
    pnh_.param<bool>("video/recording/enabled", config_.video_recording_enabled, false);
    pnh_.param<std::string>("video/recording/output_dir", config_.video_recording_output_dir, std::string(""));
}

MainNode::~MainNode()
{
    ROS_INFO("MainNode shutting down...");

    if (heartbeat_timer_.hasStarted())
    {
        heartbeat_timer_.stop();
    }
    if (register_retry_timer_.hasStarted())
    {
        register_retry_timer_.stop();
    }
    if (udp_ready_timer_.hasStarted())
    {
        udp_ready_timer_.stop();
    }

    pairing_running_ = false;
    if (pairing_thread_.joinable())
    {
        pairing_thread_.join();
    }

    if (udp_video_sender_)
    {
        udp_video_sender_->stop();
        udp_video_sender_.reset();
    }
    if (udp_manager_)
    {
        udp_manager_->stop();
        udp_manager_.reset();
    }
    pose_udp_receiver_.reset();

    if (signaling_client_)
    {
        signaling_client_->stopEventStream();
    }
}

const char *MainNode::stateToString(State s)
{
    switch (s)
    {
    case State::kConnecting:
        return "connecting";
    case State::kRegistered:
        return "registered";
    case State::kPairing:
        return "pairing";
    case State::kRunning:
        return "running";
    default:
        return "unknown";
    }
}
} // namespace trb

int main(int argc, char **argv)
{
    ros::init(argc, argv, "teleoperation_robot_bridge");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    trb::MainNode node(nh, pnh);
    ros::spin();
    return 0;
}
