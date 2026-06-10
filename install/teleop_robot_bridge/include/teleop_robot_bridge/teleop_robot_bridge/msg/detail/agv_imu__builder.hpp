// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleop_robot_bridge:msg/AgvImu.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_imu.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__BUILDER_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleop_robot_bridge/msg/detail/agv_imu__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleop_robot_bridge
{

namespace msg
{

namespace builder
{

class Init_AgvImu_magnetic_field
{
public:
  explicit Init_AgvImu_magnetic_field(::teleop_robot_bridge::msg::AgvImu & msg)
  : msg_(msg)
  {}
  ::teleop_robot_bridge::msg::AgvImu magnetic_field(::teleop_robot_bridge::msg::AgvImu::_magnetic_field_type arg)
  {
    msg_.magnetic_field = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvImu msg_;
};

class Init_AgvImu_imu
{
public:
  Init_AgvImu_imu()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgvImu_magnetic_field imu(::teleop_robot_bridge::msg::AgvImu::_imu_type arg)
  {
    msg_.imu = std::move(arg);
    return Init_AgvImu_magnetic_field(msg_);
  }

private:
  ::teleop_robot_bridge::msg::AgvImu msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleop_robot_bridge::msg::AgvImu>()
{
  return teleop_robot_bridge::msg::builder::Init_AgvImu_imu();
}

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__BUILDER_HPP_
