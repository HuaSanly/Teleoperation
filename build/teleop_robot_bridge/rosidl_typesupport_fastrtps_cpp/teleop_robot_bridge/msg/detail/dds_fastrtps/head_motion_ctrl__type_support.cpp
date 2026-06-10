// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/HeadMotionCtrl.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/head_motion_ctrl__rosidl_typesupport_fastrtps_cpp.hpp"
#include "teleop_robot_bridge/msg/detail/head_motion_ctrl__functions.h"
#include "teleop_robot_bridge/msg/detail/head_motion_ctrl__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace teleop_robot_bridge
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_serialize(
  const teleop_robot_bridge::msg::HeadMotionCtrl & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: enable_states
  {
    cdr << ros_message.enable_states;
  }

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  teleop_robot_bridge::msg::HeadMotionCtrl & ros_message)
{
  // Member: enable_states
  {
    cdr >> ros_message.enable_states;
  }

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
get_serialized_size(
  const teleop_robot_bridge::msg::HeadMotionCtrl & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: enable_states
  {
    size_t array_size = 3;
    size_t item_size = sizeof(ros_message.enable_states[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
max_serialized_size_HeadMotionCtrl(
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

  // Member: enable_states
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge::msg::HeadMotionCtrl;
    is_plain =
      (
      offsetof(DataType, enable_states) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_serialize_key(
  const teleop_robot_bridge::msg::HeadMotionCtrl & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: enable_states
  {
    cdr << ros_message.enable_states;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
get_serialized_size_key(
  const teleop_robot_bridge::msg::HeadMotionCtrl & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: enable_states
  {
    size_t array_size = 3;
    size_t item_size = sizeof(ros_message.enable_states[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
max_serialized_size_key_HeadMotionCtrl(
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

  // Member: enable_states
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge::msg::HeadMotionCtrl;
    is_plain =
      (
      offsetof(DataType, enable_states) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _HeadMotionCtrl__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const teleop_robot_bridge::msg::HeadMotionCtrl *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _HeadMotionCtrl__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<teleop_robot_bridge::msg::HeadMotionCtrl *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _HeadMotionCtrl__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const teleop_robot_bridge::msg::HeadMotionCtrl *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _HeadMotionCtrl__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_HeadMotionCtrl(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _HeadMotionCtrl__callbacks = {
  "teleop_robot_bridge::msg",
  "HeadMotionCtrl",
  _HeadMotionCtrl__cdr_serialize,
  _HeadMotionCtrl__cdr_deserialize,
  _HeadMotionCtrl__get_serialized_size,
  _HeadMotionCtrl__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _HeadMotionCtrl__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_HeadMotionCtrl__callbacks,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__HeadMotionCtrl__get_type_hash,
  &teleop_robot_bridge__msg__HeadMotionCtrl__get_type_description,
  &teleop_robot_bridge__msg__HeadMotionCtrl__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::HeadMotionCtrl>()
{
  return &teleop_robot_bridge::msg::typesupport_fastrtps_cpp::_HeadMotionCtrl__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, teleop_robot_bridge, msg, HeadMotionCtrl)() {
  return &teleop_robot_bridge::msg::typesupport_fastrtps_cpp::_HeadMotionCtrl__handle;
}

#ifdef __cplusplus
}
#endif
