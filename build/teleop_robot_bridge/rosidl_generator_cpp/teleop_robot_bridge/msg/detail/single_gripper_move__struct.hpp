// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/SingleGripperMove.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_gripper_move.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__SingleGripperMove __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__SingleGripperMove __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SingleGripperMove_
{
  using Type = SingleGripperMove_<ContainerAllocator>;

  explicit SingleGripperMove_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->emergency_release = false;
      this->emergency_release_dir = 0;
      this->stop = false;
      this->position = 0l;
      this->speed = 0l;
      this->force = 0l;
    }
  }

  explicit SingleGripperMove_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->emergency_release = false;
      this->emergency_release_dir = 0;
      this->stop = false;
      this->position = 0l;
      this->speed = 0l;
      this->force = 0l;
    }
  }

  // field types and members
  using _emergency_release_type =
    bool;
  _emergency_release_type emergency_release;
  using _emergency_release_dir_type =
    uint8_t;
  _emergency_release_dir_type emergency_release_dir;
  using _stop_type =
    bool;
  _stop_type stop;
  using _position_type =
    int32_t;
  _position_type position;
  using _speed_type =
    int32_t;
  _speed_type speed;
  using _force_type =
    int32_t;
  _force_type force;

  // setters for named parameter idiom
  Type & set__emergency_release(
    const bool & _arg)
  {
    this->emergency_release = _arg;
    return *this;
  }
  Type & set__emergency_release_dir(
    const uint8_t & _arg)
  {
    this->emergency_release_dir = _arg;
    return *this;
  }
  Type & set__stop(
    const bool & _arg)
  {
    this->stop = _arg;
    return *this;
  }
  Type & set__position(
    const int32_t & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__speed(
    const int32_t & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__force(
    const int32_t & _arg)
  {
    this->force = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__SingleGripperMove
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__SingleGripperMove
    std::shared_ptr<teleop_robot_bridge::msg::SingleGripperMove_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SingleGripperMove_ & other) const
  {
    if (this->emergency_release != other.emergency_release) {
      return false;
    }
    if (this->emergency_release_dir != other.emergency_release_dir) {
      return false;
    }
    if (this->stop != other.stop) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    if (this->force != other.force) {
      return false;
    }
    return true;
  }
  bool operator!=(const SingleGripperMove_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SingleGripperMove_

// alias to use template instance with default allocator
using SingleGripperMove =
  teleop_robot_bridge::msg::SingleGripperMove_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__STRUCT_HPP_
