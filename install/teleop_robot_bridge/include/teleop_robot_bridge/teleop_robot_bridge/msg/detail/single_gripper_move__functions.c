// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleop_robot_bridge:msg/SingleGripperMove.idl
// generated code does not contain a copyright notice
#include "teleop_robot_bridge/msg/detail/single_gripper_move__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
teleop_robot_bridge__msg__SingleGripperMove__init(teleop_robot_bridge__msg__SingleGripperMove * msg)
{
  if (!msg) {
    return false;
  }
  // emergency_release
  // emergency_release_dir
  // stop
  // position
  // speed
  // force
  return true;
}

void
teleop_robot_bridge__msg__SingleGripperMove__fini(teleop_robot_bridge__msg__SingleGripperMove * msg)
{
  if (!msg) {
    return;
  }
  // emergency_release
  // emergency_release_dir
  // stop
  // position
  // speed
  // force
}

bool
teleop_robot_bridge__msg__SingleGripperMove__are_equal(const teleop_robot_bridge__msg__SingleGripperMove * lhs, const teleop_robot_bridge__msg__SingleGripperMove * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // emergency_release
  if (lhs->emergency_release != rhs->emergency_release) {
    return false;
  }
  // emergency_release_dir
  if (lhs->emergency_release_dir != rhs->emergency_release_dir) {
    return false;
  }
  // stop
  if (lhs->stop != rhs->stop) {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // speed
  if (lhs->speed != rhs->speed) {
    return false;
  }
  // force
  if (lhs->force != rhs->force) {
    return false;
  }
  return true;
}

bool
teleop_robot_bridge__msg__SingleGripperMove__copy(
  const teleop_robot_bridge__msg__SingleGripperMove * input,
  teleop_robot_bridge__msg__SingleGripperMove * output)
{
  if (!input || !output) {
    return false;
  }
  // emergency_release
  output->emergency_release = input->emergency_release;
  // emergency_release_dir
  output->emergency_release_dir = input->emergency_release_dir;
  // stop
  output->stop = input->stop;
  // position
  output->position = input->position;
  // speed
  output->speed = input->speed;
  // force
  output->force = input->force;
  return true;
}

teleop_robot_bridge__msg__SingleGripperMove *
teleop_robot_bridge__msg__SingleGripperMove__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleGripperMove * msg = (teleop_robot_bridge__msg__SingleGripperMove *)allocator.allocate(sizeof(teleop_robot_bridge__msg__SingleGripperMove), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleop_robot_bridge__msg__SingleGripperMove));
  bool success = teleop_robot_bridge__msg__SingleGripperMove__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleop_robot_bridge__msg__SingleGripperMove__destroy(teleop_robot_bridge__msg__SingleGripperMove * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleop_robot_bridge__msg__SingleGripperMove__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleop_robot_bridge__msg__SingleGripperMove__Sequence__init(teleop_robot_bridge__msg__SingleGripperMove__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleGripperMove * data = NULL;

  if (size) {
    data = (teleop_robot_bridge__msg__SingleGripperMove *)allocator.zero_allocate(size, sizeof(teleop_robot_bridge__msg__SingleGripperMove), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleop_robot_bridge__msg__SingleGripperMove__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleop_robot_bridge__msg__SingleGripperMove__fini(&data[i - 1]);
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
teleop_robot_bridge__msg__SingleGripperMove__Sequence__fini(teleop_robot_bridge__msg__SingleGripperMove__Sequence * array)
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
      teleop_robot_bridge__msg__SingleGripperMove__fini(&array->data[i]);
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

teleop_robot_bridge__msg__SingleGripperMove__Sequence *
teleop_robot_bridge__msg__SingleGripperMove__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleop_robot_bridge__msg__SingleGripperMove__Sequence * array = (teleop_robot_bridge__msg__SingleGripperMove__Sequence *)allocator.allocate(sizeof(teleop_robot_bridge__msg__SingleGripperMove__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleop_robot_bridge__msg__SingleGripperMove__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleop_robot_bridge__msg__SingleGripperMove__Sequence__destroy(teleop_robot_bridge__msg__SingleGripperMove__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleop_robot_bridge__msg__SingleGripperMove__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleop_robot_bridge__msg__SingleGripperMove__Sequence__are_equal(const teleop_robot_bridge__msg__SingleGripperMove__Sequence * lhs, const teleop_robot_bridge__msg__SingleGripperMove__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleop_robot_bridge__msg__SingleGripperMove__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleop_robot_bridge__msg__SingleGripperMove__Sequence__copy(
  const teleop_robot_bridge__msg__SingleGripperMove__Sequence * input,
  teleop_robot_bridge__msg__SingleGripperMove__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleop_robot_bridge__msg__SingleGripperMove);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleop_robot_bridge__msg__SingleGripperMove * data =
      (teleop_robot_bridge__msg__SingleGripperMove *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleop_robot_bridge__msg__SingleGripperMove__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleop_robot_bridge__msg__SingleGripperMove__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleop_robot_bridge__msg__SingleGripperMove__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
