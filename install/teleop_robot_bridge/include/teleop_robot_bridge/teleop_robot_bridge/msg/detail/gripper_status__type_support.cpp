// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/gripper_status__functions.h"
#include "teleop_robot_bridge/msg/detail/gripper_status__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace teleop_robot_bridge
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void GripperStatus_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::GripperStatus(_init);
}

void GripperStatus_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::GripperStatus *>(message_memory);
  typed_message->~GripperStatus();
}

size_t size_function__GripperStatus__grippers(const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * get_const_function__GripperStatus__grippers(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<teleop_robot_bridge::msg::SingleGripperStatus, 2> *>(untyped_member);
  return &member[index];
}

void * get_function__GripperStatus__grippers(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<teleop_robot_bridge::msg::SingleGripperStatus, 2> *>(untyped_member);
  return &member[index];
}

void fetch_function__GripperStatus__grippers(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const teleop_robot_bridge::msg::SingleGripperStatus *>(
    get_const_function__GripperStatus__grippers(untyped_member, index));
  auto & value = *reinterpret_cast<teleop_robot_bridge::msg::SingleGripperStatus *>(untyped_value);
  value = item;
}

void assign_function__GripperStatus__grippers(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<teleop_robot_bridge::msg::SingleGripperStatus *>(
    get_function__GripperStatus__grippers(untyped_member, index));
  const auto & value = *reinterpret_cast<const teleop_robot_bridge::msg::SingleGripperStatus *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GripperStatus_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::GripperStatus, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "grippers",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<teleop_robot_bridge::msg::SingleGripperStatus>(),  // members of sub message
    false,  // is key
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::GripperStatus, grippers),  // bytes offset in struct
    nullptr,  // default value
    size_function__GripperStatus__grippers,  // size() function pointer
    get_const_function__GripperStatus__grippers,  // get_const(index) function pointer
    get_function__GripperStatus__grippers,  // get(index) function pointer
    fetch_function__GripperStatus__grippers,  // fetch(index, &value) function pointer
    assign_function__GripperStatus__grippers,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GripperStatus_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "GripperStatus",  // message name
  2,  // number of fields
  sizeof(teleop_robot_bridge::msg::GripperStatus),
  false,  // has_any_key_member_
  GripperStatus_message_member_array,  // message members
  GripperStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  GripperStatus_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GripperStatus_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GripperStatus_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__GripperStatus__get_type_hash,
  &teleop_robot_bridge__msg__GripperStatus__get_type_description,
  &teleop_robot_bridge__msg__GripperStatus__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::GripperStatus>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::GripperStatus_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, GripperStatus)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::GripperStatus_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
