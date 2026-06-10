// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/AgvVel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vel.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/agv_vel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'linear'
// Member 'angular'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgvVel & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: linear
  {
    out << "linear: ";
    to_flow_style_yaml(msg.linear, out);
    out << ", ";
  }

  // member: angular
  {
    out << "angular: ";
    to_flow_style_yaml(msg.angular, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AgvVel & msg,
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

  // member: linear
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linear:\n";
    to_block_style_yaml(msg.linear, out, indentation + 2);
  }

  // member: angular
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angular:\n";
    to_block_style_yaml(msg.angular, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgvVel & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::AgvVel & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::AgvVel & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::AgvVel>()
{
  return "teleop_robot_bridge::msg::AgvVel";
}

template<>
inline const char * name<teleop_robot_bridge::msg::AgvVel>()
{
  return "teleop_robot_bridge/msg/AgvVel";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::AgvVel>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Vector3>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::AgvVel>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Vector3>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<teleop_robot_bridge::msg::AgvVel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__TRAITS_HPP_
