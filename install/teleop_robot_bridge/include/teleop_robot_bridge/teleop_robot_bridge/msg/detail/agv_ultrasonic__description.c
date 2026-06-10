// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__AgvUltrasonic__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x08, 0x49, 0x26, 0xf0, 0xa4, 0x36, 0xaa, 0xd7,
      0xb9, 0x3c, 0xbd, 0x27, 0xbc, 0xcd, 0x3a, 0x71,
      0xe3, 0xb4, 0x6a, 0xe0, 0x16, 0x3d, 0x7e, 0xd3,
      0xda, 0xdb, 0x57, 0x45, 0x39, 0x07, 0x8e, 0xc0,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "std_msgs/msg/detail/header__functions.h"
#include "sensor_msgs/msg/detail/range__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t sensor_msgs__msg__Range__EXPECTED_HASH = {1, {
    0xb4, 0x2b, 0x62, 0x56, 0x2e, 0x93, 0xcb, 0xfe,
    0x9d, 0x42, 0xb8, 0x2f, 0xe5, 0x99, 0x4d, 0xfa,
    0x3d, 0x63, 0xd7, 0xd5, 0xc9, 0x0a, 0x31, 0x79,
    0x81, 0x70, 0x3f, 0x73, 0x88, 0xad, 0xff, 0x3a,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char teleop_robot_bridge__msg__AgvUltrasonic__TYPE_NAME[] = "teleop_robot_bridge/msg/AgvUltrasonic";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char sensor_msgs__msg__Range__TYPE_NAME[] = "sensor_msgs/msg/Range";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__AgvUltrasonic__FIELD_NAME__ranges[] = "ranges";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__AgvUltrasonic__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__AgvUltrasonic__FIELD_NAME__ranges, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_ARRAY,
      8,
      0,
      {sensor_msgs__msg__Range__TYPE_NAME, 21, 21},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__AgvUltrasonic__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {sensor_msgs__msg__Range__TYPE_NAME, 21, 21},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__AgvUltrasonic__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__AgvUltrasonic__TYPE_NAME, 37, 37},
      {teleop_robot_bridge__msg__AgvUltrasonic__FIELDS, 1, 1},
    },
    {teleop_robot_bridge__msg__AgvUltrasonic__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&sensor_msgs__msg__Range__EXPECTED_HASH, sensor_msgs__msg__Range__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = sensor_msgs__msg__Range__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# AGV \\xe8\\xb6\\x85\\xe5\\xa3\\xb0\\xe6\\xb3\\xa2\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xe6\\xb6\\x88\\xe6\\x81\\xaf\\xef\\xbc\\x88\\xe5\\xa4\\x9a\\xe4\\xb8\\xaa\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xef\\xbc\\x89\n"
  "\n"
  "# \\xe8\\xb6\\x85\\xe5\\xa3\\xb0\\xe6\\xb3\\xa2\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xe6\\x95\\xb0\\xe6\\x8d\\xae\\xe6\\x95\\xb0\\xe7\\xbb\\x84\\xef\\xbc\\x888\\xe4\\xb8\\xaa\\xe4\\xbc\\xa0\\xe6\\x84\\x9f\\xe5\\x99\\xa8\\xef\\xbc\\x8c\\xe5\\x9b\\xba\\xe5\\xae\\x9a\\xe9\\x95\\xbf\\xe5\\xba\\xa6\\xef\\xbc\\x89\n"
  "sensor_msgs/Range[8] ranges";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__AgvUltrasonic__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__AgvUltrasonic__TYPE_NAME, 37, 37},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 76, 76},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__AgvUltrasonic__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__AgvUltrasonic__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *sensor_msgs__msg__Range__get_individual_type_description_source(NULL);
    sources[3] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
