// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/GripperDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/gripper_device_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'devices'
#include "teleop_robot_bridge/msg/detail/single_device_state__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const GripperDeviceState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: devices
  {
    if (msg.devices.size() == 0) {
      out << "devices: []";
    } else {
      out << "devices: [";
      size_t pending_items = msg.devices.size();
      for (auto item : msg.devices) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GripperDeviceState & msg,
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

  // member: devices
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.devices.size() == 0) {
      out << "devices: []\n";
    } else {
      out << "devices:\n";
      for (auto item : msg.devices) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperDeviceState & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::GripperDeviceState & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::GripperDeviceState & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::GripperDeviceState>()
{
  return "teleop_robot_bridge::msg::GripperDeviceState";
}

template<>
inline const char * name<teleop_robot_bridge::msg::GripperDeviceState>()
{
  return "teleop_robot_bridge/msg/GripperDeviceState";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::GripperDeviceState>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value && has_fixed_size<teleop_robot_bridge::msg::SingleDeviceState>::value> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::GripperDeviceState>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value && has_bounded_size<teleop_robot_bridge::msg::SingleDeviceState>::value> {};

template<>
struct is_message<teleop_robot_bridge::msg::GripperDeviceState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__TRAITS_HPP_
