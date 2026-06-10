// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/AgvMotionCtrl.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/agv_motion_ctrl__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/agv_motion_ctrl__functions.h"
#include "teleop_robot_bridge/msg/detail/agv_motion_ctrl__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__AgvMotionCtrl__init(message_memory);
}

void teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__AgvMotionCtrl__fini(message_memory);
}

size_t teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__size_function__AgvMotionCtrl__enable_states(
  const void * untyped_member)
{
  (void)untyped_member;
  return 5;
}

const void * teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__get_const_function__AgvMotionCtrl__enable_states(
  const void * untyped_member, size_t index)
{
  const bool * member =
    (const bool *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__get_function__AgvMotionCtrl__enable_states(
  void * untyped_member, size_t index)
{
  bool * member =
    (bool *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__fetch_function__AgvMotionCtrl__enable_states(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__get_const_function__AgvMotionCtrl__enable_states(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__assign_function__AgvMotionCtrl__enable_states(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__get_function__AgvMotionCtrl__enable_states(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_member_array[1] = {
  {
    "enable_states",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    5,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvMotionCtrl, enable_states),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__size_function__AgvMotionCtrl__enable_states,  // size() function pointer
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__get_const_function__AgvMotionCtrl__enable_states,  // get_const(index) function pointer
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__get_function__AgvMotionCtrl__enable_states,  // get(index) function pointer
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__fetch_function__AgvMotionCtrl__enable_states,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__assign_function__AgvMotionCtrl__enable_states,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "AgvMotionCtrl",  // message name
  1,  // number of fields
  sizeof(teleop_robot_bridge__msg__AgvMotionCtrl),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_member_array,  // message members
  teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__AgvMotionCtrl__get_type_hash,
  &teleop_robot_bridge__msg__AgvMotionCtrl__get_type_description,
  &teleop_robot_bridge__msg__AgvMotionCtrl__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, AgvMotionCtrl)() {
  if (!teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__AgvMotionCtrl__rosidl_typesupport_introspection_c__AgvMotionCtrl_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
