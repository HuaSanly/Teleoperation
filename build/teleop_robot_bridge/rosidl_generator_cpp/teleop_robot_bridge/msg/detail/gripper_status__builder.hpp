// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/GripperStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/gripper_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_GripperStatus_grippers
{
public:
  explicit Init_GripperStatus_grippers(::teleop_robot_bridge::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::GripperStatus grippers(::teleop_robot_bridge::msg::GripperStatus::_grippers_type arg)
  {
    msg_.grippers = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::GripperStatus msg_;
};

class Init_GripperStatus_header
{
public:
  Init_GripperStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperStatus_grippers header(::teleop_robot_bridge::msg::GripperStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GripperStatus_grippers(msg_);
  }

private:
  ::teleop_robot_bridge::msg::GripperStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::GripperStatus>()
{
  return teleop_robot_bridge::msg::builder::Init_GripperStatus_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_
