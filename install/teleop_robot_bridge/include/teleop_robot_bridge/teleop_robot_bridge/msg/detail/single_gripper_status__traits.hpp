// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/SingleGripperStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_gripper_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/single_gripper_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const SingleGripperStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: is_ready
  {
    out << "is_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.is_ready, out);
    out << ", ";
  }

  // member: is_reset
  {
    out << "is_reset: ";
    rosidl_generator_traits::value_to_yaml(msg.is_reset, out);
    out << ", ";
  }

  // member: is_moving
  {
    out << "is_moving: ";
    rosidl_generator_traits::value_to_yaml(msg.is_moving, out);
    out << ", ";
  }

  // member: obj_detected
  {
    out << "obj_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.obj_detected, out);
    out << ", ";
  }

  // member: fault_status
  {
    out << "fault_status: ";
    rosidl_generator_traits::value_to_yaml(msg.fault_status, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << ", ";
  }

  // member: requested_position
  {
    out << "requested_position: ";
    rosidl_generator_traits::value_to_yaml(msg.requested_position, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SingleGripperStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: is_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.is_ready, out);
    out << "\n";
  }

  // member: is_reset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_reset: ";
    rosidl_generator_traits::value_to_yaml(msg.is_reset, out);
    out << "\n";
  }

  // member: is_moving
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_moving: ";
    rosidl_generator_traits::value_to_yaml(msg.is_moving, out);
    out << "\n";
  }

  // member: obj_detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "obj_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.obj_detected, out);
    out << "\n";
  }

  // member: fault_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fault_status: ";
    rosidl_generator_traits::value_to_yaml(msg.fault_status, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << "\n";
  }

  // member: requested_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "requested_position: ";
    rosidl_generator_traits::value_to_yaml(msg.requested_position, out);
    out << "\n";
  }

  // member: current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SingleGripperStatus & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::SingleGripperStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::SingleGripperStatus & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::SingleGripperStatus>()
{
  return "teleop_robot_bridge::msg::SingleGripperStatus";
}

template<>
inline const char * name<teleop_robot_bridge::msg::SingleGripperStatus>()
{
  return "teleop_robot_bridge/msg/SingleGripperStatus";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::SingleGripperStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::SingleGripperStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<teleop_robot_bridge::msg::SingleGripperStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__TRAITS_HPP_
