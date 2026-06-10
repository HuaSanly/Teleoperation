// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/AgvDeviceState.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/agv_device_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `manufacturer`
// Member `model`
// Member `firmware_version`
#include "rosidl_runtime_c/string_functions.h"

bool
teleop_robot_bridge__msg__AgvDeviceState__init(teleop_robot_bridge__msg__AgvDeviceState * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    teleop_robot_bridge__msg__AgvDeviceState__fini(msg);
    return false;
  }
  // health_status
  // error_domain
  // operational_mode
  // power_state
  // connectivity_status
  // manufacturer
  if (!rosidl_runtime_c__String__init(&msg->manufacturer)) {
    teleop_robot_bridge__msg__AgvDeviceState__fini(msg);
    return false;
  }
  // model
  if (!rosidl_runtime_c__String__init(&msg->model)) {
    teleop_robot_bridge__msg__AgvDeviceState__fini(msg);
    return false;
  }
  // firmware_version
  if (!rosidl_runtime_c__String__init(&msg->firmware_version)) {
    teleop_robot_bridge__msg__AgvDeviceState__fini(msg);
    return false;
  }
  return true;
}

void
teleop_robot_bridge__msg__AgvDeviceState__fini(teleop_robot_bridge__msg__AgvDeviceState * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // health_status
  // error_domain
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
teleop_robot_bridge__msg__AgvDeviceState__are_equal(const teleop_robot_bridge__msg__AgvDeviceState * lhs, const teleop_robot_bridge__msg__AgvDeviceState * rhs)
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
  // health_status
  if (lhs->health_status != rhs->health_status) {
    return false;
  }
  // error_domain
  if (lhs->error_domain != rhs->error_domain) {
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
teleop_robot_bridge__msg__AgvDeviceState__copy(
  const teleop_robot_bridge__msg__AgvDeviceState * input,
  teleop_robot_bridge__msg__AgvDeviceState * output)
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
  // health_status
  output->health_status = input->health_status;
  // error_domain
  output->error_domain = input->error_domain;
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

teleop_robot_bridge__msg__AgvDeviceState *
teleop_robot_bridge__msg__AgvDeviceState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvDeviceState * msg = (teleop_robot_bridge__msg__AgvDeviceState *)allocator.allocate(sizeof(teleop_robot_bridge__msg__AgvDeviceState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__AgvDeviceState));
  bool success = teleop_robot_bridge__msg__AgvDeviceState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__AgvDeviceState__destroy(teleop_robot_bridge__msg__AgvDeviceState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__AgvDeviceState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__AgvDeviceState__Sequence__init(teleop_robot_bridge__msg__AgvDeviceState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvDeviceState * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__AgvDeviceState *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__AgvDeviceState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__AgvDeviceState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__AgvDeviceState__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__AgvDeviceState__Sequence__fini(teleop_robot_bridge__msg__AgvDeviceState__Sequence * array)
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
      teleop_robot_bridge__msg__AgvDeviceState__fini(&array->data[i]);
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

teleop_robot_bridge__msg__AgvDeviceState__Sequence *
teleop_robot_bridge__msg__AgvDeviceState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__AgvDeviceState__Sequence * array = (teleop_robot_bridge__msg__AgvDeviceState__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__AgvDeviceState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__AgvDeviceState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__AgvDeviceState__Sequence__destroy(teleop_robot_bridge__msg__AgvDeviceState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__AgvDeviceState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__AgvDeviceState__Sequence__are_equal(const teleop_robot_bridge__msg__AgvDeviceState__Sequence * lhs, const teleop_robot_bridge__msg__AgvDeviceState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__AgvDeviceState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__AgvDeviceState__Sequence__copy(
  const teleop_robot_bridge__msg__AgvDeviceState__Sequence * input,
  teleop_robot_bridge__msg__AgvDeviceState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__AgvDeviceState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__AgvDeviceState * data =
      (teleop_robot_bridge__msg__AgvDeviceState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__AgvDeviceState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__AgvDeviceState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__AgvDeviceState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
