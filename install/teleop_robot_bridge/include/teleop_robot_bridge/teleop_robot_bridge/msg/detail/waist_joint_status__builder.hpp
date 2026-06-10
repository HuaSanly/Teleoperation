// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/WaistJointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_STATUS__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/waist_joint_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_WaistJointStatus_joint_status
{
public:
  explicit Init_WaistJointStatus_joint_status(::teleop_robot_bridge::msg::WaistJointStatus & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::WaistJointStatus joint_status(::teleop_robot_bridge::msg::WaistJointStatus::_joint_status_type arg)
  {
    msg_.joint_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointStatus msg_;
};

class Init_WaistJointStatus_name
{
public:
  explicit Init_WaistJointStatus_name(::teleop_robot_bridge::msg::WaistJointStatus & msg)
  : msg_(msg)
  {}
  Init_WaistJointStatus_joint_status name(::teleop_robot_bridge::msg::WaistJointStatus::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_WaistJointStatus_joint_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointStatus msg_;
};

class Init_WaistJointStatus_header
{
public:
  Init_WaistJointStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WaistJointStatus_name header(::teleop_robot_bridge::msg::WaistJointStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_WaistJointStatus_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::WaistJointStatus>()
{
  return teleop_robot_bridge::msg::builder::Init_WaistJointStatus_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_STATUS__BUILDER_HPP_
