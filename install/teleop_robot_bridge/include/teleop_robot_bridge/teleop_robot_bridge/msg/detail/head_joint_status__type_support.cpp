// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/HeadJointStatus.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/head_joint_status__functions.h"
#include "teleop_robot_bridge/msg/detail/head_joint_status__struct.hpp"
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

void HeadJointStatus_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::HeadJointStatus(_init);
}

void HeadJointStatus_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::HeadJointStatus *>(message_memory);
  typed_message->~HeadJointStatus();
}

size_t size_function__HeadJointStatus__name(const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * get_const_function__HeadJointStatus__name(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<std::string, 2> *>(untyped_member);
  return &member[index];
}

void * get_function__HeadJointStatus__name(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<std::string, 2> *>(untyped_member);
  return &member[index];
}

void fetch_function__HeadJointStatus__name(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__HeadJointStatus__name(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__HeadJointStatus__name(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__HeadJointStatus__name(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

size_t size_function__HeadJointStatus__joint_status(const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * get_const_function__HeadJointStatus__joint_status(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<teleop_robot_bridge::msg::JointStatus, 2> *>(untyped_member);
  return &member[index];
}

void * get_function__HeadJointStatus__joint_status(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<teleop_robot_bridge::msg::JointStatus, 2> *>(untyped_member);
  return &member[index];
}

void fetch_function__HeadJointStatus__joint_status(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const teleop_robot_bridge::msg::JointStatus *>(
    get_const_function__HeadJointStatus__joint_status(untyped_member, index));
  auto & value = *reinterpret_cast<teleop_robot_bridge::msg::JointStatus *>(untyped_value);
  value = item;
}

void assign_function__HeadJointStatus__joint_status(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<teleop_robot_bridge::msg::JointStatus *>(
    get_function__HeadJointStatus__joint_status(untyped_member, index));
  const auto & value = *reinterpret_cast<const teleop_robot_bridge::msg::JointStatus *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember HeadJointStatus_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::HeadJointStatus, header),  // bytes offset in struct
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
    2,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::HeadJointStatus, name),  // bytes offset in struct
    nullptr,  // default value
    size_function__HeadJointStatus__name,  // size() function pointer
    get_const_function__HeadJointStatus__name,  // get_const(index) function pointer
    get_function__HeadJointStatus__name,  // get(index) function pointer
    fetch_function__HeadJointStatus__name,  // fetch(index, &value) function pointer
    assign_function__HeadJointStatus__name,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "joint_status",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<teleop_robot_bridge::msg::JointStatus>(),  // members of sub message
    false,  // is key
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::HeadJointStatus, joint_status),  // bytes offset in struct
    nullptr,  // default value
    size_function__HeadJointStatus__joint_status,  // size() function pointer
    get_const_function__HeadJointStatus__joint_status,  // get_const(index) function pointer
    get_function__HeadJointStatus__joint_status,  // get(index) function pointer
    fetch_function__HeadJointStatus__joint_status,  // fetch(index, &value) function pointer
    assign_function__HeadJointStatus__joint_status,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers HeadJointStatus_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "HeadJointStatus",  // message name
  3,  // number of fields
  sizeof(teleop_robot_bridge::msg::HeadJointStatus),
  false,  // has_any_key_member_
  HeadJointStatus_message_member_array,  // message members
  HeadJointStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  HeadJointStatus_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t HeadJointStatus_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &HeadJointStatus_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__HeadJointStatus__get_type_hash,
  &teleop_robot_bridge__msg__HeadJointStatus__get_type_description,
  &teleop_robot_bridge__msg__HeadJointStatus__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::HeadJointStatus>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::HeadJointStatus_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, HeadJointStatus)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::HeadJointStatus_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
