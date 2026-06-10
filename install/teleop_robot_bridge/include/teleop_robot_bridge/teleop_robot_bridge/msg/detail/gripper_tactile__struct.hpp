// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/GripperTactile.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_tactile.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'left'
// Member 'right'
#include "teleop_robot_bridge/msg/detail/hand_tactile__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__GripperTactile __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__GripperTactile __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GripperTactile_
{
  using Type = GripperTactile_<ContainerAllocator>;

  explicit GripperTactile_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    left(_init),
    right(_init)
  {
    (void)_init;
  }

  explicit GripperTactile_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    left(_alloc, _init),
    right(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _left_type =
    teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>;
  _left_type left;
  using _right_type =
    teleop_robot_bridge::msg::HandTactile_<ContainerAllocator>;
  _right_type right;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__left(
    const teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> & _arg)
  {
    this->left = _arg;
    return *this;
  }
  Type & set__right(
    const teleop_robot_bridge::msg::HandTactile_<ContainerAllocator> & _arg)
  {
    this->right = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__GripperTactile
    std::shared_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__GripperTactile
    std::shared_ptr<teleop_robot_bridge::msg::GripperTactile_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperTactile_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->left != other.left) {
      return false;
    }
    if (this->right != other.right) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperTactile_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperTactile_

// alias to use template instance with default allocator
using GripperTactile =
  teleop_robot_bridge::msg::GripperTactile_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__STRUCT_HPP_
