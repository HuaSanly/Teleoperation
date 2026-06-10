// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/hand_tactile.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__HandTactile __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__HandTactile __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandTactile_
{
  using Type = HandTactile_<ContainerAllocator>;

  explicit HandTactile_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 4>::iterator, int32_t>(this->finger.begin(), this->finger.end(), 0l);
      std::fill<typename std::array<int32_t, 4>::iterator, int32_t>(this->thumb.begin(), this->thumb.end(), 0l);
    }
  }

  explicit HandTactile_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : finger(_alloc),
    thumb(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 4>::iterator, int32_t>(this->finger.begin(), this->finger.end(), 0l);
      std::fill<typename std::array<int32_t, 4>::iterator, int32_t>(this->thumb.begin(), this->thumb.end(), 0l);
    }
  }

  // field types and members
  using _finger_type =
    std::array<int32_t, 4>;
  _finger_type finger;
  using _thumb_type =
    std::array<int32_t, 4>;
  _thumb_type thumb;

  // setters for named parameter idiom
  Type & set__finger(
    const std::array<int32_t, 4> & _arg)
  {
    this->finger = _arg;
    return *this;
  }
  Type & set__thumb(
    const std::array<int32_t, 4> & _arg)
  {
    this->thumb = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__HandTactile
    std::shared_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__HandTactile
    std::shared_ptr<teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandTactile_ & other) const
  {
    if (this->finger != other.finger) {
      return false;
    }
    if (this->thumb != other.thumb) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandTactile_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandTactile_

// alias to use template instance with default allocator
using HandTactile =
  teleop_robot_bridge::msg::HandTactile_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__STRUCT_HPP_
