#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>

#include "rclcpp/rclcpp.hpp"

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/vector3_stamped.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/float32.hpp"

namespace trb::udp
{

    struct PoseUdpReceiverConfig
    {
        std::string bind_ip{"0.0.0.0"};
        int bind_port{7780};

        // If non-empty, only accept datagrams from this IPv4 address.
        std::string allowed_remote_ip{};

        int recv_timeout_ms{100};
        int qos_depth{10};

        std::string frame_id_hmd{"vr_hmd"};
        std::string frame_id_left_controller{"vr_left_controller"};
        std::string frame_id_right_controller{"vr_right_controller"};
        std::string frame_id_left_aim{"vr_left_aim"};
        std::string frame_id_right_aim{"vr_right_aim"};

        bool publish_euler{true};
        bool publish_buttons{true};
        bool publish_aim{true};
    };

    class PoseUdpReceiver
    {
    public:
        PoseUdpReceiver(rclcpp::Node &node, PoseUdpReceiverConfig config);
        ~PoseUdpReceiver();

        // Standalone mode: create/bind a UDP socket and run an internal recv thread.
        bool start();
        void stop();

        // Shared-socket mode: reuse an existing UDP receive loop (e.g., the video UDP socket).
        // Caller provides the full datagram bytes.
        void handleDatagram(const uint8_t *data, size_t size);

    private:
        void parseAndPublish(const uint8_t *data, size_t size);
        void recvThreadMain();

        rclcpp::Logger logger_;
        PoseUdpReceiverConfig cfg_;

        std::atomic<bool> running_{false};
        std::thread recv_thread_;
        int sockfd_{-1};

        // Throttle noisy logs to ~1Hz.
        rclcpp::Clock clock_{RCL_SYSTEM_TIME};
        rclcpp::Time last_warn_{0, 0, RCL_SYSTEM_TIME};

        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_hmd_;
        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_left_controller_;
        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_right_controller_;

        rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr pub_hmd_euler_;
        rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr pub_left_controller_euler_;
        rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr pub_right_controller_euler_;

        rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr pub_left_joy_;
        rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr pub_right_joy_;

        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_left_aim_;
        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_right_aim_;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_left_aim_valid_;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_right_aim_valid_;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_left_pinch_;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_right_pinch_;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_left_pinch_strength_;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_right_pinch_strength_;
    };

} // namespace trb::udp
