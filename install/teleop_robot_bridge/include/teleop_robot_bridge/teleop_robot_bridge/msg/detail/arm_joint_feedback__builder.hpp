// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/ArmJointFeedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/arm_joint_feedback.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_FEEDBACK__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_FEEDBACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/arm_joint_feedback__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_ArmJointFeedback_effort
{
public:
  explicit Init_ArmJointFeedback_effort(::teleop_robot_bridge::msg::ArmJointFeedback & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::ArmJointFeedback effort(::teleop_robot_bridge::msg::ArmJointFeedback::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointFeedback msg_;
};

class Init_ArmJointFeedback_velocity
{
public:
  explicit Init_ArmJointFeedback_velocity(::teleop_robot_bridge::msg::ArmJointFeedback & msg)
  : msg_(msg)
  {}
  Init_ArmJointFeedback_effort velocity(::teleop_robot_bridge::msg::ArmJointFeedback::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_ArmJointFeedback_effort(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointFeedback msg_;
};

class Init_ArmJointFeedback_position
{
public:
  explicit Init_ArmJointFeedback_position(::teleop_robot_bridge::msg::ArmJointFeedback & msg)
  : msg_(msg)
  {}
  Init_ArmJointFeedback_velocity position(::teleop_robot_bridge::msg::ArmJointFeedback::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_ArmJointFeedback_velocity(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointFeedback msg_;
};

class Init_ArmJointFeedback_name
{
public:
  explicit Init_ArmJointFeedback_name(::teleop_robot_bridge::msg::ArmJointFeedback & msg)
  : msg_(msg)
  {}
  Init_ArmJointFeedback_position name(::teleop_robot_bridge::msg::ArmJointFeedback::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_ArmJointFeedback_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointFeedback msg_;
};

class Init_ArmJointFeedback_header
{
public:
  Init_ArmJointFeedback_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArmJointFeedback_name header(::teleop_robot_bridge::msg::ArmJointFeedback::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ArmJointFeedback_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::ArmJointFeedback msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::ArmJointFeedback>()
{
  return teleop_robot_bridge::msg::builder::Init_ArmJointFeedback_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_FEEDBACK__BUILDER_HPP_
