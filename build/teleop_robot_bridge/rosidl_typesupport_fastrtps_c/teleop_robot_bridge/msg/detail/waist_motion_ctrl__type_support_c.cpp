// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from teleop_robot_bridge:msg/WaistMotionCtrl.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/waist_motion_ctrl__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "teleop_robot_bridge/msg/detail/waist_motion_ctrl__struct.h"
#include "teleop_robot_bridge/msg/detail/waist_motion_ctrl__functions.h"
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


using _WaistMotionCtrl__ros_msg_type = teleop_robot_bridge__msg__WaistMotionCtrl;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_teleop_robot_bridge__msg__WaistMotionCtrl(
  const teleop_robot_bridge__msg__WaistMotionCtrl * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: enable_states
  {
    size_t size = 4;
    auto array_ptr = ros_message->enable_states;
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_deserialize_teleop_robot_bridge__msg__WaistMotionCtrl(
  eprosima::fastcdr::Cdr & cdr,
  teleop_robot_bridge__msg__WaistMotionCtrl * ros_message)
{
  // Field name: enable_states
  {
    size_t size = 4;
    auto array_ptr = ros_message->enable_states;
    for (size_t i = 0; i < size; ++i) {
      uint8_t tmp;
      cdr >> tmp;
      array_ptr[i] = tmp ? true : false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_teleop_robot_bridge__msg__WaistMotionCtrl(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _WaistMotionCtrl__ros_msg_type * ros_message = static_cast<const _WaistMotionCtrl__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: enable_states
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->enable_states;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_teleop_robot_bridge__msg__WaistMotionCtrl(
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

  // Field name: enable_states
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__WaistMotionCtrl;
    is_plain =
      (
      offsetof(DataType, enable_states) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_key_teleop_robot_bridge__msg__WaistMotionCtrl(
  const teleop_robot_bridge__msg__WaistMotionCtrl * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: enable_states
  {
    size_t size = 4;
    auto array_ptr = ros_message->enable_states;
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_key_teleop_robot_bridge__msg__WaistMotionCtrl(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _WaistMotionCtrl__ros_msg_type * ros_message = static_cast<const _WaistMotionCtrl__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: enable_states
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->enable_states;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_key_teleop_robot_bridge__msg__WaistMotionCtrl(
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
  // Field name: enable_states
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__WaistMotionCtrl;
    is_plain =
      (
      offsetof(DataType, enable_states) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _WaistMotionCtrl__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const teleop_robot_bridge__msg__WaistMotionCtrl * ros_message = static_cast<const teleop_robot_bridge__msg__WaistMotionCtrl *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_teleop_robot_bridge__msg__WaistMotionCtrl(ros_message, cdr);
}

static bool _WaistMotionCtrl__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  teleop_robot_bridge__msg__WaistMotionCtrl * ros_message = static_cast<teleop_robot_bridge__msg__WaistMotionCtrl *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_teleop_robot_bridge__msg__WaistMotionCtrl(cdr, ros_message);
}

static uint32_t _WaistMotionCtrl__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_teleop_robot_bridge__msg__WaistMotionCtrl(
      untyped_ros_message, 0));
}

static size_t _WaistMotionCtrl__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_teleop_robot_bridge__msg__WaistMotionCtrl(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_WaistMotionCtrl = {
  "teleop_robot_bridge::msg",
  "WaistMotionCtrl",
  _WaistMotionCtrl__cdr_serialize,
  _WaistMotionCtrl__cdr_deserialize,
  _WaistMotionCtrl__get_serialized_size,
  _WaistMotionCtrl__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _WaistMotionCtrl__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_WaistMotionCtrl,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__WaistMotionCtrl__get_type_hash,
  &teleop_robot_bridge__msg__WaistMotionCtrl__get_type_description,
  &teleop_robot_bridge__msg__WaistMotionCtrl__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, teleop_robot_bridge, msg, WaistMotionCtrl)() {
  return &_WaistMotionCtrl__type_support;
}

#if defined(__cplusplus)
}
#endif
