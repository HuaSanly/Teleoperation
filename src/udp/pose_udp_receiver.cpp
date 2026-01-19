#include "udp/pose_udp_receiver.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <cstring>

namespace trb::udp
{

    namespace
    {
        constexpr uint8_t kPoseType = 0x02;
        constexpr uint8_t kProtocolVersion = 1;

        // Flags
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

        bool ipMatchesAllowed(const sockaddr_in &src, const std::string &allowed_ip)
        {
            if (allowed_ip.empty())
            {
                return true;
            }
            char src_ip[INET_ADDRSTRLEN] = {0};
            if (::inet_ntop(AF_INET, &src.sin_addr, src_ip, sizeof(src_ip)) == nullptr)
            {
                return false;
            }
            return allowed_ip == src_ip;
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

        geometry_msgs::msg::PoseStamped makePoseMsg(
            const std::string &frame_id,
            const rclcpp::Time &stamp,
            float px,
            float py,
            float pz,
            float qx,
            float qy,
            float qz,
            float qw)
        {
            geometry_msgs::msg::PoseStamped msg;
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

        geometry_msgs::msg::Vector3Stamped makeEulerMsg(
            const std::string &frame_id,
            const rclcpp::Time &stamp,
            float ex,
            float ey,
            float ez)
        {
            geometry_msgs::msg::Vector3Stamped msg;
            msg.header.stamp = stamp;
            msg.header.frame_id = frame_id;
            msg.vector.x = ex;
            msg.vector.y = ey;
            msg.vector.z = ez;
            return msg;
        }

        sensor_msgs::msg::Joy makeJoyMsg(
            const rclcpp::Time &stamp,
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
            sensor_msgs::msg::Joy msg;
            msg.header.stamp = stamp;

            // axes: keep stable ordering
            msg.axes = {
                trigger_value,
                grip_value,
                thumbstick_x,
                thumbstick_y,
            };

            // buttons: keep stable ordering
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

        std_msgs::msg::Bool makeBoolMsg(const rclcpp::Time &stamp, bool v)
        {
            std_msgs::msg::Bool msg;
            (void)stamp;
            msg.data = v;
            return msg;
        }

        std_msgs::msg::Float32 makeFloat32Msg(const rclcpp::Time &stamp, float v)
        {
            std_msgs::msg::Float32 msg;
            (void)stamp;
            msg.data = v;
            return msg;
        }

    } // namespace

    PoseUdpReceiver::PoseUdpReceiver(rclcpp::Node &node, PoseUdpReceiverConfig config)
        : logger_(node.get_logger()), cfg_(std::move(config))
    {
        const auto qos = rclcpp::QoS(rclcpp::KeepLast(std::max(1, cfg_.qos_depth))).best_effort().durability_volatile();

        pub_hmd_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/pose/hmd", qos);
        pub_left_controller_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/pose/left_controller", qos);
        pub_right_controller_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/pose/right_controller", qos);

        pub_hmd_euler_ = node.create_publisher<geometry_msgs::msg::Vector3Stamped>("teleop/euler/hmd", qos);
        pub_left_controller_euler_ = node.create_publisher<geometry_msgs::msg::Vector3Stamped>("teleop/euler/left_controller", qos);
        pub_right_controller_euler_ = node.create_publisher<geometry_msgs::msg::Vector3Stamped>("teleop/euler/right_controller", qos);

        pub_left_joy_ = node.create_publisher<sensor_msgs::msg::Joy>("teleop/controller/left_joy", qos);
        pub_right_joy_ = node.create_publisher<sensor_msgs::msg::Joy>("teleop/controller/right_joy", qos);

        pub_left_aim_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/aim/left", qos);
        pub_right_aim_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/aim/right", qos);
        pub_left_aim_valid_ = node.create_publisher<std_msgs::msg::Bool>("teleop/aim/left_valid", qos);
        pub_right_aim_valid_ = node.create_publisher<std_msgs::msg::Bool>("teleop/aim/right_valid", qos);
        pub_left_pinch_ = node.create_publisher<std_msgs::msg::Bool>("teleop/aim/left_pinch", qos);
        pub_right_pinch_ = node.create_publisher<std_msgs::msg::Bool>("teleop/aim/right_pinch", qos);
        pub_left_pinch_strength_ = node.create_publisher<std_msgs::msg::Float32>("teleop/aim/left_pinch_strength", qos);
        pub_right_pinch_strength_ = node.create_publisher<std_msgs::msg::Float32>("teleop/aim/right_pinch_strength", qos);
    }

    PoseUdpReceiver::~PoseUdpReceiver()
    {
        stop();
    }

    bool PoseUdpReceiver::start()
    {
        if (running_.exchange(true))
        {
            return true;
        }

        sockfd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd_ < 0)
        {
            running_.store(false);
            RCLCPP_ERROR(logger_, "PoseUdpReceiver: socket() failed: %s", std::strerror(errno));
            return false;
        }

        int reuse = 1;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

        if (cfg_.recv_timeout_ms > 0)
        {
            timeval tv;
            tv.tv_sec = cfg_.recv_timeout_ms / 1000;
            tv.tv_usec = (cfg_.recv_timeout_ms % 1000) * 1000;
            ::setsockopt(sockfd_, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&tv), sizeof(tv));
        }

        sockaddr_in addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(static_cast<uint16_t>(cfg_.bind_port));
        if (::inet_pton(AF_INET, cfg_.bind_ip.c_str(), &addr.sin_addr) <= 0)
        {
            RCLCPP_ERROR(logger_, "PoseUdpReceiver: invalid bind_ip=%s", cfg_.bind_ip.c_str());
            ::close(sockfd_);
            sockfd_ = -1;
            running_.store(false);
            return false;
        }

        if (::bind(sockfd_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
        {
            RCLCPP_ERROR(logger_, "PoseUdpReceiver: bind(%s:%d) failed: %s", cfg_.bind_ip.c_str(), cfg_.bind_port, std::strerror(errno));
            ::close(sockfd_);
            sockfd_ = -1;
            running_.store(false);
            return false;
        }

        recv_thread_ = std::thread(&PoseUdpReceiver::recvThreadMain, this);

        RCLCPP_INFO(logger_, "PoseUdpReceiver started: bind=%s:%d allowed_remote_ip=%s", cfg_.bind_ip.c_str(), cfg_.bind_port,
                    cfg_.allowed_remote_ip.empty() ? "(any)" : cfg_.allowed_remote_ip.c_str());

        return true;
    }

    void PoseUdpReceiver::stop()
    {
        if (!running_.exchange(false))
        {
            return;
        }

        if (sockfd_ >= 0)
        {
            ::close(sockfd_);
            sockfd_ = -1;
        }

        if (recv_thread_.joinable())
        {
            recv_thread_.join();
        }
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
            const auto now = clock_.now();
            if ((now - last_warn_).seconds() > 1.0)
            {
                last_warn_ = now;
                RCLCPP_WARN(logger_, "PoseUdpReceiver: unsupported version=%u", static_cast<unsigned>(version));
            }
            return;
        }

        const size_t expected = expectedPacketSize(flags);
        if (len < expected)
        {
            const auto now = clock_.now();
            if ((now - last_warn_).seconds() > 1.0)
            {
                last_warn_ = now;
                RCLCPP_WARN(logger_, "PoseUdpReceiver: short packet len=%zu expected>=%zu flags=0x%02x", len, expected, static_cast<unsigned>(flags));
            }
            return;
        }

        // Convert Unix ms to ROS time (ns).
        const rclcpp::Time stamp(static_cast<uint64_t>(ts_ms) * 1000000ULL, RCL_SYSTEM_TIME);

        size_t off = 13;

        auto readPose = [&](geometry_msgs::msg::PoseStamped &out, const std::string &frame_id)
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

        geometry_msgs::msg::PoseStamped hmd_pose;
        geometry_msgs::msg::PoseStamped left_pose;
        geometry_msgs::msg::PoseStamped right_pose;
        readPose(hmd_pose, cfg_.frame_id_hmd);
        readPose(left_pose, cfg_.frame_id_left_controller);
        readPose(right_pose, cfg_.frame_id_right_controller);

        pub_hmd_->publish(hmd_pose);
        pub_left_controller_->publish(left_pose);
        pub_right_controller_->publish(right_pose);

        if ((flags & kIncludeEuler) && cfg_.publish_euler)
        {
            auto readEuler = [&](const std::string &frame_id, rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr &pub)
            {
                const float ex = readLeF32(data + off + 0);
                const float ey = readLeF32(data + off + 4);
                const float ez = readLeF32(data + off + 8);
                off += 12;
                pub->publish(makeEulerMsg(frame_id, stamp, ex, ey, ez));
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
            auto readControllerButtons = [&](rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr &pub)
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
                    pub->publish(makeJoyMsg(stamp,
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
            auto readAim = [&](
                const std::string &frame_id,
                rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr &pub_pose,
                rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr &pub_valid,
                rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr &pub_pinch,
                rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr &pub_strength)
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

                pub_pose->publish(makePoseMsg(frame_id, stamp, px, py, pz, qx, qy, qz, qw));
                pub_valid->publish(makeBoolMsg(stamp, valid != 0));
                pub_pinch->publish(makeBoolMsg(stamp, pinch != 0));
                pub_strength->publish(makeFloat32Msg(stamp, pinch_strength));
            };

            readAim(cfg_.frame_id_left_aim, pub_left_aim_, pub_left_aim_valid_, pub_left_pinch_, pub_left_pinch_strength_);
            readAim(cfg_.frame_id_right_aim, pub_right_aim_, pub_right_aim_valid_, pub_right_pinch_, pub_right_pinch_strength_);
        }
    }

    void PoseUdpReceiver::recvThreadMain()
    {
        std::array<uint8_t, 2048> buf;

        last_warn_ = clock_.now();

        while (running_.load())
        {
            sockaddr_in src;
            socklen_t slen = sizeof(src);
            const int n = ::recvfrom(sockfd_, buf.data(), buf.size(), 0, reinterpret_cast<sockaddr *>(&src), &slen);
            if (n < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    continue;
                }
                if (!running_.load())
                {
                    break;
                }

                const auto now = clock_.now();
                if ((now - last_warn_).seconds() > 1.0)
                {
                    last_warn_ = now;
                    RCLCPP_WARN(logger_, "PoseUdpReceiver: recvfrom failed: %s", std::strerror(errno));
                }
                continue;
            }

            const size_t len = static_cast<size_t>(n);
            if (!ipMatchesAllowed(src, cfg_.allowed_remote_ip))
            {
                continue;
            }

            parseAndPublish(buf.data(), len);
        }
    }

} // namespace trb::udp
