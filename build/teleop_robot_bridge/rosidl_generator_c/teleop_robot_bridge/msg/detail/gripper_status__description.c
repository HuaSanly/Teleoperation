// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/gripper_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__GripperStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6d, 0x77, 0xbd, 0xd1, 0x76, 0x67, 0x42, 0xdd,
      0x97, 0xa9, 0xc5, 0xfd, 0x68, 0xc5, 0xa1, 0x54,
      0x52, 0xea, 0xbc, 0xd1, 0xa2, 0xa2, 0x99, 0x2c,
      0xf5, 0xef, 0xed, 0xb1, 0x4c, 0xdb, 0xc4, 0x26,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "teleop_robot_bridge/msg/detail/single_gripper_status__functions.h"
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
static const rosidl_type_hash_t teleop_robot_bridge__msg__SingleGripperStatus__EXPECTED_HASH = {1, {
    0xb9, 0xd5, 0x11, 0x79, 0xd9, 0x32, 0x85, 0xa6,
    0xa4, 0x3b, 0x74, 0xb8, 0xce, 0x28, 0x4f, 0x7a,
    0xfd, 0x1e, 0xd7, 0xde, 0x03, 0x6f, 0x23, 0xed,
    0xd3, 0xad, 0x19, 0xd2, 0x9f, 0x14, 0x2b, 0x4d,
  }};
#endif

static char teleop_robot_bridge__msg__GripperStatus__TYPE_NAME[] = "teleop_robot_bridge/msg/GripperStatus";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char teleop_robot_bridge__msg__SingleGripperStatus__TYPE_NAME[] = "teleop_robot_bridge/msg/SingleGripperStatus";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__GripperStatus__FIELD_NAME__header[] = "header";
static char teleop_robot_bridge__msg__GripperStatus__FIELD_NAME__grippers[] = "grippers";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__GripperStatus__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__GripperStatus__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__GripperStatus__FIELD_NAME__grippers, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_ARRAY,
      2,
      0,
      {teleop_robot_bridge__msg__SingleGripperStatus__TYPE_NAME, 43, 43},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__GripperStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperStatus__TYPE_NAME, 43, 43},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__GripperStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__GripperStatus__TYPE_NAME, 37, 37},
      {teleop_robot_bridge__msg__GripperStatus__FIELDS, 2, 2},
    },
    {teleop_robot_bridge__msg__GripperStatus__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&teleop_robot_bridge__msg__SingleGripperStatus__EXPECTED_HASH, teleop_robot_bridge__msg__SingleGripperStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = teleop_robot_bridge__msg__SingleGripperStatus__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe6\\x8a\\x93\\xe6\\x89\\x8b\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\xb6\\x88\\xe6\\x81\\xaf\n"
  "\n"
  "std_msgs/Header header\n"
  "\n"
  "# \\xe6\\x8a\\x93\\xe6\\x89\\x8b\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\x95\\xb0\\xe7\\xbb\\x84\\xef\\xbc\\x882\\xe4\\xb8\\xaa\\xef\\xbc\\x89\n"
  "teleop_robot_bridge/SingleGripperStatus[2] grippers";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__GripperStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__GripperStatus__TYPE_NAME, 37, 37},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 99, 99},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__GripperStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__GripperStatus__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[3] = *teleop_robot_bridge__msg__SingleGripperStatus__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
