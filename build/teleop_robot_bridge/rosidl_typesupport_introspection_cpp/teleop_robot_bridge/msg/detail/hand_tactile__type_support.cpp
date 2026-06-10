// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/hand_tactile__functions.h"
#include "teleop_robot_bridge/msg/detail/hand_tactile__struct.hpp"
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

void HandTactile_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::HandTactile(_init);
}

void HandTactile_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::HandTactile *>(message_memory);
  typed_message->~HandTactile();
}

size_t size_function__HandTactile__finger(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__HandTactile__finger(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int32_t, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTactile__finger(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int32_t, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTactile__finger(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__HandTactile__finger(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__HandTactile__finger(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__HandTactile__finger(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

size_t size_function__HandTactile__thumb(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__HandTactile__thumb(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int32_t, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTactile__thumb(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int32_t, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTactile__thumb(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__HandTactile__thumb(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__HandTactile__thumb(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__HandTactile__thumb(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember HandTactile_message_member_array[2] = {
  {
    "finger",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::HandTactile, finger),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTactile__finger,  // size() function pointer
    get_const_function__HandTactile__finger,  // get_const(index) function pointer
    get_function__HandTactile__finger,  // get(index) function pointer
    fetch_function__HandTactile__finger,  // fetch(index, &value) function pointer
    assign_function__HandTactile__finger,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "thumb",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::HandTactile, thumb),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTactile__thumb,  // size() function pointer
    get_const_function__HandTactile__thumb,  // get_const(index) function pointer
    get_function__HandTactile__thumb,  // get(index) function pointer
    fetch_function__HandTactile__thumb,  // fetch(index, &value) function pointer
    assign_function__HandTactile__thumb,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers HandTactile_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "HandTactile",  // message name
  2,  // number of fields
  sizeof(teleop_robot_bridge::msg::HandTactile),
  false,  // has_any_key_member_
  HandTactile_message_member_array,  // message members
  HandTactile_init_function,  // function to initialize message memory (memory has to be allocated)
  HandTactile_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t HandTactile_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &HandTactile_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__HandTactile__get_type_hash,
  &teleop_robot_bridge__msg__HandTactile__get_type_description,
  &teleop_robot_bridge__msg__HandTactile__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::HandTactile>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::HandTactile_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, HandTactile)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::HandTactile_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
