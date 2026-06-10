// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/GripperMove.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/gripper_move__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/gripper_move__functions.h"
#include "teleop_robot_bridge/msg/detail/gripper_move__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `grippers`
#include "teleop_robot_bridge/msg/single_gripper_move.h"
// Member `grippers`
#include "teleop_robot_bridge/msg/detail/single_gripper_move__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__GripperMove__init(message_memory);
}

void teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__GripperMove__fini(message_memory);
}

size_t teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__size_function__GripperMove__grippers(
  const void * untyped_member)
{
  const teleop_robot_bridge__msg__SingleGripperMove__Sequence * member =
    (const teleop_robot_bridge__msg__SingleGripperMove__Sequence *)(untyped_member);
  return member->size;
}

const void * teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__get_const_function__GripperMove__grippers(
  const void * untyped_member, size_t index)
{
  const teleop_robot_bridge__msg__SingleGripperMove__Sequence * member =
    (const teleop_robot_bridge__msg__SingleGripperMove__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__get_function__GripperMove__grippers(
  void * untyped_member, size_t index)
{
  teleop_robot_bridge__msg__SingleGripperMove__Sequence * member =
    (teleop_robot_bridge__msg__SingleGripperMove__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__fetch_function__GripperMove__grippers(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const teleop_robot_bridge__msg__SingleGripperMove * item =
    ((const teleop_robot_bridge__msg__SingleGripperMove *)
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__get_const_function__GripperMove__grippers(untyped_member, index));
  teleop_robot_bridge__msg__SingleGripperMove * value =
    (teleop_robot_bridge__msg__SingleGripperMove *)(untyped_value);
  *value = *item;
}

void teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__assign_function__GripperMove__grippers(
  void * untyped_member, size_t index, const void * untyped_value)
{
  teleop_robot_bridge__msg__SingleGripperMove * item =
    ((teleop_robot_bridge__msg__SingleGripperMove *)
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__get_function__GripperMove__grippers(untyped_member, index));
  const teleop_robot_bridge__msg__SingleGripperMove * value =
    (const teleop_robot_bridge__msg__SingleGripperMove *)(untyped_value);
  *item = *value;
}

bool teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__resize_function__GripperMove__grippers(
  void * untyped_member, size_t size)
{
  teleop_robot_bridge__msg__SingleGripperMove__Sequence * member =
    (teleop_robot_bridge__msg__SingleGripperMove__Sequence *)(untyped_member);
  teleop_robot_bridge__msg__SingleGripperMove__Sequence__fini(member);
  return teleop_robot_bridge__msg__SingleGripperMove__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__GripperMove, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "grippers",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__GripperMove, grippers),  // bytes offset in struct
    NULL,  // default value
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__size_function__GripperMove__grippers,  // size() function pointer
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__get_const_function__GripperMove__grippers,  // get_const(index) function pointer
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__get_function__GripperMove__grippers,  // get(index) function pointer
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__fetch_function__GripperMove__grippers,  // fetch(index, &value) function pointer
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__assign_function__GripperMove__grippers,  // assign(index, value) function pointer
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__resize_function__GripperMove__grippers  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "GripperMove",  // message name
  2,  // number of fields
  sizeof(teleop_robot_bridge__msg__GripperMove),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_member_array,  // message members
  teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__GripperMove__get_type_hash,
  &teleop_robot_bridge__msg__GripperMove__get_type_description,
  &teleop_robot_bridge__msg__GripperMove__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, GripperMove)() {
  teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, SingleGripperMove)();
  if (!teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__GripperMove__rosidl_typesupport_introspection_c__GripperMove_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
