// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__rosidl_typesupport_fastrtps_cpp.hpp"
#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__functions.h"
#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__struct.hpp"

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
namespace sensor_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const sensor_msgs::msg::Range &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  sensor_msgs::msg::Range &);
size_t get_serialized_size(
  const sensor_msgs::msg::Range &,
  size_t current_alignment);
size_t
max_serialized_size_Range(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
bool cdr_serialize_key(
  const sensor_msgs::msg::Range &,
  eprosima::fastcdr::Cdr &);
size_t get_serialized_size_key(
  const sensor_msgs::msg::Range &,
  size_t current_alignment);
size_t
max_serialized_size_key_Range(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace sensor_msgs


namespace teleop_robot_bridge
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_serialize(
  const teleop_robot_bridge::msg::AgvUltrasonic & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: ranges
  {
    for (size_t i = 0; i < 8; i++) {
      sensor_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.ranges[i],
        cdr);
    }
  }

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  teleop_robot_bridge::msg::AgvUltrasonic & ros_message)
{
  // Member: ranges
  {
    for (size_t i = 0; i < 8; i++) {
      sensor_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr,
        ros_message.ranges[i]);
    }
  }

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
get_serialized_size(
  const teleop_robot_bridge::msg::AgvUltrasonic & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: ranges
  {
    size_t array_size = 8;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        sensor_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.ranges[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
max_serialized_size_AgvUltrasonic(
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

  // Member: ranges
  {
    size_t array_size = 8;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        sensor_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Range(
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
    using DataType = teleop_robot_bridge::msg::AgvUltrasonic;
    is_plain =
      (
      offsetof(DataType, ranges) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_serialize_key(
  const teleop_robot_bridge::msg::AgvUltrasonic & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: ranges
  {
    for (size_t i = 0; i < 8; i++) {
      sensor_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize_key(
        ros_message.ranges[i],
        cdr);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
get_serialized_size_key(
  const teleop_robot_bridge::msg::AgvUltrasonic & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: ranges
  {
    size_t array_size = 8;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        sensor_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size_key(
        ros_message.ranges[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
max_serialized_size_key_AgvUltrasonic(
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

  // Member: ranges
  {
    size_t array_size = 8;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        sensor_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_key_Range(
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
    using DataType = teleop_robot_bridge::msg::AgvUltrasonic;
    is_plain =
      (
      offsetof(DataType, ranges) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _AgvUltrasonic__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const teleop_robot_bridge::msg::AgvUltrasonic *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _AgvUltrasonic__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<teleop_robot_bridge::msg::AgvUltrasonic *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _AgvUltrasonic__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const teleop_robot_bridge::msg::AgvUltrasonic *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _AgvUltrasonic__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_AgvUltrasonic(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _AgvUltrasonic__callbacks = {
  "teleop_robot_bridge::msg",
  "AgvUltrasonic",
  _AgvUltrasonic__cdr_serialize,
  _AgvUltrasonic__cdr_deserialize,
  _AgvUltrasonic__get_serialized_size,
  _AgvUltrasonic__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _AgvUltrasonic__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_AgvUltrasonic__callbacks,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__AgvUltrasonic__get_type_hash,
  &teleop_robot_bridge__msg__AgvUltrasonic__get_type_description,
  &teleop_robot_bridge__msg__AgvUltrasonic__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::AgvUltrasonic>()
{
  return &teleop_robot_bridge::msg::typesupport_fastrtps_cpp::_AgvUltrasonic__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, teleop_robot_bridge, msg, AgvUltrasonic)() {
  return &teleop_robot_bridge::msg::typesupport_fastrtps_cpp::_AgvUltrasonic__handle;
}

#ifdef __cplusplus
}
#endif
