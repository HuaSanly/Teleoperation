// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/AgvVel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vel.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__STRUCT_HPP_

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
// Member 'linear'
// Member 'angular'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__AgvVel __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__AgvVel __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgvVel_
{
  using Type = AgvVel_<ContainerAllocator>;

  explicit AgvVel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    linear(_init),
    angular(_init)
  {
    (void)_init;
  }

  explicit AgvVel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    linear(_alloc, _init),
    angular(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _linear_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _linear_type linear;
  using _angular_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _angular_type angular;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__linear(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->linear = _arg;
    return *this;
  }
  Type & set__angular(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->angular = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::AgvVel_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::AgvVel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvVel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvVel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvVel
    std::shared_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvVel
    std::shared_ptr<teleop_robot_bridge::msg::AgvVel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgvVel_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->linear != other.linear) {
      return false;
    }
    if (this->angular != other.angular) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgvVel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgvVel_

// alias to use template instance with default allocator
using AgvVel =
  teleop_robot_bridge::msg::AgvVel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__STRUCT_HPP_
