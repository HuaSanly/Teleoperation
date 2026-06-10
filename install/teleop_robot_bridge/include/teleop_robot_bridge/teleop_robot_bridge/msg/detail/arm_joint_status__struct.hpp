// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/ArmJointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/arm_joint_status.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_STATUS__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_STATUS__STRUCT_HPP_

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
// Member 'joint_status'
#include "teleop_robot_bridge/msg/detail/joint_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__ArmJointStatus __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__ArmJointStatus __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ArmJointStatus_
{
  using Type = ArmJointStatus_<ContainerAllocator>;

  explicit ArmJointStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 14>::iterator, std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>(this->name.begin(), this->name.end(), "");
      this->joint_status.fill(teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>{_init});
    }
  }

  explicit ArmJointStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    name(_alloc),
    joint_status(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 14>::iterator, std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>(this->name.begin(), this->name.end(), "");
      this->joint_status.fill(teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _name_type =
    std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 14>;
  _name_type name;
  using _joint_status_type =
    std::array<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>, 14>;
  _joint_status_type joint_status;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__name(
    const std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 14> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__joint_status(
    const std::array<teleop_robot_bridge::msg::JointStatus_<ContainerAllocator>, 14> & _arg)
  {
    this->joint_status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__ArmJointStatus
    std::shared_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__ArmJointStatus
    std::shared_ptr<teleop_robot_bridge::msg::ArmJointStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArmJointStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->name != other.name) {
      return false;
    }
    if (this->joint_status != other.joint_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArmJointStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArmJointStatus_

// alias to use template instance with default allocator
using ArmJointStatus =
  teleop_robot_bridge::msg::ArmJointStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_STATUS__STRUCT_HPP_
