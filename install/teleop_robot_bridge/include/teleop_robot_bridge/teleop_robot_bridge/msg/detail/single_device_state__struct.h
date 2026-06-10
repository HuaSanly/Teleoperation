// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleop_robot_bridge:msg/SingleDeviceState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/single_device_state.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_DEVICE_STATE__STRUCT_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_DEVICE_STATE__STRUCT_H_

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
  * High-level health indicators
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__HEALTH_UNKNOWN = 0
};

/// Constant 'HEALTH_OK'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__HEALTH_OK = 1
};

/// Constant 'HEALTH_DEGRADED'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__HEALTH_DEGRADED = 2
};

/// Constant 'HEALTH_WARNING'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__HEALTH_WARNING = 3
};

/// Constant 'HEALTH_ERROR'.
/**
  * Hardware stops publishing state when it returns ERROR/FATAL, how are these set/updated?
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__HEALTH_ERROR = 4
};

/// Constant 'HEALTH_FATAL'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__HEALTH_FATAL = 5
};

/// Constant 'ERROR_NONE'.
/**
  * --- Error Domain Constants --------------------------------------
  * Error categories
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__ERROR_NONE = 0
};

/// Constant 'ERROR_UNKNOWN'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__ERROR_UNKNOWN = 1
};

/// Constant 'ERROR_HW'.
/**
  * generic hardware fault/error
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__ERROR_HW = 2
};

/// Constant 'ERROR_SW'.
/**
  * generic software fault/error
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__ERROR_SW = 3
};

/// Constant 'ERROR_OVER_TRAVEL'.
/**
  * Hardware stopped motion because position is over limits
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__ERROR_OVER_TRAVEL = 4
};

/// Constant 'EMERGENCY_STOP_HW'.
/**
  * Hardware/Software emergency and safety states
  * state of the emergency stop hardware (i.e. e-stop button state)
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__EMERGENCY_STOP_HW = 5
};

/// Constant 'EMERGENCY_STOP_SW'.
/**
  * state of the emergency stop software system (over travel, pinch point)
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__EMERGENCY_STOP_SW = 6
};

/// Constant 'PROTECTIVE_STOP_HW'.
/**
  * state of the protective stop hardware (i.e. safety field state)
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__PROTECTIVE_STOP_HW = 7
};

/// Constant 'PROTECTIVE_STOP_SW'.
/**
  * state of the software protective stop
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__PROTECTIVE_STOP_SW = 8
};

/// Constant 'SAFETY_STOP'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__SAFETY_STOP = 9
};

/// Constant 'CALIBRATION_REQUIRED'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__CALIBRATION_REQUIRED = 10
};

/// Constant 'MODE_UNKNOWN'.
/**
  * --- Operational Mode Constants ----------------------------------
  * Mode of operation
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_UNKNOWN = 0
};

/// Constant 'MODE_MANUAL'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_MANUAL = 1
};

/// Constant 'MODE_AUTO'.
/**
  * automatic mode when the driver is remote controlling the hardware
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_AUTO = 2
};

/// Constant 'MODE_SAFE'.
/**
  * what is the expected use case for this mode?
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_SAFE = 3
};

/// Constant 'MODE_MAINTENANCE'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_MAINTENANCE = 4
};

/// Constant 'MODE_JOG_MANUAL'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_JOG_MANUAL = 5
};

/// Constant 'MODE_ADMITTANCE'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_ADMITTANCE = 6
};

/// Constant 'MODE_MONITORED_STOP'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_MONITORED_STOP = 7
};

/// Constant 'MODE_HOLD_TO_RUN'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_HOLD_TO_RUN = 8
};

/// Constant 'MODE_CARTESIAN_TWIST'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_CARTESIAN_TWIST = 9
};

/// Constant 'MODE_CARTESIAN_POSE'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_CARTESIAN_POSE = 10
};

/// Constant 'MODE_TRAJECTORY_FORWARDING'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_TRAJECTORY_FORWARDING = 11
};

/// Constant 'MODE_TRAJECTORY_STREAMING'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__MODE_TRAJECTORY_STREAMING = 12
};

/// Constant 'POWER_UNKNOWN'.
/**
  * --- Power State Constants ---------------------------------------
  * Power states
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_UNKNOWN = 0
};

/// Constant 'POWER_OFF'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_OFF = 1
};

/// Constant 'POWER_STANDBY'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_STANDBY = 2
};

/// Constant 'POWER_ON'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_ON = 3
};

/// Constant 'POWER_SLEEP'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_SLEEP = 4
};

/// Constant 'POWER_ERROR'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_ERROR = 5
};

/// Constant 'POWER_LEVEL_LOW'.
/**
  * Battery power states see BatteryState.msg
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_LEVEL_LOW = 6
};

/// Constant 'POWER_LEVEL_CRITICAL'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_LEVEL_CRITICAL = 7
};

/// Constant 'POWER_CHARGING'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_CHARGING = 8
};

/// Constant 'POWER_CHARGING_ERROR'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__POWER_CHARGING_ERROR = 9
};

/// Constant 'CONNECT_UNKNOWN'.
/**
  * --- Connectivity Status Constants -------------------------------
  * Connectivity states
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__CONNECT_UNKNOWN = 0
};

/// Constant 'CONNECT_UP'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__CONNECT_UP = 1
};

/// Constant 'CONNECT_DOWN'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__CONNECT_DOWN = 2
};

/// Constant 'CONNECT_FAILURE'.
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__CONNECT_FAILURE = 3
};

/// Constant 'CONNECTION_SLOW'.
/**
  * to tell the controlling system it is struggling to communicate at rate
 */
enum
{
  teleop_robot_bridge__msg__SingleDeviceState__CONNECTION_SLOW = 4
};

// Include directives for member types
// Member 'error_domain'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'manufacturer'
// Member 'model'
// Member 'firmware_version'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SingleDeviceState in the package teleop_robot_bridge.
/**
  * 设备健康状态
 */
typedef struct teleop_robot_bridge__msg__SingleDeviceState
{
  uint8_t health_status;
  /// 错误域列表
  rosidl_runtime_c__uint8__Sequence error_domain;
  /// --- Operational State -------------------------------------------
  /// Current operational mode of the device, see ModeStatus constants below
  uint8_t operational_mode;
  /// Current power state of the device, see PowerState constants below
  uint8_t power_state;
  /// Current connectivity status of the device, see ConnectivityStatus constants below
  uint8_t connectivity_status;
  /// --- Vendor & Version Info ----------------------------------------
  /// Device manufacturer name, e.g. "Bosch"
  rosidl_runtime_c__String manufacturer;
  /// Device model identifier, e.g. "Lidar-XYZ-v2"
  rosidl_runtime_c__String model;
  /// Current firmware version, e.g. "1.2.3"
  rosidl_runtime_c__String firmware_version;
} teleop_robot_bridge__msg__SingleDeviceState;

// Struct for a sequence of teleop_robot_bridge__msg__SingleDeviceState.
typedef struct teleop_robot_bridge__msg__SingleDeviceState__Sequence
{
  teleop_robot_bridge__msg__SingleDeviceState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleop_robot_bridge__msg__SingleDeviceState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__SINGLE_DEVICE_STATE__STRUCT_H_
