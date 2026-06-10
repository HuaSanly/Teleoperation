// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/AgvDeviceState.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/agv_device_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__AgvDeviceState__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe3, 0x39, 0x7f, 0xa3, 0x12, 0x8b, 0xff, 0xdd,
      0x09, 0x29, 0x4d, 0x79, 0x7a, 0x2c, 0x47, 0x11,
      0x26, 0xf7, 0x9f, 0x6d, 0x4b, 0xfb, 0x28, 0xd3,
      0x4e, 0xa0, 0x84, 0x3a, 0x5c, 0xef, 0xa9, 0x82,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char teleop_robot_bridge__msg__AgvDeviceState__TYPE_NAME[] = "teleop_robot_bridge/msg/AgvDeviceState";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__header[] = "header";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__health_status[] = "health_status";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__error_domain[] = "error_domain";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__operational_mode[] = "operational_mode";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__power_state[] = "power_state";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__connectivity_status[] = "connectivity_status";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__manufacturer[] = "manufacturer";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__model[] = "model";
static char teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__firmware_version[] = "firmware_version";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__AgvDeviceState__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__health_status, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__error_domain, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__operational_mode, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__power_state, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__connectivity_status, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__manufacturer, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__model, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvDeviceState__FIELD_NAME__firmware_version, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__AgvDeviceState__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__AgvDeviceState__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__AgvDeviceState__TYPE_NAME, 38, 38},
      {teleop_robot_bridge__msg__AgvDeviceState__FIELDS, 9, 9},
    },
    {teleop_robot_bridge__msg__AgvDeviceState__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# AGV\\xe8\\xae\\xbe\\xe5\\xa4\\x87\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\xb6\\x88\\xe6\\x81\\xaf\\xef\\xbc\\x88\\xe9\\x80\\x9a\\xe7\\x94\\xa8\\xe7\\xa1\\xac\\xe4\\xbb\\xb6\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xef\\xbc\\x89\n"
  "\n"
  "std_msgs/Header header\n"
  "\n"
  "# \\xe8\\xae\\xbe\\xe5\\xa4\\x87\\xe5\\x81\\xa5\\xe5\\xba\\xb7\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "uint8 health_status\n"
  "\n"
  "# \\xe9\\x94\\x99\\xe8\\xaf\\xaf\\xe5\\x9f\\x9f\\xef\\xbc\\x88\\xe5\\x8d\\x95\\xe4\\xb8\\xaa\\xe9\\x94\\x99\\xe8\\xaf\\xaf\\xe4\\xbb\\xa3\\xe7\\xa0\\x81\\xef\\xbc\\x89\n"
  "uint8 error_domain\n"
  "\n"
  "# \\xe6\\x93\\x8d\\xe4\\xbd\\x9c\\xe6\\xa8\\xa1\\xe5\\xbc\\x8f\n"
  "uint8 operational_mode\n"
  "\n"
  "# \\xe7\\x94\\xb5\\xe6\\xba\\x90\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "uint8 power_state\n"
  "\n"
  "# \\xe8\\xbf\\x9e\\xe6\\x8e\\xa5\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "uint8 connectivity_status\n"
  "\n"
  "# \\xe5\\x88\\xb6\\xe9\\x80\\xa0\\xe5\\x95\\x86\\xe5\\x90\\x8d\\xe7\\xa7\\xb0\n"
  "string manufacturer\n"
  "\n"
  "# \\xe8\\xae\\xbe\\xe5\\xa4\\x87\\xe5\\x9e\\x8b\\xe5\\x8f\\xb7\n"
  "string model\n"
  "\n"
  "# \\xe5\\x9b\\xba\\xe4\\xbb\\xb6\\xe7\\x89\\x88\\xe6\\x9c\\xac\n"
  "string firmware_version\n"
  "\n"
  "# --- Health Status Constants -------------------------------------\n"
  "uint8 HEALTH_UNKNOWN  = 0\n"
  "uint8 HEALTH_OK       = 1\n"
  "uint8 HEALTH_DEGRADED = 2\n"
  "uint8 HEALTH_WARNING  = 3\n"
  "uint8 HEALTH_ERROR    = 4\n"
  "uint8 HEALTH_FATAL    = 5\n"
  "\n"
  "# --- Error Domain Constants --------------------------------------\n"
  "uint8 ERROR_NONE           = 0\n"
  "uint8 ERROR_UNKNOWN        = 1\n"
  "uint8 ERROR_HW             = 2\n"
  "uint8 ERROR_SW             = 3\n"
  "uint8 ERROR_OVER_TRAVEL    = 4\n"
  "uint8 EMERGENCY_STOP_HW    = 5\n"
  "uint8 EMERGENCY_STOP_SW    = 6\n"
  "uint8 PROTECTIVE_STOP_HW   = 7\n"
  "uint8 PROTECTIVE_STOP_SW   = 8\n"
  "uint8 SAFETY_STOP          = 9\n"
  "uint8 CALIBRATION_REQUIRED = 10\n"
  "\n"
  "# --- Operational Mode Constants ----------------------------------\n"
  "uint8 MODE_UNKNOWN              = 0\n"
  "uint8 MODE_MANUAL               = 1\n"
  "uint8 MODE_AUTO                 = 2\n"
  "uint8 MODE_SAFE                 = 3\n"
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
  "uint8 POWER_UNKNOWN         = 0\n"
  "uint8 POWER_OFF             = 1\n"
  "uint8 POWER_STANDBY         = 2\n"
  "uint8 POWER_ON              = 3\n"
  "uint8 POWER_SLEEP           = 4\n"
  "uint8 POWER_ERROR           = 5\n"
  "uint8 POWER_LEVEL_LOW       = 6\n"
  "uint8 POWER_LEVEL_CRITICAL  = 7\n"
  "uint8 POWER_CHARGING        = 8\n"
  "uint8 POWER_CHARGING_ERROR  = 9\n"
  "\n"
  "# --- Connectivity Status Constants -------------------------------\n"
  "uint8 CONNECT_UNKNOWN    = 0\n"
  "uint8 CONNECT_UP         = 1\n"
  "uint8 CONNECT_DOWN       = 2\n"
  "uint8 CONNECT_FAILURE    = 3\n"
  "uint8 CONNECTION_SLOW    = 4";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__AgvDeviceState__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__AgvDeviceState__TYPE_NAME, 38, 38},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 2062, 2062},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__AgvDeviceState__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__AgvDeviceState__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
