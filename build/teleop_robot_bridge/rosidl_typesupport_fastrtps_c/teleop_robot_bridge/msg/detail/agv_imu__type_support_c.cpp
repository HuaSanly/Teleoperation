// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from teleop_robot_bridge:msg/AgvImu.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/agv_imu__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "teleop_robot_bridge/msg/detail/agv_imu__struct.h"
#include "teleop_robot_bridge/msg/detail/agv_imu__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "sensor_msgs/msg/detail/imu__functions.h"  // imu
#include "sensor_msgs/msg/detail/magnetic_field__functions.h"  // magnetic_field

// forward declare type support functions

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
bool cdr_serialize_sensor_msgs__msg__Imu(
  const sensor_msgs__msg__Imu * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
bool cdr_deserialize_sensor_msgs__msg__Imu(
  eprosima::fastcdr::Cdr & cdr,
  sensor_msgs__msg__Imu * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t get_serialized_size_sensor_msgs__msg__Imu(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t max_serialized_size_sensor_msgs__msg__Imu(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
bool cdr_serialize_key_sensor_msgs__msg__Imu(
  const sensor_msgs__msg__Imu * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t get_serialized_size_key_sensor_msgs__msg__Imu(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t max_serialized_size_key_sensor_msgs__msg__Imu(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Imu)();

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
bool cdr_serialize_sensor_msgs__msg__MagneticField(
  const sensor_msgs__msg__MagneticField * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
bool cdr_deserialize_sensor_msgs__msg__MagneticField(
  eprosima::fastcdr::Cdr & cdr,
  sensor_msgs__msg__MagneticField * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t get_serialized_size_sensor_msgs__msg__MagneticField(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t max_serialized_size_sensor_msgs__msg__MagneticField(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
bool cdr_serialize_key_sensor_msgs__msg__MagneticField(
  const sensor_msgs__msg__MagneticField * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t get_serialized_size_key_sensor_msgs__msg__MagneticField(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
size_t max_serialized_size_key_sensor_msgs__msg__MagneticField(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, MagneticField)();


using _AgvImu__ros_msg_type = teleop_robot_bridge__msg__AgvImu;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_teleop_robot_bridge__msg__AgvImu(
  const teleop_robot_bridge__msg__AgvImu * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: imu
  {
    cdr_serialize_sensor_msgs__msg__Imu(
      &ros_message->imu, cdr);
  }

  // Field name: magnetic_field
  {
    cdr_serialize_sensor_msgs__msg__MagneticField(
      &ros_message->magnetic_field, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_deserialize_teleop_robot_bridge__msg__AgvImu(
  eprosima::fastcdr::Cdr & cdr,
  teleop_robot_bridge__msg__AgvImu * ros_message)
{
  // Field name: imu
  {
    cdr_deserialize_sensor_msgs__msg__Imu(cdr, &ros_message->imu);
  }

  // Field name: magnetic_field
  {
    cdr_deserialize_sensor_msgs__msg__MagneticField(cdr, &ros_message->magnetic_field);
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_teleop_robot_bridge__msg__AgvImu(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AgvImu__ros_msg_type * ros_message = static_cast<const _AgvImu__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: imu
  current_alignment += get_serialized_size_sensor_msgs__msg__Imu(
    &(ros_message->imu), current_alignment);

  // Field name: magnetic_field
  current_alignment += get_serialized_size_sensor_msgs__msg__MagneticField(
    &(ros_message->magnetic_field), current_alignment);

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_teleop_robot_bridge__msg__AgvImu(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: imu
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_sensor_msgs__msg__Imu(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: magnetic_field
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_sensor_msgs__msg__MagneticField(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__AgvImu;
    is_plain =
      (
      offsetof(DataType, magnetic_field) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_key_teleop_robot_bridge__msg__AgvImu(
  const teleop_robot_bridge__msg__AgvImu * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: imu
  {
    cdr_serialize_key_sensor_msgs__msg__Imu(
      &ros_message->imu, cdr);
  }

  // Field name: magnetic_field
  {
    cdr_serialize_key_sensor_msgs__msg__MagneticField(
      &ros_message->magnetic_field, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_key_teleop_robot_bridge__msg__AgvImu(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AgvImu__ros_msg_type * ros_message = static_cast<const _AgvImu__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: imu
  current_alignment += get_serialized_size_key_sensor_msgs__msg__Imu(
    &(ros_message->imu), current_alignment);

  // Field name: magnetic_field
  current_alignment += get_serialized_size_key_sensor_msgs__msg__MagneticField(
    &(ros_message->magnetic_field), current_alignment);

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_key_teleop_robot_bridge__msg__AgvImu(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: imu
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_sensor_msgs__msg__Imu(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: magnetic_field
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_sensor_msgs__msg__MagneticField(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__AgvImu;
    is_plain =
      (
      offsetof(DataType, magnetic_field) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _AgvImu__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const teleop_robot_bridge__msg__AgvImu * ros_message = static_cast<const teleop_robot_bridge__msg__AgvImu *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_teleop_robot_bridge__msg__AgvImu(ros_message, cdr);
}

static bool _AgvImu__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  teleop_robot_bridge__msg__AgvImu * ros_message = static_cast<teleop_robot_bridge__msg__AgvImu *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_teleop_robot_bridge__msg__AgvImu(cdr, ros_message);
}

static uint32_t _AgvImu__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_teleop_robot_bridge__msg__AgvImu(
      untyped_ros_message, 0));
}

static size_t _AgvImu__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_teleop_robot_bridge__msg__AgvImu(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_AgvImu = {
  "teleop_robot_bridge::msg",
  "AgvImu",
  _AgvImu__cdr_serialize,
  _AgvImu__cdr_deserialize,
  _AgvImu__get_serialized_size,
  _AgvImu__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _AgvImu__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_AgvImu,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__AgvImu__get_type_hash,
  &teleop_robot_bridge__msg__AgvImu__get_type_description,
  &teleop_robot_bridge__msg__AgvImu__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, teleop_robot_bridge, msg, AgvImu)() {
  return &_AgvImu__type_support;
}

#if defined(__cplusplus)
}
#endif
