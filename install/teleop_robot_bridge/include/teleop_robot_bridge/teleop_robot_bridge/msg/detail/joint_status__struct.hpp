// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/JointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__JointStatus __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__JointStatus __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct JointStatus_
{
  using Type = JointStatus_<ContainerAllocator>;

  explicit JointStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->driver_voltage = 0.0f;
      this->driver_temperature = 0.0f;
      this->driver_state = 0;
      this->motor_temperature = 0.0f;
      this->rpm = 0l;
      this->current = 0.0f;
      this->pulse_count = 0ll;
      this->motor_angles = 0l;
      this->motor_speeds = 0l;
      this->motor_loads = 0l;
    }
  }

  explicit JointStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->driver_voltage = 0.0f;
      this->driver_temperature = 0.0f;
      this->driver_state = 0;
      this->motor_temperature = 0.0f;
      this->rpm = 0l;
      this->current = 0.0f;
      this->pulse_count = 0ll;
      this->motor_angles = 0l;
      this->motor_speeds = 0l;
      this->motor_loads = 0l;
    }
  }

  // field types and members
  using _driver_voltage_type =
    float;
  _driver_voltage_type driver_voltage;
  using _driver_temperature_type =
    float;
  _driver_temperature_type driver_temperature;
  using _driver_state_type =
    uint8_t;
  _driver_state_type driver_state;
  using _motor_temperature_type =
    float;
  _motor_temperature_type motor_temperature;
  using _rpm_type =
    int32_t;
  _rpm_type rpm;
  using _current_type =
    float;
  _current_type current;
  using _pulse_count_type =
    int64_t;
  _pulse_count_type pulse_count;
  using _motor_angles_type =
    int32_t;
  _motor_angles_type motor_angles;
  using _motor_speeds_type =
    int32_t;
  _motor_speeds_type motor_speeds;
  using _motor_loads_type =
    int32_t;
  _motor_loads_type motor_loads;

  // setters for named parameter idiom
  Type & set__driver_voltage(
    const float & _arg)
  {
    this->driver_voltage = _arg;
    return *this;
  }
  Type & set__driver_temperature(
    const float & _arg)
  {
    this->driver_temperature = _arg;
    return *this;
  }
  Type & set__driver_state(
    const uint8_t & _arg)
  {
    this->driver_state = _arg;
    return *this;
  }
  Type & set__motor_temperature(
    const float & _arg)
  {
    this->motor_temperature = _arg;
    return *this;
  }
  Type & set__rpm(
    const int32_t & _arg)
  {
    this->rpm = _arg;
    return *this;
  }
  Type & set__current(
    const float & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__pulse_count(
    const int64_t & _arg)
  {
    this->pulse_count = _arg;
    return *this;
  }
  Type & set__motor_angles(
    const int32_t & _arg)
  {
    this->motor_angles = _arg;
    return *this;
  }
  Type & set__motor_speeds(
    const int32_t & _arg)
  {
    this->motor_speeds = _arg;
    return *this;
  }
  Type & set__motor_loads(
    const int32_t & _arg)
  {
    this->motor_loads = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::JointStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::JointStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__JointStatus
    std::shared_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__JointStatus
    std::shared_ptr<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const JointStatus_ & other) const
  {
    if (this->driver_voltage != other.driver_voltage) {
      return false;
    }
    if (this->driver_temperature != other.driver_temperature) {
      return false;
    }
    if (this->driver_state != other.driver_state) {
      return false;
    }
    if (this->motor_temperature != other.motor_temperature) {
      return false;
    }
    if (this->rpm != other.rpm) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    if (this->pulse_count != other.pulse_count) {
      return false;
    }
    if (this->motor_angles != other.motor_angles) {
      return false;
    }
    if (this->motor_speeds != other.motor_speeds) {
      return false;
    }
    if (this->motor_loads != other.motor_loads) {
      return false;
    }
    return true;
  }
  bool operator!=(const JointStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct JointStatus_

// alias to use template instance with default allocator
using JointStatus =
  teleop_robot_bridge::msg::JointStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__STRUCT_HPP_
