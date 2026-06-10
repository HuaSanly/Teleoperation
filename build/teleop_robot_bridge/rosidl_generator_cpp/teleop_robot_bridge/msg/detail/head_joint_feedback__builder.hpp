// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/HeadJointFeedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/head_joint_feedback.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_FEEDBACK__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_FEEDBACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/head_joint_feedback__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_HeadJointFeedback_effort
{
public:
  explicit Init_HeadJointFeedback_effort(::teleop_robot_bridge::msg::HeadJointFeedback & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::HeadJointFeedback effort(::teleop_robot_bridge::msg::HeadJointFeedback::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointFeedback msg_;
};

class Init_HeadJointFeedback_velocity
{
public:
  explicit Init_HeadJointFeedback_velocity(::teleop_robot_bridge::msg::HeadJointFeedback & msg)
  : msg_(msg)
  {}
  Init_HeadJointFeedback_effort velocity(::teleop_robot_bridge::msg::HeadJointFeedback::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_HeadJointFeedback_effort(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointFeedback msg_;
};

class Init_HeadJointFeedback_position
{
public:
  explicit Init_HeadJointFeedback_position(::teleop_robot_bridge::msg::HeadJointFeedback & msg)
  : msg_(msg)
  {}
  Init_HeadJointFeedback_velocity position(::teleop_robot_bridge::msg::HeadJointFeedback::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_HeadJointFeedback_velocity(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointFeedback msg_;
};

class Init_HeadJointFeedback_name
{
public:
  explicit Init_HeadJointFeedback_name(::teleop_robot_bridge::msg::HeadJointFeedback & msg)
  : msg_(msg)
  {}
  Init_HeadJointFeedback_position name(::teleop_robot_bridge::msg::HeadJointFeedback::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_HeadJointFeedback_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointFeedback msg_;
};

class Init_HeadJointFeedback_header
{
public:
  Init_HeadJointFeedback_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HeadJointFeedback_name header(::teleop_robot_bridge::msg::HeadJointFeedback::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HeadJointFeedback_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::HeadJointFeedback msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::HeadJointFeedback>()
{
  return teleop_robot_bridge::msg::builder::Init_HeadJointFeedback_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HEAD_JOINT_FEEDBACK__BUILDER_HPP_
