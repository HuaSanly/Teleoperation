// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from teleop_robot_bridge:msg/JointStatus.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/joint_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "teleop_robot_bridge/msg/detail/joint_status__struct.h"
#include "teleop_robot_bridge/msg/detail/joint_status__functions.h"
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


// forward declare type support functions


using _JointStatus__ros_msg_type = teleop_robot_bridge__msg__JointStatus;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_teleop_robot_bridge__msg__JointStatus(
  const teleop_robot_bridge__msg__JointStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: driver_voltage
  {
    cdr << ros_message->driver_voltage;
  }

  // Field name: driver_temperature
  {
    cdr << ros_message->driver_temperature;
  }

  // Field name: driver_state
  {
    cdr << ros_message->driver_state;
  }

  // Field name: motor_temperature
  {
    cdr << ros_message->motor_temperature;
  }

  // Field name: rpm
  {
    cdr << ros_message->rpm;
  }

  // Field name: current
  {
    cdr << ros_message->current;
  }

  // Field name: pulse_count
  {
    cdr << ros_message->pulse_count;
  }

  // Field name: motor_angles
  {
    cdr << ros_message->motor_angles;
  }

  // Field name: motor_speeds
  {
    cdr << ros_message->motor_speeds;
  }

  // Field name: motor_loads
  {
    cdr << ros_message->motor_loads;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_deserialize_teleop_robot_bridge__msg__JointStatus(
  eprosima::fastcdr::Cdr & cdr,
  teleop_robot_bridge__msg__JointStatus * ros_message)
{
  // Field name: driver_voltage
  {
    cdr >> ros_message->driver_voltage;
  }

  // Field name: driver_temperature
  {
    cdr >> ros_message->driver_temperature;
  }

  // Field name: driver_state
  {
    cdr >> ros_message->driver_state;
  }

  // Field name: motor_temperature
  {
    cdr >> ros_message->motor_temperature;
  }

  // Field name: rpm
  {
    cdr >> ros_message->rpm;
  }

  // Field name: current
  {
    cdr >> ros_message->current;
  }

  // Field name: pulse_count
  {
    cdr >> ros_message->pulse_count;
  }

  // Field name: motor_angles
  {
    cdr >> ros_message->motor_angles;
  }

  // Field name: motor_speeds
  {
    cdr >> ros_message->motor_speeds;
  }

  // Field name: motor_loads
  {
    cdr >> ros_message->motor_loads;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_teleop_robot_bridge__msg__JointStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _JointStatus__ros_msg_type * ros_message = static_cast<const _JointStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: driver_voltage
  {
    size_t item_size = sizeof(ros_message->driver_voltage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: driver_temperature
  {
    size_t item_size = sizeof(ros_message->driver_temperature);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: driver_state
  {
    size_t item_size = sizeof(ros_message->driver_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_temperature
  {
    size_t item_size = sizeof(ros_message->motor_temperature);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: rpm
  {
    size_t item_size = sizeof(ros_message->rpm);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: current
  {
    size_t item_size = sizeof(ros_message->current);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: pulse_count
  {
    size_t item_size = sizeof(ros_message->pulse_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_angles
  {
    size_t item_size = sizeof(ros_message->motor_angles);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_speeds
  {
    size_t item_size = sizeof(ros_message->motor_speeds);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_loads
  {
    size_t item_size = sizeof(ros_message->motor_loads);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_teleop_robot_bridge__msg__JointStatus(
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

  // Field name: driver_voltage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: driver_temperature
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: driver_state
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: motor_temperature
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: rpm
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: current
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: pulse_count
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: motor_angles
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: motor_speeds
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: motor_loads
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__JointStatus;
    is_plain =
      (
      offsetof(DataType, motor_loads) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_key_teleop_robot_bridge__msg__JointStatus(
  const teleop_robot_bridge__msg__JointStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: driver_voltage
  {
    cdr << ros_message->driver_voltage;
  }

  // Field name: driver_temperature
  {
    cdr << ros_message->driver_temperature;
  }

  // Field name: driver_state
  {
    cdr << ros_message->driver_state;
  }

  // Field name: motor_temperature
  {
    cdr << ros_message->motor_temperature;
  }

  // Field name: rpm
  {
    cdr << ros_message->rpm;
  }

  // Field name: current
  {
    cdr << ros_message->current;
  }

  // Field name: pulse_count
  {
    cdr << ros_message->pulse_count;
  }

  // Field name: motor_angles
  {
    cdr << ros_message->motor_angles;
  }

  // Field name: motor_speeds
  {
    cdr << ros_message->motor_speeds;
  }

  // Field name: motor_loads
  {
    cdr << ros_message->motor_loads;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_key_teleop_robot_bridge__msg__JointStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _JointStatus__ros_msg_type * ros_message = static_cast<const _JointStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: driver_voltage
  {
    size_t item_size = sizeof(ros_message->driver_voltage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: driver_temperature
  {
    size_t item_size = sizeof(ros_message->driver_temperature);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: driver_state
  {
    size_t item_size = sizeof(ros_message->driver_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_temperature
  {
    size_t item_size = sizeof(ros_message->motor_temperature);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: rpm
  {
    size_t item_size = sizeof(ros_message->rpm);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: current
  {
    size_t item_size = sizeof(ros_message->current);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: pulse_count
  {
    size_t item_size = sizeof(ros_message->pulse_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_angles
  {
    size_t item_size = sizeof(ros_message->motor_angles);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_speeds
  {
    size_t item_size = sizeof(ros_message->motor_speeds);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: motor_loads
  {
    size_t item_size = sizeof(ros_message->motor_loads);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_key_teleop_robot_bridge__msg__JointStatus(
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
  // Field name: driver_voltage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: driver_temperature
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: driver_state
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: motor_temperature
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: rpm
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: current
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: pulse_count
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: motor_angles
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: motor_speeds
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: motor_loads
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__JointStatus;
    is_plain =
      (
      offsetof(DataType, motor_loads) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _JointStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const teleop_robot_bridge__msg__JointStatus * ros_message = static_cast<const teleop_robot_bridge__msg__JointStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_teleop_robot_bridge__msg__JointStatus(ros_message, cdr);
}

static bool _JointStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  teleop_robot_bridge__msg__JointStatus * ros_message = static_cast<teleop_robot_bridge__msg__JointStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_teleop_robot_bridge__msg__JointStatus(cdr, ros_message);
}

static uint32_t _JointStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_teleop_robot_bridge__msg__JointStatus(
      untyped_ros_message, 0));
}

static size_t _JointStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_teleop_robot_bridge__msg__JointStatus(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_JointStatus = {
  "teleop_robot_bridge::msg",
  "JointStatus",
  _JointStatus__cdr_serialize,
  _JointStatus__cdr_deserialize,
  _JointStatus__get_serialized_size,
  _JointStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _JointStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_JointStatus,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__JointStatus__get_type_hash,
  &teleop_robot_bridge__msg__JointStatus__get_type_description,
  &teleop_robot_bridge__msg__JointStatus__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, teleop_robot_bridge, msg, JointStatus)() {
  return &_JointStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
