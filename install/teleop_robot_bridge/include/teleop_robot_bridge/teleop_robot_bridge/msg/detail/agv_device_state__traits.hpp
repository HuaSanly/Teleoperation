// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/AgvDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/agv_device_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgvDeviceState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: health_status
  {
    out << "health_status: ";
    rosidl_generator_traits::value_to_yaml(msg.health_status, out);
    out << ", ";
  }

  // member: error_domain
  {
    out << "error_domain: ";
    rosidl_generator_traits::value_to_yaml(msg.error_domain, out);
    out << ", ";
  }

  // member: operational_mode
  {
    out << "operational_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.operational_mode, out);
    out << ", ";
  }

  // member: power_state
  {
    out << "power_state: ";
    rosidl_generator_traits::value_to_yaml(msg.power_state, out);
    out << ", ";
  }

  // member: connectivity_status
  {
    out << "connectivity_status: ";
    rosidl_generator_traits::value_to_yaml(msg.connectivity_status, out);
    out << ", ";
  }

  // member: manufacturer
  {
    out << "manufacturer: ";
    rosidl_generator_traits::value_to_yaml(msg.manufacturer, out);
    out << ", ";
  }

  // member: model
  {
    out << "model: ";
    rosidl_generator_traits::value_to_yaml(msg.model, out);
    out << ", ";
  }

  // member: firmware_version
  {
    out << "firmware_version: ";
    rosidl_generator_traits::value_to_yaml(msg.firmware_version, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AgvDeviceState & msg,
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

  // member: health_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "health_status: ";
    rosidl_generator_traits::value_to_yaml(msg.health_status, out);
    out << "\n";
  }

  // member: error_domain
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_domain: ";
    rosidl_generator_traits::value_to_yaml(msg.error_domain, out);
    out << "\n";
  }

  // member: operational_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operational_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.operational_mode, out);
    out << "\n";
  }

  // member: power_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "power_state: ";
    rosidl_generator_traits::value_to_yaml(msg.power_state, out);
    out << "\n";
  }

  // member: connectivity_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "connectivity_status: ";
    rosidl_generator_traits::value_to_yaml(msg.connectivity_status, out);
    out << "\n";
  }

  // member: manufacturer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "manufacturer: ";
    rosidl_generator_traits::value_to_yaml(msg.manufacturer, out);
    out << "\n";
  }

  // member: model
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model: ";
    rosidl_generator_traits::value_to_yaml(msg.model, out);
    out << "\n";
  }

  // member: firmware_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "firmware_version: ";
    rosidl_generator_traits::value_to_yaml(msg.firmware_version, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgvDeviceState & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::AgvDeviceState & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::AgvDeviceState & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::AgvDeviceState>()
{
  return "teleop_robot_bridge::msg::AgvDeviceState";
}

template<>
inline const char * name<teleop_robot_bridge::msg::AgvDeviceState>()
{
  return "teleop_robot_bridge/msg/AgvDeviceState";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::AgvDeviceState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::AgvDeviceState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<teleop_robot_bridge::msg::AgvDeviceState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__TRAITS_HPP_
