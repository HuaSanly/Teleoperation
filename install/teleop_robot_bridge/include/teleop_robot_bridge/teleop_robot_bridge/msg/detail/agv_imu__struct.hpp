// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/AgvImu.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_imu.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'imu'
#include "sensor_msgs/msg/detail/imu__struct.hpp"
// Member 'magnetic_field'
#include "sensor_msgs/msg/detail/magnetic_field__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleop_robot_bridge__msg__AgvImu __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__AgvImu __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgvImu_
{
  using Type = AgvImu_<ContainerAllocator>;

  explicit AgvImu_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : imu(_init),
    magnetic_field(_init)
  {
    (void)_init;
  }

  explicit AgvImu_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : imu(_alloc, _init),
    magnetic_field(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _imu_type =
    sensor_msgs::msg::Imu_<ContainerAllocator>;
  _imu_type imu;
  using _magnetic_field_type =
    sensor_msgs::msg::MagneticField_<ContainerAllocator>;
  _magnetic_field_type magnetic_field;

  // setters for named parameter idiom
  Type & set__imu(
    const sensor_msgs::msg::Imu_<ContainerAllocator> & _arg)
  {
    this->imu = _arg;
    return *this;
  }
  Type & set__magnetic_field(
    const sensor_msgs::msg::MagneticField_<ContainerAllocator> & _arg)
  {
    this->magnetic_field = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::AgvImu_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::AgvImu_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvImu_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvImu_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvImu
    std::shared_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvImu
    std::shared_ptr<teleop_robot_bridge::msg::AgvImu_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgvImu_ & other) const
  {
    if (this->imu != other.imu) {
      return false;
    }
    if (this->magnetic_field != other.magnetic_field) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgvImu_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgvImu_

// alias to use template instance with default allocator
using AgvImu =
  teleop_robot_bridge::msg::AgvImu_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__STRUCT_HPP_
