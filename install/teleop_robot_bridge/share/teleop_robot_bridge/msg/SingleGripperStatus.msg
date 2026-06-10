# 单个抓手状态消息

# 状态标志
bool is_ready           # 是否就绪
bool is_reset           # 是否复位
bool is_moving          # 是否运动中
bool obj_detected       # 是否检测到物体

# 故障状态码
uint8 fault_status

# 位置信息
int32 position          # 当前位置
int32 requested_position # 目标位置

# 电流信息
float32 current         # 电流 (A)
