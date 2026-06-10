// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/AgvBatteryState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_battery_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'battery_state'
#include "sensor_msgs/msg/detail/battery_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__AgvBatteryState __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__AgvBatteryState __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgvBatteryState_
{
  using Type = AgvBatteryState_<ContainerAllocator>;

  explicit AgvBatteryState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : battery_state(_init)
  {
    (void)_init;
  }

  explicit AgvBatteryState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : battery_state(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _battery_state_type =
    sensor_msgs::msg::BatteryState_<ContainerAllocator>;
  _battery_state_type battery_state;

  // setters for named parameter idiom
  Type & set__battery_state(
    const sensor_msgs::msg::BatteryState_<ContainerAllocator> & _arg)
  {
    this->battery_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvBatteryState
    std::shared_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvBatteryState
    std::shared_ptr<teleop_robot_bridge::msg::AgvBatteryState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgvBatteryState_ & other) const
  {
    if (this->battery_state != other.battery_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgvBatteryState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgvBatteryState_

// alias to use template instance with default allocator
using AgvBatteryState =
  teleop_robot_bridge::msg::AgvBatteryState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__STRUCT_HPP_
