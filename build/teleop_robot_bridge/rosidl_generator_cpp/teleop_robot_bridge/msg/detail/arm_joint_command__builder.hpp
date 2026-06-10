// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/ArmJointCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/arm_joint_command.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_COMMAND__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/arm_joint_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_ArmJointCommand_effort
{
public:
  explicit Init_ArmJointCommand_effort(::teleop_robot_bridge::msg::ArmJointCommand & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::ArmJointCommand effort(::teleop_robot_bridge::msg::ArmJointCommand::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointCommand msg_;
};

class Init_ArmJointCommand_velocity
{
public:
  explicit Init_ArmJointCommand_velocity(::teleop_robot_bridge::msg::ArmJointCommand & msg)
  : msg_(msg)
  {}
  Init_ArmJointCommand_effort velocity(::teleop_robot_bridge::msg::ArmJointCommand::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_ArmJointCommand_effort(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointCommand msg_;
};

class Init_ArmJointCommand_position
{
public:
  explicit Init_ArmJointCommand_position(::teleop_robot_bridge::msg::ArmJointCommand & msg)
  : msg_(msg)
  {}
  Init_ArmJointCommand_velocity position(::teleop_robot_bridge::msg::ArmJointCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_ArmJointCommand_velocity(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointCommand msg_;
};

class Init_ArmJointCommand_name
{
public:
  explicit Init_ArmJointCommand_name(::teleop_robot_bridge::msg::ArmJointCommand & msg)
  : msg_(msg)
  {}
  Init_ArmJointCommand_position name(::teleop_robot_bridge::msg::ArmJointCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_ArmJointCommand_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointCommand msg_;
};

class Init_ArmJointCommand_header
{
public:
  Init_ArmJointCommand_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArmJointCommand_name header(::teleop_robot_bridge::msg::ArmJointCommand::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ArmJointCommand_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::ArmJointCommand>()
{
  return teleop_robot_bridge::msg::builder::Init_ArmJointCommand_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_COMMAND__BUILDER_HPP_
