// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/WaistTcpCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_tcp_command.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__STRUCT_HPP_

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
# define DEPRECATED__teleop_robot_bridge__msg__WaistTcpCommand __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__WaistTcpCommand __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WaistTcpCommand_
{
  using Type = WaistTcpCommand_<ContainerAllocator>;

  explicit WaistTcpCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 1>::iterator, std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>(this->name.begin(), this->name.end(), "");
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->euler.begin(), this->euler.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->quat.begin(), this->quat.end(), 0.0);
    }
  }

  explicit WaistTcpCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    name(_alloc),
    position(_alloc),
    euler(_alloc),
    quat(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 1>::iterator, std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>(this->name.begin(), this->name.end(), "");
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->euler.begin(), this->euler.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->quat.begin(), this->quat.end(), 0.0);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _name_type =
    std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 1>;
  _name_type name;
  using _position_type =
    std::array<double, 3>;
  _position_type position;
  using _euler_type =
    std::array<double, 3>;
  _euler_type euler;
  using _quat_type =
    std::array<double, 4>;
  _quat_type quat;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__name(
    const std::array<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, 1> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<double, 3> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__euler(
    const std::array<double, 3> & _arg)
  {
    this->euler = _arg;
    return *this;
  }
  Type & set__quat(
    const std::array<double, 4> & _arg)
  {
    this->quat = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__WaistTcpCommand
    std::shared_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__WaistTcpCommand
    std::shared_ptr<teleop_robot_bridge::msg::WaistTcpCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WaistTcpCommand_ & other) const
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
    if (this->euler != other.euler) {
      return false;
    }
    if (this->quat != other.quat) {
      return false;
    }
    return true;
  }
  bool operator!=(const WaistTcpCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WaistTcpCommand_

// alias to use template instance with default allocator
using WaistTcpCommand =
  teleop_robot_bridge::msg::WaistTcpCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__STRUCT_HPP_
