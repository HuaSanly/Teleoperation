// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/AgvJointFeedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_joint_feedback.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__AgvJointFeedback __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__AgvJointFeedback __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgvJointFeedback_
{
  using Type = AgvJointFeedback_<ContainerAllocator>;

  explicit AgvJointFeedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 4>::iterator, std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>(this->name.begin(), this->name.end(), "");
      std::fill<typename std::array<double, 4>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->effort.begin(), this->effort.end(), 0.0);
    }
  }

  explicit AgvJointFeedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    name(_alloc),
    position(_alloc),
    velocity(_alloc),
    effort(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 4>::iterator, std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>(this->name.begin(), this->name.end(), "");
      std::fill<typename std::array<double, 4>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->effort.begin(), this->effort.end(), 0.0);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _name_type =
    std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 4>;
  _name_type name;
  using _position_type =
    std::array<double, 4>;
  _position_type position;
  using _velocity_type =
    std::array<double, 4>;
  _velocity_type velocity;
  using _effort_type =
    std::array<double, 4>;
  _effort_type effort;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__name(
    const std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 4> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<double, 4> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const std::array<double, 4> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__effort(
    const std::array<double, 4> & _arg)
  {
    this->effort = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvJointFeedback
    std::shared_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvJointFeedback
    std::shared_ptr<teleop_robot_bridge::msg::AgvJointFeedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgvJointFeedback_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->name != other.name) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->effort != other.effort) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgvJointFeedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgvJointFeedback_

// alias to use template instance with default allocator
using AgvJointFeedback =
  teleop_robot_bridge::msg::AgvJointFeedback_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__STRUCT_HPP_
