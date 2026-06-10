// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/UpperBodyDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/upper_body_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/upper_body_device_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'device_state'
#include "teleop_robot_bridge/msg/detail/single_device_state__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const UpperBodyDeviceState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: device_state
  {
    out << "device_state: ";
    to_flow_style_yaml(msg.device_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UpperBodyDeviceState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: device_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "device_state:\n";
    to_block_style_yaml(msg.device_state, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UpperBodyDeviceState & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::UpperBodyDeviceState & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::UpperBodyDeviceState & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::UpperBodyDeviceState>()
{
  return "teleop_robot_bridge::msg::UpperBodyDeviceState";
}

template<>
inline const char * name<teleop_robot_bridge::msg::UpperBodyDeviceState>()
{
  return "teleop_robot_bridge/msg/UpperBodyDeviceState";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::UpperBodyDeviceState>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value && has_fixed_size<teleop_robot_bridge::msg::SingleDeviceState>::value> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::UpperBodyDeviceState>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value && has_bounded_size<teleop_robot_bridge::msg::SingleDeviceState>::value> {};

template<>
struct is_message<teleop_robot_bridge::msg::UpperBodyDeviceState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__TRAITS_HPP_
