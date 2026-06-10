// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/HeadJointFeedback.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/head_joint_feedback__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/head_joint_feedback__functions.h"
#include "teleop_robot_bridge/msg/detail/head_joint_feedback__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__HeadJointFeedback__init(message_memory);
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__HeadJointFeedback__fini(message_memory);
}

size_t teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__name(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__name(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String * member =
    (const rosidl_runtime_c__String *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__name(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String * member =
    (rosidl_runtime_c__String *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__name(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__name(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__name(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__name(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

size_t teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__position(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__position(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__position(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__velocity(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__velocity(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__velocity(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__velocity(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__velocity(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__velocity(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__velocity(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__effort(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__effort(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__effort(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__effort(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__effort(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__effort(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__effort(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__HeadJointFeedback, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__HeadJointFeedback, name),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__name,  // size() function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__name,  // get_const(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__name,  // get(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__name,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__name,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__HeadJointFeedback, position),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__position,  // size() function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__position,  // get_const(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__position,  // get(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__position,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__position,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__HeadJointFeedback, velocity),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__velocity,  // size() function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__velocity,  // get_const(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__velocity,  // get(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__velocity,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__velocity,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "effort",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__HeadJointFeedback, effort),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__size_function__HeadJointFeedback__effort,  // size() function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_const_function__HeadJointFeedback__effort,  // get_const(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__get_function__HeadJointFeedback__effort,  // get(index) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__fetch_function__HeadJointFeedback__effort,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__assign_function__HeadJointFeedback__effort,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "HeadJointFeedback",  // message name
  5,  // number of fields
  sizeof(teleop_robot_bridge__msg__HeadJointFeedback),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_member_array,  // message members
  teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__HeadJointFeedback__get_type_hash,
  &teleop_robot_bridge__msg__HeadJointFeedback__get_type_description,
  &teleop_robot_bridge__msg__HeadJointFeedback__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, HeadJointFeedback)() {
  teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__HeadJointFeedback__rosidl_typesupport_introspection_c__HeadJointFeedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
