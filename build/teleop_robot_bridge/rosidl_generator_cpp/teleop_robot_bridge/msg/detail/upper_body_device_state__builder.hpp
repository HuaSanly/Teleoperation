// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/UpperBodyDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/upper_body_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/upper_body_device_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_UpperBodyDeviceState_device_state
{
public:
  explicit Init_UpperBodyDeviceState_device_state(::teleop_robot_bridge::msg::UpperBodyDeviceState & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::UpperBodyDeviceState device_state(::teleop_robot_bridge::msg::UpperBodyDeviceState::_device_state_type arg)
  {
    msg_.device_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::UpperBodyDeviceState msg_;
};

class Init_UpperBodyDeviceState_header
{
public:
  Init_UpperBodyDeviceState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UpperBodyDeviceState_device_state header(::teleop_robot_bridge::msg::UpperBodyDeviceState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_UpperBodyDeviceState_device_state(msg_);
  }

private:
  ::teleop_robot_bridge::msg::UpperBodyDeviceState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::UpperBodyDeviceState>()
{
  return teleop_robot_bridge::msg::builder::Init_UpperBodyDeviceState_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__BUILDER_HPP_
