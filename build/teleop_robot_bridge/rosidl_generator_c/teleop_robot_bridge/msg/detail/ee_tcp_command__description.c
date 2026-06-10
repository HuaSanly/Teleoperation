// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/EeTcpCommand.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/ee_tcp_command__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__EeTcpCommand__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x05, 0xb2, 0x07, 0x7b, 0xfa, 0xa8, 0x27, 0x66,
      0x1b, 0x4d, 0x7e, 0xd4, 0x3b, 0xf3, 0x2d, 0xd6,
      0xd2, 0xa4, 0x43, 0x3d, 0x17, 0x2a, 0xfb, 0xe2,
      0x00, 0xb3, 0xd0, 0x13, 0xe4, 0x2e, 0x43, 0x7c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
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
#endif

static char teleop_robot_bridge__msg__EeTcpCommand__TYPE_NAME[] = "teleop_robot_bridge/msg/EeTcpCommand";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__header[] = "header";
static char teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__name[] = "name";
static char teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__position[] = "position";
static char teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__euler[] = "euler";
static char teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__quat[] = "quat";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__EeTcpCommand__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__name, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING_ARRAY,
      2,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_ARRAY,
      6,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__euler, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_ARRAY,
      6,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__EeTcpCommand__FIELD_NAME__quat, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_ARRAY,
      8,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__EeTcpCommand__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__EeTcpCommand__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__EeTcpCommand__TYPE_NAME, 36, 36},
      {teleop_robot_bridge__msg__EeTcpCommand__FIELDS, 5, 5},
    },
    {teleop_robot_bridge__msg__EeTcpCommand__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# \\xe5\\x8f\\x8c\\xe6\\x9c\\xab\\xe7\\xab\\xaf TCP \\xe4\\xbd\\x8d\\xe5\\xa7\\xbf\\xe5\\x91\\xbd\\xe4\\xbb\\xa4\\xe6\\xb6\\x88\\xe6\\x81\\xaf\n"
  "std_msgs/Header header\n"
  "string[2] name\n"
  "float64[6] position     # \\xe5\\x89\\x8d3\\xe4\\xb8\\xaa\\xe4\\xb8\\xbaname[0]\\xe7\\x9a\\x84xyz\\xef\\xbc\\x8c\\xe5\\x90\\x8e3\\xe4\\xb8\\xaa\\xe4\\xb8\\xbaname[1]\\xe7\\x9a\\x84xyz\n"
  "float64[6] euler        # \\xe5\\x89\\x8d3\\xe4\\xb8\\xaa\\xe4\\xb8\\xbaname[0]\\xe7\\x9a\\x84\\xe6\\xac\\xa7\\xe6\\x8b\\x89\\xe8\\xa7\\x92[roll, pitch, yaw]\\xef\\xbc\\x8c\\xe5\\x90\\x8e3\\xe4\\xb8\\xaa\\xe4\\xb8\\xbaname[1]\\xe7\\x9a\\x84\\xe6\\xac\\xa7\\xe6\\x8b\\x89\\xe8\\xa7\\x92[roll, pitch, yaw]\n"
  "float64[8] quat         # \\xe5\\x89\\x8d4\\xe4\\xb8\\xaa\\xe4\\xb8\\xbaname[0]\\xe7\\x9a\\x84\\xe5\\x9b\\x9b\\xe5\\x85\\x83\\xe6\\x95\\xb0[x, y, z, w]\\xef\\xbc\\x8c\\xe5\\x90\\x8e4\\xe4\\xb8\\xaa\\xe4\\xb8\\xbaname[1]\\xe7\\x9a\\x84\\xe5\\x9b\\x9b\\xe5\\x85\\x83\\xe6\\x95\\xb0[x, y, z, w]";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__EeTcpCommand__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__EeTcpCommand__TYPE_NAME, 36, 36},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 288, 288},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__EeTcpCommand__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__EeTcpCommand__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
