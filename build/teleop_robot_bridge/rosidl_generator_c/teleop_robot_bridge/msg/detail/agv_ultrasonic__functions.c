// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/AgvUltrasonic.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/agv_ultrasonic__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `ranges`
#include "sensor_msgs/msg/detail/range__functions.h"

bool
teleop_robot_bridge__msg__AgvUltrasonic__init(teleop_robot_bridge__msg__AgvUltrasonic * msg)
{
  if (!msg) {
    return false;
  }
  // ranges
  for (size_t i = 0; i < 8; ++i) {
    if (!sensor_msgs__msg__Range__init(&msg->ranges[i])) {
      teleop_robot_bridge__msg__AgvUltrasonic__fini(msg);
      return false;
    }
  }
  return true;
}

void
teleop_robot_bridge__msg__AgvUltrasonic__fini(teleop_robot_bridge__msg__AgvUltrasonic * msg)
{
  if (!msg) {
    return;
  }
  // ranges
  for (size_t i = 0; i < 8; ++i) {
    sensor_msgs__msg__Range__fini(&msg->ranges[i]);
  }
}

bool
teleop_robot_bridge__msg__AgvUltrasonic__are_equal(const teleop_robot_bridge__msg__AgvUltrasonic * lhs, const teleop_robot_bridge__msg__AgvUltrasonic * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // ranges
  for (size_t i = 0; i < 8; ++i) {
    if (!sensor_msgs__msg__Range__are_equal(
        &(lhs->ranges[i]), &(rhs->ranges[i])))
    {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__AgvUltrasonic__copy(
  const teleop_robot_bridge__msg__AgvUltrasonic * input,
  teleop_robot_bridge__msg__AgvUltrasonic * output)
{
  if (!input || !output) {
    return false;
  }
  // ranges
  for (size_t i = 0; i < 8; ++i) {
    if (!sensor_msgs__msg__Range__copy(
        &(input->ranges[i]), &(output->ranges[i])))
    {
      return false;
    }
  }
  return true;
}

teleop_robot_bridge__msg__AgvUltrasonic *
teleop_robot_bridge__msg__AgvUltrasonic__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvUltrasonic * msg = (teleop_robot_bridge__msg__AgvUltrasonic *)allocator.allocate(sizeof(teleop_robot_bridge__msg__AgvUltrasonic), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__AgvUltrasonic));
  bool success = teleop_robot_bridge__msg__AgvUltrasonic__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__AgvUltrasonic__destroy(teleop_robot_bridge__msg__AgvUltrasonic * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__AgvUltrasonic__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__AgvUltrasonic__Sequence__init(teleop_robot_bridge__msg__AgvUltrasonic__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvUltrasonic * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__AgvUltrasonic *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__AgvUltrasonic), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__AgvUltrasonic__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__AgvUltrasonic__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__AgvUltrasonic__Sequence__fini(teleop_robot_bridge__msg__AgvUltrasonic__Sequence * array)
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
      teleop_robot_bridge__msg__AgvUltrasonic__fini(&array->data[i]);
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

teleop_robot_bridge__msg__AgvUltrasonic__Sequence *
teleop_robot_bridge__msg__AgvUltrasonic__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvUltrasonic__Sequence * array = (teleop_robot_bridge__msg__AgvUltrasonic__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__AgvUltrasonic__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__AgvUltrasonic__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__AgvUltrasonic__Sequence__destroy(teleop_robot_bridge__msg__AgvUltrasonic__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__AgvUltrasonic__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__AgvUltrasonic__Sequence__are_equal(const teleop_robot_bridge__msg__AgvUltrasonic__Sequence * lhs, const teleop_robot_bridge__msg__AgvUltrasonic__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__AgvUltrasonic__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__AgvUltrasonic__Sequence__copy(
  const teleop_robot_bridge__msg__AgvUltrasonic__Sequence * input,
  teleop_robot_bridge__msg__AgvUltrasonic__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__AgvUltrasonic);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__AgvUltrasonic * data =
      (teleop_robot_bridge__msg__AgvUltrasonic *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__AgvUltrasonic__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__AgvUltrasonic__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__AgvUltrasonic__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
