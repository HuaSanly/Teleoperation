// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/SingleGripperStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_gripper_status.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SingleGripperStatus in the package teleop_robot_bridge.
/**
  * 单个抓手状态消息
 */
typedef struct teleop_robot_bridge__msg__SingleGripperStatus
{
  /// 状态标志
  /// 是否就绪
  bool is_ready;
  /// 是否复位
  bool is_reset;
  /// 是否运动中
  bool is_moving;
  /// 是否检测到物体
  bool obj_detected;
  /// 故障状态码
  uint8_t fault_status;
  /// 位置信息
  /// 当前位置
  int32_t position;
  /// 目标位置
  int32_t requested_position;
  /// 电流信息
  /// 电流 (A)
  float current;
} teleop_robot_bridge__msg__SingleGripperStatus;

// Struct for a sequence of teleop_robot_bridge__msg__SingleGripperStatus.
typedef struct teleop_robot_bridge__msg__SingleGripperStatus__Sequence
{
  teleop_robot_bridge__msg__SingleGripperStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__SingleGripperStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_GRIPPER_STATUS__STRUCT_H_
