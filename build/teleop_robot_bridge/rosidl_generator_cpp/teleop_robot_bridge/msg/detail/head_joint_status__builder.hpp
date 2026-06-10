// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/HeadJointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/head_joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_STATUS__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/head_joint_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_HeadJointStatus_joint_status
{
public:
  explicit Init_HeadJointStatus_joint_status(::teleop_robot_bridge::msg::HeadJointStatus & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::HeadJointStatus joint_status(::teleop_robot_bridge::msg::HeadJointStatus::_joint_status_type arg)
  {
    msg_.joint_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointStatus msg_;
};

class Init_HeadJointStatus_name
{
public:
  explicit Init_HeadJointStatus_name(::teleop_robot_bridge::msg::HeadJointStatus & msg)
  : msg_(msg)
  {}
  Init_HeadJointStatus_joint_status name(::teleop_robot_bridge::msg::HeadJointStatus::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_HeadJointStatus_joint_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointStatus msg_;
};

class Init_HeadJointStatus_header
{
public:
  Init_HeadJointStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HeadJointStatus_name header(::teleop_robot_bridge::msg::HeadJointStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HeadJointStatus_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::HeadJointStatus>()
{
  return teleop_robot_bridge::msg::builder::Init_HeadJointStatus_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_STATUS__BUILDER_HPP_
