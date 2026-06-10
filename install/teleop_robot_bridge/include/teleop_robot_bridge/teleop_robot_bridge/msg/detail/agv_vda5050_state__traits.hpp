// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/AgvVda5050State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vda5050_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/agv_vda5050_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgvVda5050State & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: order_id
  {
    out << "order_id: ";
    rosidl_generator_traits::value_to_yaml(msg.order_id, out);
    out << ", ";
  }

  // member: action_status
  {
    out << "action_status: ";
    rosidl_generator_traits::value_to_yaml(msg.action_status, out);
    out << ", ";
  }

  // member: last_node_id
  {
    out << "last_node_id: ";
    rosidl_generator_traits::value_to_yaml(msg.last_node_id, out);
    out << ", ";
  }

  // member: driving
  {
    out << "driving: ";
    rosidl_generator_traits::value_to_yaml(msg.driving, out);
    out << ", ";
  }

  // member: battery_charge
  {
    out << "battery_charge: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_charge, out);
    out << ", ";
  }

  // member: operating_mode
  {
    out << "operating_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.operating_mode, out);
    out << ", ";
  }

  // member: error_type
  {
    out << "error_type: ";
    rosidl_generator_traits::value_to_yaml(msg.error_type, out);
    out << ", ";
  }

  // member: error_description
  {
    out << "error_description: ";
    rosidl_generator_traits::value_to_yaml(msg.error_description, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AgvVda5050State & msg,
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

  // member: order_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "order_id: ";
    rosidl_generator_traits::value_to_yaml(msg.order_id, out);
    out << "\n";
  }

  // member: action_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "action_status: ";
    rosidl_generator_traits::value_to_yaml(msg.action_status, out);
    out << "\n";
  }

  // member: last_node_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_node_id: ";
    rosidl_generator_traits::value_to_yaml(msg.last_node_id, out);
    out << "\n";
  }

  // member: driving
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driving: ";
    rosidl_generator_traits::value_to_yaml(msg.driving, out);
    out << "\n";
  }

  // member: battery_charge
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_charge: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_charge, out);
    out << "\n";
  }

  // member: operating_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operating_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.operating_mode, out);
    out << "\n";
  }

  // member: error_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_type: ";
    rosidl_generator_traits::value_to_yaml(msg.error_type, out);
    out << "\n";
  }

  // member: error_description
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_description: ";
    rosidl_generator_traits::value_to_yaml(msg.error_description, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgvVda5050State & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::AgvVda5050State & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::AgvVda5050State & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::AgvVda5050State>()
{
  return "teleop_robot_bridge::msg::AgvVda5050State";
}

template<>
inline const char * name<teleop_robot_bridge::msg::AgvVda5050State>()
{
  return "teleop_robot_bridge/msg/AgvVda5050State";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::AgvVda5050State>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::AgvVda5050State>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<teleop_robot_bridge::msg::AgvVda5050State>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__TRAITS_HPP_
