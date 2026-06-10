// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/SingleGripperMove.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_gripper_move.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SingleGripperMove in the package teleop_robot_bridge.
/**
  * 单个抓手移动命令
 */
typedef struct teleop_robot_bridge__msg__SingleGripperMove
{
  /// 紧急释放标志
  bool emergency_release;
  /// 紧急释放方向
  uint8_t emergency_release_dir;
  /// 停止标志
  bool stop;
  /// 目标位置
  int32_t position;
  /// 速度
  int32_t speed;
  /// 力度
  int32_t force;
} teleop_robot_bridge__msg__SingleGripperMove;

// Struct for a sequence of teleop_robot_bridge__msg__SingleGripperMove.
typedef struct teleop_robot_bridge__msg__SingleGripperMove__Sequence
{
  teleop_robot_bridge__msg__SingleGripperMove * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__SingleGripperMove__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_MOVE__STRUCT_H_
