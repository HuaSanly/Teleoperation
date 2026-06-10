# AGV设备状态消息（通用硬件状态）

std_msgs/Header header

# 设备健康状态
uint8 health_status

# 错误域（单个错误代码）
uint8 error_domain

# 操作模式
uint8 operational_mode

# 电源状态
uint8 power_state

# 连接状态
uint8 connectivity_status

# 制造商名称
string manufacturer

# 设备型号
string model

# 固件版本
string firmware_version

# --- Health Status Constants -------------------------------------
uint8 HEALTH_UNKNOWN  = 0
uint8 HEALTH_OK       = 1
uint8 HEALTH_DEGRADED = 2
uint8 HEALTH_WARNING  = 3
uint8 HEALTH_ERROR    = 4
uint8 HEALTH_FATAL    = 5

# --- Error Domain Constants --------------------------------------
uint8 ERROR_NONE           = 0
uint8 ERROR_UNKNOWN        = 1
uint8 ERROR_HW             = 2
uint8 ERROR_SW             = 3
uint8 ERROR_OVER_TRAVEL    = 4
uint8 EMERGENCY_STOP_HW    = 5
uint8 EMERGENCY_STOP_SW    = 6
uint8 PROTECTIVE_STOP_HW   = 7
uint8 PROTECTIVE_STOP_SW   = 8
uint8 SAFETY_STOP          = 9
uint8 CALIBRATION_REQUIRED = 10

# --- Operational Mode Constants ----------------------------------
uint8 MODE_UNKNOWN              = 0
uint8 MODE_MANUAL               = 1
uint8 MODE_AUTO                 = 2
uint8 MODE_SAFE                 = 3
uint8 MODE_MAINTENANCE          = 4
uint8 MODE_JOG_MANUAL           = 5
uint8 MODE_ADMITTANCE           = 6
uint8 MODE_MONITORED_STOP       = 7
uint8 MODE_HOLD_TO_RUN          = 8
uint8 MODE_CARTESIAN_TWIST      = 9
uint8 MODE_CARTESIAN_POSE       = 10
uint8 MODE_TRAJECTORY_FORWARDING = 11
uint8 MODE_TRAJECTORY_STREAMING  = 12

# --- Power State Constants ---------------------------------------
uint8 POWER_UNKNOWN         = 0
uint8 POWER_OFF             = 1
uint8 POWER_STANDBY         = 2
uint8 POWER_ON              = 3
uint8 POWER_SLEEP           = 4
uint8 POWER_ERROR           = 5
uint8 POWER_LEVEL_LOW       = 6
uint8 POWER_LEVEL_CRITICAL  = 7
uint8 POWER_CHARGING        = 8
uint8 POWER_CHARGING_ERROR  = 9

# --- Connectivity Status Constants -------------------------------
uint8 CONNECT_UNKNOWN    = 0
uint8 CONNECT_UP         = 1
uint8 CONNECT_DOWN       = 2
uint8 CONNECT_FAILURE    = 3
uint8 CONNECTION_SLOW    = 4
