# generated from rosidl_generator_py/resource/_idl.py.em
# with input from teleop_robot_bridge:msg/SingleGripperMove.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SingleGripperMove(type):
    """Metaclass of message 'SingleGripperMove'."""

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
                'teleop_robot_bridge.msg.SingleGripperMove')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__single_gripper_move
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__single_gripper_move
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__single_gripper_move
            cls._TYPE_SUPPORT = module.type_support_msg__msg__single_gripper_move
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__single_gripper_move

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SingleGripperMove(metaclass=Metaclass_SingleGripperMove):
    """Message class 'SingleGripperMove'."""

    __slots__ = [
        '_emergency_release',
        '_emergency_release_dir',
        '_stop',
        '_position',
        '_speed',
        '_force',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'emergency_release': 'boolean',
        'emergency_release_dir': 'uint8',
        'stop': 'boolean',
        'position': 'int32',
        'speed': 'int32',
        'force': 'int32',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
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
        self.emergency_release = kwargs.get('emergency_release', bool())
        self.emergency_release_dir = kwargs.get('emergency_release_dir', int())
        self.stop = kwargs.get('stop', bool())
        self.position = kwargs.get('position', int())
        self.speed = kwargs.get('speed', int())
        self.force = kwargs.get('force', int())

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
        if self.emergency_release != other.emergency_release:
            return False
        if self.emergency_release_dir != other.emergency_release_dir:
            return False
        if self.stop != other.stop:
            return False
        if self.position != other.position:
            return False
        if self.speed != other.speed:
            return False
        if self.force != other.force:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def emergency_release(self):
        """Message field 'emergency_release'."""
        return self._emergency_release

    @emergency_release.setter
    def emergency_release(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'emergency_release' field must be of type 'bool'"
        self._emergency_release = value

    @builtins.property
    def emergency_release_dir(self):
        """Message field 'emergency_release_dir'."""
        return self._emergency_release_dir

    @emergency_release_dir.setter
    def emergency_release_dir(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'emergency_release_dir' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'emergency_release_dir' field must be an unsigned integer in [0, 255]"
        self._emergency_release_dir = value

    @builtins.property
    def stop(self):
        """Message field 'stop'."""
        return self._stop

    @stop.setter
    def stop(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'stop' field must be of type 'bool'"
        self._stop = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'position' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'position' field must be an integer in [-2147483648, 2147483647]"
        self._position = value

    @builtins.property
    def speed(self):
        """Message field 'speed'."""
        return self._speed

    @speed.setter
    def speed(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'speed' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'speed' field must be an integer in [-2147483648, 2147483647]"
        self._speed = value

    @builtins.property
    def force(self):
        """Message field 'force'."""
        return self._force

    @force.setter
    def force(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'force' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'force' field must be an integer in [-2147483648, 2147483647]"
        self._force = value
