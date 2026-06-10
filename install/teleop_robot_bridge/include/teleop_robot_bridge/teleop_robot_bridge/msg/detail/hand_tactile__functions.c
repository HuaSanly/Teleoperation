// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/HandTactile.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/hand_tactile__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
teleop_robot_bridge__msg__HandTactile__init(teleop_robot_bridge__msg__HandTactile * msg)
{
  if (!msg) {
    return false;
  }
  // finger
  // thumb
  return true;
}

void
teleop_robot_bridge__msg__HandTactile__fini(teleop_robot_bridge__msg__HandTactile * msg)
{
  if (!msg) {
    return;
  }
  // finger
  // thumb
}

bool
teleop_robot_bridge__msg__HandTactile__are_equal(const teleop_robot_bridge__msg__HandTactile * lhs, const teleop_robot_bridge__msg__HandTactile * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // finger
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->finger[i] != rhs->finger[i]) {
      return false;
    }
  }
  // thumb
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->thumb[i] != rhs->thumb[i]) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__HandTactile__copy(
  const teleop_robot_bridge__msg__HandTactile * input,
  teleop_robot_bridge__msg__HandTactile * output)
{
  if (!input || !output) {
    return false;
  }
  // finger
  for (size_t i = 0; i < 4; ++i) {
    output->finger[i] = input->finger[i];
  }
  // thumb
  for (size_t i = 0; i < 4; ++i) {
    output->thumb[i] = input->thumb[i];
  }
  return true;
}

teleop_robot_bridge__msg__HandTactile *
teleop_robot_bridge__msg__HandTactile__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__HandTactile * msg = (teleop_robot_bridge__msg__HandTactile *)allocator.allocate(sizeof(teleop_robot_bridge__msg__HandTactile), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__HandTactile));
  bool success = teleop_robot_bridge__msg__HandTactile__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__HandTactile__destroy(teleop_robot_bridge__msg__HandTactile * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__HandTactile__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__HandTactile__Sequence__init(teleop_robot_bridge__msg__HandTactile__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__HandTactile * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__HandTactile *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__HandTactile), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__HandTactile__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__HandTactile__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__HandTactile__Sequence__fini(teleop_robot_bridge__msg__HandTactile__Sequence * array)
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
      teleop_robot_bridge__msg__HandTactile__fini(&array->data[i]);
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

teleop_robot_bridge__msg__HandTactile__Sequence *
teleop_robot_bridge__msg__HandTactile__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__HandTactile__Sequence * array = (teleop_robot_bridge__msg__HandTactile__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__HandTactile__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__HandTactile__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__HandTactile__Sequence__destroy(teleop_robot_bridge__msg__HandTactile__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__HandTactile__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__HandTactile__Sequence__are_equal(const teleop_robot_bridge__msg__HandTactile__Sequence * lhs, const teleop_robot_bridge__msg__HandTactile__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__HandTactile__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__HandTactile__Sequence__copy(
  const teleop_robot_bridge__msg__HandTactile__Sequence * input,
  teleop_robot_bridge__msg__HandTactile__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__HandTactile);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__HandTactile * data =
      (teleop_robot_bridge__msg__HandTactile *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__HandTactile__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__HandTactile__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__HandTactile__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
