#pragma once

#include <ros/ros.h>

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "signaling_client.hpp"
#include "udp/pose_udp_receiver.hpp"
#include "udp/udp_manager.hpp"
#include "udp/udp_video_sender.hpp"
#include "video/video_stream_manager.hpp"

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

    // gRPC lifecycle
    double grpc_register_retry_sec = 3.0;
    double grpc_heartbeat_sec = 15.0;

    // UDP
    std::string udp_ip;
    int udp_port = 0;
    int udp_recv_timeout_ms = 0;
    bool udp_pacing_enabled = true;
    int udp_pacing_queue_max_bytes = 300000;
    int udp_pacing_target_bps = 0;
    bool udp_handshake_enabled = true;
    double udp_handshake_interval_sec = 1.0;
    double udp_ping_interval_sec = 5.0;
    double udp_handshake_timeout_sec = 10.0;
    int udp_max_payload_bytes = 1200;
    bool udp_send_nonblocking = true;
    bool udp_fec_enabled = true;
    int udp_fec_table_id = 1;
    int udp_fec_threads = 0;
    int udp_send_threads = 1;

    // Pose UDP
    bool pose_udp_enabled = false;
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
    bool video_skip_connect = false;
    int video_decoder_buffer_pool_size = 0;
    bool video_decoder_max_perf_mode = false;
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
    ~MainNode();

private:
    enum class State
    {
        kConnecting,
        kRegistered,
        kPairing,
        kNegotiating,
        kRunning
    };

    void loadParams();
    void initGrpc();
    void initUdp();
    void initVideo();
    void wireVideoPipeline();
    void tryRegister();
    void enterPairingState();
    void enterNegotiatingState();
    void enterRunningState();
    void tryEnterPairing();
    bool publishVideoConfigOnce();
    void setState(State next, const std::string &reason);
    static const char *stateToString(State s);
    void onSignalingEvent(const signaling::EventMessage &msg);
    void heartbeatTimerCallback(const ros::TimerEvent &event);
    void registerRetryTimerCallback(const ros::TimerEvent &event);
    void udpReadyTimerCallback(const ros::TimerEvent &event);
    void videoConfigTimerCallback(const ros::TimerEvent &event);
    void videoStatsTimerCallback(const ros::TimerEvent &event);

    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    Config config_{};

    std::shared_ptr<SignalingClient> signaling_client_;
    ros::Timer heartbeat_timer_;
    ros::Timer register_retry_timer_;
    ros::Timer udp_ready_timer_;
    ros::Timer video_config_timer_;
    ros::Timer video_stats_timer_;
    bool grpc_registered_ = false;
    std::atomic<State> state_{State::kConnecting};

    bool udp_control_ready_ = false;

    std::atomic<bool> paired_{false};
    std::atomic<bool> video_config_acked_{false};
    std::atomic<bool> pairing_running_{false};
    std::thread pairing_thread_;
    std::mutex paired_mutex_;
    std::string paired_peer_session_id_;

    std::mutex video_param_mutex_;
    std::vector<uint8_t> cached_sps_;
    std::vector<uint8_t> cached_pps_;

    std::unique_ptr<udp::UdpManager> udp_manager_;
    std::unique_ptr<udp::PoseUdpReceiver> pose_udp_receiver_;
    std::unique_ptr<udp::UdpVideoSender> udp_video_sender_;

    std::unique_ptr<video::VideoStreamManager> video_stream_manager_;
};

} // namespace trb
