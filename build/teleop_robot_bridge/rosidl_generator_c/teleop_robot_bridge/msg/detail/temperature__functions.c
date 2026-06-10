// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/Temperature.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/temperature__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `temperature`
#include "sensor_msgs/msg/detail/temperature__functions.h"

bool
teleop_robot_bridge__msg__Temperature__init(teleop_robot_bridge__msg__Temperature * msg)
{
  if (!msg) {
    return false;
  }
  // temperature
  if (!sensor_msgs__msg__Temperature__init(&msg->temperature)) {
    teleop_robot_bridge__msg__Temperature__fini(msg);
    return false;
  }
  return true;
}

void
teleop_robot_bridge__msg__Temperature__fini(teleop_robot_bridge__msg__Temperature * msg)
{
  if (!msg) {
    return;
  }
  // temperature
  sensor_msgs__msg__Temperature__fini(&msg->temperature);
}

bool
teleop_robot_bridge__msg__Temperature__are_equal(const teleop_robot_bridge__msg__Temperature * lhs, const teleop_robot_bridge__msg__Temperature * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // temperature
  if (!sensor_msgs__msg__Temperature__are_equal(
      &(lhs->temperature), &(rhs->temperature)))
  {
    return false;
  }
  return true;
}

bool
teleop_robot_bridge__msg__Temperature__copy(
  const teleop_robot_bridge__msg__Temperature * input,
  teleop_robot_bridge__msg__Temperature * output)
{
  if (!input || !output) {
    return false;
  }
  // temperature
  if (!sensor_msgs__msg__Temperature__copy(
      &(input->temperature), &(output->temperature)))
  {
    return false;
  }
  return true;
}

teleop_robot_bridge__msg__Temperature *
teleop_robot_bridge__msg__Temperature__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__Temperature * msg = (teleop_robot_bridge__msg__Temperature *)allocator.allocate(sizeof(teleop_robot_bridge__msg__Temperature), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__Temperature));
  bool success = teleop_robot_bridge__msg__Temperature__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__Temperature__destroy(teleop_robot_bridge__msg__Temperature * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__Temperature__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__Temperature__Sequence__init(teleop_robot_bridge__msg__Temperature__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__Temperature * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__Temperature *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__Temperature), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__Temperature__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__Temperature__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__Temperature__Sequence__fini(teleop_robot_bridge__msg__Temperature__Sequence * array)
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
      teleop_robot_bridge__msg__Temperature__fini(&array->data[i]);
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

teleop_robot_bridge__msg__Temperature__Sequence *
teleop_robot_bridge__msg__Temperature__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__Temperature__Sequence * array = (teleop_robot_bridge__msg__Temperature__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__Temperature__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__Temperature__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__Temperature__Sequence__destroy(teleop_robot_bridge__msg__Temperature__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__Temperature__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__Temperature__Sequence__are_equal(const teleop_robot_bridge__msg__Temperature__Sequence * lhs, const teleop_robot_bridge__msg__Temperature__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__Temperature__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__Temperature__Sequence__copy(
  const teleop_robot_bridge__msg__Temperature__Sequence * input,
  teleop_robot_bridge__msg__Temperature__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__Temperature);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__Temperature * data =
      (teleop_robot_bridge__msg__Temperature *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__Temperature__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__Temperature__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__Temperature__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
