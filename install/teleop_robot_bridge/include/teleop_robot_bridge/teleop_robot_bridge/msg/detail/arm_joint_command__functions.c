// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/ArmJointCommand.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/arm_joint_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

bool
teleop_robot_bridge__msg__ArmJointCommand__init(teleop_robot_bridge__msg__ArmJointCommand * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    teleop_robot_bridge__msg__ArmJointCommand__fini(msg);
    return false;
  }
  // name
  for (size_t i = 0; i < 14; ++i) {
    if (!rosidl_runtime_c__String__init(&msg->name[i])) {
      teleop_robot_bridge__msg__ArmJointCommand__fini(msg);
      return false;
    }
  }
  // position
  // velocity
  // effort
  return true;
}

void
teleop_robot_bridge__msg__ArmJointCommand__fini(teleop_robot_bridge__msg__ArmJointCommand * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // name
  for (size_t i = 0; i < 14; ++i) {
    rosidl_runtime_c__String__fini(&msg->name[i]);
  }
  // position
  // velocity
  // effort
}

bool
teleop_robot_bridge__msg__ArmJointCommand__are_equal(const teleop_robot_bridge__msg__ArmJointCommand * lhs, const teleop_robot_bridge__msg__ArmJointCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // name
  for (size_t i = 0; i < 14; ++i) {
    if (!rosidl_runtime_c__String__are_equal(
        &(lhs->name[i]), &(rhs->name[i])))
    {
      return false;
    }
  }
  // position
  for (size_t i = 0; i < 14; ++i) {
    if (lhs->position[i] != rhs->position[i]) {
      return false;
    }
  }
  // velocity
  for (size_t i = 0; i < 14; ++i) {
    if (lhs->velocity[i] != rhs->velocity[i]) {
      return false;
    }
  }
  // effort
  for (size_t i = 0; i < 14; ++i) {
    if (lhs->effort[i] != rhs->effort[i]) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__ArmJointCommand__copy(
  const teleop_robot_bridge__msg__ArmJointCommand * input,
  teleop_robot_bridge__msg__ArmJointCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // name
  for (size_t i = 0; i < 14; ++i) {
    if (!rosidl_runtime_c__String__copy(
        &(input->name[i]), &(output->name[i])))
    {
      return false;
    }
  }
  // position
  for (size_t i = 0; i < 14; ++i) {
    output->position[i] = input->position[i];
  }
  // velocity
  for (size_t i = 0; i < 14; ++i) {
    output->velocity[i] = input->velocity[i];
  }
  // effort
  for (size_t i = 0; i < 14; ++i) {
    output->effort[i] = input->effort[i];
  }
  return true;
}

teleop_robot_bridge__msg__ArmJointCommand *
teleop_robot_bridge__msg__ArmJointCommand__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__ArmJointCommand * msg = (teleop_robot_bridge__msg__ArmJointCommand *)allocator.allocate(sizeof(teleop_robot_bridge__msg__ArmJointCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__ArmJointCommand));
  bool success = teleop_robot_bridge__msg__ArmJointCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__ArmJointCommand__destroy(teleop_robot_bridge__msg__ArmJointCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__ArmJointCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__ArmJointCommand__Sequence__init(teleop_robot_bridge__msg__ArmJointCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__ArmJointCommand * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__ArmJointCommand *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__ArmJointCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__ArmJointCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__ArmJointCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
teleop_robot_bridge__msg__ArmJointCommand__Sequence__fini(teleop_robot_bridge__msg__ArmJointCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      teleop_robot_bridge__msg__ArmJointCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

teleop_robot_bridge__msg__ArmJointCommand__Sequence *
teleop_robot_bridge__msg__ArmJointCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__ArmJointCommand__Sequence * array = (teleop_robot_bridge__msg__ArmJointCommand__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__ArmJointCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__ArmJointCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__ArmJointCommand__Sequence__destroy(teleop_robot_bridge__msg__ArmJointCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__ArmJointCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__ArmJointCommand__Sequence__are_equal(const teleop_robot_bridge__msg__ArmJointCommand__Sequence * lhs, const teleop_robot_bridge__msg__ArmJointCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__ArmJointCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__ArmJointCommand__Sequence__copy(
  const teleop_robot_bridge__msg__ArmJointCommand__Sequence * input,
  teleop_robot_bridge__msg__ArmJointCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__ArmJointCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__ArmJointCommand * data =
      (teleop_robot_bridge__msg__ArmJointCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__ArmJointCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__ArmJointCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__ArmJointCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
