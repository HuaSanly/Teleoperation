#include "teleoperation_robot_bridge/main_node.hpp"

namespace trb
{

MainNode::MainNode(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(std::move(nh)), pnh_(std::move(pnh))
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

void MainNode::loadParams()
{
    // Signaling
    pnh_.param<std::string>("server_ip", config_.server_ip, "127.0.0.1");
    pnh_.param<int>("server_port", config_.server_port, 8000);
    pnh_.param<bool>("use_ssl", config_.use_ssl, false);
    pnh_.param<std::string>("device_id", config_.device_id, "robot_001");
    pnh_.param<std::string>("token", config_.token, "default_token");

    // UDP
    pnh_.param<std::string>("udp_ip", config_.udp_ip, "192.168.3.2");
    pnh_.param<int>("udp_port", config_.udp_port, 7778);

    // Pose UDP
    pnh_.param<bool>("pose_udp.enabled", config_.pose_udp_enabled, false);
    pnh_.param<std::string>("pose_udp.bind_ip", config_.pose_udp_bind_ip, "0.0.0.0");
    pnh_.param<int>("pose_udp.bind_port", config_.pose_udp_bind_port, 7780);
    pnh_.param<std::string>("pose_udp.allowed_remote_ip", config_.pose_udp_allowed_remote_ip, "");
    pnh_.param<int>("pose_udp.recv_timeout_ms", config_.pose_udp_recv_timeout_ms, 100);
    pnh_.param<int>("pose_udp.qos.depth", config_.pose_udp_qos_depth, 10);
    pnh_.param<std::string>("pose_udp.frame_id.hmd", config_.pose_udp_frame_id_hmd, "vr_hmd");
    pnh_.param<std::string>("pose_udp.frame_id.left_controller", config_.pose_udp_frame_id_left_controller, "vr_left_controller");
    pnh_.param<std::string>("pose_udp.frame_id.right_controller", config_.pose_udp_frame_id_right_controller, "vr_right_controller");
    pnh_.param<std::string>("pose_udp.frame_id.left_aim", config_.pose_udp_frame_id_left_aim, "vr_left_aim");
    pnh_.param<std::string>("pose_udp.frame_id.right_aim", config_.pose_udp_frame_id_right_aim, "vr_right_aim");
    pnh_.param<bool>("pose_udp.publish_euler", config_.pose_udp_publish_euler, true);
    pnh_.param<bool>("pose_udp.publish_buttons", config_.pose_udp_publish_buttons, true);
    pnh_.param<bool>("pose_udp.publish_aim", config_.pose_udp_publish_aim, true);

    // Video
    if (!pnh_.getParam("video.profile", config_.video_profile))
    {
        config_.video_profile = {3840, 1520, 30};
    }
    pnh_.param<std::string>("video.device", config_.video_device, "/dev/video0");
    pnh_.param<std::string>("video.pixel_format", config_.video_pixel_format, "mjpeg");
    pnh_.param<int>("video.v4l2.buffer_count", config_.video_v4l2_buffer_count, 3);

    pnh_.param<int>("video.converter.buffer_pool_size", config_.video_converter_buffer_pool_size, 8);
    pnh_.param<std::string>("video.converter.compute", config_.video_converter_compute, "vic");
    pnh_.param<std::string>("video.converter.dec_layout", config_.video_converter_dec_layout, "block");
    pnh_.param<std::string>("video.converter.out_layout", config_.video_converter_out_layout, "pitch");

    pnh_.param<int>("video.encoder.bitrate", config_.video_encoder_bitrate, 40000000);
    pnh_.param<bool>("video.encoder.intra_refresh.enabled", config_.video_encoder_intra_refresh_enabled, true);
    pnh_.param<int>("video.encoder.intra_refresh.interval_slices", config_.video_encoder_intra_refresh_interval_slices, 1);
    pnh_.param<bool>("video.encoder.low_freq_idr.enabled", config_.video_encoder_low_freq_idr_enabled, true);
    pnh_.param<int>("video.encoder.low_freq_idr.interval_sec", config_.video_encoder_low_freq_idr_interval_sec, 3);
    pnh_.param<int>("video.encoder.idr_interval", config_.video_encoder_idr_interval, 90);
    pnh_.param<int>("video.encoder.idr_interval_gops", config_.video_encoder_idr_interval_gops, 90);
    pnh_.param<int>("video.encoder.force_idr_every_n", config_.video_encoder_force_idr_every_n, 0);
    pnh_.param<int>("video.encoder.qp_range_i_min", config_.video_encoder_qp_range_i_min, 10);
    pnh_.param<int>("video.encoder.qp_range_i_max", config_.video_encoder_qp_range_i_max, 40);
    pnh_.param<int>("video.encoder.qp_range_p_min", config_.video_encoder_qp_range_p_min, 10);
    pnh_.param<int>("video.encoder.qp_range_p_max", config_.video_encoder_qp_range_p_max, 40);
    pnh_.param<int>("video.encoder.output_plane_buffers", config_.video_encoder_output_plane_buffers, 3);
    pnh_.param<int>("video.encoder.capture_plane_buffers", config_.video_encoder_capture_plane_buffers, 3);
    pnh_.param<bool>("video.encoder.max_perf_mode", config_.video_encoder_max_perf_mode, false);
    pnh_.param<std::string>("video.encoder.hw_preset", config_.video_encoder_hw_preset, "ultrafast");
    pnh_.param<std::string>("video.encoder.rate_control", config_.video_encoder_rate_control, "cbr");
    pnh_.param<int>("video.encoder.peak_bitrate", config_.video_encoder_peak_bitrate, 40000000);
    pnh_.param<int>("video.encoder.virtual_buffer_size", config_.video_encoder_virtual_buffer_size, 200000);
    pnh_.param<int>("video.encoder.num_reference_frames", config_.video_encoder_num_reference_frames, 1);
    pnh_.param<int>("video.encoder.num_b_frames", config_.video_encoder_num_b_frames, 0);
    pnh_.param<int>("video.encoder.insert_sps_pps_at_idr", config_.video_encoder_insert_sps_pps_at_idr, 1);

    // Recording
    pnh_.param<bool>("video.recording.enabled", config_.video_recording_enabled, false);
    pnh_.param<std::string>("video.recording.output_dir", config_.video_recording_output_dir, std::string(""));
}

void MainNode::initGrpc()
{
    signaling_client_ = std::make_shared<SignalingClient>(
        config_.server_ip,
        config_.server_port,
        config_.token,
        config_.device_id,
        config_.use_ssl);

    signaling_client_->connect();
    signaling_client_->registerRobot();

    heartbeat_timer_ = nh_.createTimer(
        ros::Duration(15.0),
        &MainNode::heartbeatTimerCallback,
        this);

    signaling_client_->startEventStream(
        [this](const signaling::EventMessage &msg)
        {
            this->onSignalingEvent(msg);
        });
}

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
            signaling_client_->acceptPair(pair_event.peer_session_id());
            break;
        case signaling::PairEvent::ACCEPT:
            ROS_INFO("Pair Accepted by %s", pair_event.peer_session_id().c_str());
            break;
        case signaling::PairEvent::REJECT:
            ROS_WARN("Pair Rejected by %s", pair_event.peer_session_id().c_str());
            break;
        case signaling::PairEvent::UNPAIR:
            ROS_INFO("Unpaired by %s", pair_event.peer_session_id().c_str());
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
