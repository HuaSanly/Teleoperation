// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/SingleDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_DEVICE_STATE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_DEVICE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/single_device_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_SingleDeviceState_firmware_version
{
public:
  explicit Init_SingleDeviceState_firmware_version(::teleop_robot_bridge::msg::SingleDeviceState & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::SingleDeviceState firmware_version(::teleop_robot_bridge::msg::SingleDeviceState::_firmware_version_type arg)
  {
    msg_.firmware_version = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

class Init_SingleDeviceState_model
{
public:
  explicit Init_SingleDeviceState_model(::teleop_robot_bridge::msg::SingleDeviceState & msg)
  : msg_(msg)
  {}
  Init_SingleDeviceState_firmware_version model(::teleop_robot_bridge::msg::SingleDeviceState::_model_type arg)
  {
    msg_.model = std::move(arg);
    return Init_SingleDeviceState_firmware_version(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

class Init_SingleDeviceState_manufacturer
{
public:
  explicit Init_SingleDeviceState_manufacturer(::teleop_robot_bridge::msg::SingleDeviceState & msg)
  : msg_(msg)
  {}
  Init_SingleDeviceState_model manufacturer(::teleop_robot_bridge::msg::SingleDeviceState::_manufacturer_type arg)
  {
    msg_.manufacturer = std::move(arg);
    return Init_SingleDeviceState_model(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

class Init_SingleDeviceState_connectivity_status
{
public:
  explicit Init_SingleDeviceState_connectivity_status(::teleop_robot_bridge::msg::SingleDeviceState & msg)
  : msg_(msg)
  {}
  Init_SingleDeviceState_manufacturer connectivity_status(::teleop_robot_bridge::msg::SingleDeviceState::_connectivity_status_type arg)
  {
    msg_.connectivity_status = std::move(arg);
    return Init_SingleDeviceState_manufacturer(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

class Init_SingleDeviceState_power_state
{
public:
  explicit Init_SingleDeviceState_power_state(::teleop_robot_bridge::msg::SingleDeviceState & msg)
  : msg_(msg)
  {}
  Init_SingleDeviceState_connectivity_status power_state(::teleop_robot_bridge::msg::SingleDeviceState::_power_state_type arg)
  {
    msg_.power_state = std::move(arg);
    return Init_SingleDeviceState_connectivity_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

class Init_SingleDeviceState_operational_mode
{
public:
  explicit Init_SingleDeviceState_operational_mode(::teleop_robot_bridge::msg::SingleDeviceState & msg)
  : msg_(msg)
  {}
  Init_SingleDeviceState_power_state operational_mode(::teleop_robot_bridge::msg::SingleDeviceState::_operational_mode_type arg)
  {
    msg_.operational_mode = std::move(arg);
    return Init_SingleDeviceState_power_state(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

class Init_SingleDeviceState_error_domain
{
public:
  explicit Init_SingleDeviceState_error_domain(::teleop_robot_bridge::msg::SingleDeviceState & msg)
  : msg_(msg)
  {}
  Init_SingleDeviceState_operational_mode error_domain(::teleop_robot_bridge::msg::SingleDeviceState::_error_domain_type arg)
  {
    msg_.error_domain = std::move(arg);
    return Init_SingleDeviceState_operational_mode(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

class Init_SingleDeviceState_health_status
{
public:
  Init_SingleDeviceState_health_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SingleDeviceState_error_domain health_status(::teleop_robot_bridge::msg::SingleDeviceState::_health_status_type arg)
  {
    msg_.health_status = std::move(arg);
    return Init_SingleDeviceState_error_domain(msg_);
  }

private:
  ::teleop_robot_bridge::msg::SingleDeviceState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::SingleDeviceState>()
{
  return teleop_robot_bridge::msg::builder::Init_SingleDeviceState_health_status();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_DEVICE_STATE__BUILDER_HPP_
