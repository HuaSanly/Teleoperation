// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/WaistJointCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_joint_command.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_COMMAND__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_COMMAND__STRUCT_H_

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

/// Struct defined in msg/WaistJointCommand in the package teleop_robot_bridge.
/**
  * 腰部3个电机命令消息
 */
typedef struct teleop_robot_bridge__msg__WaistJointCommand
{
  std_msgs__msg__Header header;
  /// 关节名称
  rosidl_runtime_c__String name[3];
  /// 位置
  double position[3];
  /// 速度
  double velocity[3];
  /// 力矩
  double effort[3];
} teleop_robot_bridge__msg__WaistJointCommand;

// Struct for a sequence of teleop_robot_bridge__msg__WaistJointCommand.
typedef struct teleop_robot_bridge__msg__WaistJointCommand__Sequence
{
  teleop_robot_bridge__msg__WaistJointCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__WaistJointCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_COMMAND__STRUCT_H_
