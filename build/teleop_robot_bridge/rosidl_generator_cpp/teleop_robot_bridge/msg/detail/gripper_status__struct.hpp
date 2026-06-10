// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/GripperStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_

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
// Member 'grippers'
#include "teleop_robot_bridge/msg/detail/single_gripper_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__GripperStatus __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__GripperStatus __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GripperStatus_
{
  using Type = GripperStatus_<ContainerAllocator>;

  explicit GripperStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grippers.fill(teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>{_init});
    }
  }

  explicit GripperStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    grippers(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grippers.fill(teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _grippers_type =
    std::array<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>, 2>;
  _grippers_type grippers;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__grippers(
    const std::array<teleop_robot_bridge::msg::SingleGripperStatus_<ContainerAllocator>, 2> & _arg)
  {
    this->grippers = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__GripperStatus
    std::shared_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__GripperStatus
    std::shared_ptr<teleop_robot_bridge::msg::GripperStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->grippers != other.grippers) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperStatus_

// alias to use template instance with default allocator
using GripperStatus =
  teleop_robot_bridge::msg::GripperStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_
