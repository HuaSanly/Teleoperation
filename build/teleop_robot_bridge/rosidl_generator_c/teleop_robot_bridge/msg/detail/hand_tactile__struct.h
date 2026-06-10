// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/hand_tactile.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/HandTactile in the package teleop_robot_bridge.
/**
  * 单只手的触觉传感器数据
 */
typedef struct teleop_robot_bridge__msg__HandTactile
{
  /// 手指触觉传感器数据（4个传感器）
  int32_t finger[4];
  /// 拇指触觉传感器数据（4个传感器）
  int32_t thumb[4];
} teleop_robot_bridge__msg__HandTactile;

// Struct for a sequence of teleop_robot_bridge__msg__HandTactile.
typedef struct teleop_robot_bridge__msg__HandTactile__Sequence
{
  teleop_robot_bridge__msg__HandTactile * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__HandTactile__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__HAND_TACTILE__STRUCT_H_
