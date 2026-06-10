// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/ArmJointStatus.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/arm_joint_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__ArmJointStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x49, 0x3d, 0x00, 0xea, 0x49, 0x29, 0xf8, 0x30,
      0x67, 0xbf, 0xa5, 0x01, 0xd1, 0xbd, 0x29, 0x15,
      0xb6, 0xf5, 0x76, 0x78, 0xcf, 0x5c, 0x67, 0x7c,
      0x0a, 0xe5, 0xaf, 0x5c, 0x93, 0x72, 0x77, 0xea,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "std_msgs/msg/detail/header__functions.h"
#include "teleop_robot_bridge/msg/detail/joint_status__functions.h"

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
static const rosidl_type_hash_t teleop_robot_bridge__msg__JointStatus__EXPECTED_HASH = {1, {
    0x72, 0x0f, 0x2f, 0x22, 0xaf, 0xe9, 0xb7, 0x9d,
    0xd3, 0xdd, 0xf8, 0xd7, 0x03, 0x56, 0xc7, 0x1d,
    0x4c, 0x3f, 0x29, 0xc5, 0x8d, 0x29, 0x84, 0x35,
    0xf1, 0x13, 0x80, 0x5e, 0xc1, 0x4e, 0x83, 0x14,
  }};
#endif

static char teleop_robot_bridge__msg__ArmJointStatus__TYPE_NAME[] = "teleop_robot_bridge/msg/ArmJointStatus";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";
static char teleop_robot_bridge__msg__JointStatus__TYPE_NAME[] = "teleop_robot_bridge/msg/JointStatus";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__ArmJointStatus__FIELD_NAME__header[] = "header";
static char teleop_robot_bridge__msg__ArmJointStatus__FIELD_NAME__name[] = "name";
static char teleop_robot_bridge__msg__ArmJointStatus__FIELD_NAME__joint_status[] = "joint_status";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__ArmJointStatus__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__ArmJointStatus__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__ArmJointStatus__FIELD_NAME__name, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING_ARRAY,
      14,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__ArmJointStatus__FIELD_NAME__joint_status, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_ARRAY,
      14,
      0,
      {teleop_robot_bridge__msg__JointStatus__TYPE_NAME, 35, 35},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__ArmJointStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__JointStatus__TYPE_NAME, 35, 35},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__ArmJointStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__ArmJointStatus__TYPE_NAME, 38, 38},
      {teleop_robot_bridge__msg__ArmJointStatus__FIELDS, 3, 3},
    },
    {teleop_robot_bridge__msg__ArmJointStatus__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&teleop_robot_bridge__msg__JointStatus__EXPECTED_HASH, teleop_robot_bridge__msg__JointStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = teleop_robot_bridge__msg__JointStatus__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Arm\\xe5\\x85\\xb3\\xe8\\x8a\\x82\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\xb6\\x88\\xe6\\x81\\xaf\\xef\\xbc\\x8814\\xe4\\xb8\\xaa\\xe6\\x89\\xa7\\xe8\\xa1\\x8c\\xe5\\x99\\xa8\\xef\\xbc\\x89\n"
  "\n"
  "std_msgs/Header header\n"
  "\n"
  "#\\xe5\\x85\\xb3\\xe8\\x8a\\x82\\xe5\\x90\\x8d\\xe7\\xa7\\xb0\n"
  "string[14] name\n"
  "\n"
  "# 14\\xe4\\xb8\\xaa\\xe5\\x85\\xb3\\xe8\\x8a\\x82\\xe7\\x9a\\x84\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\x95\\xb0\\xe7\\xbb\\x84\n"
  "teleop_robot_bridge/JointStatus[14] joint_status";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__ArmJointStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__ArmJointStatus__TYPE_NAME, 38, 38},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 129, 129},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__ArmJointStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__ArmJointStatus__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    sources[3] = *teleop_robot_bridge__msg__JointStatus__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
