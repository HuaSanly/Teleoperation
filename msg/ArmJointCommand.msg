# 机械臂14个电机命令消息
std_msgs/Header header
string[14] name          # 关节名称
float64[14] position     # 位置
float64[14] velocity     # 速度
float64[14] effort       # 力矩