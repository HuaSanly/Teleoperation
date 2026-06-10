// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/WaistJointFeedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_joint_feedback.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_FEEDBACK__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_FEEDBACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/waist_joint_feedback__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_WaistJointFeedback_effort
{
public:
  explicit Init_WaistJointFeedback_effort(::teleop_robot_bridge::msg::WaistJointFeedback & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::WaistJointFeedback effort(::teleop_robot_bridge::msg::WaistJointFeedback::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointFeedback msg_;
};

class Init_WaistJointFeedback_velocity
{
public:
  explicit Init_WaistJointFeedback_velocity(::teleop_robot_bridge::msg::WaistJointFeedback & msg)
  : msg_(msg)
  {}
  Init_WaistJointFeedback_effort velocity(::teleop_robot_bridge::msg::WaistJointFeedback::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_WaistJointFeedback_effort(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointFeedback msg_;
};

class Init_WaistJointFeedback_position
{
public:
  explicit Init_WaistJointFeedback_position(::teleop_robot_bridge::msg::WaistJointFeedback & msg)
  : msg_(msg)
  {}
  Init_WaistJointFeedback_velocity position(::teleop_robot_bridge::msg::WaistJointFeedback::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_WaistJointFeedback_velocity(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointFeedback msg_;
};

class Init_WaistJointFeedback_name
{
public:
  explicit Init_WaistJointFeedback_name(::teleop_robot_bridge::msg::WaistJointFeedback & msg)
  : msg_(msg)
  {}
  Init_WaistJointFeedback_position name(::teleop_robot_bridge::msg::WaistJointFeedback::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_WaistJointFeedback_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointFeedback msg_;
};

class Init_WaistJointFeedback_header
{
public:
  Init_WaistJointFeedback_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WaistJointFeedback_name header(::teleop_robot_bridge::msg::WaistJointFeedback::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_WaistJointFeedback_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistJointFeedback msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::WaistJointFeedback>()
{
  return teleop_robot_bridge::msg::builder::Init_WaistJointFeedback_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_FEEDBACK__BUILDER_HPP_
