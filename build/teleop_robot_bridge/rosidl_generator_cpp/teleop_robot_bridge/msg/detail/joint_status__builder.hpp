// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/JointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/joint_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_JointStatus_motor_loads
{
public:
  explicit Init_JointStatus_motor_loads(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::JointStatus motor_loads(::teleop_robot_bridge::msg::JointStatus::_motor_loads_type arg)
  {
    msg_.motor_loads = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_motor_speeds
{
public:
  explicit Init_JointStatus_motor_speeds(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_motor_loads motor_speeds(::teleop_robot_bridge::msg::JointStatus::_motor_speeds_type arg)
  {
    msg_.motor_speeds = std::move(arg);
    return Init_JointStatus_motor_loads(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_motor_angles
{
public:
  explicit Init_JointStatus_motor_angles(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_motor_speeds motor_angles(::teleop_robot_bridge::msg::JointStatus::_motor_angles_type arg)
  {
    msg_.motor_angles = std::move(arg);
    return Init_JointStatus_motor_speeds(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_pulse_count
{
public:
  explicit Init_JointStatus_pulse_count(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_motor_angles pulse_count(::teleop_robot_bridge::msg::JointStatus::_pulse_count_type arg)
  {
    msg_.pulse_count = std::move(arg);
    return Init_JointStatus_motor_angles(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_current
{
public:
  explicit Init_JointStatus_current(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_pulse_count current(::teleop_robot_bridge::msg::JointStatus::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_JointStatus_pulse_count(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_rpm
{
public:
  explicit Init_JointStatus_rpm(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_current rpm(::teleop_robot_bridge::msg::JointStatus::_rpm_type arg)
  {
    msg_.rpm = std::move(arg);
    return Init_JointStatus_current(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_motor_temperature
{
public:
  explicit Init_JointStatus_motor_temperature(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_rpm motor_temperature(::teleop_robot_bridge::msg::JointStatus::_motor_temperature_type arg)
  {
    msg_.motor_temperature = std::move(arg);
    return Init_JointStatus_rpm(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_driver_state
{
public:
  explicit Init_JointStatus_driver_state(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_motor_temperature driver_state(::teleop_robot_bridge::msg::JointStatus::_driver_state_type arg)
  {
    msg_.driver_state = std::move(arg);
    return Init_JointStatus_motor_temperature(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_driver_temperature
{
public:
  explicit Init_JointStatus_driver_temperature(::teleop_robot_bridge::msg::JointStatus & msg)
  : msg_(msg)
  {}
  Init_JointStatus_driver_state driver_temperature(::teleop_robot_bridge::msg::JointStatus::_driver_temperature_type arg)
  {
    msg_.driver_temperature = std::move(arg);
    return Init_JointStatus_driver_state(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

class Init_JointStatus_driver_voltage
{
public:
  Init_JointStatus_driver_voltage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointStatus_driver_temperature driver_voltage(::teleop_robot_bridge::msg::JointStatus::_driver_voltage_type arg)
  {
    msg_.driver_voltage = std::move(arg);
    return Init_JointStatus_driver_temperature(msg_);
  }

private:
  ::teleop_robot_bridge::msg::JointStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::JointStatus>()
{
  return teleop_robot_bridge::msg::builder::Init_JointStatus_driver_voltage();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__BUILDER_HPP_
