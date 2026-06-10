// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/SingleGripperMove.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/single_gripper_move__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__SingleGripperMove__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x87, 0xb2, 0xca, 0xa0, 0x57, 0x50, 0xc4, 0x08,
      0xe8, 0x6e, 0x14, 0x5c, 0x0b, 0xe9, 0x87, 0xf4,
      0xf9, 0xcf, 0xe9, 0xa3, 0x0c, 0x54, 0xdf, 0x4f,
      0x48, 0x4e, 0x8c, 0x30, 0x90, 0x2d, 0xdb, 0x04,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char teleop_robot_bridge__msg__SingleGripperMove__TYPE_NAME[] = "teleop_robot_bridge/msg/SingleGripperMove";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__emergency_release[] = "emergency_release";
static char teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__emergency_release_dir[] = "emergency_release_dir";
static char teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__stop[] = "stop";
static char teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__position[] = "position";
static char teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__speed[] = "speed";
static char teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__force[] = "force";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__SingleGripperMove__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__emergency_release, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__emergency_release_dir, 21, 21},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__stop, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__speed, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperMove__FIELD_NAME__force, 5, 5},
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
teleop_robot_bridge__msg__SingleGripperMove__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__SingleGripperMove__TYPE_NAME, 41, 41},
      {teleop_robot_bridge__msg__SingleGripperMove__FIELDS, 6, 6},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe5\\x8d\\x95\\xe4\\xb8\\xaa\\xe6\\x8a\\x93\\xe6\\x89\\x8b\\xe7\\xa7\\xbb\\xe5\\x8a\\xa8\\xe5\\x91\\xbd\\xe4\\xbb\\xa4\n"
  "\n"
  "# \\xe7\\xb4\\xa7\\xe6\\x80\\xa5\\xe9\\x87\\x8a\\xe6\\x94\\xbe\\xe6\\xa0\\x87\\xe5\\xbf\\x97\n"
  "bool emergency_release\n"
  "\n"
  "# \\xe7\\xb4\\xa7\\xe6\\x80\\xa5\\xe9\\x87\\x8a\\xe6\\x94\\xbe\\xe6\\x96\\xb9\\xe5\\x90\\x91\n"
  "uint8 emergency_release_dir\n"
  "\n"
  "# \\xe5\\x81\\x9c\\xe6\\xad\\xa2\\xe6\\xa0\\x87\\xe5\\xbf\\x97\n"
  "bool stop\n"
  "\n"
  "# \\xe7\\x9b\\xae\\xe6\\xa0\\x87\\xe4\\xbd\\x8d\\xe7\\xbd\\xae\n"
  "int32 position\n"
  "\n"
  "# \\xe9\\x80\\x9f\\xe5\\xba\\xa6\n"
  "int32 speed\n"
  "\n"
  "# \\xe5\\x8a\\x9b\\xe5\\xba\\xa6\n"
  "int32 force";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__SingleGripperMove__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__SingleGripperMove__TYPE_NAME, 41, 41},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 159, 159},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__SingleGripperMove__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__SingleGripperMove__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
