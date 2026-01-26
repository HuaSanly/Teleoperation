#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>

namespace trb::udp
{

struct PoseUdpReceiverConfig
{
    std::string frame_id_hmd;
    std::string frame_id_left_controller;
    std::string frame_id_right_controller;
    std::string frame_id_left_aim;
    std::string frame_id_right_aim;

    bool publish_euler{true};
    bool publish_buttons{true};
    bool publish_aim{true};

    int queue_size{10};
};

class PoseUdpReceiver
{
public:
    PoseUdpReceiver(ros::NodeHandle nh, const PoseUdpReceiverConfig &config);

    void handleDatagram(const uint8_t *data, size_t size);

private:
    void parseAndPublish(const uint8_t *data, size_t len);

    ros::NodeHandle nh_;
    PoseUdpReceiverConfig cfg_;

    ros::Publisher pub_hmd_;
    ros::Publisher pub_left_controller_;
    ros::Publisher pub_right_controller_;

    ros::Publisher pub_hmd_euler_;
    ros::Publisher pub_left_controller_euler_;
    ros::Publisher pub_right_controller_euler_;

    ros::Publisher pub_left_joy_;
    ros::Publisher pub_right_joy_;

    ros::Publisher pub_left_aim_;
    ros::Publisher pub_right_aim_;
    ros::Publisher pub_left_aim_valid_;
    ros::Publisher pub_right_aim_valid_;
    ros::Publisher pub_left_pinch_;
    ros::Publisher pub_right_pinch_;
    ros::Publisher pub_left_pinch_strength_;
    ros::Publisher pub_right_pinch_strength_;
};

} // namespace trb::udp
