// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/GripperDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__STRUCT_HPP_

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
// Member 'devices'
#include "teleop_robot_bridge/msg/detail/single_device_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__GripperDeviceState __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__GripperDeviceState __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GripperDeviceState_
{
  using Type = GripperDeviceState_<ContainerAllocator>;

  explicit GripperDeviceState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->devices.fill(teleop_robot_bridge::msg::SingleDeviceState_<ContainerAllocator>{_init});
    }
  }

  explicit GripperDeviceState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    devices(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->devices.fill(teleop_robot_bridge::msg::SingleDeviceState_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _devices_type =
    std::array<teleop_robot_bridge::msg::SingleDeviceState_<ContainerAllocator>, 2>;
  _devices_type devices;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__devices(
    const std::array<teleop_robot_bridge::msg::SingleDeviceState_<ContainerAllocator>, 2> & _arg)
  {
    this->devices = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__GripperDeviceState
    std::shared_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__GripperDeviceState
    std::shared_ptr<teleop_robot_bridge::msg::GripperDeviceState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperDeviceState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->devices != other.devices) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperDeviceState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperDeviceState_

// alias to use template instance with default allocator
using GripperDeviceState =
  teleop_robot_bridge::msg::GripperDeviceState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_DEVICE_STATE__STRUCT_HPP_
