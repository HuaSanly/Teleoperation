// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/SingleGripperStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_gripper_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__SingleGripperStatus __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__SingleGripperStatus __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SingleGripperStatus_
{
  using Type = SingleGripperStatus_<ContainerAllocator>;

  explicit SingleGripperStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_ready = false;
      this->is_reset = false;
      this->is_moving = false;
      this->obj_detected = false;
      this->fault_status = 0;
      this->position = 0l;
      this->requested_position = 0l;
      this->current = 0.0f;
    }
  }

  explicit SingleGripperStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_ready = false;
      this->is_reset = false;
      this->is_moving = false;
      this->obj_detected = false;
      this->fault_status = 0;
      this->position = 0l;
      this->requested_position = 0l;
      this->current = 0.0f;
    }
  }

  // field types and members
  using _is_ready_type =
    bool;
  _is_ready_type is_ready;
  using _is_reset_type =
    bool;
  _is_reset_type is_reset;
  using _is_moving_type =
    bool;
  _is_moving_type is_moving;
  using _obj_detected_type =
    bool;
  _obj_detected_type obj_detected;
  using _fault_status_type =
    uint8_t;
  _fault_status_type fault_status;
  using _position_type =
    int32_t;
  _position_type position;
  using _requested_position_type =
    int32_t;
  _requested_position_type requested_position;
  using _current_type =
    float;
  _current_type current;

  // setters for named parameter idiom
  Type & set__is_ready(
    const bool & _arg)
  {
    this->is_ready = _arg;
    return *this;
  }
  Type & set__is_reset(
    const bool & _arg)
  {
    this->is_reset = _arg;
    return *this;
  }
  Type & set__is_moving(
    const bool & _arg)
  {
    this->is_moving = _arg;
    return *this;
  }
  Type & set__obj_detected(
    const bool & _arg)
  {
    this->obj_detected = _arg;
    return *this;
  }
  Type & set__fault_status(
    const uint8_t & _arg)
  {
    this->fault_status = _arg;
    return *this;
  }
  Type & set__position(
    const int32_t & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__requested_position(
    const int32_t & _arg)
  {
    this->requested_position = _arg;
    return *this;
  }
  Type & set__current(
    const float & _arg)
  {
    this->current = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__SingleGripperStatus
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__SingleGripperStatus
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SingleGripperStatus_ & other) const
  {
    if (this->is_ready != other.is_ready) {
      return false;
    }
    if (this->is_reset != other.is_reset) {
      return false;
    }
    if (this->is_moving != other.is_moving) {
      return false;
    }
    if (this->obj_detected != other.obj_detected) {
      return false;
    }
    if (this->fault_status != other.fault_status) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->requested_position != other.requested_position) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    return true;
  }
  bool operator!=(const SingleGripperStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SingleGripperStatus_

// alias to use template instance with default allocator
using SingleGripperStatus =
  teleop_robot_bridge::msg::SingleGripperStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__STRUCT_HPP_
