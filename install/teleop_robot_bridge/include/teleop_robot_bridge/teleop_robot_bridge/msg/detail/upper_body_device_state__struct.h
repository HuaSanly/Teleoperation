// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/UpperBodyDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/upper_body_device_state.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__STRUCT_H_

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
// Member 'device_state'
#include "teleop_robot_bridge/msg/detail/single_device_state__struct.h"

/// Struct defined in msg/UpperBodyDeviceState in the package teleop_robot_bridge.
/**
  * 上半身设备状态消息
 */
typedef struct teleop_robot_bridge__msg__UpperBodyDeviceState
{
  std_msgs__msg__Header header;
  /// 单个设备状态
  teleop_robot_bridge__msg__SingleDeviceState device_state;
} teleop_robot_bridge__msg__UpperBodyDeviceState;

// Struct for a sequence of teleop_robot_bridge__msg__UpperBodyDeviceState.
typedef struct teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence
{
  teleop_robot_bridge__msg__UpperBodyDeviceState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__UpperBodyDeviceState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__UPPER_BODY_DEVICE_STATE__STRUCT_H_
