// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/Temperature.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/temperature.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__TEMPERATURE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__TEMPERATURE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'temperature'
#include "sensor_msgs/msg/detail/temperature__struct.h"

/// Struct defined in msg/Temperature in the package teleop_robot_bridge.
/**
  * 温度传感器消息
 */
typedef struct teleop_robot_bridge__msg__Temperature
{
  /// 温度数据（使用标准 Temperature 消息）
  sensor_msgs__msg__Temperature temperature;
} teleop_robot_bridge__msg__Temperature;

// Struct for a sequence of teleop_robot_bridge__msg__Temperature.
typedef struct teleop_robot_bridge__msg__Temperature__Sequence
{
  teleop_robot_bridge__msg__Temperature * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__Temperature__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__TEMPERATURE__STRUCT_H_
