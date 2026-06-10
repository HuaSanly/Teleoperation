// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvVel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vel.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_vel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvVel_angular
{
public:
  explicit Init_AgvVel_angular(::teleop_robot_bridge::msg::AgvVel & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::AgvVel angular(::teleop_robot_bridge::msg::AgvVel::_angular_type arg)
  {
    msg_.angular = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVel msg_;
};

class Init_AgvVel_linear
{
public:
  explicit Init_AgvVel_linear(::teleop_robot_bridge::msg::AgvVel & msg)
  : msg_(msg)
  {}
  Init_AgvVel_angular linear(::teleop_robot_bridge::msg::AgvVel::_linear_type arg)
  {
    msg_.linear = std::move(arg);
    return Init_AgvVel_angular(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVel msg_;
};

class Init_AgvVel_header
{
public:
  Init_AgvVel_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgvVel_linear header(::teleop_robot_bridge::msg::AgvVel::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AgvVel_linear(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvVel>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvVel_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__BUILDER_HPP_
