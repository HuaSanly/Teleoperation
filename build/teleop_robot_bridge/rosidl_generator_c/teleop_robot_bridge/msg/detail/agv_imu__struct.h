// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvImu.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_imu.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'imu'
#include "sensor_msgs/msg/detail/imu__struct.h"
// Member 'magnetic_field'
#include "sensor_msgs/msg/detail/magnetic_field__struct.h"

/// Struct defined in msg/AgvImu in the package teleop_robot_bridge.
/**
  * AGV IMU 消息
 */
typedef struct teleop_robot_bridge__msg__AgvImu
{
  /// IMU数据（使用标准 Imu 消息）
  sensor_msgs__msg__Imu imu;
  /// IMU磁场信息（使用标准 MagneticField 消息）
  sensor_msgs__msg__MagneticField magnetic_field;
} teleop_robot_bridge__msg__AgvImu;

// Struct for a sequence of teleop_robot_bridge__msg__AgvImu.
typedef struct teleop_robot_bridge__msg__AgvImu__Sequence
{
  teleop_robot_bridge__msg__AgvImu * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvImu__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_IMU__STRUCT_H_
