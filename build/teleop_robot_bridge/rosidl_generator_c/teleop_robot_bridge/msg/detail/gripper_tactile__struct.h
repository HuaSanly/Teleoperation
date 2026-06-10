// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/GripperTactile.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_tactile.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__STRUCT_H_

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
// Member 'left'
// Member 'right'
#include "teleop_robot_bridge/msg/detail/hand_tactile__struct.h"

/// Struct defined in msg/GripperTactile in the package teleop_robot_bridge.
/**
  * 抓手触觉传感器消息（左右手）
 */
typedef struct teleop_robot_bridge__msg__GripperTactile
{
  std_msgs__msg__Header header;
  /// 左手触觉数据
  teleop_robot_bridge__msg__HandTactile left;
  /// 右手触觉数据
  teleop_robot_bridge__msg__HandTactile right;
} teleop_robot_bridge__msg__GripperTactile;

// Struct for a sequence of teleop_robot_bridge__msg__GripperTactile.
typedef struct teleop_robot_bridge__msg__GripperTactile__Sequence
{
  teleop_robot_bridge__msg__GripperTactile * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__GripperTactile__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_TACTILE__STRUCT_H_
