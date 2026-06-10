// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_device_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvDeviceState_firmware_version
{
public:
  explicit Init_AgvDeviceState_firmware_version(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::AgvDeviceState firmware_version(::teleop_robot_bridge::msg::AgvDeviceState::_firmware_version_type arg)
  {
    msg_.firmware_version = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_model
{
public:
  explicit Init_AgvDeviceState_model(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  Init_AgvDeviceState_firmware_version model(::teleop_robot_bridge::msg::AgvDeviceState::_model_type arg)
  {
    msg_.model = std::move(arg);
    return Init_AgvDeviceState_firmware_version(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_manufacturer
{
public:
  explicit Init_AgvDeviceState_manufacturer(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  Init_AgvDeviceState_model manufacturer(::teleop_robot_bridge::msg::AgvDeviceState::_manufacturer_type arg)
  {
    msg_.manufacturer = std::move(arg);
    return Init_AgvDeviceState_model(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_connectivity_status
{
public:
  explicit Init_AgvDeviceState_connectivity_status(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  Init_AgvDeviceState_manufacturer connectivity_status(::teleop_robot_bridge::msg::AgvDeviceState::_connectivity_status_type arg)
  {
    msg_.connectivity_status = std::move(arg);
    return Init_AgvDeviceState_manufacturer(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_power_state
{
public:
  explicit Init_AgvDeviceState_power_state(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  Init_AgvDeviceState_connectivity_status power_state(::teleop_robot_bridge::msg::AgvDeviceState::_power_state_type arg)
  {
    msg_.power_state = std::move(arg);
    return Init_AgvDeviceState_connectivity_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_operational_mode
{
public:
  explicit Init_AgvDeviceState_operational_mode(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  Init_AgvDeviceState_power_state operational_mode(::teleop_robot_bridge::msg::AgvDeviceState::_operational_mode_type arg)
  {
    msg_.operational_mode = std::move(arg);
    return Init_AgvDeviceState_power_state(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_error_domain
{
public:
  explicit Init_AgvDeviceState_error_domain(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  Init_AgvDeviceState_operational_mode error_domain(::teleop_robot_bridge::msg::AgvDeviceState::_error_domain_type arg)
  {
    msg_.error_domain = std::move(arg);
    return Init_AgvDeviceState_operational_mode(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_health_status
{
public:
  explicit Init_AgvDeviceState_health_status(::teleop_robot_bridge::msg::AgvDeviceState & msg)
  : msg_(msg)
  {}
  Init_AgvDeviceState_error_domain health_status(::teleop_robot_bridge::msg::AgvDeviceState::_health_status_type arg)
  {
    msg_.health_status = std::move(arg);
    return Init_AgvDeviceState_error_domain(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

class Init_AgvDeviceState_header
{
public:
  Init_AgvDeviceState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgvDeviceState_health_status header(::teleop_robot_bridge::msg::AgvDeviceState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AgvDeviceState_health_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvDeviceState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvDeviceState>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvDeviceState_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__BUILDER_HPP_
