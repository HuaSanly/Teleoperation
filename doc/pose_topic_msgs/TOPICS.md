# 位姿流 Topics 与 Msg 类型

| Topic | Msg 类型 | 对应文件 | 含义说明 |
|---|---|---|---|
| /teleop/pose/hmd | geometry_msgs/PoseStamped | PoseStamped.msg | 头显（HMD）位姿（位置+四元数） |
| /teleop/pose/left_controller | geometry_msgs/PoseStamped | PoseStamped.msg | 左手控制器位姿 |
| /teleop/pose/right_controller | geometry_msgs/PoseStamped | PoseStamped.msg | 右手控制器位姿 |
| /teleop/euler/hmd | geometry_msgs/Vector3Stamped | Vector3Stamped.msg | 头显欧拉角（单位：度） |
| /teleop/euler/left_controller | geometry_msgs/Vector3Stamped | Vector3Stamped.msg | 左手控制器欧拉角（单位：度） |
| /teleop/euler/right_controller | geometry_msgs/Vector3Stamped | Vector3Stamped.msg | 右手控制器欧拉角（单位：度） |
| /teleop/controller/left_joy | sensor_msgs/Joy | Joy.msg | 左手控制器按键/摇杆/扳机状态 |
| /teleop/controller/right_joy | sensor_msgs/Joy | Joy.msg | 右手控制器按键/摇杆/扳机状态 |
| /teleop/aim/left | geometry_msgs/PoseStamped | PoseStamped.msg | 左手瞄准射线位姿 |
| /teleop/aim/right | geometry_msgs/PoseStamped | PoseStamped.msg | 右手瞄准射线位姿 |
| /teleop/aim/left_valid | std_msgs/Bool | Bool.msg | 左手瞄准数据是否有效 |
| /teleop/aim/right_valid | std_msgs/Bool | Bool.msg | 右手瞄准数据是否有效 |
| /teleop/aim/left_pinch | std_msgs/Bool | Bool.msg | 左手是否捏合 |
| /teleop/aim/right_pinch | std_msgs/Bool | Bool.msg | 右手是否捏合 |
| /teleop/aim/left_pinch_strength | std_msgs/Float32 | Float32.msg | 左手捏合强度（0~1） |
| /teleop/aim/right_pinch_strength | std_msgs/Float32 | Float32.msg | 右手捏合强度（0~1） |

## Joy.msg 数组含义

以下索引对左右手控制器一致（分别对应 /teleop/controller/left_joy 与 /teleop/controller/right_joy）。

### axes

| 索引 | 含义 |
|---|---|
| 0 | 扳机模拟量（trigger_value） |
| 1 | 握把模拟量（grip_value） |
| 2 | 摇杆 X（thumbstick_x） |
| 3 | 摇杆 Y（thumbstick_y） |

### buttons

| 索引 | 含义 |
|---|---|
| 0 | 扳机按键（trigger_button） |
| 1 | 握把按键（grip_button） |
| 2 | 主按键（primary_button） |
| 3 | 次按键（secondary_button） |
| 4 | 菜单键（menu_button） |
| 5 | 摇杆按下（thumbstick_click） |
| 6 | 摇杆触摸（thumbstick_touch） |
