// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/SingleDeviceState.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/single_device_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `error_domain`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `manufacturer`
// Member `model`
// Member `firmware_version`
#include "rosidl_runtime_c/string_functions.h"

bool
teleop_robot_bridge__msg__SingleDeviceState__init(teleop_robot_bridge__msg__SingleDeviceState * msg)
{
  if (!msg) {
    return false;
  }
  // health_status
  // error_domain
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->error_domain, 0)) {
    teleop_robot_bridge__msg__SingleDeviceState__fini(msg);
    return false;
  }
  // operational_mode
  // power_state
  // connectivity_status
  // manufacturer
  if (!rosidl_runtime_c__String__init(&msg->manufacturer)) {
    teleop_robot_bridge__msg__SingleDeviceState__fini(msg);
    return false;
  }
  // model
  if (!rosidl_runtime_c__String__init(&msg->model)) {
    teleop_robot_bridge__msg__SingleDeviceState__fini(msg);
    return false;
  }
  // firmware_version
  if (!rosidl_runtime_c__String__init(&msg->firmware_version)) {
    teleop_robot_bridge__msg__SingleDeviceState__fini(msg);
    return false;
  }
  return true;
}

void
teleop_robot_bridge__msg__SingleDeviceState__fini(teleop_robot_bridge__msg__SingleDeviceState * msg)
{
  if (!msg) {
    return;
  }
  // health_status
  // error_domain
  rosidl_runtime_c__uint8__Sequence__fini(&msg->error_domain);
  // operational_mode
  // power_state
  // connectivity_status
  // manufacturer
  rosidl_runtime_c__String__fini(&msg->manufacturer);
  // model
  rosidl_runtime_c__String__fini(&msg->model);
  // firmware_version
  rosidl_runtime_c__String__fini(&msg->firmware_version);
}

bool
teleop_robot_bridge__msg__SingleDeviceState__are_equal(const teleop_robot_bridge__msg__SingleDeviceState * lhs, const teleop_robot_bridge__msg__SingleDeviceState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // health_status
  if (lhs->health_status != rhs->health_status) {
    return false;
  }
  // error_domain
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->error_domain), &(rhs->error_domain)))
  {
    return false;
  }
  // operational_mode
  if (lhs->operational_mode != rhs->operational_mode) {
    return false;
  }
  // power_state
  if (lhs->power_state != rhs->power_state) {
    return false;
  }
  // connectivity_status
  if (lhs->connectivity_status != rhs->connectivity_status) {
    return false;
  }
  // manufacturer
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->manufacturer), &(rhs->manufacturer)))
  {
    return false;
  }
  // model
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->model), &(rhs->model)))
  {
    return false;
  }
  // firmware_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->firmware_version), &(rhs->firmware_version)))
  {
    return false;
  }
  return true;
}

bool
teleop_robot_bridge__msg__SingleDeviceState__copy(
  const teleop_robot_bridge__msg__SingleDeviceState * input,
  teleop_robot_bridge__msg__SingleDeviceState * output)
{
  if (!input || !output) {
    return false;
  }
  // health_status
  output->health_status = input->health_status;
  // error_domain
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->error_domain), &(output->error_domain)))
  {
    return false;
  }
  // operational_mode
  output->operational_mode = input->operational_mode;
  // power_state
  output->power_state = input->power_state;
  // connectivity_status
  output->connectivity_status = input->connectivity_status;
  // manufacturer
  if (!rosidl_runtime_c__String__copy(
      &(input->manufacturer), &(output->manufacturer)))
  {
    return false;
  }
  // model
  if (!rosidl_runtime_c__String__copy(
      &(input->model), &(output->model)))
  {
    return false;
  }
  // firmware_version
  if (!rosidl_runtime_c__String__copy(
      &(input->firmware_version), &(output->firmware_version)))
  {
    return false;
  }
  return true;
}

teleop_robot_bridge__msg__SingleDeviceState *
teleop_robot_bridge__msg__SingleDeviceState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleDeviceState * msg = (teleop_robot_bridge__msg__SingleDeviceState *)allocator.allocate(sizeof(teleop_robot_bridge__msg__SingleDeviceState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__SingleDeviceState));
  bool success = teleop_robot_bridge__msg__SingleDeviceState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__SingleDeviceState__destroy(teleop_robot_bridge__msg__SingleDeviceState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__SingleDeviceState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__SingleDeviceState__Sequence__init(teleop_robot_bridge__msg__SingleDeviceState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleDeviceState * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__SingleDeviceState *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__SingleDeviceState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__SingleDeviceState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__SingleDeviceState__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__SingleDeviceState__Sequence__fini(teleop_robot_bridge__msg__SingleDeviceState__Sequence * array)
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
      teleop_robot_bridge__msg__SingleDeviceState__fini(&array->data[i]);
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

teleop_robot_bridge__msg__SingleDeviceState__Sequence *
teleop_robot_bridge__msg__SingleDeviceState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleDeviceState__Sequence * array = (teleop_robot_bridge__msg__SingleDeviceState__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__SingleDeviceState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__SingleDeviceState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__SingleDeviceState__Sequence__destroy(teleop_robot_bridge__msg__SingleDeviceState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__SingleDeviceState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__SingleDeviceState__Sequence__are_equal(const teleop_robot_bridge__msg__SingleDeviceState__Sequence * lhs, const teleop_robot_bridge__msg__SingleDeviceState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__SingleDeviceState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__SingleDeviceState__Sequence__copy(
  const teleop_robot_bridge__msg__SingleDeviceState__Sequence * input,
  teleop_robot_bridge__msg__SingleDeviceState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__SingleDeviceState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__SingleDeviceState * data =
      (teleop_robot_bridge__msg__SingleDeviceState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__SingleDeviceState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__SingleDeviceState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__SingleDeviceState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
