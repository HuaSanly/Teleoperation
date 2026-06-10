// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_ultrasonic.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'ranges'
#include "sensor_msgs/msg/detail/range__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgvUltrasonic & msg,
  std::ostream & out)
{
  out << "{";
  // member: ranges
  {
    if (msg.ranges.size() == 0) {
      out << "ranges: []";
    } else {
      out << "ranges: [";
      size_t pending_items = msg.ranges.size();
      for (auto item : msg.ranges) {
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
  const AgvUltrasonic & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ranges
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.ranges.size() == 0) {
      out << "ranges: []\n";
    } else {
      out << "ranges:\n";
      for (auto item : msg.ranges) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgvUltrasonic & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::AgvUltrasonic & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::AgvUltrasonic & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::AgvUltrasonic>()
{
  return "teleop_robot_bridge::msg::AgvUltrasonic";
}

template<>
inline const char * name<teleop_robot_bridge::msg::AgvUltrasonic>()
{
  return "teleop_robot_bridge/msg/AgvUltrasonic";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::AgvUltrasonic>
  : std::integral_constant<bool, has_fixed_size<sensor_msgs::msg::Range>::value> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::AgvUltrasonic>
  : std::integral_constant<bool, has_bounded_size<sensor_msgs::msg::Range>::value> {};

template<>
struct is_message<teleop_robot_bridge::msg::AgvUltrasonic>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__TRAITS_HPP_
