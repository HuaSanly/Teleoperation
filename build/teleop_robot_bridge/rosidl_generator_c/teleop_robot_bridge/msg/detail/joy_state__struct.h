// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/JoyState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joy_state.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'joy'
#include "sensor_msgs/msg/detail/joy__struct.h"

/// Struct defined in msg/JoyState in the package teleop_robot_bridge.
/**
  * 手柄状态消息
 */
typedef struct teleop_robot_bridge__msg__JoyState
{
  /// 手柄数据（使用标准 Joy 消息）
  sensor_msgs__msg__Joy joy;
} teleop_robot_bridge__msg__JoyState;

// Struct for a sequence of teleop_robot_bridge__msg__JoyState.
typedef struct teleop_robot_bridge__msg__JoyState__Sequence
{
  teleop_robot_bridge__msg__JoyState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__JoyState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOY_STATE__STRUCT_H_
