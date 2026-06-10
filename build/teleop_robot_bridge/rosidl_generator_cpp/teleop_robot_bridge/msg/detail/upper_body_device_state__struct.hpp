// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/UpperBodyDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/upper_body_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__STRUCT_HPP_

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
// Member 'device_state'
#include "teleop_robot_bridge/msg/detail/single_device_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__UpperBodyDeviceState __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__UpperBodyDeviceState __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UpperBodyDeviceState_
{
  using Type = UpperBodyDeviceState_<ContainerAllocator>;

  explicit UpperBodyDeviceState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    device_state(_init)
  {
    (void)_init;
  }

  explicit UpperBodyDeviceState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    device_state(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _device_state_type =
    teleop_robot_bridge::msg::SingleDeviceState_<ContainerAllocator>;
  _device_state_type device_state;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__device_state(
    const teleop_robot_bridge::msg::SingleDeviceState_<ContainerAllocator> & _arg)
  {
    this->device_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__UpperBodyDeviceState
    std::shared_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__UpperBodyDeviceState
    std::shared_ptr<teleop_robot_bridge::msg::UpperBodyDeviceState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UpperBodyDeviceState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->device_state != other.device_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const UpperBodyDeviceState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UpperBodyDeviceState_

// alias to use template instance with default allocator
using UpperBodyDeviceState =
  teleop_robot_bridge::msg::UpperBodyDeviceState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__STRUCT_HPP_
