// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/SingleGripperStatus.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/single_gripper_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
teleop_robot_bridge__msg__SingleGripperStatus__init(teleop_robot_bridge__msg__SingleGripperStatus * msg)
{
  if (!msg) {
    return false;
  }
  // is_ready
  // is_reset
  // is_moving
  // obj_detected
  // fault_status
  // position
  // requested_position
  // current
  return true;
}

void
teleop_robot_bridge__msg__SingleGripperStatus__fini(teleop_robot_bridge__msg__SingleGripperStatus * msg)
{
  if (!msg) {
    return;
  }
  // is_ready
  // is_reset
  // is_moving
  // obj_detected
  // fault_status
  // position
  // requested_position
  // current
}

bool
teleop_robot_bridge__msg__SingleGripperStatus__are_equal(const teleop_robot_bridge__msg__SingleGripperStatus * lhs, const teleop_robot_bridge__msg__SingleGripperStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_ready
  if (lhs->is_ready != rhs->is_ready) {
    return false;
  }
  // is_reset
  if (lhs->is_reset != rhs->is_reset) {
    return false;
  }
  // is_moving
  if (lhs->is_moving != rhs->is_moving) {
    return false;
  }
  // obj_detected
  if (lhs->obj_detected != rhs->obj_detected) {
    return false;
  }
  // fault_status
  if (lhs->fault_status != rhs->fault_status) {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // requested_position
  if (lhs->requested_position != rhs->requested_position) {
    return false;
  }
  // current
  if (lhs->current != rhs->current) {
    return false;
  }
  return true;
}

bool
teleop_robot_bridge__msg__SingleGripperStatus__copy(
  const teleop_robot_bridge__msg__SingleGripperStatus * input,
  teleop_robot_bridge__msg__SingleGripperStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // is_ready
  output->is_ready = input->is_ready;
  // is_reset
  output->is_reset = input->is_reset;
  // is_moving
  output->is_moving = input->is_moving;
  // obj_detected
  output->obj_detected = input->obj_detected;
  // fault_status
  output->fault_status = input->fault_status;
  // position
  output->position = input->position;
  // requested_position
  output->requested_position = input->requested_position;
  // current
  output->current = input->current;
  return true;
}

teleop_robot_bridge__msg__SingleGripperStatus *
teleop_robot_bridge__msg__SingleGripperStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleGripperStatus * msg = (teleop_robot_bridge__msg__SingleGripperStatus *)allocator.allocate(sizeof(teleop_robot_bridge__msg__SingleGripperStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__SingleGripperStatus));
  bool success = teleop_robot_bridge__msg__SingleGripperStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__SingleGripperStatus__destroy(teleop_robot_bridge__msg__SingleGripperStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__SingleGripperStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__SingleGripperStatus__Sequence__init(teleop_robot_bridge__msg__SingleGripperStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleGripperStatus * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__SingleGripperStatus *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__SingleGripperStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__SingleGripperStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__SingleGripperStatus__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__SingleGripperStatus__Sequence__fini(teleop_robot_bridge__msg__SingleGripperStatus__Sequence * array)
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
      teleop_robot_bridge__msg__SingleGripperStatus__fini(&array->data[i]);
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

teleop_robot_bridge__msg__SingleGripperStatus__Sequence *
teleop_robot_bridge__msg__SingleGripperStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleGripperStatus__Sequence * array = (teleop_robot_bridge__msg__SingleGripperStatus__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__SingleGripperStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__SingleGripperStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__SingleGripperStatus__Sequence__destroy(teleop_robot_bridge__msg__SingleGripperStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__SingleGripperStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__SingleGripperStatus__Sequence__are_equal(const teleop_robot_bridge__msg__SingleGripperStatus__Sequence * lhs, const teleop_robot_bridge__msg__SingleGripperStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__SingleGripperStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__SingleGripperStatus__Sequence__copy(
  const teleop_robot_bridge__msg__SingleGripperStatus__Sequence * input,
  teleop_robot_bridge__msg__SingleGripperStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__SingleGripperStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__SingleGripperStatus * data =
      (teleop_robot_bridge__msg__SingleGripperStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__SingleGripperStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__SingleGripperStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__SingleGripperStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
