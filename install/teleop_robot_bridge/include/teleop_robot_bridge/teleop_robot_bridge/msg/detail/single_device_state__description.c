// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/SingleDeviceState.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/single_device_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__SingleDeviceState__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa6, 0x16, 0xe3, 0x3f, 0x40, 0x08, 0xd1, 0x1a,
      0xf4, 0xbe, 0x1d, 0xc0, 0x14, 0x9b, 0xc2, 0x44,
      0x53, 0xb8, 0x68, 0xf1, 0xec, 0x3f, 0xf1, 0x89,
      0xea, 0x1a, 0xa1, 0x05, 0xe4, 0x2f, 0x4d, 0x4c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char teleop_robot_bridge__msg__SingleDeviceState__TYPE_NAME[] = "teleop_robot_bridge/msg/SingleDeviceState";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__health_status[] = "health_status";
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__error_domain[] = "error_domain";
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__operational_mode[] = "operational_mode";
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__power_state[] = "power_state";
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__connectivity_status[] = "connectivity_status";
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__manufacturer[] = "manufacturer";
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__model[] = "model";
static char teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__firmware_version[] = "firmware_version";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__SingleDeviceState__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__health_status, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__error_domain, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__operational_mode, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__power_state, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__connectivity_status, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__manufacturer, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__model, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__FIELD_NAME__firmware_version, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__SingleDeviceState__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__SingleDeviceState__TYPE_NAME, 41, 41},
      {teleop_robot_bridge__msg__SingleDeviceState__FIELDS, 8, 8},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe8\\xae\\xbe\\xe5\\xa4\\x87\\xe5\\x81\\xa5\\xe5\\xba\\xb7\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "uint8 health_status\n"
  "\n"
  "# \\xe9\\x94\\x99\\xe8\\xaf\\xaf\\xe5\\x9f\\x9f\\xe5\\x88\\x97\\xe8\\xa1\\xa8\n"
  "uint8[] error_domain\n"
  "\n"
  "# --- Operational State -------------------------------------------\n"
  "# Current operational mode of the device, see ModeStatus constants below\n"
  "uint8 operational_mode\n"
  "\n"
  "# Current power state of the device, see PowerState constants below\n"
  "uint8 power_state\n"
  "\n"
  "# Current connectivity status of the device, see ConnectivityStatus constants below\n"
  "uint8 connectivity_status\n"
  "\n"
  "# --- Vendor & Version Info ----------------------------------------\n"
  "# Device manufacturer name, e.g. \"Bosch\"\n"
  "string manufacturer\n"
  "\n"
  "# Device model identifier, e.g. \"Lidar-XYZ-v2\"\n"
  "string model\n"
  "\n"
  "# Current firmware version, e.g. \"1.2.3\"\n"
  "string firmware_version\n"
  "\n"
  "# --- Health Status Constants -------------------------------------\n"
  "# High-level health indicators\n"
  "uint8 HEALTH_UNKNOWN  = 0\n"
  "uint8 HEALTH_OK       = 1\n"
  "uint8 HEALTH_DEGRADED = 2\n"
  "uint8 HEALTH_WARNING  = 3\n"
  "# Hardware stops publishing state when it returns ERROR/FATAL, how are these set/updated?\n"
  "uint8 HEALTH_ERROR    = 4\n"
  "uint8 HEALTH_FATAL    = 5\n"
  "\n"
  "# --- Error Domain Constants --------------------------------------\n"
  "# Error categories\n"
  "uint8 ERROR_NONE           = 0\n"
  "uint8 ERROR_UNKNOWN        = 1\n"
  "uint8 ERROR_HW             = 2  # generic hardware fault/error\n"
  "uint8 ERROR_SW             = 3  # generic software fault/error\n"
  "uint8 ERROR_OVER_TRAVEL    = 4  # Hardware stopped motion because position is over limits\n"
  "\n"
  "# Hardware/Software emergency and safety states\n"
  "uint8 EMERGENCY_STOP_HW    = 5  # state of the emergency stop hardware (i.e. e-stop button state)\n"
  "uint8 EMERGENCY_STOP_SW    = 6  # state of the emergency stop software system (over travel, pinch point)\n"
  "uint8 PROTECTIVE_STOP_HW   = 7  # state of the protective stop hardware (i.e. safety field state)\n"
  "uint8 PROTECTIVE_STOP_SW   = 8  # state of the software protective stop\n"
  "uint8 SAFETY_STOP          = 9\n"
  "uint8 CALIBRATION_REQUIRED = 10\n"
  "\n"
  "# --- Operational Mode Constants ----------------------------------\n"
  "# Mode of operation\n"
  "uint8 MODE_UNKNOWN              = 0\n"
  "uint8 MODE_MANUAL               = 1\n"
  "uint8 MODE_AUTO                 = 2  # automatic mode when the driver is remote controlling the hardware\n"
  "uint8 MODE_SAFE                 = 3  # what is the expected use case for this mode?\n"
  "uint8 MODE_MAINTENANCE          = 4\n"
  "uint8 MODE_JOG_MANUAL           = 5\n"
  "uint8 MODE_ADMITTANCE           = 6\n"
  "uint8 MODE_MONITORED_STOP       = 7\n"
  "uint8 MODE_HOLD_TO_RUN          = 8\n"
  "uint8 MODE_CARTESIAN_TWIST      = 9\n"
  "uint8 MODE_CARTESIAN_POSE       = 10\n"
  "uint8 MODE_TRAJECTORY_FORWARDING = 11\n"
  "uint8 MODE_TRAJECTORY_STREAMING  = 12\n"
  "\n"
  "# --- Power State Constants ---------------------------------------\n"
  "# Power states\n"
  "uint8 POWER_UNKNOWN         = 0\n"
  "uint8 POWER_OFF             = 1\n"
  "uint8 POWER_STANDBY         = 2\n"
  "uint8 POWER_ON              = 3\n"
  "uint8 POWER_SLEEP           = 4\n"
  "uint8 POWER_ERROR           = 5\n"
  "# Battery power states see BatteryState.msg\n"
  "uint8 POWER_LEVEL_LOW       = 6\n"
  "uint8 POWER_LEVEL_CRITICAL  = 7\n"
  "uint8 POWER_CHARGING        = 8\n"
  "uint8 POWER_CHARGING_ERROR  = 9\n"
  "\n"
  "# --- Connectivity Status Constants -------------------------------\n"
  "# Connectivity states\n"
  "uint8 CONNECT_UNKNOWN    = 0\n"
  "uint8 CONNECT_UP         = 1\n"
  "uint8 CONNECT_DOWN       = 2\n"
  "uint8 CONNECT_FAILURE    = 3\n"
  "uint8 CONNECTION_SLOW    = 4  # to tell the controlling system it is struggling to communicate at rate";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__SingleDeviceState__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__SingleDeviceState__TYPE_NAME, 41, 41},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 3314, 3314},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__SingleDeviceState__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__SingleDeviceState__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
