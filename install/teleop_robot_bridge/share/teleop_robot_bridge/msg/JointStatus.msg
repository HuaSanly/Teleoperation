# 单个执行器（电机+驱动器）状态

# 驱动器信息
float32 driver_voltage          # 驱动器电压 (V)
float32 driver_temperature      # 驱动器温度 (°C)
uint8 driver_state              # 驱动器状态码

# 电机信息
float32 motor_temperature       # 电机温度 (°C)
int32 rpm                       # 转速 (转/分钟)
float32 current                 # 电流 (A)
int64 pulse_count               # 脉冲计数
int32 motor_angles              # 电机角度
int32 motor_speeds              # 电机速度
int32 motor_loads               # 电机负载
