# Arm关节状态消息（14个执行器）

std_msgs/Header header

#关节名称
string[14] name

# 14个关节的状态数组
teleop_robot_bridge/JointStatus[14] joint_status