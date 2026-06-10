// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/GripperMove.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/gripper_move__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__GripperMove__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x8f, 0xe3, 0x0d, 0x1d, 0x25, 0xda, 0x6a, 0xc5,
      0x3a, 0x0d, 0x02, 0x36, 0x3c, 0x30, 0x6b, 0x42,
      0x1c, 0x2d, 0x00, 0xed, 0x02, 0xf2, 0xc0, 0x67,
      0xfa, 0xcf, 0x60, 0xb4, 0x35, 0x2e, 0xb7, 0x90,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "teleop_robot_bridge/msg/detail/single_gripper_move__functions.h"
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
static const rosidl_type_hash_t teleop_robot_bridge__msg__SingleGripperMove__EXPECTED_HASH = {1, {
    0x87, 0xb2, 0xca, 0xa0, 0x57, 0x50, 0xc4, 0x08,
    0xe8, 0x6e, 0x14, 0x5c, 0x0b, 0xe9, 0x87, 0xf4,
    0xf9, 0xcf, 0xe9, 0xa3, 0x0c, 0x54, 0xdf, 0x4f,
    0x48, 0x4e, 0x8c, 0x30, 0x90, 0x2d, 0xdb, 0x04,
  }};
#endif

static char teleop_robot_bridge__msg__GripperMove__TYPE_NAME[] = "teleop_robot_bridge/msg/GripperMove";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char teleop_robot_bridge__msg__SingleGripperMove__TYPE_NAME[] = "teleop_robot_bridge/msg/SingleGripperMove";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__GripperMove__FIELD_NAME__header[] = "header";
static char teleop_robot_bridge__msg__GripperMove__FIELD_NAME__grippers[] = "grippers";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__GripperMove__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__GripperMove__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__GripperMove__FIELD_NAME__grippers, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {teleop_robot_bridge__msg__SingleGripperMove__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__GripperMove__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleGripperMove__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__GripperMove__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__GripperMove__TYPE_NAME, 35, 35},
      {teleop_robot_bridge__msg__GripperMove__FIELDS, 2, 2},
    },
    {teleop_robot_bridge__msg__GripperMove__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&teleop_robot_bridge__msg__SingleGripperMove__EXPECTED_HASH, teleop_robot_bridge__msg__SingleGripperMove__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = teleop_robot_bridge__msg__SingleGripperMove__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe6\\x8a\\x93\\xe6\\x89\\x8b\\xe7\\xa7\\xbb\\xe5\\x8a\\xa8\\xe5\\x91\\xbd\\xe4\\xbb\\xa4\\xe6\\xb6\\x88\\xe6\\x81\\xaf\\xef\\xbc\\x88\\xe6\\x94\\xaf\\xe6\\x8c\\x81\\xe5\\xa4\\x9a\\xe4\\xb8\\xaa\\xe6\\x8a\\x93\\xe6\\x89\\x8b\\xef\\xbc\\x89\n"
  "\n"
  "std_msgs/Header header\n"
  "\n"
  "# \\xe6\\x8a\\x93\\xe6\\x89\\x8b\\xe5\\x91\\xbd\\xe4\\xbb\\xa4\\xe6\\x95\\xb0\\xe7\\xbb\\x84\n"
  "teleop_robot_bridge/SingleGripperMove[] grippers";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__GripperMove__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__GripperMove__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 102, 102},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__GripperMove__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__GripperMove__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[3] = *teleop_robot_bridge__msg__SingleGripperMove__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
