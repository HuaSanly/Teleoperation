// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/EeTcpCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/ee_tcp_command.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__EE_TCP_COMMAND__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__EE_TCP_COMMAND__STRUCT_H_

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

/// Struct defined in msg/EeTcpCommand in the package teleop_robot_bridge.
/**
  * 双末端 TCP 位姿命令消息
 */
typedef struct teleop_robot_bridge__msg__EeTcpCommand
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String name[2];
  /// 前3个为name[0]的xyz，后3个为name[1]的xyz
  double position[6];
  /// 前3个为name[0]的欧拉角[roll, pitch, yaw]，后3个为name[1]的欧拉角[roll, pitch, yaw]
  double euler[6];
  /// 前4个为name[0]的四元数[x, y, z, w]，后4个为name[1]的四元数[x, y, z, w]
  double quat[8];
} teleop_robot_bridge__msg__EeTcpCommand;

// Struct for a sequence of teleop_robot_bridge__msg__EeTcpCommand.
typedef struct teleop_robot_bridge__msg__EeTcpCommand__Sequence
{
  teleop_robot_bridge__msg__EeTcpCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__EeTcpCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__EE_TCP_COMMAND__STRUCT_H_
