# generated from rosidl_generator_py/resource/_idl.py.em
# with input from teleop_robot_bridge:msg/AgvVda5050State.idl
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


class Metaclass_AgvVda5050State(type):
    """Metaclass of message 'AgvVda5050State'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ACTION_WAITING': 'WAITING',
        'ACTION_INITIALIZING': 'INITIALIZING',
        'ACTION_RUNNING': 'RUNNING',
        'ACTION_PAUSED': 'PAUSED',
        'ACTION_FINISHED': 'FINISHED',
        'ACTION_FAILED': 'FAILED',
        'MODE_AUTOMATIC': 'AUTOMATIC',
        'MODE_SEMI_AUTOMATIC': 'SEMIAUTOMATIC',
        'MODE_MANUAL': 'MANUAL',
        'MODE_SERVICE': 'SERVICE',
        'MODE_EMERGENCY': 'EMERGENCY',
        'MODE_TEACHIN': 'TEACHIN',
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
                'teleop_robot_bridge.msg.AgvVda5050State')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__agv_vda5050_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__agv_vda5050_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__agv_vda5050_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__agv_vda5050_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__agv_vda5050_state

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ACTION_WAITING': cls.__constants['ACTION_WAITING'],
            'ACTION_INITIALIZING': cls.__constants['ACTION_INITIALIZING'],
            'ACTION_RUNNING': cls.__constants['ACTION_RUNNING'],
            'ACTION_PAUSED': cls.__constants['ACTION_PAUSED'],
            'ACTION_FINISHED': cls.__constants['ACTION_FINISHED'],
            'ACTION_FAILED': cls.__constants['ACTION_FAILED'],
            'MODE_AUTOMATIC': cls.__constants['MODE_AUTOMATIC'],
            'MODE_SEMI_AUTOMATIC': cls.__constants['MODE_SEMI_AUTOMATIC'],
            'MODE_MANUAL': cls.__constants['MODE_MANUAL'],
            'MODE_SERVICE': cls.__constants['MODE_SERVICE'],
            'MODE_EMERGENCY': cls.__constants['MODE_EMERGENCY'],
            'MODE_TEACHIN': cls.__constants['MODE_TEACHIN'],
        }

    @property
    def ACTION_WAITING(self):
        """Message constant 'ACTION_WAITING'."""
        return Metaclass_AgvVda5050State.__constants['ACTION_WAITING']

    @property
    def ACTION_INITIALIZING(self):
        """Message constant 'ACTION_INITIALIZING'."""
        return Metaclass_AgvVda5050State.__constants['ACTION_INITIALIZING']

    @property
    def ACTION_RUNNING(self):
        """Message constant 'ACTION_RUNNING'."""
        return Metaclass_AgvVda5050State.__constants['ACTION_RUNNING']

    @property
    def ACTION_PAUSED(self):
        """Message constant 'ACTION_PAUSED'."""
        return Metaclass_AgvVda5050State.__constants['ACTION_PAUSED']

    @property
    def ACTION_FINISHED(self):
        """Message constant 'ACTION_FINISHED'."""
        return Metaclass_AgvVda5050State.__constants['ACTION_FINISHED']

    @property
    def ACTION_FAILED(self):
        """Message constant 'ACTION_FAILED'."""
        return Metaclass_AgvVda5050State.__constants['ACTION_FAILED']

    @property
    def MODE_AUTOMATIC(self):
        """Message constant 'MODE_AUTOMATIC'."""
        return Metaclass_AgvVda5050State.__constants['MODE_AUTOMATIC']

    @property
    def MODE_SEMI_AUTOMATIC(self):
        """Message constant 'MODE_SEMI_AUTOMATIC'."""
        return Metaclass_AgvVda5050State.__constants['MODE_SEMI_AUTOMATIC']

    @property
    def MODE_MANUAL(self):
        """Message constant 'MODE_MANUAL'."""
        return Metaclass_AgvVda5050State.__constants['MODE_MANUAL']

    @property
    def MODE_SERVICE(self):
        """Message constant 'MODE_SERVICE'."""
        return Metaclass_AgvVda5050State.__constants['MODE_SERVICE']

    @property
    def MODE_EMERGENCY(self):
        """Message constant 'MODE_EMERGENCY'."""
        return Metaclass_AgvVda5050State.__constants['MODE_EMERGENCY']

    @property
    def MODE_TEACHIN(self):
        """Message constant 'MODE_TEACHIN'."""
        return Metaclass_AgvVda5050State.__constants['MODE_TEACHIN']


class AgvVda5050State(metaclass=Metaclass_AgvVda5050State):
    """
    Message class 'AgvVda5050State'.

    Constants:
      ACTION_WAITING
      ACTION_INITIALIZING
      ACTION_RUNNING
      ACTION_PAUSED
      ACTION_FINISHED
      ACTION_FAILED
      MODE_AUTOMATIC
      MODE_SEMI_AUTOMATIC
      MODE_MANUAL
      MODE_SERVICE
      MODE_EMERGENCY
      MODE_TEACHIN
    """

    __slots__ = [
        '_header',
        '_order_id',
        '_action_status',
        '_last_node_id',
        '_driving',
        '_battery_charge',
        '_operating_mode',
        '_error_type',
        '_error_description',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'order_id': 'string',
        'action_status': 'string',
        'last_node_id': 'int32',
        'driving': 'boolean',
        'battery_charge': 'float',
        'operating_mode': 'string',
        'error_type': 'string',
        'error_description': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
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
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.order_id = kwargs.get('order_id', str())
        self.action_status = kwargs.get('action_status', str())
        self.last_node_id = kwargs.get('last_node_id', int())
        self.driving = kwargs.get('driving', bool())
        self.battery_charge = kwargs.get('battery_charge', float())
        self.operating_mode = kwargs.get('operating_mode', str())
        self.error_type = kwargs.get('error_type', str())
        self.error_description = kwargs.get('error_description', str())

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
        if self.header != other.header:
            return False
        if self.order_id != other.order_id:
            return False
        if self.action_status != other.action_status:
            return False
        if self.last_node_id != other.last_node_id:
            return False
        if self.driving != other.driving:
            return False
        if self.battery_charge != other.battery_charge:
            return False
        if self.operating_mode != other.operating_mode:
            return False
        if self.error_type != other.error_type:
            return False
        if self.error_description != other.error_description:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if self._check_fields:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def order_id(self):
        """Message field 'order_id'."""
        return self._order_id

    @order_id.setter
    def order_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'order_id' field must be of type 'str'"
        self._order_id = value

    @builtins.property
    def action_status(self):
        """Message field 'action_status'."""
        return self._action_status

    @action_status.setter
    def action_status(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'action_status' field must be of type 'str'"
        self._action_status = value

    @builtins.property
    def last_node_id(self):
        """Message field 'last_node_id'."""
        return self._last_node_id

    @last_node_id.setter
    def last_node_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'last_node_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'last_node_id' field must be an integer in [-2147483648, 2147483647]"
        self._last_node_id = value

    @builtins.property
    def driving(self):
        """Message field 'driving'."""
        return self._driving

    @driving.setter
    def driving(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'driving' field must be of type 'bool'"
        self._driving = value

    @builtins.property
    def battery_charge(self):
        """Message field 'battery_charge'."""
        return self._battery_charge

    @battery_charge.setter
    def battery_charge(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'battery_charge' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'battery_charge' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._battery_charge = value

    @builtins.property
    def operating_mode(self):
        """Message field 'operating_mode'."""
        return self._operating_mode

    @operating_mode.setter
    def operating_mode(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'operating_mode' field must be of type 'str'"
        self._operating_mode = value

    @builtins.property
    def error_type(self):
        """Message field 'error_type'."""
        return self._error_type

    @error_type.setter
    def error_type(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'error_type' field must be of type 'str'"
        self._error_type = value

    @builtins.property
    def error_description(self):
        """Message field 'error_description'."""
        return self._error_description

    @error_description.setter
    def error_description(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'error_description' field must be of type 'str'"
        self._error_description = value
