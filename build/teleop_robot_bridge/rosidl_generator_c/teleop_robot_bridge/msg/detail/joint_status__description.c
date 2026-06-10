// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/JointStatus.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/joint_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__JointStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x72, 0x0f, 0x2f, 0x22, 0xaf, 0xe9, 0xb7, 0x9d,
      0xd3, 0xdd, 0xf8, 0xd7, 0x03, 0x56, 0xc7, 0x1d,
      0x4c, 0x3f, 0x29, 0xc5, 0x8d, 0x29, 0x84, 0x35,
      0xf1, 0x13, 0x80, 0x5e, 0xc1, 0x4e, 0x83, 0x14,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char teleop_robot_bridge__msg__JointStatus__TYPE_NAME[] = "teleop_robot_bridge/msg/JointStatus";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__driver_voltage[] = "driver_voltage";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__driver_temperature[] = "driver_temperature";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__driver_state[] = "driver_state";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_temperature[] = "motor_temperature";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__rpm[] = "rpm";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__current[] = "current";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__pulse_count[] = "pulse_count";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_angles[] = "motor_angles";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_speeds[] = "motor_speeds";
static char teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_loads[] = "motor_loads";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__JointStatus__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__driver_voltage, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__driver_temperature, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__driver_state, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_temperature, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__rpm, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__current, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__pulse_count, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_angles, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_speeds, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__FIELD_NAME__motor_loads, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__JointStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__JointStatus__TYPE_NAME, 35, 35},
      {teleop_robot_bridge__msg__JointStatus__FIELDS, 10, 10},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe5\\x8d\\x95\\xe4\\xb8\\xaa\\xe6\\x89\\xa7\\xe8\\xa1\\x8c\\xe5\\x99\\xa8\\xef\\xbc\\x88\\xe7\\x94\\xb5\\xe6\\x9c\\xba+\\xe9\\xa9\\xb1\\xe5\\x8a\\xa8\\xe5\\x99\\xa8\\xef\\xbc\\x89\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "\n"
  "# \\xe9\\xa9\\xb1\\xe5\\x8a\\xa8\\xe5\\x99\\xa8\\xe4\\xbf\\xa1\\xe6\\x81\\xaf\n"
  "float32 driver_voltage          # \\xe9\\xa9\\xb1\\xe5\\x8a\\xa8\\xe5\\x99\\xa8\\xe7\\x94\\xb5\\xe5\\x8e\\x8b (V)\n"
  "float32 driver_temperature      # \\xe9\\xa9\\xb1\\xe5\\x8a\\xa8\\xe5\\x99\\xa8\\xe6\\xb8\\xa9\\xe5\\xba\\xa6 (\\xc2\\xb0C)\n"
  "uint8 driver_state              # \\xe9\\xa9\\xb1\\xe5\\x8a\\xa8\\xe5\\x99\\xa8\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe7\\xa0\\x81\n"
  "\n"
  "# \\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xe4\\xbf\\xa1\\xe6\\x81\\xaf\n"
  "float32 motor_temperature       # \\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xe6\\xb8\\xa9\\xe5\\xba\\xa6 (\\xc2\\xb0C)\n"
  "int32 rpm                       # \\xe8\\xbd\\xac\\xe9\\x80\\x9f (\\xe8\\xbd\\xac/\\xe5\\x88\\x86\\xe9\\x92\\x9f)\n"
  "float32 current                 # \\xe7\\x94\\xb5\\xe6\\xb5\\x81 (A)\n"
  "int64 pulse_count               # \\xe8\\x84\\x89\\xe5\\x86\\xb2\\xe8\\xae\\xa1\\xe6\\x95\\xb0\n"
  "int32 motor_angles              # \\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xe8\\xa7\\x92\\xe5\\xba\\xa6\n"
  "int32 motor_speeds              # \\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xe9\\x80\\x9f\\xe5\\xba\\xa6\n"
  "int32 motor_loads               # \\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xe8\\xb4\\x9f\\xe8\\xbd\\xbd";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__JointStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__JointStatus__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 450, 450},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__JointStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__JointStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
