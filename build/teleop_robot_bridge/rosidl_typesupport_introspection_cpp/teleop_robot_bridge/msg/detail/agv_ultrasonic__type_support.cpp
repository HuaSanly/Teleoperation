// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__functions.h"
#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace teleop_robot_bridge
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void AgvUltrasonic_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::AgvUltrasonic(_init);
}

void AgvUltrasonic_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::AgvUltrasonic *>(message_memory);
  typed_message->~AgvUltrasonic();
}

size_t size_function__AgvUltrasonic__ranges(const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * get_const_function__AgvUltrasonic__ranges(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<sensor_msgs::msg::Range, 8> *>(untyped_member);
  return &member[index];
}

void * get_function__AgvUltrasonic__ranges(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<sensor_msgs::msg::Range, 8> *>(untyped_member);
  return &member[index];
}

void fetch_function__AgvUltrasonic__ranges(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const sensor_msgs::msg::Range *>(
    get_const_function__AgvUltrasonic__ranges(untyped_member, index));
  auto & value = *reinterpret_cast<sensor_msgs::msg::Range *>(untyped_value);
  value = item;
}

void assign_function__AgvUltrasonic__ranges(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<sensor_msgs::msg::Range *>(
    get_function__AgvUltrasonic__ranges(untyped_member, index));
  const auto & value = *reinterpret_cast<const sensor_msgs::msg::Range *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AgvUltrasonic_message_member_array[1] = {
  {
    "ranges",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<sensor_msgs::msg::Range>(),  // members of sub message
    false,  // is key
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::AgvUltrasonic, ranges),  // bytes offset in struct
    nullptr,  // default value
    size_function__AgvUltrasonic__ranges,  // size() function pointer
    get_const_function__AgvUltrasonic__ranges,  // get_const(index) function pointer
    get_function__AgvUltrasonic__ranges,  // get(index) function pointer
    fetch_function__AgvUltrasonic__ranges,  // fetch(index, &value) function pointer
    assign_function__AgvUltrasonic__ranges,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AgvUltrasonic_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "AgvUltrasonic",  // message name
  1,  // number of fields
  sizeof(teleop_robot_bridge::msg::AgvUltrasonic),
  false,  // has_any_key_member_
  AgvUltrasonic_message_member_array,  // message members
  AgvUltrasonic_init_function,  // function to initialize message memory (memory has to be allocated)
  AgvUltrasonic_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AgvUltrasonic_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AgvUltrasonic_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__AgvUltrasonic__get_type_hash,
  &teleop_robot_bridge__msg__AgvUltrasonic__get_type_description,
  &teleop_robot_bridge__msg__AgvUltrasonic__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::AgvUltrasonic>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::AgvUltrasonic_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, AgvUltrasonic)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::AgvUltrasonic_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
