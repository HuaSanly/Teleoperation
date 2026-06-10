// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/JoyState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joy_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/joy_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_JoyState_joy
{
public:
  Init_JoyState_joy()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::teleop_robot_bridge::msg::JoyState joy(::teleop_robot_bridge::msg::JoyState::_joy_type arg)
  {
    msg_.joy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JoyState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::JoyState>()
{
  return teleop_robot_bridge::msg::builder::Init_JoyState_joy();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__BUILDER_HPP_
