// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/WaistMotionCtrl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_motion_ctrl.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/WaistMotionCtrl in the package teleop_robot_bridge.
/**
  * 控制3个电机的使能/失能状态
  * 每个元素对应一个电机（索引0~2），true表示使能，false表示失能,3为true表示全部使能,false表示全部失能
 */
typedef struct teleop_robot_bridge__msg__WaistMotionCtrl
{
  bool enable_states[4];
} teleop_robot_bridge__msg__WaistMotionCtrl;

// Struct for a sequence of teleop_robot_bridge__msg__WaistMotionCtrl.
typedef struct teleop_robot_bridge__msg__WaistMotionCtrl__Sequence
{
  teleop_robot_bridge__msg__WaistMotionCtrl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__WaistMotionCtrl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_MOTION_CTRL__STRUCT_H_
