// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/JoyState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joy_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'joy'
#include "sensor_msgs/msg/detail/joy__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__JoyState __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__JoyState __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct JoyState_
{
  using Type = JoyState_<ContainerAllocator>;

  explicit JoyState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : joy(_init)
  {
    (void)_init;
  }

  explicit JoyState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : joy(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _joy_type =
    sensor_msgs::msg::Joy_<ContainerAllocator>;
  _joy_type joy;

  // setters for named parameter idiom
  Type & set__joy(
    const sensor_msgs::msg::Joy_<ContainerAllocator> & _arg)
  {
    this->joy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::JoyState_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::JoyState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::JoyState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::JoyState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__JoyState
    std::shared_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__JoyState
    std::shared_ptr<teleop_robot_bridge::msg::JoyState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const JoyState_ & other) const
  {
    if (this->joy != other.joy) {
      return false;
    }
    return true;
  }
  bool operator!=(const JoyState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct JoyState_

// alias to use template instance with default allocator
using JoyState =
  teleop_robot_bridge::msg::JoyState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__STRUCT_HPP_
