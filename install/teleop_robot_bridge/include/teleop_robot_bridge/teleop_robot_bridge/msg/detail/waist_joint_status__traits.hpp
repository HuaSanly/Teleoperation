// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/WaistJointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_STATUS__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/waist_joint_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'joint_status'
#include "teleop_robot_bridge/msg/detail/joint_status__traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const WaistJointStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: name
  {
    if (msg.name.size() == 0) {
      out << "name: []";
    } else {
      out << "name: [";
      size_t pending_items = msg.name.size();
      for (auto item : msg.name) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: joint_status
  {
    if (msg.joint_status.size() == 0) {
      out << "joint_status: []";
    } else {
      out << "joint_status: [";
      size_t pending_items = msg.joint_status.size();
      for (auto item : msg.joint_status) {
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
  const WaistJointStatus & msg,
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

  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.name.size() == 0) {
      out << "name: []\n";
    } else {
      out << "name:\n";
      for (auto item : msg.name) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: joint_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joint_status.size() == 0) {
      out << "joint_status: []\n";
    } else {
      out << "joint_status:\n";
      for (auto item : msg.joint_status) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WaistJointStatus & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::WaistJointStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::WaistJointStatus & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::WaistJointStatus>()
{
  return "teleop_robot_bridge::msg::WaistJointStatus";
}

template<>
inline const char * name<teleop_robot_bridge::msg::WaistJointStatus>()
{
  return "teleop_robot_bridge/msg/WaistJointStatus";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::WaistJointStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::WaistJointStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<teleop_robot_bridge::msg::WaistJointStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_STATUS__TRAITS_HPP_
