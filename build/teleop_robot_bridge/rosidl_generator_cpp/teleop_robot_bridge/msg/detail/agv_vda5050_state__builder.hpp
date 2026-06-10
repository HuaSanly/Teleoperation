// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvVda5050State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vda5050_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_vda5050_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvVda5050State_error_description
{
public:
  explicit Init_AgvVda5050State_error_description(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::AgvVda5050State error_description(::teleop_robot_bridge::msg::AgvVda5050State::_error_description_type arg)
  {
    msg_.error_description = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_error_type
{
public:
  explicit Init_AgvVda5050State_error_type(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  Init_AgvVda5050State_error_description error_type(::teleop_robot_bridge::msg::AgvVda5050State::_error_type_type arg)
  {
    msg_.error_type = std::move(arg);
    return Init_AgvVda5050State_error_description(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_operating_mode
{
public:
  explicit Init_AgvVda5050State_operating_mode(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  Init_AgvVda5050State_error_type operating_mode(::teleop_robot_bridge::msg::AgvVda5050State::_operating_mode_type arg)
  {
    msg_.operating_mode = std::move(arg);
    return Init_AgvVda5050State_error_type(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_battery_charge
{
public:
  explicit Init_AgvVda5050State_battery_charge(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  Init_AgvVda5050State_operating_mode battery_charge(::teleop_robot_bridge::msg::AgvVda5050State::_battery_charge_type arg)
  {
    msg_.battery_charge = std::move(arg);
    return Init_AgvVda5050State_operating_mode(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_driving
{
public:
  explicit Init_AgvVda5050State_driving(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  Init_AgvVda5050State_battery_charge driving(::teleop_robot_bridge::msg::AgvVda5050State::_driving_type arg)
  {
    msg_.driving = std::move(arg);
    return Init_AgvVda5050State_battery_charge(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_last_node_id
{
public:
  explicit Init_AgvVda5050State_last_node_id(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  Init_AgvVda5050State_driving last_node_id(::teleop_robot_bridge::msg::AgvVda5050State::_last_node_id_type arg)
  {
    msg_.last_node_id = std::move(arg);
    return Init_AgvVda5050State_driving(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_action_status
{
public:
  explicit Init_AgvVda5050State_action_status(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  Init_AgvVda5050State_last_node_id action_status(::teleop_robot_bridge::msg::AgvVda5050State::_action_status_type arg)
  {
    msg_.action_status = std::move(arg);
    return Init_AgvVda5050State_last_node_id(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_order_id
{
public:
  explicit Init_AgvVda5050State_order_id(::teleop_robot_bridge::msg::AgvVda5050State & msg)
  : msg_(msg)
  {}
  Init_AgvVda5050State_action_status order_id(::teleop_robot_bridge::msg::AgvVda5050State::_order_id_type arg)
  {
    msg_.order_id = std::move(arg);
    return Init_AgvVda5050State_action_status(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

class Init_AgvVda5050State_header
{
public:
  Init_AgvVda5050State_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgvVda5050State_order_id header(::teleop_robot_bridge::msg::AgvVda5050State::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AgvVda5050State_order_id(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvVda5050State msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvVda5050State>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvVda5050State_header();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__BUILDER_HPP_
