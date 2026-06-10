// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/AgvBatteryState.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/agv_battery_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `battery_state`
#include "sensor_msgs/msg/detail/battery_state__functions.h"

bool
teleop_robot_bridge__msg__AgvBatteryState__init(teleop_robot_bridge__msg__AgvBatteryState * msg)
{
  if (!msg) {
    return false;
  }
  // battery_state
  if (!sensor_msgs__msg__BatteryState__init(&msg->battery_state)) {
    teleop_robot_bridge__msg__AgvBatteryState__fini(msg);
    return false;
  }
  return true;
}

void
teleop_robot_bridge__msg__AgvBatteryState__fini(teleop_robot_bridge__msg__AgvBatteryState * msg)
{
  if (!msg) {
    return;
  }
  // battery_state
  sensor_msgs__msg__BatteryState__fini(&msg->battery_state);
}

bool
teleop_robot_bridge__msg__AgvBatteryState__are_equal(const teleop_robot_bridge__msg__AgvBatteryState * lhs, const teleop_robot_bridge__msg__AgvBatteryState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // battery_state
  if (!sensor_msgs__msg__BatteryState__are_equal(
      &(lhs->battery_state), &(rhs->battery_state)))
  {
    return false;
  }
  return true;
}

bool
teleop_robot_bridge__msg__AgvBatteryState__copy(
  const teleop_robot_bridge__msg__AgvBatteryState * input,
  teleop_robot_bridge__msg__AgvBatteryState * output)
{
  if (!input || !output) {
    return false;
  }
  // battery_state
  if (!sensor_msgs__msg__BatteryState__copy(
      &(input->battery_state), &(output->battery_state)))
  {
    return false;
  }
  return true;
}

teleop_robot_bridge__msg__AgvBatteryState *
teleop_robot_bridge__msg__AgvBatteryState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvBatteryState * msg = (teleop_robot_bridge__msg__AgvBatteryState *)allocator.allocate(sizeof(teleop_robot_bridge__msg__AgvBatteryState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__AgvBatteryState));
  bool success = teleop_robot_bridge__msg__AgvBatteryState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__AgvBatteryState__destroy(teleop_robot_bridge__msg__AgvBatteryState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__AgvBatteryState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__AgvBatteryState__Sequence__init(teleop_robot_bridge__msg__AgvBatteryState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvBatteryState * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__AgvBatteryState *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__AgvBatteryState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__AgvBatteryState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__AgvBatteryState__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__AgvBatteryState__Sequence__fini(teleop_robot_bridge__msg__AgvBatteryState__Sequence * array)
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
      teleop_robot_bridge__msg__AgvBatteryState__fini(&array->data[i]);
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

teleop_robot_bridge__msg__AgvBatteryState__Sequence *
teleop_robot_bridge__msg__AgvBatteryState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvBatteryState__Sequence * array = (teleop_robot_bridge__msg__AgvBatteryState__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__AgvBatteryState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__AgvBatteryState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__AgvBatteryState__Sequence__destroy(teleop_robot_bridge__msg__AgvBatteryState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__AgvBatteryState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__AgvBatteryState__Sequence__are_equal(const teleop_robot_bridge__msg__AgvBatteryState__Sequence * lhs, const teleop_robot_bridge__msg__AgvBatteryState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__AgvBatteryState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__AgvBatteryState__Sequence__copy(
  const teleop_robot_bridge__msg__AgvBatteryState__Sequence * input,
  teleop_robot_bridge__msg__AgvBatteryState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__AgvBatteryState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__AgvBatteryState * data =
      (teleop_robot_bridge__msg__AgvBatteryState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__AgvBatteryState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__AgvBatteryState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__AgvBatteryState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
