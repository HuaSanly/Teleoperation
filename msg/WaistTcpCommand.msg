# 腰部 TCP 位姿命令消息
std_msgs/Header header
string[1] name
float64[3] position
float64[3] euler        # 欧拉角顺序为[roll, pitch, yaw]
float64[4] quat         # 四元数顺序为[x, y, z, w]