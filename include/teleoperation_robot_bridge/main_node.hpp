#pragma once

#include <ros/ros.h>

#include <memory>
#include <string>
#include <vector>

#include "teleoperation_robot_bridge/signaling_client.hpp"

namespace trb
{

struct Config
{
    // Signaling
    std::string server_ip;
    int server_port = 0;
    bool use_ssl = false;
    std::string device_id;
    std::string token;

    // UDP
    std::string udp_ip;
    int udp_port = 0;

    // Pose UDP
    bool pose_udp_enabled = false;
    std::string pose_udp_bind_ip;
    int pose_udp_bind_port = 0;
    std::string pose_udp_allowed_remote_ip;
    int pose_udp_recv_timeout_ms = 0;
    int pose_udp_qos_depth = 0;
    std::string pose_udp_frame_id_hmd;
    std::string pose_udp_frame_id_left_controller;
    std::string pose_udp_frame_id_right_controller;
    std::string pose_udp_frame_id_left_aim;
    std::string pose_udp_frame_id_right_aim;
    bool pose_udp_publish_euler = true;
    bool pose_udp_publish_buttons = true;
    bool pose_udp_publish_aim = true;

    // Video
    std::vector<int> video_profile;
    std::string video_device;
    std::string video_pixel_format;
    int video_v4l2_buffer_count = 0;

    int video_converter_buffer_pool_size = 0;
    std::string video_converter_compute;
    std::string video_converter_dec_layout;
    std::string video_converter_out_layout;

    int video_encoder_bitrate = 0;
    bool video_encoder_intra_refresh_enabled = false;
    int video_encoder_intra_refresh_interval_slices = 0;
    bool video_encoder_low_freq_idr_enabled = false;
    int video_encoder_low_freq_idr_interval_sec = 0;
    int video_encoder_idr_interval = 0;
    int video_encoder_idr_interval_gops = 0;
    int video_encoder_force_idr_every_n = 0;
    int video_encoder_qp_range_i_min = 0;
    int video_encoder_qp_range_i_max = 0;
    int video_encoder_qp_range_p_min = 0;
    int video_encoder_qp_range_p_max = 0;
    int video_encoder_output_plane_buffers = 0;
    int video_encoder_capture_plane_buffers = 0;
    bool video_encoder_max_perf_mode = false;
    std::string video_encoder_hw_preset;
    std::string video_encoder_rate_control;
    int video_encoder_peak_bitrate = 0;
    int video_encoder_virtual_buffer_size = 0;
    int video_encoder_num_reference_frames = 0;
    int video_encoder_num_b_frames = 0;
    int video_encoder_insert_sps_pps_at_idr = 0;

    // Recording
    bool video_recording_enabled = false;
    std::string video_recording_output_dir;
};

class MainNode
{
public:
    explicit MainNode(ros::NodeHandle nh, ros::NodeHandle pnh);

private:
    void loadParams();
    void initGrpc();
    void onSignalingEvent(const signaling::EventMessage &msg);
    void heartbeatTimerCallback(const ros::TimerEvent &event);

    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    Config config_{};

    std::shared_ptr<SignalingClient> signaling_client_;
    ros::Timer heartbeat_timer_;
};

} // namespace trb
