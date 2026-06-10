// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/WaistMotionCtrl.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/waist_motion_ctrl__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__WaistMotionCtrl__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4c, 0x79, 0x89, 0x0b, 0xee, 0x71, 0x63, 0x00,
      0x95, 0x0b, 0x06, 0x22, 0x82, 0x93, 0x48, 0xc3,
      0x96, 0xe7, 0x07, 0xea, 0x88, 0x19, 0x5c, 0xc4,
      0xe5, 0xeb, 0xca, 0x9d, 0xe4, 0x29, 0x8b, 0x4d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char teleop_robot_bridge__msg__WaistMotionCtrl__TYPE_NAME[] = "teleop_robot_bridge/msg/WaistMotionCtrl";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__WaistMotionCtrl__FIELD_NAME__enable_states[] = "enable_states";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__WaistMotionCtrl__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__WaistMotionCtrl__FIELD_NAME__enable_states, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__WaistMotionCtrl__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__WaistMotionCtrl__TYPE_NAME, 39, 39},
      {teleop_robot_bridge__msg__WaistMotionCtrl__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe6\\x8e\\xa7\\xe5\\x88\\xb63\\xe4\\xb8\\xaa\\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xe7\\x9a\\x84\\xe4\\xbd\\xbf\\xe8\\x83\\xbd/\\xe5\\xa4\\xb1\\xe8\\x83\\xbd\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "# \\xe6\\xaf\\x8f\\xe4\\xb8\\xaa\\xe5\\x85\\x83\\xe7\\xb4\\xa0\\xe5\\xaf\\xb9\\xe5\\xba\\x94\\xe4\\xb8\\x80\\xe4\\xb8\\xaa\\xe7\\x94\\xb5\\xe6\\x9c\\xba\\xef\\xbc\\x88\\xe7\\xb4\\xa2\\xe5\\xbc\\x950~2\\xef\\xbc\\x89\\xef\\xbc\\x8ctrue\\xe8\\xa1\\xa8\\xe7\\xa4\\xba\\xe4\\xbd\\xbf\\xe8\\x83\\xbd\\xef\\xbc\\x8cfalse\\xe8\\xa1\\xa8\\xe7\\xa4\\xba\\xe5\\xa4\\xb1\\xe8\\x83\\xbd,3\\xe4\\xb8\\xbatrue\\xe8\\xa1\\xa8\\xe7\\xa4\\xba\\xe5\\x85\\xa8\\xe9\\x83\\xa8\\xe4\\xbd\\xbf\\xe8\\x83\\xbd,false\\xe8\\xa1\\xa8\\xe7\\xa4\\xba\\xe5\\x85\\xa8\\xe9\\x83\\xa8\\xe5\\xa4\\xb1\\xe8\\x83\\xbd\n"
  "bool[4] enable_states";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__WaistMotionCtrl__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__WaistMotionCtrl__TYPE_NAME, 39, 39},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 102, 102},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__WaistMotionCtrl__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__WaistMotionCtrl__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
