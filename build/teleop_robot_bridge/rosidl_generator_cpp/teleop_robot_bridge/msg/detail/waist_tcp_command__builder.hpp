// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/WaistTcpCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_tcp_command.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/waist_tcp_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_WaistTcpCommand_quat
{
public:
  explicit Init_WaistTcpCommand_quat(::teleop_robot_bridge::msg::WaistTcpCommand & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::WaistTcpCommand quat(::teleop_robot_bridge::msg::WaistTcpCommand::_quat_type arg)
  {
    msg_.quat = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistTcpCommand msg_;
};

class Init_WaistTcpCommand_euler
{
public:
  explicit Init_WaistTcpCommand_euler(::teleop_robot_bridge::msg::WaistTcpCommand & msg)
  : msg_(msg)
  {}
  Init_WaistTcpCommand_quat euler(::teleop_robot_bridge::msg::WaistTcpCommand::_euler_type arg)
  {
    msg_.euler = std::move(arg);
    return Init_WaistTcpCommand_quat(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistTcpCommand msg_;
};

class Init_WaistTcpCommand_position
{
public:
  explicit Init_WaistTcpCommand_position(::teleop_robot_bridge::msg::WaistTcpCommand & msg)
  : msg_(msg)
  {}
  Init_WaistTcpCommand_euler position(::teleop_robot_bridge::msg::WaistTcpCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_WaistTcpCommand_euler(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistTcpCommand msg_;
};

class Init_WaistTcpCommand_name
{
public:
  explicit Init_WaistTcpCommand_name(::teleop_robot_bridge::msg::WaistTcpCommand & msg)
  : msg_(msg)
  {}
  Init_WaistTcpCommand_position name(::teleop_robot_bridge::msg::WaistTcpCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_WaistTcpCommand_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistTcpCommand msg_;
};

class Init_WaistTcpCommand_header
{
public:
  Init_WaistTcpCommand_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WaistTcpCommand_name header(::teleop_robot_bridge::msg::WaistTcpCommand::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_WaistTcpCommand_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistTcpCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::WaistTcpCommand>()
{
  return teleop_robot_bridge::msg::builder::Init_WaistTcpCommand_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__BUILDER_HPP_
