// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvVel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vel.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__STRUCT_H_

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
// Member 'linear'
// Member 'angular'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/AgvVel in the package teleop_robot_bridge.
/**
  * AGV速度消息
 */
typedef struct teleop_robot_bridge__msg__AgvVel
{
  std_msgs__msg__Header header;
  /// 线速度 (m/s)
  geometry_msgs__msg__Vector3 linear;
  /// 角速度 (rad/s)
  geometry_msgs__msg__Vector3 angular;
} teleop_robot_bridge__msg__AgvVel;

// Struct for a sequence of teleop_robot_bridge__msg__AgvVel.
typedef struct teleop_robot_bridge__msg__AgvVel__Sequence
{
  teleop_robot_bridge__msg__AgvVel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvVel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VEL__STRUCT_H_
