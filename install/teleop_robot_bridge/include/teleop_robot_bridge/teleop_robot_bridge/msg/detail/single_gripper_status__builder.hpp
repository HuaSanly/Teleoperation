// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/SingleGripperStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_gripper_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/single_gripper_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_SingleGripperStatus_current
{
public:
  explicit Init_SingleGripperStatus_current(::teleop_robot_bridge::msg::SingleGripperStatus & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::SingleGripperStatus current(::teleop_robot_bridge::msg::SingleGripperStatus::_current_type arg)
  {
    msg_.current = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

class Init_SingleGripperStatus_requested_position
{
public:
  explicit Init_SingleGripperStatus_requested_position(::teleop_robot_bridge::msg::SingleGripperStatus & msg)
  : msg_(msg)
  {}
  Init_SingleGripperStatus_current requested_position(::teleop_robot_bridge::msg::SingleGripperStatus::_requested_position_type arg)
  {
    msg_.requested_position = std::move(arg);
    return Init_SingleGripperStatus_current(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

class Init_SingleGripperStatus_position
{
public:
  explicit Init_SingleGripperStatus_position(::teleop_robot_bridge::msg::SingleGripperStatus & msg)
  : msg_(msg)
  {}
  Init_SingleGripperStatus_requested_position position(::teleop_robot_bridge::msg::SingleGripperStatus::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_SingleGripperStatus_requested_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

class Init_SingleGripperStatus_fault_status
{
public:
  explicit Init_SingleGripperStatus_fault_status(::teleop_robot_bridge::msg::SingleGripperStatus & msg)
  : msg_(msg)
  {}
  Init_SingleGripperStatus_position fault_status(::teleop_robot_bridge::msg::SingleGripperStatus::_fault_status_type arg)
  {
    msg_.fault_status = std::move(arg);
    return Init_SingleGripperStatus_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

class Init_SingleGripperStatus_obj_detected
{
public:
  explicit Init_SingleGripperStatus_obj_detected(::teleop_robot_bridge::msg::SingleGripperStatus & msg)
  : msg_(msg)
  {}
  Init_SingleGripperStatus_fault_status obj_detected(::teleop_robot_bridge::msg::SingleGripperStatus::_obj_detected_type arg)
  {
    msg_.obj_detected = std::move(arg);
    return Init_SingleGripperStatus_fault_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

class Init_SingleGripperStatus_is_moving
{
public:
  explicit Init_SingleGripperStatus_is_moving(::teleop_robot_bridge::msg::SingleGripperStatus & msg)
  : msg_(msg)
  {}
  Init_SingleGripperStatus_obj_detected is_moving(::teleop_robot_bridge::msg::SingleGripperStatus::_is_moving_type arg)
  {
    msg_.is_moving = std::move(arg);
    return Init_SingleGripperStatus_obj_detected(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

class Init_SingleGripperStatus_is_reset
{
public:
  explicit Init_SingleGripperStatus_is_reset(::teleop_robot_bridge::msg::SingleGripperStatus & msg)
  : msg_(msg)
  {}
  Init_SingleGripperStatus_is_moving is_reset(::teleop_robot_bridge::msg::SingleGripperStatus::_is_reset_type arg)
  {
    msg_.is_reset = std::move(arg);
    return Init_SingleGripperStatus_is_moving(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

class Init_SingleGripperStatus_is_ready
{
public:
  Init_SingleGripperStatus_is_ready()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SingleGripperStatus_is_reset is_ready(::teleop_robot_bridge::msg::SingleGripperStatus::_is_ready_type arg)
  {
    msg_.is_ready = std::move(arg);
    return Init_SingleGripperStatus_is_reset(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::SingleGripperStatus>()
{
  return teleop_robot_bridge::msg::builder::Init_SingleGripperStatus_is_ready();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__BUILDER_HPP_
