// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/AgvDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_device_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__STRUCT_HPP_

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
# define DEPRECATED__teleop_robot_bridge__msg__AgvDeviceState __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__AgvDeviceState __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgvDeviceState_
{
  using Type = AgvDeviceState_<ContainerAllocator>;

  explicit AgvDeviceState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->health_status = 0;
      this->error_domain = 0;
      this->operational_mode = 0;
      this->power_state = 0;
      this->connectivity_status = 0;
      this->manufacturer = "";
      this->model = "";
      this->firmware_version = "";
    }
  }

  explicit AgvDeviceState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    manufacturer(_alloc),
    model(_alloc),
    firmware_version(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->health_status = 0;
      this->error_domain = 0;
      this->operational_mode = 0;
      this->power_state = 0;
      this->connectivity_status = 0;
      this->manufacturer = "";
      this->model = "";
      this->firmware_version = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _health_status_type =
    uint8_t;
  _health_status_type health_status;
  using _error_domain_type =
    uint8_t;
  _error_domain_type error_domain;
  using _operational_mode_type =
    uint8_t;
  _operational_mode_type operational_mode;
  using _power_state_type =
    uint8_t;
  _power_state_type power_state;
  using _connectivity_status_type =
    uint8_t;
  _connectivity_status_type connectivity_status;
  using _manufacturer_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _manufacturer_type manufacturer;
  using _model_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _model_type model;
  using _firmware_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _firmware_version_type firmware_version;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__health_status(
    const uint8_t & _arg)
  {
    this->health_status = _arg;
    return *this;
  }
  Type & set__error_domain(
    const uint8_t & _arg)
  {
    this->error_domain = _arg;
    return *this;
  }
  Type & set__operational_mode(
    const uint8_t & _arg)
  {
    this->operational_mode = _arg;
    return *this;
  }
  Type & set__power_state(
    const uint8_t & _arg)
  {
    this->power_state = _arg;
    return *this;
  }
  Type & set__connectivity_status(
    const uint8_t & _arg)
  {
    this->connectivity_status = _arg;
    return *this;
  }
  Type & set__manufacturer(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->manufacturer = _arg;
    return *this;
  }
  Type & set__model(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->model = _arg;
    return *this;
  }
  Type & set__firmware_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->firmware_version = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t HEALTH_UNKNOWN =
    0u;
  static constexpr uint8_t HEALTH_OK =
    1u;
  static constexpr uint8_t HEALTH_DEGRADED =
    2u;
  static constexpr uint8_t HEALTH_WARNING =
    3u;
  static constexpr uint8_t HEALTH_ERROR =
    4u;
  static constexpr uint8_t HEALTH_FATAL =
    5u;
  static constexpr uint8_t ERROR_NONE =
    0u;
  static constexpr uint8_t ERROR_UNKNOWN =
    1u;
  static constexpr uint8_t ERROR_HW =
    2u;
  static constexpr uint8_t ERROR_SW =
    3u;
  static constexpr uint8_t ERROR_OVER_TRAVEL =
    4u;
  static constexpr uint8_t EMERGENCY_STOP_HW =
    5u;
  static constexpr uint8_t EMERGENCY_STOP_SW =
    6u;
  static constexpr uint8_t PROTECTIVE_STOP_HW =
    7u;
  static constexpr uint8_t PROTECTIVE_STOP_SW =
    8u;
  static constexpr uint8_t SAFETY_STOP =
    9u;
  static constexpr uint8_t CALIBRATION_REQUIRED =
    10u;
  static constexpr uint8_t MODE_UNKNOWN =
    0u;
  static constexpr uint8_t MODE_MANUAL =
    1u;
  static constexpr uint8_t MODE_AUTO =
    2u;
  static constexpr uint8_t MODE_SAFE =
    3u;
  static constexpr uint8_t MODE_MAINTENANCE =
    4u;
  static constexpr uint8_t MODE_JOG_MANUAL =
    5u;
  static constexpr uint8_t MODE_ADMITTANCE =
    6u;
  static constexpr uint8_t MODE_MONITORED_STOP =
    7u;
  static constexpr uint8_t MODE_HOLD_TO_RUN =
    8u;
  static constexpr uint8_t MODE_CARTESIAN_TWIST =
    9u;
  static constexpr uint8_t MODE_CARTESIAN_POSE =
    10u;
  static constexpr uint8_t MODE_TRAJECTORY_FORWARDING =
    11u;
  static constexpr uint8_t MODE_TRAJECTORY_STREAMING =
    12u;
  static constexpr uint8_t POWER_UNKNOWN =
    0u;
  static constexpr uint8_t POWER_OFF =
    1u;
  static constexpr uint8_t POWER_STANDBY =
    2u;
  static constexpr uint8_t POWER_ON =
    3u;
  static constexpr uint8_t POWER_SLEEP =
    4u;
  static constexpr uint8_t POWER_ERROR =
    5u;
  static constexpr uint8_t POWER_LEVEL_LOW =
    6u;
  static constexpr uint8_t POWER_LEVEL_CRITICAL =
    7u;
  static constexpr uint8_t POWER_CHARGING =
    8u;
  static constexpr uint8_t POWER_CHARGING_ERROR =
    9u;
  static constexpr uint8_t CONNECT_UNKNOWN =
    0u;
  static constexpr uint8_t CONNECT_UP =
    1u;
  static constexpr uint8_t CONNECT_DOWN =
    2u;
  static constexpr uint8_t CONNECT_FAILURE =
    3u;
  static constexpr uint8_t CONNECTION_SLOW =
    4u;

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvDeviceState
    std::shared_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvDeviceState
    std::shared_ptr<teleop_robot_bridge::msg::AgvDeviceState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgvDeviceState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->health_status != other.health_status) {
      return false;
    }
    if (this->error_domain != other.error_domain) {
      return false;
    }
    if (this->operational_mode != other.operational_mode) {
      return false;
    }
    if (this->power_state != other.power_state) {
      return false;
    }
    if (this->connectivity_status != other.connectivity_status) {
      return false;
    }
    if (this->manufacturer != other.manufacturer) {
      return false;
    }
    if (this->model != other.model) {
      return false;
    }
    if (this->firmware_version != other.firmware_version) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgvDeviceState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgvDeviceState_

// alias to use template instance with default allocator
using AgvDeviceState =
  teleop_robot_bridge::msg::AgvDeviceState_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::HEALTH_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::HEALTH_OK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::HEALTH_DEGRADED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::HEALTH_WARNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::HEALTH_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::HEALTH_FATAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::ERROR_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::ERROR_HW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::ERROR_SW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::ERROR_OVER_TRAVEL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::EMERGENCY_STOP_HW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::EMERGENCY_STOP_SW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::PROTECTIVE_STOP_HW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::PROTECTIVE_STOP_SW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::SAFETY_STOP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::CALIBRATION_REQUIRED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_MANUAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_AUTO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_SAFE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_MAINTENANCE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_JOG_MANUAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_ADMITTANCE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_MONITORED_STOP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_HOLD_TO_RUN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_CARTESIAN_TWIST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_CARTESIAN_POSE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_TRAJECTORY_FORWARDING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::MODE_TRAJECTORY_STREAMING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_OFF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_STANDBY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_ON;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_SLEEP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_LEVEL_LOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_LEVEL_CRITICAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_CHARGING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::POWER_CHARGING_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::CONNECT_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::CONNECT_UP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::CONNECT_DOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::CONNECT_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgvDeviceState_<ContainerAllocator>::CONNECTION_SLOW;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__STRUCT_HPP_
