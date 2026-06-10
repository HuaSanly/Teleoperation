// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/hand_tactile__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__HandTactile__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe8, 0xf3, 0x76, 0x79, 0xd7, 0xe2, 0x54, 0xaf,
      0xb9, 0x02, 0x73, 0xb2, 0xbc, 0xed, 0xd2, 0xa6,
      0x62, 0xf9, 0xa5, 0xf2, 0x09, 0x66, 0x89, 0x20,
      0x51, 0xd3, 0x8a, 0x34, 0x03, 0x3f, 0xad, 0xf1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char teleop_robot_bridge__msg__HandTactile__TYPE_NAME[] = "teleop_robot_bridge/msg/HandTactile";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__HandTactile__FIELD_NAME__finger[] = "finger";
static char teleop_robot_bridge__msg__HandTactile__FIELD_NAME__thumb[] = "thumb";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__HandTactile__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__HandTactile__FIELD_NAME__finger, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__HandTactile__FIELD_NAME__thumb, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32_ARRAY,
      4,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__HandTactile__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__HandTactile__TYPE_NAME, 35, 35},
      {teleop_robot_bridge__msg__HandTactile__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe5\\x8d\\x95\\xe5\\x8f\\xaa\\xe6\\x89\\x8b\\xe7\\x9a\\x84\\xe8\\xa7\\xa6\\xe8\\xa7\\x89\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xe6\\x95\\xb0\\xe6\\x8d\\xae\n"
  "\n"
  "# \\xe6\\x89\\x8b\\xe6\\x8c\\x87\\xe8\\xa7\\xa6\\xe8\\xa7\\x89\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xe6\\x95\\xb0\\xe6\\x8d\\xae\\xef\\xbc\\x884\\xe4\\xb8\\xaa\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xef\\xbc\\x89\n"
  "int32[4] finger\n"
  "\n"
  "# \\xe6\\x8b\\x87\\xe6\\x8c\\x87\\xe8\\xa7\\xa6\\xe8\\xa7\\x89\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xe6\\x95\\xb0\\xe6\\x8d\\xae\\xef\\xbc\\x884\\xe4\\xb8\\xaa\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xef\\xbc\\x89\n"
  "int32[4] thumb";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__HandTactile__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__HandTactile__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 85, 85},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__HandTactile__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__HandTactile__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
