// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/WaistMotionCtrl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_motion_ctrl.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/waist_motion_ctrl__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_WaistMotionCtrl_enable_states
{
public:
  Init_WaistMotionCtrl_enable_states()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::teleop_robot_bridge::msg::WaistMotionCtrl enable_states(::teleop_robot_bridge::msg::WaistMotionCtrl::_enable_states_type arg)
  {
    msg_.enable_states = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::WaistMotionCtrl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::WaistMotionCtrl>()
{
  return teleop_robot_bridge::msg::builder::Init_WaistMotionCtrl_enable_states();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__BUILDER_HPP_
