// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvBatteryState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_battery_state.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'battery_state'
#include "sensor_msgs/msg/detail/battery_state__struct.h"

/// Struct defined in msg/AgvBatteryState in the package teleop_robot_bridge.
/**
  * AGV电池状态消息
 */
typedef struct teleop_robot_bridge__msg__AgvBatteryState
{
  /// 电池状态（使用标准 BatteryState）
  sensor_msgs__msg__BatteryState battery_state;
} teleop_robot_bridge__msg__AgvBatteryState;

// Struct for a sequence of teleop_robot_bridge__msg__AgvBatteryState.
typedef struct teleop_robot_bridge__msg__AgvBatteryState__Sequence
{
  teleop_robot_bridge__msg__AgvBatteryState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvBatteryState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_BATTERY_STATE__STRUCT_H_
