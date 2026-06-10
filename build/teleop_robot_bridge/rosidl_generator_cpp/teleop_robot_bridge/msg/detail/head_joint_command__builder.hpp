// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/HeadJointCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/head_joint_command.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_COMMAND__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/head_joint_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_HeadJointCommand_effort
{
public:
  explicit Init_HeadJointCommand_effort(::teleop_robot_bridge::msg::HeadJointCommand & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::HeadJointCommand effort(::teleop_robot_bridge::msg::HeadJointCommand::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointCommand msg_;
};

class Init_HeadJointCommand_velocity
{
public:
  explicit Init_HeadJointCommand_velocity(::teleop_robot_bridge::msg::HeadJointCommand & msg)
  : msg_(msg)
  {}
  Init_HeadJointCommand_effort velocity(::teleop_robot_bridge::msg::HeadJointCommand::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_HeadJointCommand_effort(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointCommand msg_;
};

class Init_HeadJointCommand_position
{
public:
  explicit Init_HeadJointCommand_position(::teleop_robot_bridge::msg::HeadJointCommand & msg)
  : msg_(msg)
  {}
  Init_HeadJointCommand_velocity position(::teleop_robot_bridge::msg::HeadJointCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_HeadJointCommand_velocity(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointCommand msg_;
};

class Init_HeadJointCommand_name
{
public:
  explicit Init_HeadJointCommand_name(::teleop_robot_bridge::msg::HeadJointCommand & msg)
  : msg_(msg)
  {}
  Init_HeadJointCommand_position name(::teleop_robot_bridge::msg::HeadJointCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_HeadJointCommand_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointCommand msg_;
};

class Init_HeadJointCommand_header
{
public:
  Init_HeadJointCommand_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HeadJointCommand_name header(::teleop_robot_bridge::msg::HeadJointCommand::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HeadJointCommand_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::HeadJointCommand>()
{
  return teleop_robot_bridge::msg::builder::Init_HeadJointCommand_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_COMMAND__BUILDER_HPP_
