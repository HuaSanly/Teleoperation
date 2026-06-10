// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleop_robot_bridge:msg/AgvVda5050State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vda5050_state.hpp"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__STRUCT_HPP_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__STRUCT_HPP_

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
# define DEPRECATED__teleop_robot_bridge__msg__AgvVda5050State __attribute__((deprecated))
#else
# define DEPRECATED__teleop_robot_bridge__msg__AgvVda5050State __declspec(deprecated)
#endif

namespace teleop_robot_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgvVda5050State_
{
  using Type = AgvVda5050State_<ContainerAllocator>;

  explicit AgvVda5050State_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->order_id = "";
      this->action_status = "";
      this->last_node_id = 0l;
      this->driving = false;
      this->battery_charge = 0.0f;
      this->operating_mode = "";
      this->error_type = "";
      this->error_description = "";
    }
  }

  explicit AgvVda5050State_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    order_id(_alloc),
    action_status(_alloc),
    operating_mode(_alloc),
    error_type(_alloc),
    error_description(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->order_id = "";
      this->action_status = "";
      this->last_node_id = 0l;
      this->driving = false;
      this->battery_charge = 0.0f;
      this->operating_mode = "";
      this->error_type = "";
      this->error_description = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _order_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _order_id_type order_id;
  using _action_status_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _action_status_type action_status;
  using _last_node_id_type =
    int32_t;
  _last_node_id_type last_node_id;
  using _driving_type =
    bool;
  _driving_type driving;
  using _battery_charge_type =
    float;
  _battery_charge_type battery_charge;
  using _operating_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _operating_mode_type operating_mode;
  using _error_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _error_type_type error_type;
  using _error_description_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _error_description_type error_description;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__order_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->order_id = _arg;
    return *this;
  }
  Type & set__action_status(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->action_status = _arg;
    return *this;
  }
  Type & set__last_node_id(
    const int32_t & _arg)
  {
    this->last_node_id = _arg;
    return *this;
  }
  Type & set__driving(
    const bool & _arg)
  {
    this->driving = _arg;
    return *this;
  }
  Type & set__battery_charge(
    const float & _arg)
  {
    this->battery_charge = _arg;
    return *this;
  }
  Type & set__operating_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->operating_mode = _arg;
    return *this;
  }
  Type & set__error_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->error_type = _arg;
    return *this;
  }
  Type & set__error_description(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->error_description = _arg;
    return *this;
  }

  // constant declarations
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> ACTION_WAITING;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> ACTION_INITIALIZING;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> ACTION_RUNNING;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> ACTION_PAUSED;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> ACTION_FINISHED;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> ACTION_FAILED;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> MODE_AUTOMATIC;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> MODE_SEMI_AUTOMATIC;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> MODE_MANUAL;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> MODE_SERVICE;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> MODE_EMERGENCY;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> MODE_TEACHIN;

  // pointer types
  using RawPtr =
    teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvVda5050State
    std::shared_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleop_robot_bridge__msg__AgvVda5050State
    std::shared_ptr<teleop_robot_bridge::msg::AgvVda5050State_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgvVda5050State_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->order_id != other.order_id) {
      return false;
    }
    if (this->action_status != other.action_status) {
      return false;
    }
    if (this->last_node_id != other.last_node_id) {
      return false;
    }
    if (this->driving != other.driving) {
      return false;
    }
    if (this->battery_charge != other.battery_charge) {
      return false;
    }
    if (this->operating_mode != other.operating_mode) {
      return false;
    }
    if (this->error_type != other.error_type) {
      return false;
    }
    if (this->error_description != other.error_description) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgvVda5050State_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgvVda5050State_

// alias to use template instance with default allocator
using AgvVda5050State =
  teleop_robot_bridge::msg::AgvVda5050State_<std::allocator<void>>;

// constant definitions
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::ACTION_WAITING = "WAITING";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::ACTION_INITIALIZING = "INITIALIZING";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::ACTION_RUNNING = "RUNNING";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::ACTION_PAUSED = "PAUSED";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::ACTION_FINISHED = "FINISHED";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::ACTION_FAILED = "FAILED";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::MODE_AUTOMATIC = "AUTOMATIC";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::MODE_SEMI_AUTOMATIC = "SEMIAUTOMATIC";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::MODE_MANUAL = "MANUAL";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::MODE_SERVICE = "SERVICE";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::MODE_EMERGENCY = "EMERGENCY";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
AgvVda5050State_<ContainerAllocator>::MODE_TEACHIN = "TEACHIN";

}  // namespace msg

}  // namespace teleop_robot_bridge

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__STRUCT_HPP_
