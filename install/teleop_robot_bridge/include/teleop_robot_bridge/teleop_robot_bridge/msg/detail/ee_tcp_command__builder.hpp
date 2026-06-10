// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/EeTcpCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/ee_tcp_command.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__EE_TCP_COMMAND__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__EE_TCP_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/ee_tcp_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_EeTcpCommand_quat
{
public:
  explicit Init_EeTcpCommand_quat(::teleop_robot_bridge::msg::EeTcpCommand & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::EeTcpCommand quat(::teleop_robot_bridge::msg::EeTcpCommand::_quat_type arg)
  {
    msg_.quat = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::EeTcpCommand msg_;
};

class Init_EeTcpCommand_euler
{
public:
  explicit Init_EeTcpCommand_euler(::teleop_robot_bridge::msg::EeTcpCommand & msg)
  : msg_(msg)
  {}
  Init_EeTcpCommand_quat euler(::teleop_robot_bridge::msg::EeTcpCommand::_euler_type arg)
  {
    msg_.euler = std::move(arg);
    return Init_EeTcpCommand_quat(msg_);
  }

private:
  ::teleop_robot_bridge::msg::EeTcpCommand msg_;
};

class Init_EeTcpCommand_position
{
public:
  explicit Init_EeTcpCommand_position(::teleop_robot_bridge::msg::EeTcpCommand & msg)
  : msg_(msg)
  {}
  Init_EeTcpCommand_euler position(::teleop_robot_bridge::msg::EeTcpCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_EeTcpCommand_euler(msg_);
  }

private:
  ::teleop_robot_bridge::msg::EeTcpCommand msg_;
};

class Init_EeTcpCommand_name
{
public:
  explicit Init_EeTcpCommand_name(::teleop_robot_bridge::msg::EeTcpCommand & msg)
  : msg_(msg)
  {}
  Init_EeTcpCommand_position name(::teleop_robot_bridge::msg::EeTcpCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_EeTcpCommand_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::EeTcpCommand msg_;
};

class Init_EeTcpCommand_header
{
public:
  Init_EeTcpCommand_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EeTcpCommand_name header(::teleop_robot_bridge::msg::EeTcpCommand::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_EeTcpCommand_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::EeTcpCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::EeTcpCommand>()
{
  return teleop_robot_bridge::msg::builder::Init_EeTcpCommand_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__EE_TCP_COMMAND__BUILDER_HPP_
