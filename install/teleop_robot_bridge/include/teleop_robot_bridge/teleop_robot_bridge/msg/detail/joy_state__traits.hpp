// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/JoyState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joy_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/joy_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'joy'
#include "sensor_msgs/msg/detail/joy__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const JoyState & msg,
  std::ostream & out)
{
  out << "{";
  // member: joy
  {
    out << "joy: ";
    to_flow_style_yaml(msg.joy, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const JoyState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "joy:\n";
    to_block_style_yaml(msg.joy, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const JoyState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace teleop_robot_bridge

namespace rosidl_generator_traits
{

[[deprecated("use teleop_robot_bridge::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const teleop_robot_bridge::msg::JoyState & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::JoyState & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::JoyState>()
{
  return "teleop_robot_bridge::msg::JoyState";
}

template<>
inline const char * name<teleop_robot_bridge::msg::JoyState>()
{
  return "teleop_robot_bridge/msg/JoyState";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::JoyState>
  : std::integral_constant<bool, has_fixed_size<sensor_msgs::msg::Joy>::value> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::JoyState>
  : std::integral_constant<bool, has_bounded_size<sensor_msgs::msg::Joy>::value> {};

template<>
struct is_message<teleop_robot_bridge::msg::JoyState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__TRAITS_HPP_
