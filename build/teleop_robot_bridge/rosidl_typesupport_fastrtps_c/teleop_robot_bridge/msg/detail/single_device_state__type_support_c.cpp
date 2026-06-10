// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from teleop_robot_bridge:msg/SingleDeviceState.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/single_device_state__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "teleop_robot_bridge/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "teleop_robot_bridge/msg/detail/single_device_state__struct.h"
#include "teleop_robot_bridge/msg/detail/single_device_state__functions.h"
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

#include "rosidl_runtime_c/primitives_sequence.h"  // error_domain
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // error_domain
#include "rosidl_runtime_c/string.h"  // firmware_version, manufacturer, model
#include "rosidl_runtime_c/string_functions.h"  // firmware_version, manufacturer, model

// forward declare type support functions


using _SingleDeviceState__ros_msg_type = teleop_robot_bridge__msg__SingleDeviceState;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_teleop_robot_bridge__msg__SingleDeviceState(
  const teleop_robot_bridge__msg__SingleDeviceState * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: health_status
  {
    cdr << ros_message->health_status;
  }

  // Field name: error_domain
  {
    size_t size = ros_message->error_domain.size;
    auto array_ptr = ros_message->error_domain.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: operational_mode
  {
    cdr << ros_message->operational_mode;
  }

  // Field name: power_state
  {
    cdr << ros_message->power_state;
  }

  // Field name: connectivity_status
  {
    cdr << ros_message->connectivity_status;
  }

  // Field name: manufacturer
  {
    const rosidl_runtime_c__String * str = &ros_message->manufacturer;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: model
  {
    const rosidl_runtime_c__String * str = &ros_message->model;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: firmware_version
  {
    const rosidl_runtime_c__String * str = &ros_message->firmware_version;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_deserialize_teleop_robot_bridge__msg__SingleDeviceState(
  eprosima::fastcdr::Cdr & cdr,
  teleop_robot_bridge__msg__SingleDeviceState * ros_message)
{
  // Field name: health_status
  {
    cdr >> ros_message->health_status;
  }

  // Field name: error_domain
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.get_state();
    bool correct_size = cdr.jump(size);
    cdr.set_state(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->error_domain.data) {
      rosidl_runtime_c__uint8__Sequence__fini(&ros_message->error_domain);
    }
    if (!rosidl_runtime_c__uint8__Sequence__init(&ros_message->error_domain, size)) {
      fprintf(stderr, "failed to create array for field 'error_domain'");
      return false;
    }
    auto array_ptr = ros_message->error_domain.data;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: operational_mode
  {
    cdr >> ros_message->operational_mode;
  }

  // Field name: power_state
  {
    cdr >> ros_message->power_state;
  }

  // Field name: connectivity_status
  {
    cdr >> ros_message->connectivity_status;
  }

  // Field name: manufacturer
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->manufacturer.data) {
      rosidl_runtime_c__String__init(&ros_message->manufacturer);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->manufacturer,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'manufacturer'\n");
      return false;
    }
  }

  // Field name: model
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->model.data) {
      rosidl_runtime_c__String__init(&ros_message->model);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->model,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'model'\n");
      return false;
    }
  }

  // Field name: firmware_version
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->firmware_version.data) {
      rosidl_runtime_c__String__init(&ros_message->firmware_version);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->firmware_version,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'firmware_version'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_teleop_robot_bridge__msg__SingleDeviceState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SingleDeviceState__ros_msg_type * ros_message = static_cast<const _SingleDeviceState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: health_status
  {
    size_t item_size = sizeof(ros_message->health_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: error_domain
  {
    size_t array_size = ros_message->error_domain.size;
    auto array_ptr = ros_message->error_domain.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: operational_mode
  {
    size_t item_size = sizeof(ros_message->operational_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: power_state
  {
    size_t item_size = sizeof(ros_message->power_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: connectivity_status
  {
    size_t item_size = sizeof(ros_message->connectivity_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: manufacturer
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->manufacturer.size + 1);

  // Field name: model
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->model.size + 1);

  // Field name: firmware_version
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->firmware_version.size + 1);

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_teleop_robot_bridge__msg__SingleDeviceState(
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

  // Field name: health_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: error_domain
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: operational_mode
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: power_state
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: connectivity_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: manufacturer
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: model
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: firmware_version
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__SingleDeviceState;
    is_plain =
      (
      offsetof(DataType, firmware_version) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
bool cdr_serialize_key_teleop_robot_bridge__msg__SingleDeviceState(
  const teleop_robot_bridge__msg__SingleDeviceState * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: health_status
  {
    cdr << ros_message->health_status;
  }

  // Field name: error_domain
  {
    size_t size = ros_message->error_domain.size;
    auto array_ptr = ros_message->error_domain.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: operational_mode
  {
    cdr << ros_message->operational_mode;
  }

  // Field name: power_state
  {
    cdr << ros_message->power_state;
  }

  // Field name: connectivity_status
  {
    cdr << ros_message->connectivity_status;
  }

  // Field name: manufacturer
  {
    const rosidl_runtime_c__String * str = &ros_message->manufacturer;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: model
  {
    const rosidl_runtime_c__String * str = &ros_message->model;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: firmware_version
  {
    const rosidl_runtime_c__String * str = &ros_message->firmware_version;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t get_serialized_size_key_teleop_robot_bridge__msg__SingleDeviceState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SingleDeviceState__ros_msg_type * ros_message = static_cast<const _SingleDeviceState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: health_status
  {
    size_t item_size = sizeof(ros_message->health_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: error_domain
  {
    size_t array_size = ros_message->error_domain.size;
    auto array_ptr = ros_message->error_domain.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: operational_mode
  {
    size_t item_size = sizeof(ros_message->operational_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: power_state
  {
    size_t item_size = sizeof(ros_message->power_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: connectivity_status
  {
    size_t item_size = sizeof(ros_message->connectivity_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: manufacturer
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->manufacturer.size + 1);

  // Field name: model
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->model.size + 1);

  // Field name: firmware_version
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->firmware_version.size + 1);

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleop_robot_bridge
size_t max_serialized_size_key_teleop_robot_bridge__msg__SingleDeviceState(
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
  // Field name: health_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: error_domain
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: operational_mode
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: power_state
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: connectivity_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: manufacturer
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: model
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: firmware_version
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleop_robot_bridge__msg__SingleDeviceState;
    is_plain =
      (
      offsetof(DataType, firmware_version) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _SingleDeviceState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const teleop_robot_bridge__msg__SingleDeviceState * ros_message = static_cast<const teleop_robot_bridge__msg__SingleDeviceState *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_teleop_robot_bridge__msg__SingleDeviceState(ros_message, cdr);
}

static bool _SingleDeviceState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  teleop_robot_bridge__msg__SingleDeviceState * ros_message = static_cast<teleop_robot_bridge__msg__SingleDeviceState *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_teleop_robot_bridge__msg__SingleDeviceState(cdr, ros_message);
}

static uint32_t _SingleDeviceState__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_teleop_robot_bridge__msg__SingleDeviceState(
      untyped_ros_message, 0));
}

static size_t _SingleDeviceState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_teleop_robot_bridge__msg__SingleDeviceState(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SingleDeviceState = {
  "teleop_robot_bridge::msg",
  "SingleDeviceState",
  _SingleDeviceState__cdr_serialize,
  _SingleDeviceState__cdr_deserialize,
  _SingleDeviceState__get_serialized_size,
  _SingleDeviceState__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _SingleDeviceState__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SingleDeviceState,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__SingleDeviceState__get_type_hash,
  &teleop_robot_bridge__msg__SingleDeviceState__get_type_description,
  &teleop_robot_bridge__msg__SingleDeviceState__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, teleop_robot_bridge, msg, SingleDeviceState)() {
  return &_SingleDeviceState__type_support;
}

#if defined(__cplusplus)
}
#endif
