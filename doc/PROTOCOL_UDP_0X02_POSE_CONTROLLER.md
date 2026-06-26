# UDP 0X02 HMD/Controller Pose Protocol

本文档描述 `Type = 0x02` 的 HMD、左右手柄位姿和手柄按键包。该包沿用现有发送链路，不承载 body tracking 24 关节数据。

当前发送实现位于 [Assets/Scripts/PoseSend/PoseSender.cs](../Assets/Scripts/PoseSend/PoseSender.cs)。

## 1. 总览

- `Type = 0x02`
- `Version = 1`
- 默认发送目标频率：`72 Hz`
- 默认发送间隔：`1 / 72 s`，约 `13.89 ms`，由发送端按频率换算
- 数据源：Unity XR input / XROrigin tracking space
- 内容：HMD pose、LeftController pose、RightController pose、可选欧拉角、手柄按键、可选 aim 数据
- 不包含：PICO body tracking 24 关节、bodyAction、body tracking 速度/加速度

当前标准配置为“位姿 + 按键”，总长 `143 bytes`。

```text
Header      : 13 bytes
Pose Data   : 84 bytes  (3 devices * 28 bytes)
Buttons     : 46 bytes  (2 controllers * 23 bytes)
----------------------
Total       : 143 bytes
```

## 2. Header

```c
struct PoseControllerHeader0X02 {
    uint8_t  Type;          // 固定 0x02
    uint64_t TimestampMs;   // Unix 毫秒时间戳, 小端
    uint8_t  Version;       // 固定 1
    uint8_t  Flags;         // 特性标志
    uint8_t  Reserved0;     // 0
    uint8_t  Reserved1;     // 0
}; // 13 bytes
```

`Flags`：

| Bit | Mask | Name | 含义 |
| --- | --- | --- | --- |
| 0 | `0x01` | `INCLUDE_EULER` | 每个设备追加欧拉角调试字段 |
| 1 | `0x02` | `INCLUDE_AIM` | 追加左右手 aim 数据 |
| 2 | `0x04` | `INCLUDE_BUTTONS` | 追加左右手柄按键数据 |
| 3..7 | - | reserved | 保留 |

当前发送端默认 `INCLUDE_BUTTONS = true`，`INCLUDE_EULER = false`，`INCLUDE_AIM = false`。

## 3. Pose Data

固定顺序：

1. HMD
2. LeftController
3. RightController

```c
struct PoseEntry0X02 {
    float Pos[3]; // x/y/z, meters
    float Rot[4]; // qx/qy/qz/qw
}; // 28 bytes
```

数据来源：

- HMD：`Camera` transform 或 `XRNode.Head`
- LeftController：`XRNode.LeftHand`
- RightController：`XRNode.RightHand`

发送端当前可按配置选择 local tracking space 或 world space。默认 `_useLocalSpace = false` 时，会通过 XROrigin 的 tracking-to-world transform 转换到 Unity world reference。

## 4. Buttons Data

当 `Flags & 0x04 != 0` 时存在。

固定顺序：

1. LeftController
2. RightController

```c
struct ControllerButtonsEntry0X02 {
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
}; // 23 bytes
```

读取的 Unity XR feature：

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

## 5. Optional Euler Data

当 `Flags & 0x01 != 0` 时存在。固定顺序与 pose data 相同。

```c
struct EulerEntry0X02 {
    float EulerDeg[3]; // x/y/z, degrees
}; // 12 bytes
```

欧拉角仅用于调试，不建议作为控制主输入。

## 6. Optional Aim Data

当 `Flags & 0x02 != 0` 时存在。固定顺序：LeftHand、RightHand。

```c
struct AimEntry0X02 {
    uint8_t Valid;
    uint8_t Pinch;
    float   PinchStrength;
    float   RayPos[3];
    float   RayRot[4];
    float   Reserved;
}; // 38 bytes
```

## 7. Size Table

```text
Base pose only:
Header      13
Pose        84
Total       97 bytes

Standard pose + buttons:
Header      13
Pose        84
Buttons     46
Total       143 bytes

Full debug pose + euler + buttons + aim:
Header      13
Pose        84
Euler       36
Buttons     46
Aim         76
Total       255 bytes
```

## 8. Relationship With 0X09

`0x02` 只表示 XR HMD/controller pose 和 controller input。PICO body tracking 24 关节数据使用独立 `Type = 0x09`，见 [PROTOCOL_UDP_0X09_BODY24RAW.md](PROTOCOL_UDP_0X09_BODY24RAW.md)。

接收端不要把 `0x09` 的 `LEFT_HAND` / `RIGHT_HAND` body joint 当作手柄 pose。若需要精确手柄位姿，应使用本 `0x02` 包。