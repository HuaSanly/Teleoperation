// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleop_robot_bridge:msg/AgvBatteryState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleop_robot_bridge/msg/detail/agv_battery_state__rosidl_typesupport_introspection_c.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleop_robot_bridge/msg/detail/agv_battery_state__functions.h"
#include "teleop_robot_bridge/msg/detail/agv_battery_state__struct.h"


// Include directives for member types
// Member `battery_state`
#include "sensor_msgs/msg/battery_state.h"
// Member `battery_state`
#include "sensor_msgs/msg/detail/battery_state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleop_robot_bridge__msg__AgvBatteryState__init(message_memory);
}

void teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_fini_function(void * message_memory)
{
  teleop_robot_bridge__msg__AgvBatteryState__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_member_array[1] = {
  {
    "battery_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge__msg__AgvBatteryState, battery_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_members = {
  "teleop_robot_bridge__msg",  // message namespace
  "AgvBatteryState",  // message name
  1,  // number of fields
  sizeof(teleop_robot_bridge__msg__AgvBatteryState),
  false,  // has_any_key_member_
  teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_member_array,  // message members
  teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_init_function,  // function to initialize message memory (memory has to be allocated)
  teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_type_support_handle = {
  0,
  &teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__AgvBatteryState__get_type_hash,
  &teleop_robot_bridge__msg__AgvBatteryState__get_type_description,
  &teleop_robot_bridge__msg__AgvBatteryState__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleop_robot_bridge, msg, AgvBatteryState)() {
  teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, BatteryState)();
  if (!teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_type_support_handle.typesupport_identifier) {
    teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleop_robot_bridge__msg__AgvBatteryState__rosidl_typesupport_introspection_c__AgvBatteryState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
