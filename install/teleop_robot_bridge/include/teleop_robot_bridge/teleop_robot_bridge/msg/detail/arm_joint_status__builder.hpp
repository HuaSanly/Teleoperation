// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/ArmJointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/arm_joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_STATUS__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/arm_joint_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_ArmJointStatus_joint_status
{
public:
  explicit Init_ArmJointStatus_joint_status(::teleop_robot_bridge::msg::ArmJointStatus & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::ArmJointStatus joint_status(::teleop_robot_bridge::msg::ArmJointStatus::_joint_status_type arg)
  {
    msg_.joint_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointStatus msg_;
};

class Init_ArmJointStatus_name
{
public:
  explicit Init_ArmJointStatus_name(::teleop_robot_bridge::msg::ArmJointStatus & msg)
  : msg_(msg)
  {}
  Init_ArmJointStatus_joint_status name(::teleop_robot_bridge::msg::ArmJointStatus::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_ArmJointStatus_joint_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointStatus msg_;
};

class Init_ArmJointStatus_header
{
public:
  Init_ArmJointStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArmJointStatus_name header(::teleop_robot_bridge::msg::ArmJointStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ArmJointStatus_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::ArmJointStatus>()
{
  return teleop_robot_bridge::msg::builder::Init_ArmJointStatus_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_STATUS__BUILDER_HPP_
