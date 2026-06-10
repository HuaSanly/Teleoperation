// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/JointStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/joint_status.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/JointStatus in the package teleop_robot_bridge.
/**
  * 单个执行器（电机+驱动器）状态
 */
typedef struct teleop_robot_bridge__msg__JointStatus
{
  /// 驱动器信息
  /// 驱动器电压 (V)
  float driver_voltage;
  /// 驱动器温度 (°C)
  float driver_temperature;
  /// 驱动器状态码
  uint8_t driver_state;
  /// 电机信息
  /// 电机温度 (°C)
  float motor_temperature;
  /// 转速 (转/分钟)
  int32_t rpm;
  /// 电流 (A)
  float current;
  /// 脉冲计数
  int64_t pulse_count;
  /// 电机角度
  int32_t motor_angles;
  /// 电机速度
  int32_t motor_speeds;
  /// 电机负载
  int32_t motor_loads;
} teleop_robot_bridge__msg__JointStatus;

// Struct for a sequence of teleop_robot_bridge__msg__JointStatus.
typedef struct teleop_robot_bridge__msg__JointStatus__Sequence
{
  teleop_robot_bridge__msg__JointStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__JointStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__JOINT_STATUS__STRUCT_H_
