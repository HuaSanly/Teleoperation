// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/hand_tactile.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/hand_tactile__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_HandTactile_thumb
{
public:
  explicit Init_HandTactile_thumb(::teleop_robot_bridge::msg::HandTactile & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::HandTactile thumb(::teleop_robot_bridge::msg::HandTactile::_thumb_type arg)
  {
    msg_.thumb = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HandTactile msg_;
};

class Init_HandTactile_finger
{
public:
  Init_HandTactile_finger()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandTactile_thumb finger(::teleop_robot_bridge::msg::HandTactile::_finger_type arg)
  {
    msg_.finger = std::move(arg);
    return Init_HandTactile_thumb(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HandTactile msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::HandTactile>()
{
  return teleop_robot_bridge::msg::builder::Init_HandTactile_finger();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__BUILDER_HPP_
