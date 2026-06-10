// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/AgvMotionCtrl.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/agv_motion_ctrl__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__AgvMotionCtrl__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6c, 0x6e, 0xed, 0xda, 0x13, 0x76, 0xd3, 0x09,
      0x23, 0xcd, 0x22, 0xe4, 0xa9, 0x53, 0x65, 0x20,
      0xd1, 0x7d, 0x6a, 0xba, 0x0a, 0xd2, 0x1b, 0x30,
      0x7d, 0x5b, 0xcb, 0x0d, 0xad, 0xf2, 0xc7, 0xe1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char teleop_robot_bridge__msg__AgvMotionCtrl__TYPE_NAME[] = "teleop_robot_bridge/msg/AgvMotionCtrl";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__AgvMotionCtrl__FIELD_NAME__enable_states[] = "enable_states";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__AgvMotionCtrl__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__AgvMotionCtrl__FIELD_NAME__enable_states, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN_ARRAY,
      5,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__AgvMotionCtrl__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__AgvMotionCtrl__TYPE_NAME, 37, 37},
      {teleop_robot_bridge__msg__AgvMotionCtrl__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe6\\x8e\\xa7\\xe5\\x88\\xb64\\xe4\\xb8\\xaa\\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xe7\\x9a\\x84\\xe4\\xbd\\xbf\\xe8\\x83\\xbd/\\xe5\\xa4\\xb1\\xe8\\x83\\xbd\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "# \\xe5\\x89\\x8d4\\xe4\\xb8\\xaa\\xe5\\x85\\x83\\xe7\\xb4\\xa0\\xe4\\xbe\\x9d\\xe6\\xac\\xa1\\xe5\\xaf\\xb9\\xe5\\xba\\x94\\xe5\\xb7\\xa6\\xe8\\xbd\\xae\\xe6\\xaf\\x82\\xe3\\x80\\x81\\xe5\\x8f\\xb3\\xe8\\xbd\\xae\\xe6\\xaf\\x82\\xe3\\x80\\x81\\xe5\\xb7\\xa6\\xe8\\xbd\\xac\\xe5\\x90\\x91\\xe3\\x80\\x81\\xe5\\x8f\\xb3\\xe8\\xbd\\xac\\xe5\\x90\\x91\\xef\\xbc\\x8c\\xe7\\xac\\xac5\\xe4\\xb8\\xaa\\xe4\\xb8\\xba\\xe5\\x85\\xa8\\xe9\\x83\\xa8\\xe4\\xbd\\xbf\\xe8\\x83\\xbd/\\xe5\\xa4\\xb1\\xe8\\x83\\xbd\n"
  "bool[5] enable_states";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__AgvMotionCtrl__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__AgvMotionCtrl__TYPE_NAME, 37, 37},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 77, 77},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__AgvMotionCtrl__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__AgvMotionCtrl__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
