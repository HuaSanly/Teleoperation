// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/WaistJointStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/waist_joint_status__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/waist_joint_status__functions.h"
#include "teleop_robot_bridge/msg/detail/waist_joint_status__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `joint_status`
#include "teleop_robot_bridge/msg/joint_status.h"
// Member `joint_status`
#include "teleop_robot_bridge/msg/detail/joint_status__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__WaistJointStatus__init(message_memory);
}

void teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__WaistJointStatus__fini(message_memory);
}

size_t teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__size_function__WaistJointStatus__name(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_const_function__WaistJointStatus__name(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String * member =
    (const rosidl_runtime_c__String *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_function__WaistJointStatus__name(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String * member =
    (rosidl_runtime_c__String *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__fetch_function__WaistJointStatus__name(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_const_function__WaistJointStatus__name(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__assign_function__WaistJointStatus__name(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_function__WaistJointStatus__name(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

size_t teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__size_function__WaistJointStatus__joint_status(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_const_function__WaistJointStatus__joint_status(
  const void * untyped_member, size_t index)
{
  const teleop_robot_bridge__msg__JointStatus * member =
    (const teleop_robot_bridge__msg__JointStatus *)(untyped_member);
  return &member[index];
}

void * teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_function__WaistJointStatus__joint_status(
  void * untyped_member, size_t index)
{
  teleop_robot_bridge__msg__JointStatus * member =
    (teleop_robot_bridge__msg__JointStatus *)(untyped_member);
  return &member[index];
}

void teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__fetch_function__WaistJointStatus__joint_status(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const teleop_robot_bridge__msg__JointStatus * item =
    ((const teleop_robot_bridge__msg__JointStatus *)
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_const_function__WaistJointStatus__joint_status(untyped_member, index));
  teleop_robot_bridge__msg__JointStatus * value =
    (teleop_robot_bridge__msg__JointStatus *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__assign_function__WaistJointStatus__joint_status(
  void * untyped_member, size_t index, const void * untyped_value)
{
  teleop_robot_bridge__msg__JointStatus * item =
    ((teleop_robot_bridge__msg__JointStatus *)
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_function__WaistJointStatus__joint_status(untyped_member, index));
  const teleop_robot_bridge__msg__JointStatus * value =
    (const teleop_robot_bridge__msg__JointStatus *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__WaistJointStatus, header),  // bytes offset in struct
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
    3,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__WaistJointStatus, name),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__size_function__WaistJointStatus__name,  // size() function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_const_function__WaistJointStatus__name,  // get_const(index) function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_function__WaistJointStatus__name,  // get(index) function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__fetch_function__WaistJointStatus__name,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__assign_function__WaistJointStatus__name,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "joint_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__WaistJointStatus, joint_status),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__size_function__WaistJointStatus__joint_status,  // size() function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_const_function__WaistJointStatus__joint_status,  // get_const(index) function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__get_function__WaistJointStatus__joint_status,  // get(index) function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__fetch_function__WaistJointStatus__joint_status,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__assign_function__WaistJointStatus__joint_status,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "WaistJointStatus",  // message name
  3,  // number of fields
  sizeof(teleop_robot_bridge__msg__WaistJointStatus),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_member_array,  // message members
  teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__WaistJointStatus__get_type_hash,
  &teleop_robot_bridge__msg__WaistJointStatus__get_type_description,
  &teleop_robot_bridge__msg__WaistJointStatus__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, WaistJointStatus)() {
  teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, JointStatus)();
  if (!teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__WaistJointStatus__rosidl_typesupport_introspection_c__WaistJointStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
