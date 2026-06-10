// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/WaistMotionCtrl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_motion_ctrl.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__WaistMotionCtrl __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__WaistMotionCtrl __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WaistMotionCtrl_
{
  using Type = WaistMotionCtrl_<ContainerAllocator>;

  explicit WaistMotionCtrl_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<bool, 4>::iterator, bool>(this->enable_states.begin(), this->enable_states.end(), false);
    }
  }

  explicit WaistMotionCtrl_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : enable_states(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<bool, 4>::iterator, bool>(this->enable_states.begin(), this->enable_states.end(), false);
    }
  }

  // field types and members
  using _enable_states_type =
    std::array<bool, 4>;
  _enable_states_type enable_states;

  // setters for named parameter idiom
  Type & set__enable_states(
    const std::array<bool, 4> & _arg)
  {
    this->enable_states = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__WaistMotionCtrl
    std::shared_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__WaistMotionCtrl
    std::shared_ptr<teleop_robot_bridge::msg::WaistMotionCtrl_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WaistMotionCtrl_ & other) const
  {
    if (this->enable_states != other.enable_states) {
      return false;
    }
    return true;
  }
  bool operator!=(const WaistMotionCtrl_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WaistMotionCtrl_

// alias to use template instance with default allocator
using WaistMotionCtrl =
  teleop_robot_bridge::msg::WaistMotionCtrl_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__STRUCT_HPP_
