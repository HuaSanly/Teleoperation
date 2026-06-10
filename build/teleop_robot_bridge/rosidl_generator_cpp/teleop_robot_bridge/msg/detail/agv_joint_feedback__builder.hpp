// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvJointFeedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_joint_feedback.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_joint_feedback__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvJointFeedback_effort
{
public:
  explicit Init_AgvJointFeedback_effort(::teleop_robot_bridge::msg::AgvJointFeedback & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::AgvJointFeedback effort(::teleop_robot_bridge::msg::AgvJointFeedback::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointFeedback msg_;
};

class Init_AgvJointFeedback_velocity
{
public:
  explicit Init_AgvJointFeedback_velocity(::teleop_robot_bridge::msg::AgvJointFeedback & msg)
  : msg_(msg)
  {}
  Init_AgvJointFeedback_effort velocity(::teleop_robot_bridge::msg::AgvJointFeedback::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_AgvJointFeedback_effort(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointFeedback msg_;
};

class Init_AgvJointFeedback_position
{
public:
  explicit Init_AgvJointFeedback_position(::teleop_robot_bridge::msg::AgvJointFeedback & msg)
  : msg_(msg)
  {}
  Init_AgvJointFeedback_velocity position(::teleop_robot_bridge::msg::AgvJointFeedback::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_AgvJointFeedback_velocity(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointFeedback msg_;
};

class Init_AgvJointFeedback_name
{
public:
  explicit Init_AgvJointFeedback_name(::teleop_robot_bridge::msg::AgvJointFeedback & msg)
  : msg_(msg)
  {}
  Init_AgvJointFeedback_position name(::teleop_robot_bridge::msg::AgvJointFeedback::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_AgvJointFeedback_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointFeedback msg_;
};

class Init_AgvJointFeedback_header
{
public:
  Init_AgvJointFeedback_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgvJointFeedback_name header(::teleop_robot_bridge::msg::AgvJointFeedback::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AgvJointFeedback_name(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvJointFeedback msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvJointFeedback>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvJointFeedback_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__BUILDER_HPP_
