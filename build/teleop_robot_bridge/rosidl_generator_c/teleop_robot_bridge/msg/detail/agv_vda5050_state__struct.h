// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvVda5050State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_vda5050_state.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'ACTION_WAITING'.
/**
  * --- Action Status Constants ---------------------------------------
  *  action execution states
  * Action is waiting to be executed
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__ACTION_WAITING = "WAITING";

/// Constant 'ACTION_INITIALIZING'.
/**
  * Action is being initialized
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__ACTION_INITIALIZING = "INITIALIZING";

/// Constant 'ACTION_RUNNING'.
/**
  * Action is currently executing
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__ACTION_RUNNING = "RUNNING";

/// Constant 'ACTION_PAUSED'.
/**
  * Action execution is paused
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__ACTION_PAUSED = "PAUSED";

/// Constant 'ACTION_FINISHED'.
/**
  * Action completed successfully
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__ACTION_FINISHED = "FINISHED";

/// Constant 'ACTION_FAILED'.
/**
  * Action execution failed
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__ACTION_FAILED = "FAILED";

/// Constant 'MODE_AUTOMATIC'.
/**
  * --- Operating Mode Constants -------------------------------------
  *  vehicle operating modes
  * Vehicle operates autonomously
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__MODE_AUTOMATIC = "AUTOMATIC";

/// Constant 'MODE_SEMI_AUTOMATIC'.
/**
  * Vehicle requires operator confirmation
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__MODE_SEMI_AUTOMATIC = "SEMIAUTOMATIC";

/// Constant 'MODE_MANUAL'.
/**
  * Vehicle is under manual control
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__MODE_MANUAL = "MANUAL";

/// Constant 'MODE_SERVICE'.
/**
  * Vehicle is in service/maintenance mode
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__MODE_SERVICE = "SERVICE";

/// Constant 'MODE_EMERGENCY'.
/**
  * Vehicle is in emergency mode
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__MODE_EMERGENCY = "EMERGENCY";

/// Constant 'MODE_TEACHIN'.
/**
  * Vehicle is in teach-in mode for route learning
 */
static const char * const teleop_robot_bridge__msg__AgvVda5050State__MODE_TEACHIN = "TEACHIN";

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'order_id'
// Member 'action_status'
// Member 'operating_mode'
// Member 'error_type'
// Member 'error_description'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/AgvVda5050State in the package teleop_robot_bridge.
/**
  * AGV设备状态消息
 */
typedef struct teleop_robot_bridge__msg__AgvVda5050State
{
  std_msgs__msg__Header header;
  /// 命令ID
  rosidl_runtime_c__String order_id;
  /// 动作状态
  rosidl_runtime_c__String action_status;
  /// 最后节点ID
  int32_t last_node_id;
  /// 是否正在行驶
  bool driving;
  /// 电池电量 (%)
  float battery_charge;
  /// 操作模式
  rosidl_runtime_c__String operating_mode;
  /// 错误类型
  rosidl_runtime_c__String error_type;
  /// 错误描述
  rosidl_runtime_c__String error_description;
} teleop_robot_bridge__msg__AgvVda5050State;

// Struct for a sequence of teleop_robot_bridge__msg__AgvVda5050State.
typedef struct teleop_robot_bridge__msg__AgvVda5050State__Sequence
{
  teleop_robot_bridge__msg__AgvVda5050State * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvVda5050State__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_VDA5050_STATE__STRUCT_H_
