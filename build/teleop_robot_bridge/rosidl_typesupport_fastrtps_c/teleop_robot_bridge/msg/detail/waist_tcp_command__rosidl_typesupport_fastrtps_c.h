// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from teleop_robot_bridge:msg/WaistTcpCommand.idl
// generated code does not contain a copyright notice
#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "teleop_robot_bridge/msg/detail/waist_tcp_command__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_teleop_robot_bridge__msg__WaistTcpCommand(
  const teleop_robot_bridge__msg__WaistTcpCommand * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_deserialize_teleop_robot_bridge__msg__WaistTcpCommand(
  eprosima::fastcdr::Cdr &,
  teleop_robot_bridge__msg__WaistTcpCommand * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_teleop_robot_bridge__msg__WaistTcpCommand(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_teleop_robot_bridge__msg__WaistTcpCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_key_teleop_robot_bridge__msg__WaistTcpCommand(
  const teleop_robot_bridge__msg__WaistTcpCommand * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_key_teleop_robot_bridge__msg__WaistTcpCommand(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_key_teleop_robot_bridge__msg__WaistTcpCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, teleop_robot_bridge, msg, WaistTcpCommand)();

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_TCP_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
