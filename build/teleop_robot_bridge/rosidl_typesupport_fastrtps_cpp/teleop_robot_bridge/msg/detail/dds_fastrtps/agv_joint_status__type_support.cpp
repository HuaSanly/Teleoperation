// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/AgvJointStatus.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/agv_joint_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "teleop_robot_bridge/msg/detail/agv_joint_status__functions.h"
#include "teleop_robot_bridge/msg/detail/agv_joint_status__struct.hpp"

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
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
bool cdr_serialize_key(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
size_t get_serialized_size_key(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_key_Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs

namespace teleop_robot_bridge
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const teleop_robot_bridge::msg::JointStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  teleop_robot_bridge::msg::JointStatus &);
size_t get_serialized_size(
  const teleop_robot_bridge::msg::JointStatus &,
  size_t current_alignment);
size_t
max_serialized_size_JointStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
bool cdr_serialize_key(
  const teleop_robot_bridge::msg::JointStatus &,
  eprosima::fastcdr::Cdr &);
size_t get_serialized_size_key(
  const teleop_robot_bridge::msg::JointStatus &,
  size_t current_alignment);
size_t
max_serialized_size_key_JointStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace teleop_robot_bridge


namespace teleop_robot_bridge
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_serialize(
  const teleop_robot_bridge::msg::AgvJointStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);

  // Member: name
  {
    cdr << ros_message.name;
  }

  // Member: joint_status
  {
    for (size_t i = 0; i < 4; i++) {
      teleop_robot_bridge::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.joint_status[i],
        cdr);
    }
  }

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  teleop_robot_bridge::msg::AgvJointStatus & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: name
  {
    cdr >> ros_message.name;
  }

  // Member: joint_status
  {
    for (size_t i = 0; i < 4; i++) {
      teleop_robot_bridge::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr,
        ros_message.joint_status[i]);
    }
  }

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
get_serialized_size(
  const teleop_robot_bridge::msg::AgvJointStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header
  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);

  // Member: name
  {
    size_t array_size = 4;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.name[index].size() + 1);
    }
  }

  // Member: joint_status
  {
    size_t array_size = 4;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        teleop_robot_bridge::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.joint_status[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
max_serialized_size_AgvJointStatus(
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

  // Member: header
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // Member: name
  {
    size_t array_size = 4;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // Member: joint_status
  {
    size_t array_size = 4;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        teleop_robot_bridge::msg::typesupport_fastrtps_cpp::max_serialized_size_JointStatus(
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
    using DataType = teleop_robot_bridge::msg::AgvJointStatus;
    is_plain =
      (
      offsetof(DataType, joint_status) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
cdr_serialize_key(
  const teleop_robot_bridge::msg::AgvJointStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize_key(
    ros_message.header,
    cdr);

  // Member: name
  {
    cdr << ros_message.name;
  }

  // Member: joint_status
  {
    for (size_t i = 0; i < 4; i++) {
      teleop_robot_bridge::msg::typesupport_fastrtps_cpp::cdr_serialize_key(
        ros_message.joint_status[i],
        cdr);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
get_serialized_size_key(
  const teleop_robot_bridge::msg::AgvJointStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header
  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size_key(
    ros_message.header, current_alignment);

  // Member: name
  {
    size_t array_size = 4;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.name[index].size() + 1);
    }
  }

  // Member: joint_status
  {
    size_t array_size = 4;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        teleop_robot_bridge::msg::typesupport_fastrtps_cpp::get_serialized_size_key(
        ros_message.joint_status[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleop_robot_bridge
max_serialized_size_key_AgvJointStatus(
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

  // Member: header
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_key_Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: name
  {
    size_t array_size = 4;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: joint_status
  {
    size_t array_size = 4;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        teleop_robot_bridge::msg::typesupport_fastrtps_cpp::max_serialized_size_key_JointStatus(
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
    using DataType = teleop_robot_bridge::msg::AgvJointStatus;
    is_plain =
      (
      offsetof(DataType, joint_status) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _AgvJointStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const teleop_robot_bridge::msg::AgvJointStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _AgvJointStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<teleop_robot_bridge::msg::AgvJointStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _AgvJointStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const teleop_robot_bridge::msg::AgvJointStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _AgvJointStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_AgvJointStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _AgvJointStatus__callbacks = {
  "teleop_robot_bridge::msg",
  "AgvJointStatus",
  _AgvJointStatus__cdr_serialize,
  _AgvJointStatus__cdr_deserialize,
  _AgvJointStatus__get_serialized_size,
  _AgvJointStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _AgvJointStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_AgvJointStatus__callbacks,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__AgvJointStatus__get_type_hash,
  &teleop_robot_bridge__msg__AgvJointStatus__get_type_description,
  &teleop_robot_bridge__msg__AgvJointStatus__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_teleop_robot_bridge
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::AgvJointStatus>()
{
  return &teleop_robot_bridge::msg::typesupport_fastrtps_cpp::_AgvJointStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, teleop_robot_bridge, msg, AgvJointStatus)() {
  return &teleop_robot_bridge::msg::typesupport_fastrtps_cpp::_AgvJointStatus__handle;
}

#ifdef __cplusplus
}
#endif
