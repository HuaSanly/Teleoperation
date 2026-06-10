// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/ArmJointCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/arm_joint_command.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_COMMAND__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_COMMAND__STRUCT_H_

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

/// Struct defined in msg/ArmJointCommand in the package teleop_robot_bridge.
/**
  * 机械臂14个电机命令消息
 */
typedef struct teleop_robot_bridge__msg__ArmJointCommand
{
  std_msgs__msg__Header header;
  /// 关节名称
  rosidl_runtime_c__String name[14];
  /// 位置
  double position[14];
  /// 速度
  double velocity[14];
  /// 力矩
  double effort[14];
} teleop_robot_bridge__msg__ArmJointCommand;

// Struct for a sequence of teleop_robot_bridge__msg__ArmJointCommand.
typedef struct teleop_robot_bridge__msg__ArmJointCommand__Sequence
{
  teleop_robot_bridge__msg__ArmJointCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__ArmJointCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__ARM_JOINT_COMMAND__STRUCT_H_
