// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleop_robot_bridge:msg/JointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__TRAITS_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleop_robot_bridge/msg/detail/joint_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace teleop_robot_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const JointStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: driver_voltage
  {
    out << "driver_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_voltage, out);
    out << ", ";
  }

  // member: driver_temperature
  {
    out << "driver_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_temperature, out);
    out << ", ";
  }

  // member: driver_state
  {
    out << "driver_state: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_state, out);
    out << ", ";
  }

  // member: motor_temperature
  {
    out << "motor_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_temperature, out);
    out << ", ";
  }

  // member: rpm
  {
    out << "rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.rpm, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << ", ";
  }

  // member: pulse_count
  {
    out << "pulse_count: ";
    rosidl_generator_traits::value_to_yaml(msg.pulse_count, out);
    out << ", ";
  }

  // member: motor_angles
  {
    out << "motor_angles: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_angles, out);
    out << ", ";
  }

  // member: motor_speeds
  {
    out << "motor_speeds: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_speeds, out);
    out << ", ";
  }

  // member: motor_loads
  {
    out << "motor_loads: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_loads, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const JointStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: driver_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driver_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_voltage, out);
    out << "\n";
  }

  // member: driver_temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driver_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_temperature, out);
    out << "\n";
  }

  // member: driver_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driver_state: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_state, out);
    out << "\n";
  }

  // member: motor_temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_temperature, out);
    out << "\n";
  }

  // member: rpm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.rpm, out);
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

  // member: pulse_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pulse_count: ";
    rosidl_generator_traits::value_to_yaml(msg.pulse_count, out);
    out << "\n";
  }

  // member: motor_angles
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor_angles: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_angles, out);
    out << "\n";
  }

  // member: motor_speeds
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor_speeds: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_speeds, out);
    out << "\n";
  }

  // member: motor_loads
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor_loads: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_loads, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const JointStatus & msg, bool use_flow_style = false)
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
  const teleop_robot_bridge::msg::JointStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleop_robot_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleop_robot_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleop_robot_bridge::msg::JointStatus & msg)
{
  return teleop_robot_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleop_robot_bridge::msg::JointStatus>()
{
  return "teleop_robot_bridge::msg::JointStatus";
}

template<>
inline const char * name<teleop_robot_bridge::msg::JointStatus>()
{
  return "teleop_robot_bridge/msg/JointStatus";
}

template<>
struct has_fixed_size<teleop_robot_bridge::msg::JointStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<teleop_robot_bridge::msg::JointStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<teleop_robot_bridge::msg::JointStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__TRAITS_HPP_
