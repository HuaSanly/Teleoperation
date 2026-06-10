// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from teleop_robot_bridge:msg/UpperBodyDeviceState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "teleop_robot_bridge/msg/detail/upper_body_device_state__functions.h"
#include "teleop_robot_bridge/msg/detail/upper_body_device_state__struct.hpp"
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

void UpperBodyDeviceState_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) teleop_robot_bridge::msg::UpperBodyDeviceState(_init);
}

void UpperBodyDeviceState_fini_function(void * message_memory)
{
  auto typed_message = static_cast<teleop_robot_bridge::msg::UpperBodyDeviceState *>(message_memory);
  typed_message->~UpperBodyDeviceState();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember UpperBodyDeviceState_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::UpperBodyDeviceState, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "device_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<teleop_robot_bridge::msg::SingleDeviceState>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleop_robot_bridge::msg::UpperBodyDeviceState, device_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers UpperBodyDeviceState_message_members = {
  "teleop_robot_bridge::msg",  // message namespace
  "UpperBodyDeviceState",  // message name
  2,  // number of fields
  sizeof(teleop_robot_bridge::msg::UpperBodyDeviceState),
  false,  // has_any_key_member_
  UpperBodyDeviceState_message_member_array,  // message members
  UpperBodyDeviceState_init_function,  // function to initialize message memory (memory has to be allocated)
  UpperBodyDeviceState_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t UpperBodyDeviceState_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &UpperBodyDeviceState_message_members,
  get_message_typesupport_handle_function,
  &teleop_robot_bridge__msg__UpperBodyDeviceState__get_type_hash,
  &teleop_robot_bridge__msg__UpperBodyDeviceState__get_type_description,
  &teleop_robot_bridge__msg__UpperBodyDeviceState__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace teleop_robot_bridge


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<teleop_robot_bridge::msg::UpperBodyDeviceState>()
{
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::UpperBodyDeviceState_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, teleop_robot_bridge, msg, UpperBodyDeviceState)() {
  return &::teleop_robot_bridge::msg::rosidl_typesupport_introspection_cpp::UpperBodyDeviceState_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
