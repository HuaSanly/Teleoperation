# AGV设备状态消息

std_msgs/Header header

# 命令ID
string order_id

# 动作状态
string action_status

# 最后节点ID
int32 last_node_id

# 是否正在行驶
bool driving

# 电池电量 (%)
float32 battery_charge

# 操作模式
string operating_mode

# 错误类型
string error_type

# 错误描述
string error_description


# --- Action Status Constants ---------------------------------------
#  action execution states
string ACTION_WAITING    = "WAITING"     # Action is waiting to be executed
string ACTION_INITIALIZING = "INITIALIZING" # Action is being initialized
string ACTION_RUNNING    = "RUNNING"     # Action is currently executing
string ACTION_PAUSED     = "PAUSED"      # Action execution is paused
string ACTION_FINISHED   = "FINISHED"    # Action completed successfully
string ACTION_FAILED     = "FAILED"      # Action execution failed

# --- Operating Mode Constants -------------------------------------
#  vehicle operating modes
string MODE_AUTOMATIC    = "AUTOMATIC"   # Vehicle operates autonomously
string MODE_SEMI_AUTOMATIC = "SEMIAUTOMATIC" # Vehicle requires operator confirmation
string MODE_MANUAL       = "MANUAL"      # Vehicle is under manual control
string MODE_SERVICE      = "SERVICE"     # Vehicle is in service/maintenance mode
string MODE_EMERGENCY    = "EMERGENCY"   # Vehicle is in emergency mode
string MODE_TEACHIN      = "TEACHIN"     # Vehicle is in teach-in mode for route learning