// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvMotionCtrl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_motion_ctrl.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_MOTION_CTRL__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_MOTION_CTRL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/AgvMotionCtrl in the package teleop_robot_bridge.
/**
  * 控制4个电机的使能/失能状态
  * 前4个元素依次对应左轮毂、右轮毂、左转向、右转向，第5个为全部使能/失能
 */
typedef struct teleop_robot_bridge__msg__AgvMotionCtrl
{
  bool enable_states[5];
} teleop_robot_bridge__msg__AgvMotionCtrl;

// Struct for a sequence of teleop_robot_bridge__msg__AgvMotionCtrl.
typedef struct teleop_robot_bridge__msg__AgvMotionCtrl__Sequence
{
  teleop_robot_bridge__msg__AgvMotionCtrl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvMotionCtrl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_MOTION_CTRL__STRUCT_H_
