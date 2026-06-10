// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/GripperStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/gripper_status.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_

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
#include "teleop_robot_bridge/msg/detail/single_gripper_status__struct.h"

/// Struct defined in msg/GripperStatus in the package teleop_robot_bridge.
/**
  * 抓手状态消息
 */
typedef struct teleop_robot_bridge__msg__GripperStatus
{
  std_msgs__msg__Header header;
  /// 抓手状态数组（2个）
  teleop_robot_bridge__msg__SingleGripperStatus grippers[2];
} teleop_robot_bridge__msg__GripperStatus;

// Struct for a sequence of teleop_robot_bridge__msg__GripperStatus.
typedef struct teleop_robot_bridge__msg__GripperStatus__Sequence
{
  teleop_robot_bridge__msg__GripperStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__GripperStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_
