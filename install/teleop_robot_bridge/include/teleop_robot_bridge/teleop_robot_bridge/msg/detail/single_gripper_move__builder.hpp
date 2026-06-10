// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/SingleGripperMove.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_gripper_move.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/single_gripper_move__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_SingleGripperMove_force
{
public:
  explicit Init_SingleGripperMove_force(::teleop_robot_bridge::msg::SingleGripperMove & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::SingleGripperMove force(::teleop_robot_bridge::msg::SingleGripperMove::_force_type arg)
  {
    msg_.force = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperMove msg_;
};

class Init_SingleGripperMove_speed
{
public:
  explicit Init_SingleGripperMove_speed(::teleop_robot_bridge::msg::SingleGripperMove & msg)
  : msg_(msg)
  {}
  Init_SingleGripperMove_force speed(::teleop_robot_bridge::msg::SingleGripperMove::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_SingleGripperMove_force(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperMove msg_;
};

class Init_SingleGripperMove_position
{
public:
  explicit Init_SingleGripperMove_position(::teleop_robot_bridge::msg::SingleGripperMove & msg)
  : msg_(msg)
  {}
  Init_SingleGripperMove_speed position(::teleop_robot_bridge::msg::SingleGripperMove::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_SingleGripperMove_speed(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperMove msg_;
};

class Init_SingleGripperMove_stop
{
public:
  explicit Init_SingleGripperMove_stop(::teleop_robot_bridge::msg::SingleGripperMove & msg)
  : msg_(msg)
  {}
  Init_SingleGripperMove_position stop(::teleop_robot_bridge::msg::SingleGripperMove::_stop_type arg)
  {
    msg_.stop = std::move(arg);
    return Init_SingleGripperMove_position(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperMove msg_;
};

class Init_SingleGripperMove_emergency_release_dir
{
public:
  explicit Init_SingleGripperMove_emergency_release_dir(::teleop_robot_bridge::msg::SingleGripperMove & msg)
  : msg_(msg)
  {}
  Init_SingleGripperMove_stop emergency_release_dir(::teleop_robot_bridge::msg::SingleGripperMove::_emergency_release_dir_type arg)
  {
    msg_.emergency_release_dir = std::move(arg);
    return Init_SingleGripperMove_stop(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperMove msg_;
};

class Init_SingleGripperMove_emergency_release
{
public:
  Init_SingleGripperMove_emergency_release()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SingleGripperMove_emergency_release_dir emergency_release(::teleop_robot_bridge::msg::SingleGripperMove::_emergency_release_type arg)
  {
    msg_.emergency_release = std::move(arg);
    return Init_SingleGripperMove_emergency_release_dir(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleGripperMove msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::SingleGripperMove>()
{
  return teleop_robot_bridge::msg::builder::Init_SingleGripperMove_emergency_release();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__BUILDER_HPP_
