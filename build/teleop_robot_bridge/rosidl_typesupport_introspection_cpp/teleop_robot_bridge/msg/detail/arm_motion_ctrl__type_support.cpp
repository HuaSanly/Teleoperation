// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/ArmMotionCtrl.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/arm_motion_ctrl__functions.h"
#include "teleop_robot_bridge/msg/detail/arm_motion_ctrl__struct.hpp"
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

void ArmMotionCtrl_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::ArmMotionCtrl(_init);
}

void ArmMotionCtrl_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::ArmMotionCtrl *>(message_memory);
  typed_message->~ArmMotionCtrl();
}

size_t size_function__ArmMotionCtrl__enable_states(const void * untyped_member)
{
  (void)untyped_member;
  return 15;
}

const void * get_const_function__ArmMotionCtrl__enable_states(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<bool, 15> *>(untyped_member);
  return &member[index];
}

void * get_function__ArmMotionCtrl__enable_states(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<bool, 15> *>(untyped_member);
  return &member[index];
}

void fetch_function__ArmMotionCtrl__enable_states(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const bool *>(
    get_const_function__ArmMotionCtrl__enable_states(untyped_member, index));
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = item;
}

void assign_function__ArmMotionCtrl__enable_states(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<bool *>(
    get_function__ArmMotionCtrl__enable_states(untyped_member, index));
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ArmMotionCtrl_message_member_array[1] = {
  {
    "enable_states",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    15,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::ArmMotionCtrl, enable_states),  // bytes offset in struct
    nullptr,  // default value
    size_function__ArmMotionCtrl__enable_states,  // size() function pointer
    get_const_function__ArmMotionCtrl__enable_states,  // get_const(index) function pointer
    get_function__ArmMotionCtrl__enable_states,  // get(index) function pointer
    fetch_function__ArmMotionCtrl__enable_states,  // fetch(index, &value) function pointer
    assign_function__ArmMotionCtrl__enable_states,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ArmMotionCtrl_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "ArmMotionCtrl",  // message name
  1,  // number of fields
  sizeof(teleop_robot_bridge::msg::ArmMotionCtrl),
  false,  // has_any_key_member_
  ArmMotionCtrl_message_member_array,  // message members
  ArmMotionCtrl_init_function,  // function to initialize message memory (memory has to be allocated)
  ArmMotionCtrl_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ArmMotionCtrl_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ArmMotionCtrl_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__ArmMotionCtrl__get_type_hash,
  &teleop_robot_bridge__msg__ArmMotionCtrl__get_type_description,
  &teleop_robot_bridge__msg__ArmMotionCtrl__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::ArmMotionCtrl>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::ArmMotionCtrl_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, ArmMotionCtrl)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::ArmMotionCtrl_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
