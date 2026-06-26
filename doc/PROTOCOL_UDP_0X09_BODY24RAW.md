

# UDP 0X09 Body24Raw Protocol

本文档描述 `Type = 0x09` 的 PICO body tracking 24 关节原始数据包。该包只承载人体骨架数据，不承载 HMD、手柄 pose 或手柄按键。

当前发送端尚未实现该包；现有 body tracking 发送逻辑位于 [Assets/Scripts/PoseSend/PoseSenderV2.cs](../Assets/Scripts/PoseSend/PoseSenderV2.cs)，仍使用 `Type = 0x02` 的 V2 混合包。

## 1. 总览

- `Type = 0x09`
- `Version = 1`
- 默认发送目标频率：`72 Hz`
- 默认发送间隔：`1 / 72 s`，约 `13.89 ms`，由发送端按频率换算
- 数据源：`PXR_MotionTracking.GetBodyTrackingData(...).roleDatas[i]`
- 坐标源：PICO body tracking `localPose`
- 不发送：`globalPose`、HMD pose、controller pose、controller buttons
- 总长：`1236 bytes`

```text
Body24RawDatagramHeader : 16
BodyStateBlock          : 40
Joint24RawPoseQBlock    : 540
Joint24FullMotionQBlock : 640
-----------------------------
Total                   : 1236 bytes
```

## 2. Datagram Header

```c
struct Body24RawDatagramHeader0X09 {
    uint8_t  Type;         // 固定 0x09
    uint8_t  Version;      // 固定 1
    uint16_t TotalBytes;   // 固定 1236, 小端
    uint64_t TimestampMs;  // Unix 毫秒时间戳, 小端
    uint8_t  Profile;      // 1 = full motion quantized
    uint8_t  BodySpace;    // 0 = PICO body tracking localPose space
    uint8_t  BlockCount;   // 固定 3
    uint8_t  HeaderFlags;  // reserved
}; // 16 bytes
```

`BodySpace = 0` 表示：

- joint pose 直接来自 `BodyTrackingData.roleDatas[i].localPose`。
- 原始 root 空间不承诺是安全区原点、HMD 原点、Unity 世界原点或稳定全局地图原点。
- 接收端负责 pelvis-relative 转换、重定位跳变剔除和坐标系对齐。

## 3. Block Header

所有 block 使用相同的 4 bytes 头：

```c
struct Body24BlockHeader {
    uint8_t  BlockType;
    uint8_t  BlockFlags;
    uint16_t BlockBytes; // 小端，包含本 header
}; // 4 bytes
```

固定 block 顺序：

1. `BodyStateBlock`，`BlockType = 1`，`BlockBytes = 40`
2. `Joint24RawPoseQBlock`，`BlockType = 2`，`BlockBytes = 540`
3. `Joint24FullMotionQBlock`，`BlockType = 3`，`BlockBytes = 640`

## 4. BodyStateBlock

```c
struct BodyStateBlock0X09 {
    Body24BlockHeader Header;     // BlockType = 1, BlockBytes = 40

    int32_t  StateResult;         // GetBodyTrackingState return code
    int32_t  DataResult;          // GetBodyTrackingData return code
    uint8_t  IsTracking;          // 0/1
    uint8_t  StateCode;           // BodyTrackingStatusCode
    uint8_t  StateMessage;        // BodyTrackingMessage
    uint8_t  BodyFlags;

    uint32_t JointValidMask;      // bit i = role i localPose valid
    uint32_t ActionValidMask;     // bit i = role i bodyAction meaningful
    uint32_t SourceFlags;
    uint32_t Reserved;

    int64_t  BodyTimestamp;       // 建议 Pelvis.localPose.TimeStamp；SDK 原样透传
}; // 40 bytes
```

`BodyFlags`：

- bit0 = body tracking supported known
- bit1 = body tracking supported
- bit2 = body tracking session started
- bit3 = body tracking data available this frame
- bit4 = pelvis valid
- bit5 = sender detected possible root/joint discontinuity
- bit6 = `Joint24RawPoseQBlock` uses PICO `localPose`
- bit7 = reserved

`SourceFlags`：

- bit0 = pose data present
- bit1 = `bodyAction` present
- bit2 = linear velocity present
- bit3 = linear acceleration present
- bit4 = angular velocity present
- bit5 = angular acceleration present
- bit6 = values are quantized
- bit7 = velocity/acceleration axis sign verified against localPose delta
- bit8..31 = reserved

## 5. Joint Order

固定 24 个关节，顺序与 `BodyTrackerRole` 一致：

| Index | Role |
| ---: | --- |
| 0 | Pelvis |
| 1 | LEFT_HIP |
| 2 | RIGHT_HIP |
| 3 | SPINE1 |
| 4 | LEFT_KNEE |
| 5 | RIGHT_KNEE |
| 6 | SPINE2 |
| 7 | LEFT_ANKLE |
| 8 | RIGHT_ANKLE |
| 9 | SPINE3 |
| 10 | LEFT_FOOT |
| 11 | RIGHT_FOOT |
| 12 | NECK |
| 13 | LEFT_COLLAR |
| 14 | RIGHT_COLLAR |
| 15 | HEAD |
| 16 | LEFT_SHOULDER |
| 17 | RIGHT_SHOULDER |
| 18 | LEFT_ELBOW |
| 19 | RIGHT_ELBOW |
| 20 | LEFT_WRIST |
| 21 | RIGHT_WRIST |
| 22 | LEFT_HAND |
| 23 | RIGHT_HAND |

如果 `roleDatas[i].role != (BodyTrackerRole)i`，对应 bit 不应置 valid。

## 6. Joint24RawPoseQBlock

```c
struct Joint24RawPoseQBlock0X09 {
    Body24BlockHeader Header;     // BlockType = 2, BlockBytes = 540

    uint8_t  JointCount;          // 24
    uint8_t  JointPoseFlags;
    uint8_t  PositionScaleCode;   // 1 = 0.001 m
    uint8_t  Reserved;
    uint32_t ValidMask;

    JointPoseQEntry0X09 Joints[24];
}; // 540 bytes

struct JointPoseQEntry0X09 {
    int16_t Pos[3];               // round(localPose position / 0.001m)
    float   Rot[4];               // localPose RotQx/RotQy/RotQz/RotQw
}; // 22 bytes
```

`JointPoseFlags`：

- bit0 = quantized position present
- bit1 = rotation present
- bit2 = source is PICO body tracking `localPose`
- bit3 = raw/root space is not guaranteed stable across recenter/calibration/session changes
- bit4 = pelvis-relative conversion not applied
- bit5..7 = reserved

`PositionScaleCode = 1`：

```text
position_m = PosInt16 * 0.001
step       = 0.001 m
max error  = 0.0005 m
range      = [-32.768, 32.767] m
```

该位置精度是协议编码精度，不声明 PICO body tracking 的真实测量精度。

## 7. Joint24FullMotionQBlock

```c
struct Joint24FullMotionQBlock0X09 {
    Body24BlockHeader Header;     // BlockType = 3, BlockBytes = 640

    uint8_t  JointCount;          // 24
    uint8_t  MotionFlags;
    uint8_t  VelocityScaleCode;
    uint8_t  AccelerationScaleCode;
    uint8_t  AngularVelocityScaleCode;
    uint8_t  AngularAccelerationScaleCode;
    uint16_t Reserved;
    uint32_t ValidMask;

    JointFullMotionQEntry0X09 Entries[24];
}; // 640 bytes

struct JointFullMotionQEntry0X09 {
    int16_t Vel[3];               // velo
    int16_t Accel[3];             // acce
    int16_t AngularVel[3];        // wvelo
    int16_t AngularAccel[3];      // wacce
    uint16_t BodyAction;          // low 16 bits of BodyActionList
}; // 26 bytes
```

`MotionFlags`：

- bit0 = linear velocity present
- bit1 = linear acceleration present
- bit2 = angular velocity present
- bit3 = angular acceleration present
- bit4 = bodyAction present
- bit5 = values are SDK-provided, not sender-side finite difference
- bit6 = quantization saturated at least once in this block
- bit7 = reserved

Scale codes：

```text
VelocityScaleCode = 1:
  velocity_mps = VelInt16 * 0.001
  max error    = 0.0005 m/s
  range        = [-32.767, 32.767] m/s

AccelerationScaleCode = 1:
  accel_mps2 = AccelInt16 * 0.01
  max error  = 0.005 m/s^2
  range      = [-327.67, 327.67] m/s^2

AngularVelocityScaleCode = 1:
  angular_velocity_radps = AngularVelInt16 * 0.001
  max error              = 0.0005 rad/s
  range                  = [-32.767, 32.767] rad/s

AngularAccelerationScaleCode = 1:
  angular_accel_radps2 = AngularAccelInt16 * 0.01
  max error            = 0.005 rad/s^2
  range                = [-327.67, 327.67] rad/s^2

AngularAccelerationScaleCode = 2:
  angular_accel_radps2 = AngularAccelInt16 * 0.1
  max error            = 0.05 rad/s^2
  range                = [-3276.7, 3276.7] rad/s^2
```

线加速度固定使用 `AccelerationScaleCode = 1`。角加速度默认使用 `AngularAccelerationScaleCode = 1`；若本帧任一关节超过 code 1 范围，可切换到 code 2。超过最高范围时 clamp 到 `int16` 并置 `MotionFlags.bit6`。

`BodyAction` 当前关注值：

```text
PxrTouchGround = 1
PxrKeepStatic  = 2
```

如果 SDK 同时返回两个动作位，则 `BodyAction = 3`。

## 8. Wrist/Hand Source

`LEFT_WRIST`、`RIGHT_WRIST`、`LEFT_HAND`、`RIGHT_HAND` 来自 `PXR_MotionTracking.GetBodyTrackingData(...).roleDatas[i]`，不是 Unity `XRNode.LeftHand` / `XRNode.RightHand` 的手柄 pose。

手环、tracker、手柄同时存在时，PICO SDK 可能内部融合多个输入源，但当前 API 没有逐关节 provenance 标志。发送端不能可靠声明某个 wrist/hand joint 来自手柄或手环。

如果业务需要精确 controller pose，应使用独立 `0x02` 包，不要把本包的 `LEFT_HAND` / `RIGHT_HAND` 当作 controller pose。

## 9. Receiver Guidance

- `BT_INVALID` 或 `DataResult != 0`：不要信任本帧 joint/motion/action。
- `JointValidMask` 是关节可用性的主依据。
- `ActionValidMask` 是 `bodyAction` 是否有业务意义的主依据。
- `PxrTouchGround` 可作为脚/踝触地语义辅助。
- `PxrKeepStatic` 是对应 role 的静止提示，不是整个人静止。
- 若 root 或多个关节同帧大跳，优先判为 tracking discontinuity，不要直接判为真实高速运动。
- 接收端若需要 pelvis-relative pose，应自行使用 raw Pelvis 做转换。