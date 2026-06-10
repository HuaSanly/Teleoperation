// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/SingleGripperStatus.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/single_gripper_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__SingleGripperStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb9, 0xd5, 0x11, 0x79, 0xd9, 0x32, 0x85, 0xa6,
      0xa4, 0x3b, 0x74, 0xb8, 0xce, 0x28, 0x4f, 0x7a,
      0xfd, 0x1e, 0xd7, 0xde, 0x03, 0x6f, 0x23, 0xed,
      0xd3, 0xad, 0x19, 0xd2, 0x9f, 0x14, 0x2b, 0x4d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char teleop_robot_bridge__msg__SingleGripperStatus__TYPE_NAME[] = "teleop_robot_bridge/msg/SingleGripperStatus";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__is_ready[] = "is_ready";
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__is_reset[] = "is_reset";
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__is_moving[] = "is_moving";
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__obj_detected[] = "obj_detected";
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__fault_status[] = "fault_status";
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__position[] = "position";
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__requested_position[] = "requested_position";
static char teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__current[] = "current";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__SingleGripperStatus__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__is_ready, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__is_reset, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__is_moving, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__obj_detected, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__fault_status, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__requested_position, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__FIELD_NAME__current, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__SingleGripperStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__SingleGripperStatus__TYPE_NAME, 43, 43},
      {teleop_robot_bridge__msg__SingleGripperStatus__FIELDS, 8, 8},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe5\\x8d\\x95\\xe4\\xb8\\xaa\\xe6\\x8a\\x93\\xe6\\x89\\x8b\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\xb6\\x88\\xe6\\x81\\xaf\n"
  "\n"
  "# \\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\xa0\\x87\\xe5\\xbf\\x97\n"
  "bool is_ready           # \\xe6\\x98\\xaf\\xe5\\x90\\xa6\\xe5\\xb0\\xb1\\xe7\\xbb\\xaa\n"
  "bool is_reset           # \\xe6\\x98\\xaf\\xe5\\x90\\xa6\\xe5\\xa4\\x8d\\xe4\\xbd\\x8d\n"
  "bool is_moving          # \\xe6\\x98\\xaf\\xe5\\x90\\xa6\\xe8\\xbf\\x90\\xe5\\x8a\\xa8\\xe4\\xb8\\xad\n"
  "bool obj_detected       # \\xe6\\x98\\xaf\\xe5\\x90\\xa6\\xe6\\xa3\\x80\\xe6\\xb5\\x8b\\xe5\\x88\\xb0\\xe7\\x89\\xa9\\xe4\\xbd\\x93\n"
  "\n"
  "# \\xe6\\x95\\x85\\xe9\\x9a\\x9c\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe7\\xa0\\x81\n"
  "uint8 fault_status\n"
  "\n"
  "# \\xe4\\xbd\\x8d\\xe7\\xbd\\xae\\xe4\\xbf\\xa1\\xe6\\x81\\xaf\n"
  "int32 position          # \\xe5\\xbd\\x93\\xe5\\x89\\x8d\\xe4\\xbd\\x8d\\xe7\\xbd\\xae\n"
  "int32 requested_position # \\xe7\\x9b\\xae\\xe6\\xa0\\x87\\xe4\\xbd\\x8d\\xe7\\xbd\\xae\n"
  "\n"
  "# \\xe7\\x94\\xb5\\xe6\\xb5\\x81\\xe4\\xbf\\xa1\\xe6\\x81\\xaf\n"
  "float32 current         # \\xe7\\x94\\xb5\\xe6\\xb5\\x81 (A)";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__SingleGripperStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__SingleGripperStatus__TYPE_NAME, 43, 43},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 287, 287},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__SingleGripperStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__SingleGripperStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
