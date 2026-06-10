# generated from rosidl_generator_py/resource/_idl.py.em
# with input from teleop_robot_bridge:msg/SingleDeviceState.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

# Member 'error_domain'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SingleDeviceState(type):
    """Metaclass of message 'SingleDeviceState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'HEALTH_UNKNOWN': 0,
        'HEALTH_OK': 1,
        'HEALTH_DEGRADED': 2,
        'HEALTH_WARNING': 3,
        'HEALTH_ERROR': 4,
        'HEALTH_FATAL': 5,
        'ERROR_NONE': 0,
        'ERROR_UNKNOWN': 1,
        'ERROR_HW': 2,
        'ERROR_SW': 3,
        'ERROR_OVER_TRAVEL': 4,
        'EMERGENCY_STOP_HW': 5,
        'EMERGENCY_STOP_SW': 6,
        'PROTECTIVE_STOP_HW': 7,
        'PROTECTIVE_STOP_SW': 8,
        'SAFETY_STOP': 9,
        'CALIBRATION_REQUIRED': 10,
        'MODE_UNKNOWN': 0,
        'MODE_MANUAL': 1,
        'MODE_AUTO': 2,
        'MODE_SAFE': 3,
        'MODE_MAINTENANCE': 4,
        'MODE_JOG_MANUAL': 5,
        'MODE_ADMITTANCE': 6,
        'MODE_MONITORED_STOP': 7,
        'MODE_HOLD_TO_RUN': 8,
        'MODE_CARTESIAN_TWIST': 9,
        'MODE_CARTESIAN_POSE': 10,
        'MODE_TRAJECTORY_FORWARDING': 11,
        'MODE_TRAJECTORY_STREAMING': 12,
        'POWER_UNKNOWN': 0,
        'POWER_OFF': 1,
        'POWER_STANDBY': 2,
        'POWER_ON': 3,
        'POWER_SLEEP': 4,
        'POWER_ERROR': 5,
        'POWER_LEVEL_LOW': 6,
        'POWER_LEVEL_CRITICAL': 7,
        'POWER_CHARGING': 8,
        'POWER_CHARGING_ERROR': 9,
        'CONNECT_UNKNOWN': 0,
        'CONNECT_UP': 1,
        'CONNECT_DOWN': 2,
        'CONNECT_FAILURE': 3,
        'CONNECTION_SLOW': 4,
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
                'teleop_robot_bridge.msg.SingleDeviceState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__single_device_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__single_device_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__single_device_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__single_device_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__single_device_state

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'HEALTH_UNKNOWN': cls.__constants['HEALTH_UNKNOWN'],
            'HEALTH_OK': cls.__constants['HEALTH_OK'],
            'HEALTH_DEGRADED': cls.__constants['HEALTH_DEGRADED'],
            'HEALTH_WARNING': cls.__constants['HEALTH_WARNING'],
            'HEALTH_ERROR': cls.__constants['HEALTH_ERROR'],
            'HEALTH_FATAL': cls.__constants['HEALTH_FATAL'],
            'ERROR_NONE': cls.__constants['ERROR_NONE'],
            'ERROR_UNKNOWN': cls.__constants['ERROR_UNKNOWN'],
            'ERROR_HW': cls.__constants['ERROR_HW'],
            'ERROR_SW': cls.__constants['ERROR_SW'],
            'ERROR_OVER_TRAVEL': cls.__constants['ERROR_OVER_TRAVEL'],
            'EMERGENCY_STOP_HW': cls.__constants['EMERGENCY_STOP_HW'],
            'EMERGENCY_STOP_SW': cls.__constants['EMERGENCY_STOP_SW'],
            'PROTECTIVE_STOP_HW': cls.__constants['PROTECTIVE_STOP_HW'],
            'PROTECTIVE_STOP_SW': cls.__constants['PROTECTIVE_STOP_SW'],
            'SAFETY_STOP': cls.__constants['SAFETY_STOP'],
            'CALIBRATION_REQUIRED': cls.__constants['CALIBRATION_REQUIRED'],
            'MODE_UNKNOWN': cls.__constants['MODE_UNKNOWN'],
            'MODE_MANUAL': cls.__constants['MODE_MANUAL'],
            'MODE_AUTO': cls.__constants['MODE_AUTO'],
            'MODE_SAFE': cls.__constants['MODE_SAFE'],
            'MODE_MAINTENANCE': cls.__constants['MODE_MAINTENANCE'],
            'MODE_JOG_MANUAL': cls.__constants['MODE_JOG_MANUAL'],
            'MODE_ADMITTANCE': cls.__constants['MODE_ADMITTANCE'],
            'MODE_MONITORED_STOP': cls.__constants['MODE_MONITORED_STOP'],
            'MODE_HOLD_TO_RUN': cls.__constants['MODE_HOLD_TO_RUN'],
            'MODE_CARTESIAN_TWIST': cls.__constants['MODE_CARTESIAN_TWIST'],
            'MODE_CARTESIAN_POSE': cls.__constants['MODE_CARTESIAN_POSE'],
            'MODE_TRAJECTORY_FORWARDING': cls.__constants['MODE_TRAJECTORY_FORWARDING'],
            'MODE_TRAJECTORY_STREAMING': cls.__constants['MODE_TRAJECTORY_STREAMING'],
            'POWER_UNKNOWN': cls.__constants['POWER_UNKNOWN'],
            'POWER_OFF': cls.__constants['POWER_OFF'],
            'POWER_STANDBY': cls.__constants['POWER_STANDBY'],
            'POWER_ON': cls.__constants['POWER_ON'],
            'POWER_SLEEP': cls.__constants['POWER_SLEEP'],
            'POWER_ERROR': cls.__constants['POWER_ERROR'],
            'POWER_LEVEL_LOW': cls.__constants['POWER_LEVEL_LOW'],
            'POWER_LEVEL_CRITICAL': cls.__constants['POWER_LEVEL_CRITICAL'],
            'POWER_CHARGING': cls.__constants['POWER_CHARGING'],
            'POWER_CHARGING_ERROR': cls.__constants['POWER_CHARGING_ERROR'],
            'CONNECT_UNKNOWN': cls.__constants['CONNECT_UNKNOWN'],
            'CONNECT_UP': cls.__constants['CONNECT_UP'],
            'CONNECT_DOWN': cls.__constants['CONNECT_DOWN'],
            'CONNECT_FAILURE': cls.__constants['CONNECT_FAILURE'],
            'CONNECTION_SLOW': cls.__constants['CONNECTION_SLOW'],
        }

    @property
    def HEALTH_UNKNOWN(self):
        """Message constant 'HEALTH_UNKNOWN'."""
        return Metaclass_SingleDeviceState.__constants['HEALTH_UNKNOWN']

    @property
    def HEALTH_OK(self):
        """Message constant 'HEALTH_OK'."""
        return Metaclass_SingleDeviceState.__constants['HEALTH_OK']

    @property
    def HEALTH_DEGRADED(self):
        """Message constant 'HEALTH_DEGRADED'."""
        return Metaclass_SingleDeviceState.__constants['HEALTH_DEGRADED']

    @property
    def HEALTH_WARNING(self):
        """Message constant 'HEALTH_WARNING'."""
        return Metaclass_SingleDeviceState.__constants['HEALTH_WARNING']

    @property
    def HEALTH_ERROR(self):
        """Message constant 'HEALTH_ERROR'."""
        return Metaclass_SingleDeviceState.__constants['HEALTH_ERROR']

    @property
    def HEALTH_FATAL(self):
        """Message constant 'HEALTH_FATAL'."""
        return Metaclass_SingleDeviceState.__constants['HEALTH_FATAL']

    @property
    def ERROR_NONE(self):
        """Message constant 'ERROR_NONE'."""
        return Metaclass_SingleDeviceState.__constants['ERROR_NONE']

    @property
    def ERROR_UNKNOWN(self):
        """Message constant 'ERROR_UNKNOWN'."""
        return Metaclass_SingleDeviceState.__constants['ERROR_UNKNOWN']

    @property
    def ERROR_HW(self):
        """Message constant 'ERROR_HW'."""
        return Metaclass_SingleDeviceState.__constants['ERROR_HW']

    @property
    def ERROR_SW(self):
        """Message constant 'ERROR_SW'."""
        return Metaclass_SingleDeviceState.__constants['ERROR_SW']

    @property
    def ERROR_OVER_TRAVEL(self):
        """Message constant 'ERROR_OVER_TRAVEL'."""
        return Metaclass_SingleDeviceState.__constants['ERROR_OVER_TRAVEL']

    @property
    def EMERGENCY_STOP_HW(self):
        """Message constant 'EMERGENCY_STOP_HW'."""
        return Metaclass_SingleDeviceState.__constants['EMERGENCY_STOP_HW']

    @property
    def EMERGENCY_STOP_SW(self):
        """Message constant 'EMERGENCY_STOP_SW'."""
        return Metaclass_SingleDeviceState.__constants['EMERGENCY_STOP_SW']

    @property
    def PROTECTIVE_STOP_HW(self):
        """Message constant 'PROTECTIVE_STOP_HW'."""
        return Metaclass_SingleDeviceState.__constants['PROTECTIVE_STOP_HW']

    @property
    def PROTECTIVE_STOP_SW(self):
        """Message constant 'PROTECTIVE_STOP_SW'."""
        return Metaclass_SingleDeviceState.__constants['PROTECTIVE_STOP_SW']

    @property
    def SAFETY_STOP(self):
        """Message constant 'SAFETY_STOP'."""
        return Metaclass_SingleDeviceState.__constants['SAFETY_STOP']

    @property
    def CALIBRATION_REQUIRED(self):
        """Message constant 'CALIBRATION_REQUIRED'."""
        return Metaclass_SingleDeviceState.__constants['CALIBRATION_REQUIRED']

    @property
    def MODE_UNKNOWN(self):
        """Message constant 'MODE_UNKNOWN'."""
        return Metaclass_SingleDeviceState.__constants['MODE_UNKNOWN']

    @property
    def MODE_MANUAL(self):
        """Message constant 'MODE_MANUAL'."""
        return Metaclass_SingleDeviceState.__constants['MODE_MANUAL']

    @property
    def MODE_AUTO(self):
        """Message constant 'MODE_AUTO'."""
        return Metaclass_SingleDeviceState.__constants['MODE_AUTO']

    @property
    def MODE_SAFE(self):
        """Message constant 'MODE_SAFE'."""
        return Metaclass_SingleDeviceState.__constants['MODE_SAFE']

    @property
    def MODE_MAINTENANCE(self):
        """Message constant 'MODE_MAINTENANCE'."""
        return Metaclass_SingleDeviceState.__constants['MODE_MAINTENANCE']

    @property
    def MODE_JOG_MANUAL(self):
        """Message constant 'MODE_JOG_MANUAL'."""
        return Metaclass_SingleDeviceState.__constants['MODE_JOG_MANUAL']

    @property
    def MODE_ADMITTANCE(self):
        """Message constant 'MODE_ADMITTANCE'."""
        return Metaclass_SingleDeviceState.__constants['MODE_ADMITTANCE']

    @property
    def MODE_MONITORED_STOP(self):
        """Message constant 'MODE_MONITORED_STOP'."""
        return Metaclass_SingleDeviceState.__constants['MODE_MONITORED_STOP']

    @property
    def MODE_HOLD_TO_RUN(self):
        """Message constant 'MODE_HOLD_TO_RUN'."""
        return Metaclass_SingleDeviceState.__constants['MODE_HOLD_TO_RUN']

    @property
    def MODE_CARTESIAN_TWIST(self):
        """Message constant 'MODE_CARTESIAN_TWIST'."""
        return Metaclass_SingleDeviceState.__constants['MODE_CARTESIAN_TWIST']

    @property
    def MODE_CARTESIAN_POSE(self):
        """Message constant 'MODE_CARTESIAN_POSE'."""
        return Metaclass_SingleDeviceState.__constants['MODE_CARTESIAN_POSE']

    @property
    def MODE_TRAJECTORY_FORWARDING(self):
        """Message constant 'MODE_TRAJECTORY_FORWARDING'."""
        return Metaclass_SingleDeviceState.__constants['MODE_TRAJECTORY_FORWARDING']

    @property
    def MODE_TRAJECTORY_STREAMING(self):
        """Message constant 'MODE_TRAJECTORY_STREAMING'."""
        return Metaclass_SingleDeviceState.__constants['MODE_TRAJECTORY_STREAMING']

    @property
    def POWER_UNKNOWN(self):
        """Message constant 'POWER_UNKNOWN'."""
        return Metaclass_SingleDeviceState.__constants['POWER_UNKNOWN']

    @property
    def POWER_OFF(self):
        """Message constant 'POWER_OFF'."""
        return Metaclass_SingleDeviceState.__constants['POWER_OFF']

    @property
    def POWER_STANDBY(self):
        """Message constant 'POWER_STANDBY'."""
        return Metaclass_SingleDeviceState.__constants['POWER_STANDBY']

    @property
    def POWER_ON(self):
        """Message constant 'POWER_ON'."""
        return Metaclass_SingleDeviceState.__constants['POWER_ON']

    @property
    def POWER_SLEEP(self):
        """Message constant 'POWER_SLEEP'."""
        return Metaclass_SingleDeviceState.__constants['POWER_SLEEP']

    @property
    def POWER_ERROR(self):
        """Message constant 'POWER_ERROR'."""
        return Metaclass_SingleDeviceState.__constants['POWER_ERROR']

    @property
    def POWER_LEVEL_LOW(self):
        """Message constant 'POWER_LEVEL_LOW'."""
        return Metaclass_SingleDeviceState.__constants['POWER_LEVEL_LOW']

    @property
    def POWER_LEVEL_CRITICAL(self):
        """Message constant 'POWER_LEVEL_CRITICAL'."""
        return Metaclass_SingleDeviceState.__constants['POWER_LEVEL_CRITICAL']

    @property
    def POWER_CHARGING(self):
        """Message constant 'POWER_CHARGING'."""
        return Metaclass_SingleDeviceState.__constants['POWER_CHARGING']

    @property
    def POWER_CHARGING_ERROR(self):
        """Message constant 'POWER_CHARGING_ERROR'."""
        return Metaclass_SingleDeviceState.__constants['POWER_CHARGING_ERROR']

    @property
    def CONNECT_UNKNOWN(self):
        """Message constant 'CONNECT_UNKNOWN'."""
        return Metaclass_SingleDeviceState.__constants['CONNECT_UNKNOWN']

    @property
    def CONNECT_UP(self):
        """Message constant 'CONNECT_UP'."""
        return Metaclass_SingleDeviceState.__constants['CONNECT_UP']

    @property
    def CONNECT_DOWN(self):
        """Message constant 'CONNECT_DOWN'."""
        return Metaclass_SingleDeviceState.__constants['CONNECT_DOWN']

    @property
    def CONNECT_FAILURE(self):
        """Message constant 'CONNECT_FAILURE'."""
        return Metaclass_SingleDeviceState.__constants['CONNECT_FAILURE']

    @property
    def CONNECTION_SLOW(self):
        """Message constant 'CONNECTION_SLOW'."""
        return Metaclass_SingleDeviceState.__constants['CONNECTION_SLOW']


class SingleDeviceState(metaclass=Metaclass_SingleDeviceState):
    """
    Message class 'SingleDeviceState'.

    Constants:
      HEALTH_UNKNOWN
      HEALTH_OK
      HEALTH_DEGRADED
      HEALTH_WARNING
      HEALTH_ERROR
      HEALTH_FATAL
      ERROR_NONE
      ERROR_UNKNOWN
      ERROR_HW
      ERROR_SW
      ERROR_OVER_TRAVEL
      EMERGENCY_STOP_HW
      EMERGENCY_STOP_SW
      PROTECTIVE_STOP_HW
      PROTECTIVE_STOP_SW
      SAFETY_STOP
      CALIBRATION_REQUIRED
      MODE_UNKNOWN
      MODE_MANUAL
      MODE_AUTO
      MODE_SAFE
      MODE_MAINTENANCE
      MODE_JOG_MANUAL
      MODE_ADMITTANCE
      MODE_MONITORED_STOP
      MODE_HOLD_TO_RUN
      MODE_CARTESIAN_TWIST
      MODE_CARTESIAN_POSE
      MODE_TRAJECTORY_FORWARDING
      MODE_TRAJECTORY_STREAMING
      POWER_UNKNOWN
      POWER_OFF
      POWER_STANDBY
      POWER_ON
      POWER_SLEEP
      POWER_ERROR
      POWER_LEVEL_LOW
      POWER_LEVEL_CRITICAL
      POWER_CHARGING
      POWER_CHARGING_ERROR
      CONNECT_UNKNOWN
      CONNECT_UP
      CONNECT_DOWN
      CONNECT_FAILURE
      CONNECTION_SLOW
    """

    __slots__ = [
        '_health_status',
        '_error_domain',
        '_operational_mode',
        '_power_state',
        '_connectivity_status',
        '_manufacturer',
        '_model',
        '_firmware_version',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'health_status': 'uint8',
        'error_domain': 'sequence<uint8>',
        'operational_mode': 'uint8',
        'power_state': 'uint8',
        'connectivity_status': 'uint8',
        'manufacturer': 'string',
        'model': 'string',
        'firmware_version': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint8')),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
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
        self.health_status = kwargs.get('health_status', int())
        self.error_domain = array.array('B', kwargs.get('error_domain', []))
        self.operational_mode = kwargs.get('operational_mode', int())
        self.power_state = kwargs.get('power_state', int())
        self.connectivity_status = kwargs.get('connectivity_status', int())
        self.manufacturer = kwargs.get('manufacturer', str())
        self.model = kwargs.get('model', str())
        self.firmware_version = kwargs.get('firmware_version', str())

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
        if self.health_status != other.health_status:
            return False
        if self.error_domain != other.error_domain:
            return False
        if self.operational_mode != other.operational_mode:
            return False
        if self.power_state != other.power_state:
            return False
        if self.connectivity_status != other.connectivity_status:
            return False
        if self.manufacturer != other.manufacturer:
            return False
        if self.model != other.model:
            return False
        if self.firmware_version != other.firmware_version:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def health_status(self):
        """Message field 'health_status'."""
        return self._health_status

    @health_status.setter
    def health_status(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'health_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'health_status' field must be an unsigned integer in [0, 255]"
        self._health_status = value

    @builtins.property
    def error_domain(self):
        """Message field 'error_domain'."""
        return self._error_domain

    @error_domain.setter
    def error_domain(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'B', \
                    "The 'error_domain' array.array() must have the type code of 'B'"
                self._error_domain = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'error_domain' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 255]"
        self._error_domain = array.array('B', value)

    @builtins.property
    def operational_mode(self):
        """Message field 'operational_mode'."""
        return self._operational_mode

    @operational_mode.setter
    def operational_mode(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'operational_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'operational_mode' field must be an unsigned integer in [0, 255]"
        self._operational_mode = value

    @builtins.property
    def power_state(self):
        """Message field 'power_state'."""
        return self._power_state

    @power_state.setter
    def power_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'power_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'power_state' field must be an unsigned integer in [0, 255]"
        self._power_state = value

    @builtins.property
    def connectivity_status(self):
        """Message field 'connectivity_status'."""
        return self._connectivity_status

    @connectivity_status.setter
    def connectivity_status(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'connectivity_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'connectivity_status' field must be an unsigned integer in [0, 255]"
        self._connectivity_status = value

    @builtins.property
    def manufacturer(self):
        """Message field 'manufacturer'."""
        return self._manufacturer

    @manufacturer.setter
    def manufacturer(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'manufacturer' field must be of type 'str'"
        self._manufacturer = value

    @builtins.property
    def model(self):
        """Message field 'model'."""
        return self._model

    @model.setter
    def model(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'model' field must be of type 'str'"
        self._model = value

    @builtins.property
    def firmware_version(self):
        """Message field 'firmware_version'."""
        return self._firmware_version

    @firmware_version.setter
    def firmware_version(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'firmware_version' field must be of type 'str'"
        self._firmware_version = value
