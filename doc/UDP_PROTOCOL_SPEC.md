# UDP 协议规格

> 状态：草案  
> 适用范围：机器人端重写时必须保持兼容的 UDP wire protocol。  
> 原则：服务器端和 VR 端无感，现有 UDP 包格式不变。

## 1. 总览

当前 UDP 通道分为两类：

```text
共享媒体/遥测 UDP 通道:
  机器人端 -> 远端
  Type 0x01: video
  Type 0x04: audio
  Type 0x05: low-rate robot telemetry
  Type 0x06: high-rate robot telemetry
  text: HELLO / PING / ACK control plane

独立姿态 UDP 通道:
  VR 端 -> 机器人端
  Type 0x02: pose V2
```

新机器人端实现必须保留现有共享 UDP 通道的 wire format，并继续支持姿态 UDP 接收。

## 2. 基本约定

- 多字节字段使用 Little-Endian。
- 默认视频 payload 预算为 `1200 bytes`。
- 共享媒体/遥测通道使用单个 UDP socket。
- 对外仍然是同一远端 IP/port。
- 发送层内部可以有队列和 pacing，但不得改变 datagram 内容。
- 每个 datagram 的第一个字节用于区分二进制包类型；文本控制包以 ASCII 文本开头。

## 3. Type 定义

| Type | 方向 | 名称 | 说明 |
|---:|---|---|---|
| `0x01` | Robot -> VR/server | Video V2 | H.264/H.265 编码帧分片，可带 FEC |
| `0x02` | VR -> Robot | Pose V2 | VR 姿态、手柄按钮、24 关节姿态 |
| `0x04` | 双向或 Robot -> VR | Audio V2 | 单个 Opus packet |
| `0x05` | Robot -> server/VR | Robot telemetry low-rate | 低频机器人状态 |
| `0x06` | Robot -> server/VR | Robot telemetry high-rate | 高频 17 关节状态 |

## 4. UDP 控制面

控制面使用文本 datagram。

### HELLO

格式：

```text
HELLO|{session_id}|{unix_seconds}|{signature}
```

发送规则：

- gRPC 注册成功并获得 `session_id` 后才可生成。
- UDP handshake 未 ready 时按 `hello_interval_sec` 周期发送。
- `session_id` 为空时不发送。

### PING

格式：

```text
PING|{session_id}|{unix_seconds}|{signature}
```

发送规则：

- UDP handshake ready 后按 `ping_interval_sec` 周期发送。
- 用于维持 peer activity。

### ACK

接收规则：

- 收到以 `ACK` 开头的 datagram 后，视为 UDP handshake ready。
- 更新 peer activity 时间。

### Signature

当前实现使用：

```text
HMAC-SHA256(key=session_id, data=type + session_id + unix_seconds)
```

输出为小写十六进制字符串。

## 5. Video V2: Type `0x01`

### Header

固定 27 bytes，随后跟随 video payload。

```c
struct VideoPacketHeaderV2 {
  uint8_t  Type;               // 0x01
  uint16_t PacketSeqNum;       // LE, 16-bit packet sequence
  uint64_t Timestamp;          // LE, NTP64-like timestamp
  uint32_t FrameId;            // LE, frame sequence
  uint16_t FragmentIndex;      // LE
  uint16_t TotalFragments;     // LE, source fragment count
  uint16_t PayloadLength;      // LE
  uint32_t FramePayloadLength; // LE, original encoded frame bytes
  uint8_t  FecTableId;         // 0 disables FEC
  uint8_t  KeyframeFlag;       // 0/1
};
```

### Fragment rules

- 一个 encoded video frame 对应一个 `FrameId`。
- 原始分片 `FragmentIndex` 从 `0` 到 `TotalFragments - 1`。
- `PayloadLength` 是当前分片有效载荷长度。
- `FramePayloadLength` 是当前帧完整 encoded bytes。
- `PacketSeqNum` 按 datagram 递增，16 bit 回绕。

### FEC rules

- `FecTableId == 0`：本帧不启用 FEC，只发送源分片。
- `FecTableId != 0`：按现有 FEC table 推导 group 和 parity。
- FEC parity 的 `FragmentIndex >= TotalFragments`。
- 新实现必须保持现有 FEC 字节兼容。
- 发送压力下 parity 可以优先丢弃，但 wire format 不变。

### Keyframe

- `KeyframeFlag = 1` 表示当前帧为 IDR / 可恢复关键帧。
- 接收端可用它决定是否开始或恢复解码。

## 6. Audio V2: Type `0x04`

### Header

固定 11 bytes，随后跟随一个 Opus payload。

```c
struct AudioPacketHeaderV2 {
  uint8_t  Type;         // 0x04
  uint16_t Seq;          // LE, 16-bit audio packet sequence
  uint64_t TimestampNtp; // LE, audio timestamp
};
```

### Payload rules

- 一个 UDP datagram 只承载一个 Opus packet。
- 不做应用层分片。
- payload 长度由 datagram 长度减 11 得到。

### Recommended audio config

```text
codec: Opus
sample_rate: 48000
channels: 1
frame_duration_ms: 20
samples_per_channel: 960
bitrate_bps: 64000
opus_inband_fec_enabled: true
opus_dtx_enabled: false
```

## 7. Telemetry V1: Type `0x05` / `0x06`

`0x05` 和 `0x06` 共用轻量外层头。

```c
struct TelemetryDatagramHeaderV1 {
  uint8_t  Type;           // 0x05 or 0x06
  uint16_t Seq;            // LE
  uint64_t TxTimestampMs;  // LE, Unix ms
  uint8_t  SessionIdBytes;
  uint8_t  DeviceIdBytes;
  uint8_t  IdentifierTable[]; // SessionId then DeviceId
};
```

### Type `0x05`: low-rate telemetry

Payload:

```c
struct RobotTelemetryLowRatePayloadV1 {
  uint8_t  Version;                 // 1
  uint16_t BatteryVoltageMv;        // LE, unknown 0xFFFF
  int16_t  BatteryCurrentMa;        // LE, unknown INT16_MIN
  int16_t  BatteryTemperatureDeciC; // LE, unknown INT16_MIN
  uint8_t  FaultCodeBytes;
  uint8_t  NetworkQualityBytes;
  uint8_t  ModelBytes;
  uint8_t  FirmwareVersionBytes;
  uint8_t  TextTable[];             // FaultCode, NetworkQuality, Model, FirmwareVersion
};
```

Recommended period: `1 Hz`.

### Type `0x06`: high-rate joint telemetry

Payload:

```c
struct RobotJointTelemetryHighRatePayloadV1 {
  uint8_t  Version;           // 1
  uint16_t SchemaId;          // LE, 1
  uint64_t SampleTimestampMs; // LE
  uint8_t  JointCount;        // 17
  uint32_t ValidMask;         // LE
  struct {
    float PositionRad;
    float VelocityRadS;
    float EffortNm;
  } JointStates[JointCount];
};
```

Recommended period: `20 ms` / `50 Hz`.

`SchemaId == 1` joint order:

| Index | Joint |
|---:|---|
| 0 | `Waist01_Joint` |
| 1 | `Waist02_Joint` |
| 2 | `Body0422_Joint` |
| 3 | `openarm_left_joint1` |
| 4 | `openarm_left_joint2` |
| 5 | `openarm_left_joint3` |
| 6 | `openarm_left_joint4` |
| 7 | `openarm_left_joint5` |
| 8 | `openarm_left_joint6` |
| 9 | `openarm_left_joint7` |
| 10 | `openarm_right_joint1` |
| 11 | `openarm_right_joint2` |
| 12 | `openarm_right_joint3` |
| 13 | `openarm_right_joint4` |
| 14 | `openarm_right_joint5` |
| 15 | `openarm_right_joint6` |
| 16 | `openarm_right_joint7` |

## 8. Pose V2: Type `0x02`

Pose V2 是 VR 到机器人端的独立 UDP datagram。

### Header

固定 16 bytes。

```c
struct PoseDatagramHeaderV2 {
  uint8_t  Type;        // 0x02
  uint8_t  Version;     // 2
  uint16_t TotalBytes;  // LE, 930
  uint64_t TimestampMs; // LE, Unix ms
  uint8_t  RefSpace;    // 0
  uint8_t  OriginSensor;// 0
  uint8_t  BlockCount;  // 3
  uint8_t  Reserved;    // 0
};
```

V2 固定总长度：

```text
PoseDatagramHeaderV2 : 16
SensorRawBlock       : 176
ButtonsBlock         : 54
Joint24Block         : 684
Total                : 930
```

### Blocks

固定顺序：

1. `SensorRawBlock`, `BlockType = 1`, `BlockBytes = 176`
2. `ButtonsBlock`, `BlockType = 2`, `BlockBytes = 54`
3. `Joint24Block`, `BlockType = 3`, `BlockBytes = 684`

当前接收端发布：

- `teleop/pose/hmd`
- `teleop/pose/left_controller`
- `teleop/pose/right_controller`
- `teleop/controller/left_joy`
- `teleop/controller/right_joy`
- `teleop/pose/joint24`
- `teleop/pose/joint24_valid_mask`
- `teleop/pose/joint24_waist`
- `teleop/pose/joint24_waist_valid_mask`

`teleop/pose/joint24` 发布 UDP 中的原始 24 关节数据。`teleop/pose/joint24_waist` 由接收端使用 `joint24[0]` (`Pelvis`) 转换得到，以腰部/Pelvis 为原点。

## 9. 新实现发送架构约束

协议上仍然共用现有 UDP 通道；实现上使用两个队列：

```text
video_queue:
  Type 0x01 video source fragments
  Type 0x01 video FEC parity

other_queue:
  HELLO / PING / ACK
  Type 0x04 audio
  Type 0x05 telemetry
  Type 0x06 telemetry
```

所有 datagram 最终经过：

```text
SendScheduler -> global pacer -> single UDP socket
```

该架构不得改变任何 UDP datagram 的 wire format。

实现约束：

- 共享媒体/遥测通道对外只使用一个 UDP socket 和同一个远端 endpoint。
- 只有 UDP send thread 可以对该 socket 执行 `sendto()`。
- 所有 stream 都是 producer，只能把已编码好的 datagram 投递到 `video_queue` 或 `other_queue`。
- `0x01` 视频源分片和 FEC parity 只进入 `video_queue`。
- HELLO / PING / ACK、`0x04`、`0x05`、`0x06` 只进入 `other_queue`。
- `video_queue` 和 `other_queue` 都经过同一个 global pacer。
- 内部线程、队列、pacing 和丢弃策略不得泄漏到 wire protocol；服务器端和 VR 端必须无感。
