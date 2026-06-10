// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvJointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_STATUS__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_joint_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvJointStatus_joint_status
{
public:
  explicit Init_AgvJointStatus_joint_status(::teleop_robot_bridge::msg::AgvJointStatus & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::AgvJointStatus joint_status(::teleop_robot_bridge::msg::AgvJointStatus::_joint_status_type arg)
  {
    msg_.joint_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointStatus msg_;
};

class Init_AgvJointStatus_name
{
public:
  explicit Init_AgvJointStatus_name(::teleop_robot_bridge::msg::AgvJointStatus & msg)
  : msg_(msg)
  {}
  Init_AgvJointStatus_joint_status name(::teleop_robot_bridge::msg::AgvJointStatus::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_AgvJointStatus_joint_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointStatus msg_;
};

class Init_AgvJointStatus_header
{
public:
  Init_AgvJointStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgvJointStatus_name header(::teleop_robot_bridge::msg::AgvJointStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AgvJointStatus_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvJointStatus>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvJointStatus_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_STATUS__BUILDER_HPP_
