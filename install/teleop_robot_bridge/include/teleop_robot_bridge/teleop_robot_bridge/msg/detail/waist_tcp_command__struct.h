// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/WaistTcpCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_tcp_command.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__STRUCT_H_

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

/// Struct defined in msg/WaistTcpCommand in the package teleop_robot_bridge.
/**
  * 腰部 TCP 位姿命令消息
 */
typedef struct teleop_robot_bridge__msg__WaistTcpCommand
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String name[1];
  double position[3];
  /// 欧拉角顺序为[roll, pitch, yaw]
  double euler[3];
  /// 四元数顺序为[x, y, z, w]
  double quat[4];
} teleop_robot_bridge__msg__WaistTcpCommand;

// Struct for a sequence of teleop_robot_bridge__msg__WaistTcpCommand.
typedef struct teleop_robot_bridge__msg__WaistTcpCommand__Sequence
{
  teleop_robot_bridge__msg__WaistTcpCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__WaistTcpCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__STRUCT_H_
