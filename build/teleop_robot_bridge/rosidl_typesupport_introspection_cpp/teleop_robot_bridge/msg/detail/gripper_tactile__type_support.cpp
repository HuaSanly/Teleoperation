// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/GripperTactile.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/gripper_tactile__functions.h"
#include "teleop_robot_bridge/msg/detail/gripper_tactile__struct.hpp"
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

void GripperTactile_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::GripperTactile(_init);
}

void GripperTactile_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::GripperTactile *>(message_memory);
  typed_message->~GripperTactile();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GripperTactile_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::GripperTactile, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "left",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<teleop_robot_bridge::msg::HandTactile>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::GripperTactile, left),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "right",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<teleop_robot_bridge::msg::HandTactile>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::GripperTactile, right),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GripperTactile_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "GripperTactile",  // message name
  3,  // number of fields
  sizeof(teleop_robot_bridge::msg::GripperTactile),
  false,  // has_any_key_member_
  GripperTactile_message_member_array,  // message members
  GripperTactile_init_function,  // function to initialize message memory (memory has to be allocated)
  GripperTactile_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GripperTactile_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GripperTactile_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__GripperTactile__get_type_hash,
  &teleop_robot_bridge__msg__GripperTactile__get_type_description,
  &teleop_robot_bridge__msg__GripperTactile__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::GripperTactile>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::GripperTactile_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, GripperTactile)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::GripperTactile_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
