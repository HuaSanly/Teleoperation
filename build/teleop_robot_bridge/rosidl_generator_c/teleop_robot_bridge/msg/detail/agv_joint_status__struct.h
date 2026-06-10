// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvJointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_joint_status.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_STATUS__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_STATUS__STRUCT_H_

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
// Member 'joint_status'
#include "teleop_robot_bridge/msg/detail/joint_status__struct.h"

/// Struct defined in msg/AgvJointStatus in the package teleop_robot_bridge.
/**
  * AGV关节状态消息（4个执行器）
 */
typedef struct teleop_robot_bridge__msg__AgvJointStatus
{
  std_msgs__msg__Header header;
  /// 关节名称
  rosidl_runtime_c__String name[4];
  /// 4个关节的状态数组
  teleop_robot_bridge__msg__JointStatus joint_status[4];
} teleop_robot_bridge__msg__AgvJointStatus;

// Struct for a sequence of teleop_robot_bridge__msg__AgvJointStatus.
typedef struct teleop_robot_bridge__msg__AgvJointStatus__Sequence
{
  teleop_robot_bridge__msg__AgvJointStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvJointStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_JOINT_STATUS__STRUCT_H_
