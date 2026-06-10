// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/WaistTcpCommand.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/waist_tcp_command__functions.h"
#include "teleop_robot_bridge/msg/detail/waist_tcp_command__struct.hpp"
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

void WaistTcpCommand_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::WaistTcpCommand(_init);
}

void WaistTcpCommand_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::WaistTcpCommand *>(message_memory);
  typed_message->~WaistTcpCommand();
}

size_t size_function__WaistTcpCommand__name(const void * untyped_member)
{
  (void)untyped_member;
  return 1;
}

const void * get_const_function__WaistTcpCommand__name(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<std::string, 1> *>(untyped_member);
  return &member[index];
}

void * get_function__WaistTcpCommand__name(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<std::string, 1> *>(untyped_member);
  return &member[index];
}

void fetch_function__WaistTcpCommand__name(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__WaistTcpCommand__name(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__WaistTcpCommand__name(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__WaistTcpCommand__name(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

size_t size_function__WaistTcpCommand__position(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__WaistTcpCommand__position(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__WaistTcpCommand__position(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__WaistTcpCommand__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__WaistTcpCommand__position(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__WaistTcpCommand__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__WaistTcpCommand__position(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__WaistTcpCommand__euler(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__WaistTcpCommand__euler(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__WaistTcpCommand__euler(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__WaistTcpCommand__euler(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__WaistTcpCommand__euler(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__WaistTcpCommand__euler(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__WaistTcpCommand__euler(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__WaistTcpCommand__quat(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__WaistTcpCommand__quat(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__WaistTcpCommand__quat(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__WaistTcpCommand__quat(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__WaistTcpCommand__quat(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__WaistTcpCommand__quat(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__WaistTcpCommand__quat(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember WaistTcpCommand_message_member_array[5] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::WaistTcpCommand, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::WaistTcpCommand, name),  // bytes offset in struct
    nullptr,  // default value
    size_function__WaistTcpCommand__name,  // size() function pointer
    get_const_function__WaistTcpCommand__name,  // get_const(index) function pointer
    get_function__WaistTcpCommand__name,  // get(index) function pointer
    fetch_function__WaistTcpCommand__name,  // fetch(index, &value) function pointer
    assign_function__WaistTcpCommand__name,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::WaistTcpCommand, position),  // bytes offset in struct
    nullptr,  // default value
    size_function__WaistTcpCommand__position,  // size() function pointer
    get_const_function__WaistTcpCommand__position,  // get_const(index) function pointer
    get_function__WaistTcpCommand__position,  // get(index) function pointer
    fetch_function__WaistTcpCommand__position,  // fetch(index, &value) function pointer
    assign_function__WaistTcpCommand__position,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "euler",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::WaistTcpCommand, euler),  // bytes offset in struct
    nullptr,  // default value
    size_function__WaistTcpCommand__euler,  // size() function pointer
    get_const_function__WaistTcpCommand__euler,  // get_const(index) function pointer
    get_function__WaistTcpCommand__euler,  // get(index) function pointer
    fetch_function__WaistTcpCommand__euler,  // fetch(index, &value) function pointer
    assign_function__WaistTcpCommand__euler,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "quat",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::WaistTcpCommand, quat),  // bytes offset in struct
    nullptr,  // default value
    size_function__WaistTcpCommand__quat,  // size() function pointer
    get_const_function__WaistTcpCommand__quat,  // get_const(index) function pointer
    get_function__WaistTcpCommand__quat,  // get(index) function pointer
    fetch_function__WaistTcpCommand__quat,  // fetch(index, &value) function pointer
    assign_function__WaistTcpCommand__quat,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers WaistTcpCommand_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "WaistTcpCommand",  // message name
  5,  // number of fields
  sizeof(teleop_robot_bridge::msg::WaistTcpCommand),
  false,  // has_any_key_member_
  WaistTcpCommand_message_member_array,  // message members
  WaistTcpCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  WaistTcpCommand_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t WaistTcpCommand_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &WaistTcpCommand_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__WaistTcpCommand__get_type_hash,
  &teleop_robot_bridge__msg__WaistTcpCommand__get_type_description,
  &teleop_robot_bridge__msg__WaistTcpCommand__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::WaistTcpCommand>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::WaistTcpCommand_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, WaistTcpCommand)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::WaistTcpCommand_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
