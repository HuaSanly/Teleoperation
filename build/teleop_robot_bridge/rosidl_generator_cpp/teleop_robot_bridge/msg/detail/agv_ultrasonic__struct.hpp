// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_ultrasonic.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'ranges'
#include "sensor_msgs/msg/detail/range__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__AgvUltrasonic __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__AgvUltrasonic __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgvUltrasonic_
{
  using Type = AgvUltrasonic_<ContainerAllocator>;

  explicit AgvUltrasonic_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ranges.fill(sensor_msgs::msg::Range_<ContainerAllocator>{_init});
    }
  }

  explicit AgvUltrasonic_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : ranges(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ranges.fill(sensor_msgs::msg::Range_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _ranges_type =
    std::array<sensor_msgs::msg::Range_<ContainerAllocator>, 8>;
  _ranges_type ranges;

  // setters for named parameter idiom
  Type & set__ranges(
    const std::array<sensor_msgs::msg::Range_<ContainerAllocator>, 8> & _arg)
  {
    this->ranges = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvUltrasonic
    std::shared_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvUltrasonic
    std::shared_ptr<teleop_robot_bridge::msg::AgvUltrasonic_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgvUltrasonic_ & other) const
  {
    if (this->ranges != other.ranges) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgvUltrasonic_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgvUltrasonic_

// alias to use template instance with default allocator
using AgvUltrasonic =
  teleop_robot_bridge::msg::AgvUltrasonic_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__STRUCT_HPP_
