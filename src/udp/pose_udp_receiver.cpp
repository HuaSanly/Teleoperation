#include "udp/pose_udp_receiver.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <cmath>
#include <cstring>

namespace trb::udp
{

    namespace
    {
        constexpr uint8_t kPoseType = 0x02;
        constexpr uint8_t kProtocolVersion = 2;
        constexpr uint16_t kTotalPacketBytes = 930;

        constexpr uint8_t kSensorBlockType = 1;
        constexpr uint8_t kButtonsBlockType = 2;
        constexpr uint8_t kJoint24BlockType = 3;

        constexpr uint16_t kSensorBlockBytes = 176;
        constexpr uint16_t kButtonsBlockBytes = 54;
        constexpr uint16_t kJoint24BlockBytes = 684;

        constexpr uint8_t kSensorMaskHmd = 1u << 0;
        constexpr uint8_t kSensorMaskWaist = 1u << 1;
        constexpr uint8_t kSensorMaskLeftController = 1u << 2;
        constexpr uint8_t kSensorMaskRightController = 1u << 3;
        constexpr uint8_t kSensorMaskLeftFoot = 1u << 4;
        constexpr uint8_t kSensorMaskRightFoot = 1u << 5;

        constexpr uint8_t kControllerMaskLeft = 1u << 0;
        constexpr uint8_t kControllerMaskRight = 1u << 1;

        constexpr uint8_t kSensorEntryCount = 3;
        constexpr uint8_t kJointCount = 24;
        constexpr uint32_t kJointMaskAll = (1u << kJointCount) - 1u;
        constexpr double kQuatNormEpsilon = 1e-8;

        struct Vec3
        {
            double x{0.0};
            double y{0.0};
            double z{0.0};
        };

        struct Quat
        {
            double x{0.0};
            double y{0.0};
            double z{0.0};
            double w{1.0};
        };

        uint16_t readLeU16(const uint8_t *p)
        {
            return static_cast<uint16_t>((static_cast<uint16_t>(p[0]) << 0) |
                                         (static_cast<uint16_t>(p[1]) << 8));
        }

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

        geometry_msgs::msg::Pose makePose(
            float px,
            float py,
            float pz,
            float qx,
            float qy,
            float qz,
            float qw)
        {
            geometry_msgs::msg::Pose pose;
            pose.position.x = px;
            pose.position.y = py;
            pose.position.z = pz;
            pose.orientation.x = qx;
            pose.orientation.y = qy;
            pose.orientation.z = qz;
            pose.orientation.w = qw;
            return pose;
        }

        geometry_msgs::msg::Pose makeIdentityPose()
        {
            return makePose(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        }

        bool isFinite(double value)
        {
            return std::isfinite(value);
        }

        bool normalizeQuat(Quat &q)
        {
            const double norm_sq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
            if (!isFinite(norm_sq) || norm_sq < kQuatNormEpsilon)
            {
                return false;
            }
            const double inv_norm = 1.0 / std::sqrt(norm_sq);
            q.x *= inv_norm;
            q.y *= inv_norm;
            q.z *= inv_norm;
            q.w *= inv_norm;
            return true;
        }

        Quat conjugateQuat(const Quat &q)
        {
            return Quat{-q.x, -q.y, -q.z, q.w};
        }

        Quat multiplyQuat(const Quat &a, const Quat &b)
        {
            return Quat{
                a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
                a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
            };
        }

        Vec3 rotateVector(const Quat &q, const Vec3 &v)
        {
            const Quat vector_quat{v.x, v.y, v.z, 0.0};
            const Quat rotated = multiplyQuat(multiplyQuat(q, vector_quat), conjugateQuat(q));
            return Vec3{rotated.x, rotated.y, rotated.z};
        }

        bool poseToTransform(const geometry_msgs::msg::Pose &pose, Vec3 &position, Quat &orientation)
        {
            position = Vec3{pose.position.x, pose.position.y, pose.position.z};
            orientation = Quat{pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w};
            if (!isFinite(position.x) || !isFinite(position.y) || !isFinite(position.z) ||
                !isFinite(orientation.x) || !isFinite(orientation.y) || !isFinite(orientation.z) || !isFinite(orientation.w))
            {
                return false;
            }
            return normalizeQuat(orientation);
        }

        geometry_msgs::msg::Pose makeRelativePose(
            const Vec3 &joint_position,
            const Quat &joint_orientation,
            const Vec3 &origin_position,
            const Quat &origin_inverse)
        {
            const Vec3 relative_position = rotateVector(origin_inverse,
                                                        Vec3{joint_position.x - origin_position.x,
                                                             joint_position.y - origin_position.y,
                                                             joint_position.z - origin_position.z});
            Quat relative_orientation = multiplyQuat(origin_inverse, joint_orientation);
            (void)normalizeQuat(relative_orientation);

            geometry_msgs::msg::Pose pose;
            pose.position.x = relative_position.x;
            pose.position.y = relative_position.y;
            pose.position.z = relative_position.z;
            pose.orientation.x = relative_orientation.x;
            pose.orientation.y = relative_orientation.y;
            pose.orientation.z = relative_orientation.z;
            pose.orientation.w = relative_orientation.w;
            return pose;
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

    } // namespace

    PoseUdpReceiver::PoseUdpReceiver(rclcpp::Node &node, PoseUdpReceiverConfig config)
        : logger_(node.get_logger()), cfg_(std::move(config))
    {
        const auto qos = rclcpp::QoS(rclcpp::KeepLast(std::max(1, cfg_.qos_depth))).best_effort().durability_volatile();

        pub_hmd_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/pose/hmd", qos);
        pub_left_controller_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/pose/left_controller", qos);
        pub_right_controller_ = node.create_publisher<geometry_msgs::msg::PoseStamped>("teleop/pose/right_controller", qos);

        pub_joint24_ = node.create_publisher<geometry_msgs::msg::PoseArray>("teleop/pose/joint24", qos);
        pub_joint24_valid_mask_ = node.create_publisher<std_msgs::msg::UInt32>("teleop/pose/joint24_valid_mask", qos);
        pub_joint24_waist_ = node.create_publisher<geometry_msgs::msg::PoseArray>("teleop/pose/joint24_waist", qos);
        pub_joint24_waist_valid_mask_ = node.create_publisher<std_msgs::msg::UInt32>("teleop/pose/joint24_waist_valid_mask", qos);

        pub_left_joy_ = node.create_publisher<sensor_msgs::msg::Joy>("teleop/controller/left_joy", qos);
        pub_right_joy_ = node.create_publisher<sensor_msgs::msg::Joy>("teleop/controller/right_joy", qos);
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
        if (data == nullptr || len < 16)
        {
            return;
        }

        const uint8_t type = data[0];
        if (type != kPoseType)
        {
            return;
        }

        const uint8_t version = data[1];
        const uint16_t total_bytes = readLeU16(data + 2);
        const uint64_t ts_ms = readLeU64(data + 4);
        const uint8_t block_count = data[14];

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

        if (total_bytes != kTotalPacketBytes || block_count != 3 || len < total_bytes)
        {
            const auto now = clock_.now();
            if ((now - last_warn_).seconds() > 1.0)
            {
                last_warn_ = now;
                RCLCPP_WARN(logger_, "PoseUdpReceiver: invalid V2 header len=%zu total=%u block_count=%u",
                            len,
                            static_cast<unsigned>(total_bytes),
                            static_cast<unsigned>(block_count));
            }
            return;
        }

        // Convert Unix ms to ROS time (ns).
        const rclcpp::Time stamp(static_cast<uint64_t>(ts_ms) * 1000000ULL, RCL_SYSTEM_TIME);

        size_t off = 16;

        auto readPoseMsg = [&](size_t pose_offset, const std::string &frame_id)
        {
            return makePoseMsg(frame_id,
                               stamp,
                               readLeF32(data + pose_offset + 0),
                               readLeF32(data + pose_offset + 4),
                               readLeF32(data + pose_offset + 8),
                               readLeF32(data + pose_offset + 12),
                               readLeF32(data + pose_offset + 16),
                               readLeF32(data + pose_offset + 20),
                               readLeF32(data + pose_offset + 24));
        };

        auto readBlockHeader = [&](uint8_t expected_type, uint16_t expected_bytes) -> bool
        {
            if (off + 4 > total_bytes)
            {
                return false;
            }
            const uint8_t block_type = data[off + 0];
            const uint16_t block_bytes = readLeU16(data + off + 2);
            if (block_type != expected_type || block_bytes != expected_bytes || off + block_bytes > total_bytes)
            {
                const auto now = clock_.now();
                if ((now - last_warn_).seconds() > 1.0)
                {
                    last_warn_ = now;
                    RCLCPP_WARN(logger_, "PoseUdpReceiver: invalid block header off=%zu type=%u bytes=%u expected_type=%u expected_bytes=%u",
                                off,
                                static_cast<unsigned>(block_type),
                                static_cast<unsigned>(block_bytes),
                                static_cast<unsigned>(expected_type),
                                static_cast<unsigned>(expected_bytes));
                }
                return false;
            }
            off += 4;
            return true;
        };

        if (!readBlockHeader(kSensorBlockType, kSensorBlockBytes))
        {
            return;
        }

        const size_t sensor_block_payload = off;
        const uint8_t sensor_mask = data[sensor_block_payload + 0];
        const uint8_t entry_count = data[sensor_block_payload + 2];
        if (entry_count != kSensorEntryCount)
        {
            const auto now = clock_.now();
            if ((now - last_warn_).seconds() > 1.0)
            {
                last_warn_ = now;
                RCLCPP_WARN(logger_, "PoseUdpReceiver: invalid SensorRaw entry_count=%u", static_cast<unsigned>(entry_count));
            }
            return;
        }

        const size_t reserved_pose_offset = sensor_block_payload + 4;
        const size_t entries_offset = reserved_pose_offset + 28;
        const size_t hmd_pose_offset = entries_offset + 0 * 28;
        const size_t left_controller_pose_offset = entries_offset + 1 * 28;
        const size_t right_controller_pose_offset = entries_offset + 2 * 28;

        if (sensor_mask & kSensorMaskHmd)
        {
            pub_hmd_->publish(readPoseMsg(hmd_pose_offset, cfg_.frame_id_hmd));
        }
        if (sensor_mask & kSensorMaskLeftController)
        {
            pub_left_controller_->publish(readPoseMsg(left_controller_pose_offset, cfg_.frame_id_left_controller));
        }
        if (sensor_mask & kSensorMaskRightController)
        {
            pub_right_controller_->publish(readPoseMsg(right_controller_pose_offset, cfg_.frame_id_right_controller));
        }

        off = 16 + kSensorBlockBytes;
        if (!readBlockHeader(kButtonsBlockType, kButtonsBlockBytes))
        {
            return;
        }

        const size_t buttons_block_payload = off;
        const uint8_t controller_mask = data[buttons_block_payload + 0];
        const size_t left_buttons_offset = buttons_block_payload + 4;
        const size_t right_buttons_offset = left_buttons_offset + 23;

        auto publishControllerButtons = [&](size_t buttons_offset,
                                            rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr &pub)
        {
            pub->publish(makeJoyMsg(stamp,
                                    readLeF32(data + buttons_offset + 0),
                                    data[buttons_offset + 4],
                                    readLeF32(data + buttons_offset + 5),
                                    data[buttons_offset + 9],
                                    data[buttons_offset + 10],
                                    data[buttons_offset + 11],
                                    data[buttons_offset + 12],
                                    readLeF32(data + buttons_offset + 13),
                                    readLeF32(data + buttons_offset + 17),
                                    data[buttons_offset + 21],
                                    data[buttons_offset + 22]));
        };

        if (cfg_.publish_buttons)
        {
            if (controller_mask & kControllerMaskLeft)
            {
                publishControllerButtons(left_buttons_offset, pub_left_joy_);
            }
            if (controller_mask & kControllerMaskRight)
            {
                publishControllerButtons(right_buttons_offset, pub_right_joy_);
            }
        }

        off = 16 + kSensorBlockBytes + kButtonsBlockBytes;
        if (!readBlockHeader(kJoint24BlockType, kJoint24BlockBytes))
        {
            return;
        }

        const size_t joint_block_payload = off;
        const uint8_t joint_count = data[joint_block_payload + 0];
        const uint8_t joint_flags = data[joint_block_payload + 1];
        const uint32_t valid_mask = readLeU32(data + joint_block_payload + 4);
        const uint32_t raw_joint_mask = valid_mask & kJointMaskAll;
        if (joint_count != kJointCount)
        {
            const auto now = clock_.now();
            if ((now - last_warn_).seconds() > 1.0)
            {
                last_warn_ = now;
                RCLCPP_WARN(logger_, "PoseUdpReceiver: invalid Joint24 count=%u", static_cast<unsigned>(joint_count));
            }
            return;
        }

        const size_t joint_entries_offset = joint_block_payload + 8;
        std::array<geometry_msgs::msg::Pose, kJointCount> raw_poses;

        auto readPose = [&](size_t pose_offset)
        {
            return makePose(readLeF32(data + pose_offset + 0),
                            readLeF32(data + pose_offset + 4),
                            readLeF32(data + pose_offset + 8),
                            readLeF32(data + pose_offset + 12),
                            readLeF32(data + pose_offset + 16),
                            readLeF32(data + pose_offset + 20),
                            readLeF32(data + pose_offset + 24));
        };

        for (size_t joint_index = 0; joint_index < kJointCount; ++joint_index)
        {
            raw_poses[joint_index] = readPose(joint_entries_offset + joint_index * 28);
        }

        geometry_msgs::msg::PoseArray joint24_msg;
        joint24_msg.header.stamp = stamp;
        joint24_msg.header.frame_id = cfg_.frame_id_joint24;
        joint24_msg.poses.reserve(kJointCount);
        for (const auto &pose : raw_poses)
        {
            joint24_msg.poses.push_back(pose);
        }
        pub_joint24_->publish(joint24_msg);

        std_msgs::msg::UInt32 valid_mask_msg;
        valid_mask_msg.data = valid_mask;
        pub_joint24_valid_mask_->publish(valid_mask_msg);

        geometry_msgs::msg::PoseArray joint24_waist_msg;
        joint24_waist_msg.header.stamp = stamp;
        joint24_waist_msg.header.frame_id = cfg_.frame_id_waist;
        joint24_waist_msg.poses.reserve(kJointCount);

        uint32_t waist_valid_mask = 0;
        Vec3 pelvis_position;
        Quat pelvis_orientation;
        const bool pelvis_valid = (raw_joint_mask & 1u) != 0u &&
                                  poseToTransform(raw_poses[0], pelvis_position, pelvis_orientation);

        if (pelvis_valid)
        {
            const Quat pelvis_inverse = conjugateQuat(pelvis_orientation);
            for (size_t joint_index = 0; joint_index < kJointCount; ++joint_index)
            {
                const uint32_t joint_bit = 1u << joint_index;
                Vec3 joint_position;
                Quat joint_orientation;
                if ((raw_joint_mask & joint_bit) != 0u &&
                    poseToTransform(raw_poses[joint_index], joint_position, joint_orientation))
                {
                    joint24_waist_msg.poses.push_back(makeRelativePose(
                        joint_position,
                        joint_orientation,
                        pelvis_position,
                        pelvis_inverse));
                    waist_valid_mask |= joint_bit;
                }
                else
                {
                    joint24_waist_msg.poses.push_back(makeIdentityPose());
                }
            }
        }
        else
        {
            for (size_t joint_index = 0; joint_index < kJointCount; ++joint_index)
            {
                joint24_waist_msg.poses.push_back(makeIdentityPose());
            }
        }

        pub_joint24_waist_->publish(joint24_waist_msg);

        std_msgs::msg::UInt32 waist_valid_mask_msg;
        waist_valid_mask_msg.data = waist_valid_mask;
        pub_joint24_waist_valid_mask_->publish(waist_valid_mask_msg);

        (void)joint_flags;
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
