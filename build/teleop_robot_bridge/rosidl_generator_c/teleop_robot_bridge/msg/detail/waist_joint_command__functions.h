// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from teleop_robot_bridge:msg/WaistJointCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "teleop_robot_bridge/msg/waist_joint_command.h"


#ifndef TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_COMMAND__FUNCTIONS_H_
#define TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_COMMAND__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "teleop_robot_bridge/msg/rosidl_generator_c__visibility_control.h"

#include "teleop_robot_bridge/msg/detail/waist_joint_command__struct.h"

/// Initialize msg/WaistJointCommand message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * teleop_robot_bridge__msg__WaistJointCommand
 * )) before or use
 * teleop_robot_bridge__msg__WaistJointCommand__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
bool
teleop_robot_bridge__msg__WaistJointCommand__init(teleop_robot_bridge__msg__WaistJointCommand * msg);

/// Finalize msg/WaistJointCommand message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
void
teleop_robot_bridge__msg__WaistJointCommand__fini(teleop_robot_bridge__msg__WaistJointCommand * msg);

/// Create msg/WaistJointCommand message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * teleop_robot_bridge__msg__WaistJointCommand__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
teleop_robot_bridge__msg__WaistJointCommand *
teleop_robot_bridge__msg__WaistJointCommand__create(void);

/// Destroy msg/WaistJointCommand message.
/**
 * It calls
 * teleop_robot_bridge__msg__WaistJointCommand__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
void
teleop_robot_bridge__msg__WaistJointCommand__destroy(teleop_robot_bridge__msg__WaistJointCommand * msg);

/// Check for msg/WaistJointCommand message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
bool
teleop_robot_bridge__msg__WaistJointCommand__are_equal(const teleop_robot_bridge__msg__WaistJointCommand * lhs, const teleop_robot_bridge__msg__WaistJointCommand * rhs);

/// Copy a msg/WaistJointCommand message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
bool
teleop_robot_bridge__msg__WaistJointCommand__copy(
  const teleop_robot_bridge__msg__WaistJointCommand * input,
  teleop_robot_bridge__msg__WaistJointCommand * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_type_hash_t *
teleop_robot_bridge__msg__WaistJointCommand__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_runtime_c__type_description__TypeDescription *
teleop_robot_bridge__msg__WaistJointCommand__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_runtime_c__type_description__TypeSource *
teleop_robot_bridge__msg__WaistJointCommand__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
const rosidl_runtime_c__type_description__TypeSource__Sequence *
teleop_robot_bridge__msg__WaistJointCommand__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/WaistJointCommand messages.
/**
 * It allocates the memory for the number of elements and calls
 * teleop_robot_bridge__msg__WaistJointCommand__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
bool
teleop_robot_bridge__msg__WaistJointCommand__Sequence__init(teleop_robot_bridge__msg__WaistJointCommand__Sequence * array, size_t size);

/// Finalize array of msg/WaistJointCommand messages.
/**
 * It calls
 * teleop_robot_bridge__msg__WaistJointCommand__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
void
teleop_robot_bridge__msg__WaistJointCommand__Sequence__fini(teleop_robot_bridge__msg__WaistJointCommand__Sequence * array);

/// Create array of msg/WaistJointCommand messages.
/**
 * It allocates the memory for the array and calls
 * teleop_robot_bridge__msg__WaistJointCommand__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
teleop_robot_bridge__msg__WaistJointCommand__Sequence *
teleop_robot_bridge__msg__WaistJointCommand__Sequence__create(size_t size);

/// Destroy array of msg/WaistJointCommand messages.
/**
 * It calls
 * teleop_robot_bridge__msg__WaistJointCommand__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
void
teleop_robot_bridge__msg__WaistJointCommand__Sequence__destroy(teleop_robot_bridge__msg__WaistJointCommand__Sequence * array);

/// Check for msg/WaistJointCommand message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
bool
teleop_robot_bridge__msg__WaistJointCommand__Sequence__are_equal(const teleop_robot_bridge__msg__WaistJointCommand__Sequence * lhs, const teleop_robot_bridge__msg__WaistJointCommand__Sequence * rhs);

/// Copy an array of msg/WaistJointCommand messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleop_robot_bridge
bool
teleop_robot_bridge__msg__WaistJointCommand__Sequence__copy(
  const teleop_robot_bridge__msg__WaistJointCommand__Sequence * input,
  teleop_robot_bridge__msg__WaistJointCommand__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TELEOP_ROBOT_BRIDGE__MSG__DETAIL__WAIST_JOINT_COMMAND__FUNCTIONS_H_
