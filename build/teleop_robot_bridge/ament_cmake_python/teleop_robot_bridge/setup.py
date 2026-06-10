from setuptools import find_packages
from setuptools import setup

setup(
    name='teleop_robot_bridge',
    version='0.0.0',
    packages=find_packages(
        include=('teleop_robot_bridge', 'teleop_robot_bridge.*')),
)
