// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/GripperMove.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_move.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_MOVE__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_MOVE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/gripper_move__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'grippers'
#include "teleop_robot_bridge/msg/detail/single_gripper_move__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const GripperMove & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: grippers
  {
    if (msg.grippers.size() == 0) {
      out << "grippers: []";
    } else {
      out << "grippers: [";
      size_t pending_items = msg.grippers.size();
      for (auto item : msg.grippers) {
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
  const GripperMove & msg,
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

  // member: grippers
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.grippers.size() == 0) {
      out << "grippers: []\n";
    } else {
      out << "grippers:\n";
      for (auto item : msg.grippers) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperMove & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::GripperMove & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::GripperMove & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::GripperMove>()
{
  return "teleop_robot_bridge::msg::GripperMove";
}

template<>
inline const char * name<teleop_robot_bridge::msg::GripperMove>()
{
  return "teleop_robot_bridge/msg/GripperMove";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::GripperMove>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::GripperMove>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<teleop_robot_bridge::msg::GripperMove>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_MOVE__TRAITS_HPP_
