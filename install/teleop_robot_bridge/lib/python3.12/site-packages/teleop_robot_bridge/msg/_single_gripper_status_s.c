// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from teleop_robot_bridge:msg/SingleGripperStatus.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "teleop_robot_bridge/msg/detail/single_gripper_status__struct.h"
#include "teleop_robot_bridge/msg/detail/single_gripper_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool teleop_robot_bridge__msg__single_gripper_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[67];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("teleop_robot_bridge.msg._single_gripper_status.SingleGripperStatus", full_classname_dest, 66) == 0);
  }
  teleop_robot_bridge__msg__SingleGripperStatus * ros_message = _ros_message;
  {  // is_ready
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_ready");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_ready = (Py_True == field);
    Py_DECREF(field);
  }
  {  // is_reset
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_reset");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_reset = (Py_True == field);
    Py_DECREF(field);
  }
  {  // is_moving
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_moving");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_moving = (Py_True == field);
    Py_DECREF(field);
  }
  {  // obj_detected
    PyObject * field = PyObject_GetAttrString(_pymsg, "obj_detected");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->obj_detected = (Py_True == field);
    Py_DECREF(field);
  }
  {  // fault_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "fault_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fault_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // position
    PyObject * field = PyObject_GetAttrString(_pymsg, "position");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->position = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // requested_position
    PyObject * field = PyObject_GetAttrString(_pymsg, "requested_position");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->requested_position = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // current
    PyObject * field = PyObject_GetAttrString(_pymsg, "current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->current = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * teleop_robot_bridge__msg__single_gripper_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SingleGripperStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("teleop_robot_bridge.msg._single_gripper_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SingleGripperStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  teleop_robot_bridge__msg__SingleGripperStatus * ros_message = (teleop_robot_bridge__msg__SingleGripperStatus *)raw_ros_message;
  {  // is_ready
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_ready ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_ready", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // is_reset
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_reset ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_reset", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // is_moving
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_moving ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_moving", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // obj_detected
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->obj_detected ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "obj_detected", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fault_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fault_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fault_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // position
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->position);
    {
      int rc = PyObject_SetAttrString(_pymessage, "position", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // requested_position
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->requested_position);
    {
      int rc = PyObject_SetAttrString(_pymessage, "requested_position", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
