// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/JointStatus.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/joint_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
teleop_robot_bridge__msg__JointStatus__init(teleop_robot_bridge__msg__JointStatus * msg)
{
  if (!msg) {
    return false;
  }
  // driver_voltage
  // driver_temperature
  // driver_state
  // motor_temperature
  // rpm
  // current
  // pulse_count
  // motor_angles
  // motor_speeds
  // motor_loads
  return true;
}

void
teleop_robot_bridge__msg__JointStatus__fini(teleop_robot_bridge__msg__JointStatus * msg)
{
  if (!msg) {
    return;
  }
  // driver_voltage
  // driver_temperature
  // driver_state
  // motor_temperature
  // rpm
  // current
  // pulse_count
  // motor_angles
  // motor_speeds
  // motor_loads
}

bool
teleop_robot_bridge__msg__JointStatus__are_equal(const teleop_robot_bridge__msg__JointStatus * lhs, const teleop_robot_bridge__msg__JointStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // driver_voltage
  if (lhs->driver_voltage != rhs->driver_voltage) {
    return false;
  }
  // driver_temperature
  if (lhs->driver_temperature != rhs->driver_temperature) {
    return false;
  }
  // driver_state
  if (lhs->driver_state != rhs->driver_state) {
    return false;
  }
  // motor_temperature
  if (lhs->motor_temperature != rhs->motor_temperature) {
    return false;
  }
  // rpm
  if (lhs->rpm != rhs->rpm) {
    return false;
  }
  // current
  if (lhs->current != rhs->current) {
    return false;
  }
  // pulse_count
  if (lhs->pulse_count != rhs->pulse_count) {
    return false;
  }
  // motor_angles
  if (lhs->motor_angles != rhs->motor_angles) {
    return false;
  }
  // motor_speeds
  if (lhs->motor_speeds != rhs->motor_speeds) {
    return false;
  }
  // motor_loads
  if (lhs->motor_loads != rhs->motor_loads) {
    return false;
  }
  return true;
}

bool
teleop_robot_bridge__msg__JointStatus__copy(
  const teleop_robot_bridge__msg__JointStatus * input,
  teleop_robot_bridge__msg__JointStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // driver_voltage
  output->driver_voltage = input->driver_voltage;
  // driver_temperature
  output->driver_temperature = input->driver_temperature;
  // driver_state
  output->driver_state = input->driver_state;
  // motor_temperature
  output->motor_temperature = input->motor_temperature;
  // rpm
  output->rpm = input->rpm;
  // current
  output->current = input->current;
  // pulse_count
  output->pulse_count = input->pulse_count;
  // motor_angles
  output->motor_angles = input->motor_angles;
  // motor_speeds
  output->motor_speeds = input->motor_speeds;
  // motor_loads
  output->motor_loads = input->motor_loads;
  return true;
}

teleop_robot_bridge__msg__JointStatus *
teleop_robot_bridge__msg__JointStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__JointStatus * msg = (teleop_robot_bridge__msg__JointStatus *)allocator.allocate(sizeof(teleop_robot_bridge__msg__JointStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__JointStatus));
  bool success = teleop_robot_bridge__msg__JointStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__JointStatus__destroy(teleop_robot_bridge__msg__JointStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__JointStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__JointStatus__Sequence__init(teleop_robot_bridge__msg__JointStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__JointStatus * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__JointStatus *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__JointStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__JointStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__JointStatus__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__JointStatus__Sequence__fini(teleop_robot_bridge__msg__JointStatus__Sequence * array)
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
      teleop_robot_bridge__msg__JointStatus__fini(&array->data[i]);
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

teleop_robot_bridge__msg__JointStatus__Sequence *
teleop_robot_bridge__msg__JointStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__JointStatus__Sequence * array = (teleop_robot_bridge__msg__JointStatus__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__JointStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__JointStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__JointStatus__Sequence__destroy(teleop_robot_bridge__msg__JointStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__JointStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__JointStatus__Sequence__are_equal(const teleop_robot_bridge__msg__JointStatus__Sequence * lhs, const teleop_robot_bridge__msg__JointStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__JointStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__JointStatus__Sequence__copy(
  const teleop_robot_bridge__msg__JointStatus__Sequence * input,
  teleop_robot_bridge__msg__JointStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__JointStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__JointStatus * data =
      (teleop_robot_bridge__msg__JointStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__JointStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__JointStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__JointStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
