// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/UpperBodyDeviceState.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/upper_body_device_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__UpperBodyDeviceState__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe1, 0x20, 0x18, 0x81, 0xa2, 0xd9, 0x68, 0x9e,
      0x73, 0x3e, 0x5c, 0x65, 0x01, 0x8f, 0xd7, 0x34,
      0x81, 0xed, 0x5d, 0x09, 0x62, 0x3c, 0x0e, 0xa1,
      0x13, 0xaf, 0x20, 0xc2, 0xdb, 0x97, 0xd3, 0xd6,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "teleop_robot_bridge/msg/detail/single_device_state__functions.h"
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
static const rosidl_type_hash_t teleop_robot_bridge__msg__SingleDeviceState__EXPECTED_HASH = {1, {
    0xa6, 0x16, 0xe3, 0x3f, 0x40, 0x08, 0xd1, 0x1a,
    0xf4, 0xbe, 0x1d, 0xc0, 0x14, 0x9b, 0xc2, 0x44,
    0x53, 0xb8, 0x68, 0xf1, 0xec, 0x3f, 0xf1, 0x89,
    0xea, 0x1a, 0xa1, 0x05, 0xe4, 0x2f, 0x4d, 0x4c,
  }};
#endif

static char teleop_robot_bridge__msg__UpperBodyDeviceState__TYPE_NAME[] = "teleop_robot_bridge/msg/UpperBodyDeviceState";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char teleop_robot_bridge__msg__SingleDeviceState__TYPE_NAME[] = "teleop_robot_bridge/msg/SingleDeviceState";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__UpperBodyDeviceState__FIELD_NAME__header[] = "header";
static char teleop_robot_bridge__msg__UpperBodyDeviceState__FIELD_NAME__device_state[] = "device_state";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__UpperBodyDeviceState__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__UpperBodyDeviceState__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__UpperBodyDeviceState__FIELD_NAME__device_state, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {teleop_robot_bridge__msg__SingleDeviceState__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__UpperBodyDeviceState__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__SingleDeviceState__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__UpperBodyDeviceState__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__UpperBodyDeviceState__TYPE_NAME, 44, 44},
      {teleop_robot_bridge__msg__UpperBodyDeviceState__FIELDS, 2, 2},
    },
    {teleop_robot_bridge__msg__UpperBodyDeviceState__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&teleop_robot_bridge__msg__SingleDeviceState__EXPECTED_HASH, teleop_robot_bridge__msg__SingleDeviceState__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = teleop_robot_bridge__msg__SingleDeviceState__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe4\\xb8\\x8a\\xe5\\x8d\\x8a\\xe8\\xba\\xab\\xe8\\xae\\xbe\\xe5\\xa4\\x87\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\xb6\\x88\\xe6\\x81\\xaf\n"
  "\n"
  "std_msgs/Header header\n"
  "\n"
  "# \\xe5\\x8d\\x95\\xe4\\xb8\\xaa\\xe8\\xae\\xbe\\xe5\\xa4\\x87\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "teleop_robot_bridge/SingleDeviceState device_state";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__UpperBodyDeviceState__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__UpperBodyDeviceState__TYPE_NAME, 44, 44},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 97, 97},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__UpperBodyDeviceState__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__UpperBodyDeviceState__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[3] = *teleop_robot_bridge__msg__SingleDeviceState__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
