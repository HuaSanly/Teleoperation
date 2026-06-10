# 双末端 TCP 位姿命令消息
std_msgs/Header header
string[2] name
float64[6] position     # 前3个为name[0]的xyz，后3个为name[1]的xyz
float64[6] euler        # 前3个为name[0]的欧拉角[roll, pitch, yaw]，后3个为name[1]的欧拉角[roll, pitch, yaw]
float64[8] quat         # 前4个为name[0]的四元数[x, y, z, w]，后4个为name[1]的四元数[x, y, z, w]