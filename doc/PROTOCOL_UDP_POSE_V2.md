# UDP 位姿协议 V2

本文档只描述当前发送端已经实现的 V2 UDP 包格式，不描述设计预期，也不包含待实现项。

当前实现位于 [Assets/Scripts/PoseSend/PoseSenderV2.cs](Assets/Scripts/PoseSend/PoseSenderV2.cs)。

## 1. 总览

V2 为固定长度单包，固定 3 个块，固定顺序：

1. SensorRawBlock
2. ButtonsBlock
3. Joint24Block

当前实现固定总长为 930 bytes。

```text
PoseDatagramHeaderV2 : 16
SensorRawBlock       : 176
ButtonsBlock         : 54
Joint24Block         : 684
--------------------------
V2 Total             : 930
```

## 2. 数据报头

```c
struct PoseDatagramHeaderV2 {
    uint8_t  Type;         // 固定 0x02
    uint8_t  Version;      // 固定 2
    uint16_t TotalBytes;   // 固定 930, 小端
    uint64_t TimestampMs;  // Unix 毫秒时间戳, 小端
    uint8_t  RefSpace;     // 固定 0
    uint8_t  OriginSensor; // 固定 0, 当前表示 tracking space 原点
    uint8_t  BlockCount;   // 固定 3
    uint8_t  Reserved;     // 固定 0
};
```

当前实现中：

- `RefSpace = 0`
- `OriginSensor = 0`，当前第一块使用 tracking space 原点
- `BlockCount = 3`

## 3. SensorRawBlock

### 3.1 结构

```c
struct PoseBlockHeader {
    uint8_t  BlockType;   // 1
    uint8_t  BlockFlags;  // 0
    uint16_t BlockBytes;  // 176
};

struct SensorRawBlockHeader {
    uint8_t  SensorMask;
    uint8_t  PoseFlags;   // 固定 0x00
    uint8_t  EntryCount;  // 固定 3
    uint8_t  Reserved;    // 0
    float    ReservedPos[3]; // 当前固定写 0
    float    ReservedRot[4]; // 当前固定写 0
};

struct SensorPoseEntry {
    float Pos[3];
    float Rot[4];
};
```

固定顺序：

1. HMD
2. LeftController
3. RightController
4. LeftFootTracker（当前保留占位，固定无效）
5. RightFootTracker（当前保留占位，固定无效）

### 3.2 数据来源

当前实现保留了 `SensorRawBlock` 这一块的固定长度结构，但当前只使用其中的 HMD/左右手柄条目：

- HMD: `XRNode.Head` 的 `devicePosition/deviceRotation`
- LeftController: `XRNode.LeftHand` 的 `devicePosition/deviceRotation`
- RightController: `XRNode.RightHand` 的 `devicePosition/deviceRotation`
- WaistAbsPos/Rot: 当前固定写 0，仅作兼容占位
- LeftFootTracker: 当前固定无效，仅作兼容占位
- RightFootTracker: 当前固定无效，仅作兼容占位

当前实现不再读取 raw motion tracker pose，也不再把腰/脚写进第一块。

### 3.3 有效位定义

`SensorMask` 当前实现定义：

- bit0 = HMD valid
- bit1 = WaistTracker reserved, 当前固定 0
- bit2 = LeftController valid
- bit3 = RightController valid
- bit4 = LeftFootTracker reserved, 当前固定 0
- bit5 = RightFootTracker reserved, 当前固定 0

`PoseFlags` 当前固定为：

- `0x00`，当前表示第一块条目直接写 tracking-space 原始位姿，不做相对腰部转换

### 3.4 当前填充规则

当前实现第一块只写 tracking-space 下的 HMD / 左右手柄原始位姿：

- HMD / 左右手柄直接写 `devicePosition/deviceRotation`
- 不再做“相对 pelvis / 腰部”的坐标变换
- 腰部字段与左右脚字段固定按无效占位写入

### 3.5 缺失值写法

当前实现对第一块缺失/占位数据的写法分两类：

1. `ReservedPos/Rot`

- 当前固定写入 7 个 `0.0f`。
- 也就是位置为 `(0,0,0)`，旋转为 `(0,0,0,0)`。

2. HMD / 左右手柄 / 左右脚条目

- 使用默认的 `WritePose(...)` 写入。
- 如果无效，当前实际写入为：
  - 位置 `(0,0,0)`
  - 旋转 `(0,0,0,1)`

接收端应以 `SensorMask` 为准，而不是只看数值本身。当前只有 bit0/bit2/bit3 可能为 1。

## 4. ButtonsBlock

### 4.1 结构

```c
struct PoseBlockHeader {
    uint8_t  BlockType;   // 2
    uint8_t  BlockFlags;  // 0
    uint16_t BlockBytes;  // 54
};

struct ButtonsBlockHeader {
    uint8_t  ControllerMask;
    uint8_t  Reserved0;
    uint8_t  Reserved1;
    uint8_t  Reserved2;
};

struct ControllerButtonsEntry {
    float   TriggerValue;
    uint8_t TriggerButton;
    float   GripValue;
    uint8_t GripButton;
    uint8_t PrimaryButton;
    uint8_t SecondaryButton;
    uint8_t MenuButton;
    float   ThumbstickX;
    float   ThumbstickY;
    uint8_t ThumbstickClick;
    uint8_t ThumbstickTouch;
};
```

固定顺序：

1. LeftController
2. RightController

### 4.2 数据来源

当前实现直接读取 `InputDevices.GetDeviceAtXRNode(...)` 的常用 feature：

- `trigger`
- `triggerButton`
- `grip`
- `gripButton`
- `primaryButton`
- `secondaryButton`
- `menuButton`
- `primary2DAxis`
- `primary2DAxisClick`
- `primary2DAxisTouch`

### 4.3 有效位定义

`ControllerMask` 当前实现定义：

- bit0 = LeftController valid
- bit1 = RightController valid

这里的 valid 只取决于 `InputDevice.isValid`。

这意味着：

- 即使 pelvis 无效，ButtonsBlock 也可能仍然有有效位。
- ButtonsBlock 是否有效，与 SensorRawBlock 的手柄 pose 是否有效不是同一个条件。

### 4.4 缺失值写法

如果某只手柄无效，当前实现写入该手柄条目时所有数值字段为 `0`，所有按钮字段为 `0`。

## 5. Joint24Block

### 5.1 结构

```c
struct PoseBlockHeader {
    uint8_t  BlockType;   // 3
    uint8_t  BlockFlags;  // 0
    uint16_t BlockBytes;  // 684
};

struct Joint24BlockHeader {
    uint8_t  JointCount;  // 固定 24
    uint8_t  JointFlags;  // 固定 0x07
    uint16_t Reserved;    // 0
    uint32_t ValidMask;
};

struct JointPoseEntry {
    float Pos[3];
    float Rot[4];
};
```

固定 24 个关节，顺序与 `BodyTrackerRole` 一致：

1. Pelvis
2. LEFT_HIP
3. RIGHT_HIP
4. SPINE1
5. LEFT_KNEE
6. RIGHT_KNEE
7. SPINE2
8. LEFT_ANKLE
9. RIGHT_ANKLE
10. SPINE3
11. LEFT_FOOT
12. RIGHT_FOOT
13. NECK
14. LEFT_COLLAR
15. RIGHT_COLLAR
16. HEAD
17. LEFT_SHOULDER
18. RIGHT_SHOULDER
19. LEFT_ELBOW
20. RIGHT_ELBOW
21. LEFT_WRIST
22. RIGHT_WRIST
23. LEFT_HAND
24. RIGHT_HAND

### 5.2 数据来源

当前实现通过：

- `PXR_MotionTracking.GetBodyTrackingState(...)`
- `PXR_MotionTracking.GetBodyTrackingData(...)`

读取 `BodyTrackingData.roleDatas[i].localPose` 作为关节输入数据。

### 5.3 当前填充规则

Joint24Block 直接承载 body tracking 输出的原始关节位姿，不再由发送端转换成相对 `Pelvis` 的 pose。

Joint24Block 只有在下面两个条件同时满足时才会产生有效数据：

1. body tracking 当前有效
2. `Pelvis` joint 当前有效

满足时：

- 所有关节直接写入原始关节 pose
- `ValidMask` 标记当前确实有 body tracking 数据的原始关节
- 接收端如果需要“以腰部/Pelvis 为原点”的 24 关节数组，需要基于 `joint24[0]` (`Pelvis`) 自行转换

不满足时：

- `ValidMask = 0`
- 24 个关节条目全部按无效值写入

### 5.4 缺失值写法

无效关节当前写入为：

- 位置 `(0,0,0)`
- 旋转 `(0,0,0,1)`

## 6. 当前发送行为摘要

当前实现可以概括为：

- 包结构固定，大小固定，顺序固定。
- 第一块结构仍保留固定长度，但当前只承载 HMD / 左右手柄的 tracking-space 原始位姿。
- 第一块不再承载腰和双脚，也不再做相对 pelvis 的坐标变换。
- 第三块继续使用 body tracking 的原始关节 pose，不再在发送端转换成相对 `Pelvis` 的 pose。
- ROS2 接收端同时发布原始 24 关节数组和本地转换出的腰部原点 24 关节数组。
- buttons block 独立于 pose，可单独有效。
- 缺失值会被明确写成默认值，真正的有效性由 mask 决定。

## 7. ROS2 接收端发布话题

当前 ROS2 接收端实现位于 `teleop_robot_bridge/src/udp/pose_udp_receiver.cpp`。

### 7.1 第一块对应的话题

第一块当前只直接发布 HMD 和左右手柄的 tracking-space 原始位姿：

- `teleop/pose/hmd`
    - 类型: `geometry_msgs/msg/PoseStamped`
    - 来源: `SensorRawBlock` 第 1 个条目
- `teleop/pose/left_controller`
    - 类型: `geometry_msgs/msg/PoseStamped`
    - 来源: `SensorRawBlock` 第 2 个条目
- `teleop/pose/right_controller`
    - 类型: `geometry_msgs/msg/PoseStamped`
    - 来源: `SensorRawBlock` 第 3 个条目

接收端当前不再从第一块发布腰和双脚，因为这几个位置在第一块里已经变成兼容占位。

### 7.2 第二块对应的话题

第二块发布左右手柄按键状态：

- `teleop/controller/left_joy`
    - 类型: `sensor_msgs/msg/Joy`
- `teleop/controller/right_joy`
    - 类型: `sensor_msgs/msg/Joy`

`Joy.axes` 当前固定顺序为：

1. `trigger_value`
2. `grip_value`
3. `thumbstick_x`
4. `thumbstick_y`

`Joy.buttons` 当前固定顺序为：

1. `trigger_button`
2. `grip_button`
3. `primary_button`
4. `secondary_button`
5. `menu_button`
6. `thumbstick_click`
7. `thumbstick_touch`

### 7.3 第三块对应的话题

第三块当前已经完整发布为原始 24 关节数组、腰部原点 24 关节数组，以及各自的有效位掩码：

- `teleop/pose/joint24`
    - 类型: `geometry_msgs/msg/PoseArray`
    - `header.stamp`: 取自 UDP 包头 `TimestampMs`
    - `header.frame_id`: 当前接收端使用 `pose_udp.frame_id.joint24` 对应配置值，默认 `vr_tracking`
    - `poses.size()`: 固定 24
    - 内容: UDP 第三块收到的原始关节 pose
- `teleop/pose/joint24_valid_mask`
    - 类型: `std_msgs/msg/UInt32`
    - 内容: 直接对应 `Joint24BlockHeader.ValidMask`
- `teleop/pose/joint24_waist`
    - 类型: `geometry_msgs/msg/PoseArray`
    - `header.stamp`: 取自 UDP 包头 `TimestampMs`
    - `header.frame_id`: 当前接收端使用 `pose_udp.frame_id.waist` 对应配置值，默认 `vr_waist`
    - `poses.size()`: 固定 24
    - 内容: 接收端用 `joint24[0]` (`Pelvis`) 转换出的腰部原点关节 pose
- `teleop/pose/joint24_waist_valid_mask`
    - 类型: `std_msgs/msg/UInt32`
    - 内容: 腰部原点转换后的有效位；如果 `Pelvis` 无效，则为 `0`

`teleop/pose/joint24.poses[i]` 的索引与协议中的 24 个关节顺序严格一致：

1. `poses[0]` = `Pelvis`
2. `poses[1]` = `LEFT_HIP`
3. `poses[2]` = `RIGHT_HIP`
4. `poses[3]` = `SPINE1`
5. `poses[4]` = `LEFT_KNEE`
6. `poses[5]` = `RIGHT_KNEE`
7. `poses[6]` = `SPINE2`
8. `poses[7]` = `LEFT_ANKLE`
9. `poses[8]` = `RIGHT_ANKLE`
10. `poses[9]` = `SPINE3`
11. `poses[10]` = `LEFT_FOOT`
12. `poses[11]` = `RIGHT_FOOT`
13. `poses[12]` = `NECK`
14. `poses[13]` = `LEFT_COLLAR`
15. `poses[14]` = `RIGHT_COLLAR`
16. `poses[15]` = `HEAD`
17. `poses[16]` = `LEFT_SHOULDER`
18. `poses[17]` = `RIGHT_SHOULDER`
19. `poses[18]` = `LEFT_ELBOW`
20. `poses[19]` = `RIGHT_ELBOW`
21. `poses[20]` = `LEFT_WRIST`
22. `poses[21]` = `RIGHT_WRIST`
23. `poses[22]` = `LEFT_HAND`
24. `poses[23]` = `RIGHT_HAND`

### 7.4 腰部原点转换规则

接收端将原始关节数组转换成腰部原点数组时使用：

```text
pelvis = raw_joint24[0]
joint24_waist[i].position = inverse(pelvis.rotation) * (raw_joint24[i].position - pelvis.position)
joint24_waist[i].rotation = inverse(pelvis.rotation) * raw_joint24[i].rotation
```

只有当 `Pelvis` 有效且对应关节有效时，`joint24_waist_valid_mask` 中对应位才会置 1。`Pelvis` 无效时，接收端仍发布固定 24 个默认 pose，但 `joint24_waist_valid_mask = 0`。
