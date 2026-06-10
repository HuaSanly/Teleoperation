import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    package_share = get_package_share_directory('teleop_robot_bridge')
    default_params_file = os.path.join(package_share, 'config', 'params.yaml')
    default_fov_file = os.path.join(package_share, 'config', 'fov.yaml')

    params_file = LaunchConfiguration('params_file')
    fov_file = LaunchConfiguration('fov_file')

    main_node = Node(
        package='teleop_robot_bridge',
        executable='teleop_robot_bridge',
        name='teleop_robot_bridge',
        output='screen',
        parameters=[
            params_file,
            {'video.fov_file': fov_file},
        ]
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'params_file',
            default_value=default_params_file,
            description='Main ROS2 parameter file for teleop_robot_bridge'),
        DeclareLaunchArgument(
            'fov_file',
            default_value=default_fov_file,
            description='Video FOV table parameter file for teleop_robot_bridge'),
        main_node
    ])
