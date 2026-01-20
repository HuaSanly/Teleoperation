#include "udp/pose_udp_receiver.hpp"

#include <array>
#include <cstring>

namespace trb::udp
{

namespace
{
constexpr uint8_t kPoseType = 0x02;
constexpr uint8_t kProtocolVersion = 1;

constexpr uint8_t kIncludeEuler = 0x01;
constexpr uint8_t kIncludeAim = 0x02;
constexpr uint8_t kIncludeButtons = 0x04;

uint64_t readLeU64(const uint8_t *p)
{
    uint64_t v = 0;
    for (int i = 0; i < 8; ++i)
    {
        v |= (static_cast<uint64_t>(p[i]) << (8 * i));
    }
    return v;
}

uint32_t readLeU32(const uint8_t *p)
{
    return (static_cast<uint32_t>(p[0]) << 0) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

float readLeF32(const uint8_t *p)
{
    const uint32_t u = readLeU32(p);
    float f;
    static_assert(sizeof(float) == sizeof(uint32_t), "float must be 32-bit");
    std::memcpy(&f, &u, sizeof(f));
    return f;
}

size_t expectedPacketSize(uint8_t flags)
{
    size_t total = 13 + 84;
    if (flags & kIncludeEuler)
    {
        total += 36;
    }
    if (flags & kIncludeButtons)
    {
        total += 46;
    }
    if (flags & kIncludeAim)
    {
        total += 76;
    }
    return total;
}

geometry_msgs::PoseStamped makePoseMsg(
    const std::string &frame_id,
    const ros::Time &stamp,
    float px,
    float py,
    float pz,
    float qx,
    float qy,
    float qz,
    float qw)
{
    geometry_msgs::PoseStamped msg;
    msg.header.stamp = stamp;
    msg.header.frame_id = frame_id;
    msg.pose.position.x = px;
    msg.pose.position.y = py;
    msg.pose.position.z = pz;
    msg.pose.orientation.x = qx;
    msg.pose.orientation.y = qy;
    msg.pose.orientation.z = qz;
    msg.pose.orientation.w = qw;
    return msg;
}

geometry_msgs::Vector3Stamped makeEulerMsg(
    const std::string &frame_id,
    const ros::Time &stamp,
    float ex,
    float ey,
    float ez)
{
    geometry_msgs::Vector3Stamped msg;
    msg.header.stamp = stamp;
    msg.header.frame_id = frame_id;
    msg.vector.x = ex;
    msg.vector.y = ey;
    msg.vector.z = ez;
    return msg;
}

sensor_msgs::Joy makeJoyMsg(
    const ros::Time &stamp,
    float trigger_value,
    uint8_t trigger_button,
    float grip_value,
    uint8_t grip_button,
    uint8_t primary_button,
    uint8_t secondary_button,
    uint8_t menu_button,
    float thumbstick_x,
    float thumbstick_y,
    uint8_t thumbstick_click,
    uint8_t thumbstick_touch)
{
    sensor_msgs::Joy msg;
    msg.header.stamp = stamp;

    msg.axes = {
        trigger_value,
        grip_value,
        thumbstick_x,
        thumbstick_y,
    };

    msg.buttons = {
        static_cast<int32_t>(trigger_button),
        static_cast<int32_t>(grip_button),
        static_cast<int32_t>(primary_button),
        static_cast<int32_t>(secondary_button),
        static_cast<int32_t>(menu_button),
        static_cast<int32_t>(thumbstick_click),
        static_cast<int32_t>(thumbstick_touch),
    };
    return msg;
}

std_msgs::Bool makeBoolMsg(bool v)
{
    std_msgs::Bool msg;
    msg.data = v;
    return msg;
}

std_msgs::Float32 makeFloat32Msg(float v)
{
    std_msgs::Float32 msg;
    msg.data = v;
    return msg;
}

} // namespace

PoseUdpReceiver::PoseUdpReceiver(ros::NodeHandle nh, const PoseUdpReceiverConfig &config)
    : nh_(std::move(nh)), cfg_(config)
{
    const int q = std::max(1, cfg_.queue_size);

    pub_hmd_ = nh_.advertise<geometry_msgs::PoseStamped>("teleop/pose/hmd", q);
    pub_left_controller_ = nh_.advertise<geometry_msgs::PoseStamped>("teleop/pose/left_controller", q);
    pub_right_controller_ = nh_.advertise<geometry_msgs::PoseStamped>("teleop/pose/right_controller", q);

    pub_hmd_euler_ = nh_.advertise<geometry_msgs::Vector3Stamped>("teleop/euler/hmd", q);
    pub_left_controller_euler_ = nh_.advertise<geometry_msgs::Vector3Stamped>("teleop/euler/left_controller", q);
    pub_right_controller_euler_ = nh_.advertise<geometry_msgs::Vector3Stamped>("teleop/euler/right_controller", q);

    pub_left_joy_ = nh_.advertise<sensor_msgs::Joy>("teleop/controller/left_joy", q);
    pub_right_joy_ = nh_.advertise<sensor_msgs::Joy>("teleop/controller/right_joy", q);

    pub_left_aim_ = nh_.advertise<geometry_msgs::PoseStamped>("teleop/aim/left", q);
    pub_right_aim_ = nh_.advertise<geometry_msgs::PoseStamped>("teleop/aim/right", q);
    pub_left_aim_valid_ = nh_.advertise<std_msgs::Bool>("teleop/aim/left_valid", q);
    pub_right_aim_valid_ = nh_.advertise<std_msgs::Bool>("teleop/aim/right_valid", q);
    pub_left_pinch_ = nh_.advertise<std_msgs::Bool>("teleop/aim/left_pinch", q);
    pub_right_pinch_ = nh_.advertise<std_msgs::Bool>("teleop/aim/right_pinch", q);
    pub_left_pinch_strength_ = nh_.advertise<std_msgs::Float32>("teleop/aim/left_pinch_strength", q);
    pub_right_pinch_strength_ = nh_.advertise<std_msgs::Float32>("teleop/aim/right_pinch_strength", q);
}

void PoseUdpReceiver::handleDatagram(const uint8_t *data, size_t size)
{
    parseAndPublish(data, size);
}

void PoseUdpReceiver::parseAndPublish(const uint8_t *data, size_t len)
{
    if (data == nullptr || len < 13)
    {
        return;
    }

    const uint8_t type = data[0];
    if (type != kPoseType)
    {
        return;
    }

    const uint64_t ts_ms = readLeU64(data + 1);
    const uint8_t version = data[9];
    const uint8_t flags = data[10];

    if (version != kProtocolVersion)
    {
        ROS_WARN_THROTTLE(1.0, "PoseUdpReceiver: unsupported version=%u", static_cast<unsigned>(version));
        return;
    }

    const size_t expected = expectedPacketSize(flags);
    if (len < expected)
    {
        ROS_WARN_THROTTLE(1.0, "PoseUdpReceiver: short packet len=%zu expected>=%zu flags=0x%02x", len, expected, static_cast<unsigned>(flags));
        return;
    }

    const ros::Time stamp = ros::Time().fromNSec(ts_ms * 1000000ULL);

    size_t off = 13;

    auto readPose = [&](geometry_msgs::PoseStamped &out, const std::string &frame_id)
    {
        const float px = readLeF32(data + off + 0);
        const float py = readLeF32(data + off + 4);
        const float pz = readLeF32(data + off + 8);
        const float qx = readLeF32(data + off + 12);
        const float qy = readLeF32(data + off + 16);
        const float qz = readLeF32(data + off + 20);
        const float qw = readLeF32(data + off + 24);
        out = makePoseMsg(frame_id, stamp, px, py, pz, qx, qy, qz, qw);
        off += 28;
    };

    geometry_msgs::PoseStamped hmd_pose;
    geometry_msgs::PoseStamped left_pose;
    geometry_msgs::PoseStamped right_pose;
    readPose(hmd_pose, cfg_.frame_id_hmd);
    readPose(left_pose, cfg_.frame_id_left_controller);
    readPose(right_pose, cfg_.frame_id_right_controller);

    pub_hmd_.publish(hmd_pose);
    pub_left_controller_.publish(left_pose);
    pub_right_controller_.publish(right_pose);

    if ((flags & kIncludeEuler) && cfg_.publish_euler)
    {
        auto readEuler = [&](const std::string &frame_id, ros::Publisher &pub)
        {
            const float ex = readLeF32(data + off + 0);
            const float ey = readLeF32(data + off + 4);
            const float ez = readLeF32(data + off + 8);
            off += 12;
            pub.publish(makeEulerMsg(frame_id, stamp, ex, ey, ez));
        };

        readEuler(cfg_.frame_id_hmd, pub_hmd_euler_);
        readEuler(cfg_.frame_id_left_controller, pub_left_controller_euler_);
        readEuler(cfg_.frame_id_right_controller, pub_right_controller_euler_);
    }
    else if (flags & kIncludeEuler)
    {
        off += 36;
    }

    if (flags & kIncludeButtons)
    {
        auto readControllerButtons = [&](ros::Publisher &pub)
        {
            const float trigger_value = readLeF32(data + off + 0);
            const uint8_t trigger_button = data[off + 4];
            const float grip_value = readLeF32(data + off + 5);
            const uint8_t grip_button = data[off + 9];
            const uint8_t primary_button = data[off + 10];
            const uint8_t secondary_button = data[off + 11];
            const uint8_t menu_button = data[off + 12];
            const float thumbstick_x = readLeF32(data + off + 13);
            const float thumbstick_y = readLeF32(data + off + 17);
            const uint8_t thumbstick_click = data[off + 21];
            const uint8_t thumbstick_touch = data[off + 22];
            off += 23;

            if (cfg_.publish_buttons)
            {
                pub.publish(makeJoyMsg(stamp,
                                       trigger_value,
                                       trigger_button,
                                       grip_value,
                                       grip_button,
                                       primary_button,
                                       secondary_button,
                                       menu_button,
                                       thumbstick_x,
                                       thumbstick_y,
                                       thumbstick_click,
                                       thumbstick_touch));
            }
        };

        readControllerButtons(pub_left_joy_);
        readControllerButtons(pub_right_joy_);
    }

    if (flags & kIncludeAim)
    {
        auto readAim = [&](const std::string &frame_id,
                           ros::Publisher &pub_pose,
                           ros::Publisher &pub_valid,
                           ros::Publisher &pub_pinch,
                           ros::Publisher &pub_strength)
        {
            const uint8_t valid = data[off + 0];
            const uint8_t pinch = data[off + 1];
            const float pinch_strength = readLeF32(data + off + 2);
            const float px = readLeF32(data + off + 6);
            const float py = readLeF32(data + off + 10);
            const float pz = readLeF32(data + off + 14);
            const float qx = readLeF32(data + off + 18);
            const float qy = readLeF32(data + off + 22);
            const float qz = readLeF32(data + off + 26);
            const float qw = readLeF32(data + off + 30);
            off += 38;

            if (!cfg_.publish_aim)
            {
                return;
            }

            pub_pose.publish(makePoseMsg(frame_id, stamp, px, py, pz, qx, qy, qz, qw));
            pub_valid.publish(makeBoolMsg(valid != 0));
            pub_pinch.publish(makeBoolMsg(pinch != 0));
            pub_strength.publish(makeFloat32Msg(pinch_strength));
        };

        readAim(cfg_.frame_id_left_aim, pub_left_aim_, pub_left_aim_valid_, pub_left_pinch_, pub_left_pinch_strength_);
        readAim(cfg_.frame_id_right_aim, pub_right_aim_, pub_right_aim_valid_, pub_right_pinch_, pub_right_pinch_strength_);
    }
}

} // namespace trb::udp
