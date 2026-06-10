// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvBatteryState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_battery_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_battery_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvBatteryState_battery_state
{
public:
  Init_AgvBatteryState_battery_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::teleop_robot_bridge::msg::AgvBatteryState battery_state(::teleop_robot_bridge::msg::AgvBatteryState::_battery_state_type arg)
  {
    msg_.battery_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvBatteryState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvBatteryState>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvBatteryState_battery_state();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__BUILDER_HPP_
