// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_ultrasonic.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvUltrasonic_ranges
{
public:
  Init_AgvUltrasonic_ranges()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::teleop_robot_bridge::msg::AgvUltrasonic ranges(::teleop_robot_bridge::msg::AgvUltrasonic::_ranges_type arg)
  {
    msg_.ranges = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvUltrasonic msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvUltrasonic>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvUltrasonic_ranges();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__BUILDER_HPP_
