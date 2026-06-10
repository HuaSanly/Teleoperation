// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/hand_tactile.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/hand_tactile__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const HandTactile & msg,
  std::ostream & out)
{
  out << "{";
  // member: finger
  {
    if (msg.finger.size() == 0) {
      out << "finger: []";
    } else {
      out << "finger: [";
      size_t pending_items = msg.finger.size();
      for (auto item : msg.finger) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: thumb
  {
    if (msg.thumb.size() == 0) {
      out << "thumb: []";
    } else {
      out << "thumb: [";
      size_t pending_items = msg.thumb.size();
      for (auto item : msg.thumb) {
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
  const HandTactile & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: finger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.finger.size() == 0) {
      out << "finger: []\n";
    } else {
      out << "finger:\n";
      for (auto item : msg.finger) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: thumb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.thumb.size() == 0) {
      out << "thumb: []\n";
    } else {
      out << "thumb:\n";
      for (auto item : msg.thumb) {
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

inline std::string to_yaml(const HandTactile & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::HandTactile & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::HandTactile & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::HandTactile>()
{
  return "teleop_robot_bridge::msg::HandTactile";
}

template<>
inline const char * name<teleop_robot_bridge::msg::HandTactile>()
{
  return "teleop_robot_bridge/msg/HandTactile";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::HandTactile>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::HandTactile>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<teleop_robot_bridge::msg::HandTactile>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__TRAITS_HPP_
