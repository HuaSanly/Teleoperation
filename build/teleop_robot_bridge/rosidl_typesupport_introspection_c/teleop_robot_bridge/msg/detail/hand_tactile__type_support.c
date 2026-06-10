// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/hand_tactile__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/hand_tactile__functions.h"
#include "teleop_robot_bridge/msg/detail/hand_tactile__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__HandTactile__init(message_memory);
}

void teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__HandTactile__fini(message_memory);
}

size_t teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__size_function__HandTactile__finger(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_const_function__HandTactile__finger(
  const void * untyped_member, size_t index)
{
  const int32_t * member =
    (const int32_t *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_function__HandTactile__finger(
  void * untyped_member, size_t index)
{
  int32_t * member =
    (int32_t *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__fetch_function__HandTactile__finger(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_const_function__HandTactile__finger(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__assign_function__HandTactile__finger(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_function__HandTactile__finger(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

size_t teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__size_function__HandTactile__thumb(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_const_function__HandTactile__thumb(
  const void * untyped_member, size_t index)
{
  const int32_t * member =
    (const int32_t *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_function__HandTactile__thumb(
  void * untyped_member, size_t index)
{
  int32_t * member =
    (int32_t *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__fetch_function__HandTactile__thumb(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_const_function__HandTactile__thumb(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__assign_function__HandTactile__thumb(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_function__HandTactile__thumb(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_member_array[2] = {
  {
    "finger",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__HandTactile, finger),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__size_function__HandTactile__finger,  // size() function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_const_function__HandTactile__finger,  // get_const(index) function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_function__HandTactile__finger,  // get(index) function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__fetch_function__HandTactile__finger,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__assign_function__HandTactile__finger,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "thumb",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__HandTactile, thumb),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__size_function__HandTactile__thumb,  // size() function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_const_function__HandTactile__thumb,  // get_const(index) function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__get_function__HandTactile__thumb,  // get(index) function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__fetch_function__HandTactile__thumb,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__assign_function__HandTactile__thumb,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "HandTactile",  // message name
  2,  // number of fields
  sizeof(teleop_robot_bridge__msg__HandTactile),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_member_array,  // message members
  teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__HandTactile__get_type_hash,
  &teleop_robot_bridge__msg__HandTactile__get_type_description,
  &teleop_robot_bridge__msg__HandTactile__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, HandTactile)() {
  if (!teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__HandTactile__rosidl_typesupport_introspection_c__HandTactile_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
