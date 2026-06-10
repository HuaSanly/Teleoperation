// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from teleop_robot_bridge:msg/AgvVda5050State.idl
// generated code does not contain a copyright notice

#include "teleop_robot_bridge/msg/detail/agv_vda5050_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__AgvVda5050State__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x94, 0xf1, 0xe3, 0x7d, 0xe7, 0x16, 0x62, 0x2d,
      0xed, 0xa6, 0x43, 0x5f, 0x72, 0x9e, 0xe3, 0xc0,
      0xc0, 0x33, 0xb4, 0x28, 0x83, 0x13, 0x0d, 0x96,
      0x30, 0xf2, 0x69, 0x0b, 0x49, 0x3e, 0x42, 0x40,
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

static char teleop_robot_bridge__msg__AgvVda5050State__TYPE_NAME[] = "teleop_robot_bridge/msg/AgvVda5050State";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__header[] = "header";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__order_id[] = "order_id";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__action_status[] = "action_status";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__last_node_id[] = "last_node_id";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__driving[] = "driving";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__battery_charge[] = "battery_charge";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__operating_mode[] = "operating_mode";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__error_type[] = "error_type";
static char teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__error_description[] = "error_description";

static rosidl_runtime_c__type_description__Field teleop_robot_bridge__msg__AgvVda5050State__FIELDS[] = {
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__order_id, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__action_status, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__last_node_id, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__driving, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__battery_charge, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__operating_mode, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__error_type, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {teleop_robot_bridge__msg__AgvVda5050State__FIELD_NAME__error_description, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription teleop_robot_bridge__msg__AgvVda5050State__REFERENCED_TYPE_DESCRIPTIONS[] = {
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
teleop_robot_bridge__msg__AgvVda5050State__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {teleop_robot_bridge__msg__AgvVda5050State__TYPE_NAME, 39, 39},
      {teleop_robot_bridge__msg__AgvVda5050State__FIELDS, 9, 9},
    },
    {teleop_robot_bridge__msg__AgvVda5050State__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
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
  "# AGV\\xe8\\xae\\xbe\\xe5\\xa4\\x87\\xe7\\x8a\\xb6\\xe6\\x80\\x81\\xe6\\xb6\\x88\\xe6\\x81\\xaf\n"
  "\n"
  "std_msgs/Header header\n"
  "\n"
  "# \\xe5\\x91\\xbd\\xe4\\xbb\\xa4ID\n"
  "string order_id\n"
  "\n"
  "# \\xe5\\x8a\\xa8\\xe4\\xbd\\x9c\\xe7\\x8a\\xb6\\xe6\\x80\\x81\n"
  "string action_status\n"
  "\n"
  "# \\xe6\\x9c\\x80\\xe5\\x90\\x8e\\xe8\\x8a\\x82\\xe7\\x82\\xb9ID\n"
  "int32 last_node_id\n"
  "\n"
  "# \\xe6\\x98\\xaf\\xe5\\x90\\xa6\\xe6\\xad\\xa3\\xe5\\x9c\\xa8\\xe8\\xa1\\x8c\\xe9\\xa9\\xb6\n"
  "bool driving\n"
  "\n"
  "# \\xe7\\x94\\xb5\\xe6\\xb1\\xa0\\xe7\\x94\\xb5\\xe9\\x87\\x8f (%)\n"
  "float32 battery_charge\n"
  "\n"
  "# \\xe6\\x93\\x8d\\xe4\\xbd\\x9c\\xe6\\xa8\\xa1\\xe5\\xbc\\x8f\n"
  "string operating_mode\n"
  "\n"
  "# \\xe9\\x94\\x99\\xe8\\xaf\\xaf\\xe7\\xb1\\xbb\\xe5\\x9e\\x8b\n"
  "string error_type\n"
  "\n"
  "# \\xe9\\x94\\x99\\xe8\\xaf\\xaf\\xe6\\x8f\\x8f\\xe8\\xbf\\xb0\n"
  "string error_description\n"
  "\n"
  "\n"
  "# --- Action Status Constants ---------------------------------------\n"
  "#  action execution states\n"
  "string ACTION_WAITING    = \"WAITING\"     # Action is waiting to be executed\n"
  "string ACTION_INITIALIZING = \"INITIALIZING\" # Action is being initialized\n"
  "string ACTION_RUNNING    = \"RUNNING\"     # Action is currently executing\n"
  "string ACTION_PAUSED     = \"PAUSED\"      # Action execution is paused\n"
  "string ACTION_FINISHED   = \"FINISHED\"    # Action completed successfully\n"
  "string ACTION_FAILED     = \"FAILED\"      # Action execution failed\n"
  "\n"
  "# --- Operating Mode Constants -------------------------------------\n"
  "#  vehicle operating modes\n"
  "string MODE_AUTOMATIC    = \"AUTOMATIC\"   # Vehicle operates autonomously\n"
  "string MODE_SEMI_AUTOMATIC = \"SEMIAUTOMATIC\" # Vehicle requires operator confirmation\n"
  "string MODE_MANUAL       = \"MANUAL\"      # Vehicle is under manual control\n"
  "string MODE_SERVICE      = \"SERVICE\"     # Vehicle is in service/maintenance mode\n"
  "string MODE_EMERGENCY    = \"EMERGENCY\"   # Vehicle is in emergency mode\n"
  "string MODE_TEACHIN      = \"TEACHIN\"     # Vehicle is in teach-in mode for route learning";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__AgvVda5050State__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {teleop_robot_bridge__msg__AgvVda5050State__TYPE_NAME, 39, 39},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1371, 1371},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__AgvVda5050State__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *teleop_robot_bridge__msg__AgvVda5050State__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
