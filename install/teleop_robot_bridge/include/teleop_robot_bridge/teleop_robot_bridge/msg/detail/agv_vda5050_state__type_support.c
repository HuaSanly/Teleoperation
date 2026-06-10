// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/AgvVda5050State.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/agv_vda5050_state__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/agv_vda5050_state__functions.h"
#include "teleop_robot_bridge/msg/detail/agv_vda5050_state__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `order_id`
// Member `action_status`
// Member `operating_mode`
// Member `error_type`
// Member `error_description`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__AgvVda5050State__init(message_memory);
}

void teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__AgvVda5050State__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_member_array[9] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "order_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, order_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "action_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, action_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "last_node_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, last_node_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "driving",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, driving),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_charge",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, battery_charge),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "operating_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, operating_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, error_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_description",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvVda5050State, error_description),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "AgvVda5050State",  // message name
  9,  // number of fields
  sizeof(teleop_robot_bridge__msg__AgvVda5050State),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_member_array,  // message members
  teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__AgvVda5050State__get_type_hash,
  &teleop_robot_bridge__msg__AgvVda5050State__get_type_description,
  &teleop_robot_bridge__msg__AgvVda5050State__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, AgvVda5050State)() {
  teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__AgvVda5050State__rosidl_typesupport_introspection_c__AgvVda5050State_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
