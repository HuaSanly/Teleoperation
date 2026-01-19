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

        void stopVideo();

        // members
        // grpc
        bool subscribe_vr_pose_flag_ = false;

        std::shared_ptr<SignalingClient> signaling_client_;
        std::unique_ptr<trb::video::VideoStreamManager> video_stream_manager_;
        std::unique_ptr<trb::udp::UdpStreamManager> udp_stream_manager_;
        std::unique_ptr<trb::udp::PoseUdpReceiver> pose_udp_receiver_;

        rclcpp::TimerBase::SharedPtr heartbeat_timer_;
    };
} // namespace trb
#endif // MAIN_NODE_H