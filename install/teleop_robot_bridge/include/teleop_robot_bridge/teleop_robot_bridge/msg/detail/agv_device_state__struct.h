// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/AgvDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/agv_device_state.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'HEALTH_UNKNOWN'.
/**
  * --- Health Status Constants -------------------------------------
 */
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__HEALTH_UNKNOWN = 0
};

/// Constant 'HEALTH_OK'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__HEALTH_OK = 1
};

/// Constant 'HEALTH_DEGRADED'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__HEALTH_DEGRADED = 2
};

/// Constant 'HEALTH_WARNING'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__HEALTH_WARNING = 3
};

/// Constant 'HEALTH_ERROR'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__HEALTH_ERROR = 4
};

/// Constant 'HEALTH_FATAL'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__HEALTH_FATAL = 5
};

/// Constant 'ERROR_NONE'.
/**
  * --- Error Domain Constants --------------------------------------
 */
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__ERROR_NONE = 0
};

/// Constant 'ERROR_UNKNOWN'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__ERROR_UNKNOWN = 1
};

/// Constant 'ERROR_HW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__ERROR_HW = 2
};

/// Constant 'ERROR_SW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__ERROR_SW = 3
};

/// Constant 'ERROR_OVER_TRAVEL'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__ERROR_OVER_TRAVEL = 4
};

/// Constant 'EMERGENCY_STOP_HW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__EMERGENCY_STOP_HW = 5
};

/// Constant 'EMERGENCY_STOP_SW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__EMERGENCY_STOP_SW = 6
};

/// Constant 'PROTECTIVE_STOP_HW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__PROTECTIVE_STOP_HW = 7
};

/// Constant 'PROTECTIVE_STOP_SW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__PROTECTIVE_STOP_SW = 8
};

/// Constant 'SAFETY_STOP'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__SAFETY_STOP = 9
};

/// Constant 'CALIBRATION_REQUIRED'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__CALIBRATION_REQUIRED = 10
};

/// Constant 'MODE_UNKNOWN'.
/**
  * --- Operational Mode Constants ----------------------------------
 */
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_UNKNOWN = 0
};

/// Constant 'MODE_MANUAL'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_MANUAL = 1
};

/// Constant 'MODE_AUTO'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_AUTO = 2
};

/// Constant 'MODE_SAFE'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_SAFE = 3
};

/// Constant 'MODE_MAINTENANCE'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_MAINTENANCE = 4
};

/// Constant 'MODE_JOG_MANUAL'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_JOG_MANUAL = 5
};

/// Constant 'MODE_ADMITTANCE'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_ADMITTANCE = 6
};

/// Constant 'MODE_MONITORED_STOP'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_MONITORED_STOP = 7
};

/// Constant 'MODE_HOLD_TO_RUN'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_HOLD_TO_RUN = 8
};

/// Constant 'MODE_CARTESIAN_TWIST'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_CARTESIAN_TWIST = 9
};

/// Constant 'MODE_CARTESIAN_POSE'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_CARTESIAN_POSE = 10
};

/// Constant 'MODE_TRAJECTORY_FORWARDING'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_TRAJECTORY_FORWARDING = 11
};

/// Constant 'MODE_TRAJECTORY_STREAMING'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__MODE_TRAJECTORY_STREAMING = 12
};

/// Constant 'POWER_UNKNOWN'.
/**
  * --- Power State Constants ---------------------------------------
 */
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_UNKNOWN = 0
};

/// Constant 'POWER_OFF'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_OFF = 1
};

/// Constant 'POWER_STANDBY'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_STANDBY = 2
};

/// Constant 'POWER_ON'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_ON = 3
};

/// Constant 'POWER_SLEEP'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_SLEEP = 4
};

/// Constant 'POWER_ERROR'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_ERROR = 5
};

/// Constant 'POWER_LEVEL_LOW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_LEVEL_LOW = 6
};

/// Constant 'POWER_LEVEL_CRITICAL'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_LEVEL_CRITICAL = 7
};

/// Constant 'POWER_CHARGING'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_CHARGING = 8
};

/// Constant 'POWER_CHARGING_ERROR'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__POWER_CHARGING_ERROR = 9
};

/// Constant 'CONNECT_UNKNOWN'.
/**
  * --- Connectivity Status Constants -------------------------------
 */
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__CONNECT_UNKNOWN = 0
};

/// Constant 'CONNECT_UP'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__CONNECT_UP = 1
};

/// Constant 'CONNECT_DOWN'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__CONNECT_DOWN = 2
};

/// Constant 'CONNECT_FAILURE'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__CONNECT_FAILURE = 3
};

/// Constant 'CONNECTION_SLOW'.
enum
{
  teleop_robot_bridge__msg__AgvDeviceState__CONNECTION_SLOW = 4
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'manufacturer'
// Member 'model'
// Member 'firmware_version'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/AgvDeviceState in the package teleop_robot_bridge.
/**
  * AGV设备状态消息（通用硬件状态）
 */
typedef struct teleop_robot_bridge__msg__AgvDeviceState
{
  std_msgs__msg__Header header;
  /// 设备健康状态
  uint8_t health_status;
  /// 错误域（单个错误代码）
  uint8_t error_domain;
  /// 操作模式
  uint8_t operational_mode;
  /// 电源状态
  uint8_t power_state;
  /// 连接状态
  uint8_t connectivity_status;
  /// 制造商名称
  rosidl_runtime_c__String manufacturer;
  /// 设备型号
  rosidl_runtime_c__String model;
  /// 固件版本
  rosidl_runtime_c__String firmware_version;
} teleop_robot_bridge__msg__AgvDeviceState;

// Struct for a sequence of teleop_robot_bridge__msg__AgvDeviceState.
typedef struct teleop_robot_bridge__msg__AgvDeviceState__Sequence
{
  teleop_robot_bridge__msg__AgvDeviceState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__AgvDeviceState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__AGV_DEVICE_STATE__STRUCT_H_
