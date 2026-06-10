// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/GripperDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/gripper_device_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_GripperDeviceState_devices
{
public:
  explicit Init_GripperDeviceState_devices(::teleop_robot_bridge::msg::GripperDeviceState & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::GripperDeviceState devices(::teleop_robot_bridge::msg::GripperDeviceState::_devices_type arg)
  {
    msg_.devices = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::GripperDeviceState msg_;
};

class Init_GripperDeviceState_header
{
public:
  Init_GripperDeviceState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperDeviceState_devices header(::teleop_robot_bridge::msg::GripperDeviceState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GripperDeviceState_devices(msg_);
  }

private:
  ::teleop_robot_bridge::msg::GripperDeviceState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::GripperDeviceState>()
{
  return teleop_robot_bridge::msg::builder::Init_GripperDeviceState_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__BUILDER_HPP_
