// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/GripperTactile.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_tactile.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/gripper_tactile__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_GripperTactile_right
{
public:
  explicit Init_GripperTactile_right(::teleop_robot_bridge::msg::GripperTactile & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::GripperTactile right(::teleop_robot_bridge::msg::GripperTactile::_right_type arg)
  {
    msg_.right = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::GripperTactile msg_;
};

class Init_GripperTactile_left
{
public:
  explicit Init_GripperTactile_left(::teleop_robot_bridge::msg::GripperTactile & msg)
  : msg_(msg)
  {}
  Init_GripperTactile_right left(::teleop_robot_bridge::msg::GripperTactile::_left_type arg)
  {
    msg_.left = std::move(arg);
    return Init_GripperTactile_right(msg_);
  }

private:
  ::teleop_robot_bridge::msg::GripperTactile msg_;
};

class Init_GripperTactile_header
{
public:
  Init_GripperTactile_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperTactile_left header(::teleop_robot_bridge::msg::GripperTactile::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GripperTactile_left(msg_);
  }

private:
  ::teleop_robot_bridge::msg::GripperTactile msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::GripperTactile>()
{
  return teleop_robot_bridge::msg::builder::Init_GripperTactile_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__BUILDER_HPP_
