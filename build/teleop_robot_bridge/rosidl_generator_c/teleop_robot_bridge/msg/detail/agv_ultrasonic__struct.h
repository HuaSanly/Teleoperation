// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_ultrasonic.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'ranges'
#include "sensor_msgs/msg/detail/range__struct.h"

/// Struct defined in msg/AgvUltrasonic in the package teleop_robot_bridge.
/**
  * AGV 超声波传感器消息（多个传感器）
 */
typedef struct teleop_robot_bridge__msg__AgvUltrasonic
{
  /// 超声波传感器数据数组（8个传感器，固定长度）
  sensor_msgs__msg__Range ranges[8];
} teleop_robot_bridge__msg__AgvUltrasonic;

// Struct for a sequence of teleop_robot_bridge__msg__AgvUltrasonic.
typedef struct teleop_robot_bridge__msg__AgvUltrasonic__Sequence
{
  teleop_robot_bridge__msg__AgvUltrasonic * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvUltrasonic__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_ULTRASONIC__STRUCT_H_
