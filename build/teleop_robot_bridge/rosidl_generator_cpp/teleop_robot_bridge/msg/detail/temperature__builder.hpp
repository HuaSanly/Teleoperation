// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/Temperature.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/temperature.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__TEMPERATURE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__TEMPERATURE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/temperature__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_Temperature_temperature
{
public:
  Init_Temperature_temperature()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::teleop_robot_bridge::msg::Temperature temperature(::teleop_robot_bridge::msg::Temperature::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::Temperature msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::Temperature>()
{
  return teleop_robot_bridge::msg::builder::Init_Temperature_temperature();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__TEMPERATURE__BUILDER_HPP_
