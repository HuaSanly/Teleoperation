// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/WaistMotionCtrl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_motion_ctrl.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/waist_motion_ctrl__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const WaistMotionCtrl & msg,
  std::ostream & out)
{
  out << "{";
  // member: enable_states
  {
    if (msg.enable_states.size() == 0) {
      out << "enable_states: []";
    } else {
      out << "enable_states: [";
      size_t pending_items = msg.enable_states.size();
      for (auto item : msg.enable_states) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const WaistMotionCtrl & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: enable_states
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.enable_states.size() == 0) {
      out << "enable_states: []\n";
    } else {
      out << "enable_states:\n";
      for (auto item : msg.enable_states) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WaistMotionCtrl & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::WaistMotionCtrl & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::WaistMotionCtrl & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::WaistMotionCtrl>()
{
  return "teleop_robot_bridge::msg::WaistMotionCtrl";
}

template<>
inline const char * name<teleop_robot_bridge::msg::WaistMotionCtrl>()
{
  return "teleop_robot_bridge/msg/WaistMotionCtrl";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::WaistMotionCtrl>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::WaistMotionCtrl>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<teleop_robot_bridge::msg::WaistMotionCtrl>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__TRAITS_HPP_
