// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/SingleDeviceState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/single_device_state__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/single_device_state__functions.h"
#include "teleop_robot_bridge/msg/detail/single_device_state__struct.h"


// Include directives for member types
// Member `error_domain`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `manufacturer`
// Member `model`
// Member `firmware_version`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__SingleDeviceState__init(message_memory);
}

void teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__SingleDeviceState__fini(message_memory);
}

size_t teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__size_function__SingleDeviceState__error_domain(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__get_const_function__SingleDeviceState__error_domain(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__get_function__SingleDeviceState__error_domain(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__fetch_function__SingleDeviceState__error_domain(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__get_const_function__SingleDeviceState__error_domain(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__assign_function__SingleDeviceState__error_domain(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__get_function__SingleDeviceState__error_domain(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__resize_function__SingleDeviceState__error_domain(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_member_array[8] = {
  {
    "health_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, health_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_domain",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, error_domain),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__size_function__SingleDeviceState__error_domain,  // size() function pointer
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__get_const_function__SingleDeviceState__error_domain,  // get_const(index) function pointer
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__get_function__SingleDeviceState__error_domain,  // get(index) function pointer
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__fetch_function__SingleDeviceState__error_domain,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__assign_function__SingleDeviceState__error_domain,  // assign(index, value) function pointer
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__resize_function__SingleDeviceState__error_domain  // resize(index) function pointer
  },
  {
    "operational_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, operational_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "power_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, power_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "connectivity_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, connectivity_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "manufacturer",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, manufacturer),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "model",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, model),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "firmware_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__SingleDeviceState, firmware_version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "SingleDeviceState",  // message name
  8,  // number of fields
  sizeof(teleop_robot_bridge__msg__SingleDeviceState),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_member_array,  // message members
  teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__SingleDeviceState__get_type_hash,
  &teleop_robot_bridge__msg__SingleDeviceState__get_type_description,
  &teleop_robot_bridge__msg__SingleDeviceState__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, SingleDeviceState)() {
  if (!teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__SingleDeviceState__rosidl_typesupport_introspection_c__SingleDeviceState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
