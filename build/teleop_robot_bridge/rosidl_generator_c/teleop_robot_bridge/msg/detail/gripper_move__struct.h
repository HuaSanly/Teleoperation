// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/GripperMove.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_move.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_MOVE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_MOVE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'grippers'
#include "teleop_robot_bridge/msg/detail/single_gripper_move__struct.h"

/// Struct defined in msg/GripperMove in the package teleop_robot_bridge.
/**
  * 抓手移动命令消息（支持多个抓手）
 */
typedef struct teleop_robot_bridge__msg__GripperMove
{
  std_msgs__msg__Header header;
  /// 抓手命令数组
  teleop_robot_bridge__msg__SingleGripperMove__Sequence grippers;
} teleop_robot_bridge__msg__GripperMove;

// Struct for a sequence of teleop_robot_bridge__msg__GripperMove.
typedef struct teleop_robot_bridge__msg__GripperMove__Sequence
{
  teleop_robot_bridge__msg__GripperMove * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__GripperMove__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_MOVE__STRUCT_H_
