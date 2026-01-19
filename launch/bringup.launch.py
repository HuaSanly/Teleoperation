import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('teleop_robot_bridge'), 'config', 'config.yaml')
    # Create node
    main_node = Node(
        package='teleop_robot_bridge',
        executable='teleop_robot_bridge',
        name='teleop_robot_bridge',
        output='screen',
        parameters=[config]
    )

    return LaunchDescription([
        main_node
    ])
