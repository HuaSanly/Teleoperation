// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvJointFeedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_joint_feedback.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__STRUCT_H_

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
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/AgvJointFeedback in the package teleop_robot_bridge.
/**
  * 底盘4个电机反馈
 */
typedef struct teleop_robot_bridge__msg__AgvJointFeedback
{
  std_msgs__msg__Header header;
  /// 关节名称
  rosidl_runtime_c__String name[4];
  /// 位置
  double position[4];
  /// 速度
  double velocity[4];
  /// 力矩
  double effort[4];
} teleop_robot_bridge__msg__AgvJointFeedback;

// Struct for a sequence of teleop_robot_bridge__msg__AgvJointFeedback.
typedef struct teleop_robot_bridge__msg__AgvJointFeedback__Sequence
{
  teleop_robot_bridge__msg__AgvJointFeedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvJointFeedback__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_FEEDBACK__STRUCT_H_
