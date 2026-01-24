#ifndef MAIN_NODE_H
#define MAIN_NODE_H

/*
    __________      ___.               _____                   __
    \______   \ ____\_ |__   ____     /     \ _____    _______/  |_  ___________
     |       _//  _ \| __ \ /  _ \   /  \ /  \\__  \  /  ___/\   __\/ __ \_  __ \
     |    |   (  <_> ) \_\ (  <_> ) /    Y    \/ __ \_\___ \  |  | \  ___/|  | \/
     |____|_  /\____/|___  /\____/  \____|__  (____  /____  > |__|  \___  >__|
              \/           \/                 \/     \/     \/            \/
*/

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <string>

#include <cstddef>
#include <unordered_map>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "signaling_client.hpp"
#include "video/video_stream_manager.hpp"
#include "udp/udp_stream_manager.hpp"
#include "udp/pose_udp_receiver.hpp"

namespace trb
{
    class MainNode : public rclcpp::Node
    {
    public:
        MainNode();
        ~MainNode();
        void initGrpc();
        void initVideo();
        void initUdp();
        void initPoseUdp();

    private:
        // methods
        // handle
        void heartbeatTimerCallback();
        void onSignalingEvent(const signaling::EventMessage &msg);

        void startVideoConfigPublisher();
        void stopVideoConfigPublisher();
        void videoConfigPublisherLoop();
        void updateSpsPpsFromEncodedFrame(const uint8_t *data, size_t size);
        void resetVideoConfigState();
        std::string makeVideoConfigId();
        bool reRegisterAndWaitForPairing();

        void stopVideo();

        // members
        // grpc
        bool subscribe_vr_pose_flag_ = false;
        bool pair_auto_accept_ = true;
        bool pair_auto_request_ = true;
        bool pair_list_unpaired_on_start_ = false;
        std::string desired_peer_session_id_;
        std::string paired_peer_session_id_;
        std::string pair_mode_ = "passive"; // active | passive

        std::mutex pair_mutex_;
        std::condition_variable pair_cv_;
        bool paired_ready_ = false;
        std::atomic<bool> shutting_down_{false};

        std::shared_ptr<SignalingClient> signaling_client_;
        std::unique_ptr<trb::video::VideoStreamManager> video_stream_manager_;
        std::unique_ptr<trb::udp::UdpStreamManager> udp_stream_manager_;
        std::unique_ptr<trb::udp::PoseUdpReceiver> pose_udp_receiver_;

        rclcpp::TimerBase::SharedPtr heartbeat_timer_;

        // video config publish state
        uint32_t video_width_ = 0;
        uint32_t video_height_ = 0;
        uint32_t video_fps_ = 0;
        std::vector<uint8_t> video_sps_;
        std::vector<uint8_t> video_pps_;
        std::vector<uint8_t> video_vps_;
        std::atomic<uint64_t> video_config_seq_{0};
        std::string last_video_config_id_;
        std::mutex video_config_mutex_;
        std::condition_variable video_config_cv_;
        std::atomic<bool> video_config_running_{false};
        std::atomic<bool> video_config_acked_{false};
        std::atomic<bool> reconnecting_{false};
        std::thread video_config_thread_;

        // helpers
        bool selfCheckCamera();
        bool runActivePairing();
        bool waitForPairing();
    };
} // namespace trb
#endif // MAIN_NODE_H