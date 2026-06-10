# generated from rosidl_generator_py/resource/_idl.py.em
# with input from teleop_robot_bridge:msg/JointStatus.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_JointStatus(type):
    """Metaclass of message 'JointStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('teleop_robot_bridge')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'teleop_robot_bridge.msg.JointStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__joint_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__joint_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__joint_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__joint_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__joint_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class JointStatus(metaclass=Metaclass_JointStatus):
    """Message class 'JointStatus'."""

    __slots__ = [
        '_driver_voltage',
        '_driver_temperature',
        '_driver_state',
        '_motor_temperature',
        '_rpm',
        '_current',
        '_pulse_count',
        '_motor_angles',
        '_motor_speeds',
        '_motor_loads',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'driver_voltage': 'float',
        'driver_temperature': 'float',
        'driver_state': 'uint8',
        'motor_temperature': 'float',
        'rpm': 'int32',
        'current': 'float',
        'pulse_count': 'int64',
        'motor_angles': 'int32',
        'motor_speeds': 'int32',
        'motor_loads': 'int32',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.driver_voltage = kwargs.get('driver_voltage', float())
        self.driver_temperature = kwargs.get('driver_temperature', float())
        self.driver_state = kwargs.get('driver_state', int())
        self.motor_temperature = kwargs.get('motor_temperature', float())
        self.rpm = kwargs.get('rpm', int())
        self.current = kwargs.get('current', float())
        self.pulse_count = kwargs.get('pulse_count', int())
        self.motor_angles = kwargs.get('motor_angles', int())
        self.motor_speeds = kwargs.get('motor_speeds', int())
        self.motor_loads = kwargs.get('motor_loads', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.driver_voltage != other.driver_voltage:
            return False
        if self.driver_temperature != other.driver_temperature:
            return False
        if self.driver_state != other.driver_state:
            return False
        if self.motor_temperature != other.motor_temperature:
            return False
        if self.rpm != other.rpm:
            return False
        if self.current != other.current:
            return False
        if self.pulse_count != other.pulse_count:
            return False
        if self.motor_angles != other.motor_angles:
            return False
        if self.motor_speeds != other.motor_speeds:
            return False
        if self.motor_loads != other.motor_loads:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def driver_voltage(self):
        """Message field 'driver_voltage'."""
        return self._driver_voltage

    @driver_voltage.setter
    def driver_voltage(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'driver_voltage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'driver_voltage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._driver_voltage = value

    @builtins.property
    def driver_temperature(self):
        """Message field 'driver_temperature'."""
        return self._driver_temperature

    @driver_temperature.setter
    def driver_temperature(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'driver_temperature' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'driver_temperature' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._driver_temperature = value

    @builtins.property
    def driver_state(self):
        """Message field 'driver_state'."""
        return self._driver_state

    @driver_state.setter
    def driver_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'driver_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'driver_state' field must be an unsigned integer in [0, 255]"
        self._driver_state = value

    @builtins.property
    def motor_temperature(self):
        """Message field 'motor_temperature'."""
        return self._motor_temperature

    @motor_temperature.setter
    def motor_temperature(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'motor_temperature' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'motor_temperature' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._motor_temperature = value

    @builtins.property
    def rpm(self):
        """Message field 'rpm'."""
        return self._rpm

    @rpm.setter
    def rpm(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'rpm' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'rpm' field must be an integer in [-2147483648, 2147483647]"
        self._rpm = value

    @builtins.property
    def current(self):
        """Message field 'current'."""
        return self._current

    @current.setter
    def current(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'current' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current = value

    @builtins.property
    def pulse_count(self):
        """Message field 'pulse_count'."""
        return self._pulse_count

    @pulse_count.setter
    def pulse_count(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'pulse_count' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'pulse_count' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._pulse_count = value

    @builtins.property
    def motor_angles(self):
        """Message field 'motor_angles'."""
        return self._motor_angles

    @motor_angles.setter
    def motor_angles(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'motor_angles' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'motor_angles' field must be an integer in [-2147483648, 2147483647]"
        self._motor_angles = value

    @builtins.property
    def motor_speeds(self):
        """Message field 'motor_speeds'."""
        return self._motor_speeds

    @motor_speeds.setter
    def motor_speeds(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'motor_speeds' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'motor_speeds' field must be an integer in [-2147483648, 2147483647]"
        self._motor_speeds = value

    @builtins.property
    def motor_loads(self):
        """Message field 'motor_loads'."""
        return self._motor_loads

    @motor_loads.setter
    def motor_loads(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'motor_loads' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'motor_loads' field must be an integer in [-2147483648, 2147483647]"
        self._motor_loads = value
