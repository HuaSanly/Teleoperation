# SCReAM 接入说明（机器人端 UDP 视频链路）

> 适用范围：teleop_robot_bridge 机器人端视频 UDP 发送链路（V2 协议）。
> 目的：给出 SCReAM 接入的端到端协议与模块改造说明，包含反馈包（FB）定义、发送端行为、接收端行为与时序要求。

---

## 1. 背景与现有链路

当前链路：
- V4L2 采集 → 颜色转换 → H.264 编码 → `UdpStreamManager::sendH264Frame()`
- 视频包头为 V2（26B），包含 `PacketSeqNum` 与 `Timestamp` 字段（SCReAM 所需）。
- 发送端仅做 **固定速率 pacing**（`udp.pacing.bps`），无闭环拥塞控制。

SCReAM 接入需要：
- **接收端生成反馈包（Feedback, FB）** 并回传；
- **发送端根据反馈调整发送速率/节奏**；
- 可选：根据 SCReAM 目标码率调整编码器码率。

---

## 2. 数据面（视频包）结构

视频包沿用现有 V2 头，不做破坏性修改：

```
[VideoPacketHeaderV2 (26 bytes)] + [payload <= 1200 bytes]
```

**VideoPacketHeaderV2**（小端）：
- `Type` (u8) = 0x01
- `PacketSeqNum` (u16) 连续递增（0-65535 环回）
- `Timestamp` (u64) NTP 时间戳
- `FrameId` (u32)
- `FragmentIndex` (u16)
- `TotalFragments` (u16)
- `PayloadLength` (u16)
- `FramePayloadLength` (u32)
- `FecTableId` (u8)

> SCReAM 使用 `PacketSeqNum` 和 `Timestamp` 进行接收统计与反馈生成。

---

## 3. 新增反馈包（FB）协议（Type=0x03）

### 3.1 总体结构

```
[FeedbackHeader (固定 16 bytes)] + [AckVector 可变长度]
```

### 3.2 反馈头定义

```
#pragma pack(push, 1)
typedef struct {
  uint8_t  Type;              // 0x03
  uint16_t BaseSeq;           // ack_vector 基准序号（PacketSeqNum）
  uint16_t AckVectorBits;     // AckVector 位数（bit 数，建议 32/64/128）
  uint64_t RxTimestamp;       // 反馈生成时间戳（NTP 64-bit）
} FeedbackHeader;
#pragma pack(pop)
```

**AckVector 定义**：
- 紧随 `FeedbackHeader`，长度 = `AckVectorBits/8` 字节（向上取整）。
- 第 0 位表示 `BaseSeq` 包是否收到；第 i 位表示 `(BaseSeq + i) mod 65536`。
- 1=收到，0=未收到（或未到达）。

### 3.3 建议参数

- `AckVectorBits`：64（推荐），或 128（更抗抖动）
- 反馈发送周期：10~20ms
- `RxTimestamp` 使用接收端 `system_clock` 转 NTP64

---

## 4. 接收端（操作端）职责

### 4.1 解析视频包

收到 `Type=0x01` 包时：
- 读取 `PacketSeqNum` 与本地接收时间 `t_rx`（NTP64）
- 记录到 SCReAM receiver 状态（或本地 ACK 位图窗口）

### 4.2 生成反馈包

定时（10~20ms）：
- 选择 `BaseSeq`（通常为“窗口最老的期望序号”）
- 构建 `AckVector`（基于是否收到对应 `PacketSeqNum`）
- 填充 `RxTimestamp` 为当前 NTP 时间
- 发送 `Type=0x03` 反馈包到机器人端 UDP 端口

---

## 5. 发送端（机器人端）职责

### 5.1 发送记录

每次发送一个 UDP 包（包括 FEC parity 包）时，记录：
- `seq`（PacketSeqNum）
- `send_time`（steady_clock 或 system_clock 转 NTP）
- `size_bytes`

### 5.2 反馈处理

收到 `Type=0x03`：
- 解析 `BaseSeq`、`AckVectorBits`、`AckVector`、`RxTimestamp`
- 更新 SCReAM sender 的 ACK/RTT/丢包估计
- 计算下一阶段的 `target_rate_bps` 或 `next_send_time`

### 5.3 pacing

使用 SCReAM 输出替代固定 `udp.pacing.bps`：
- 若 SCReAM 给出 `target_rate_bps`：按字节速率 pacing
- 若给出 `next_send_time`：直接 `sleep_until(next_send_time)`

### 5.4 编码器码率（可选）

若接入 `VideoEncoder::setBitrate()`：
- 按 SCReAM 目标媒体码率更新编码器
- 更新频率：100~200ms

---

## 6. FEC 与 SCReAM 的关系

- FEC parity 包同样消耗带宽，应纳入拥塞控制统计。
- 现阶段建议保持静态 FEC 表，不进行动态调节；后续可根据拥塞/丢包调整 `FecTableId` 或策略表。

---

## 7. 兼容性与时钟要求

- `Timestamp` 与 `RxTimestamp` 默认使用 NTP64（system_clock）。
- 建议两端启用 NTP/chrony，保证时钟偏差尽量小。
- 若无法保证对时，可考虑改成“发送端单调时间戳 + 接收端相对时差”的变种，但这需要协议升级。

---

## 8. 机器人端改造点（文件级）

- [src/udp/udp_stream_manager.cpp](src/udp/udp_stream_manager.cpp)
  - `recvThreadMain()`：新增 Type=0x03 解析与回调
  - `sendThreadMain()`：用 SCReAM pacing 替换固定速率
  - 维护发送历史与 ACK 窗口

- [include/udp/udp_packet.hpp](include/udp/udp_packet.hpp)
  - 增加 FeedbackHeader 结构体与序列化

- （可选）[include/video/video_encoder.hpp](include/video/video_encoder.hpp)
  - 增加 `setBitrate(uint32_t bps)`

---

## 9. 示例：反馈包序列化伪代码

```
FeedbackHeader h;
h.Type = 0x03;
h.Version = 0x01;
h.BaseSeq = base_seq;
h.AckVectorBits = bits;
h.Reserved = 0;
h.RxTimestamp = ntp_now();

uint8_t payload[bits/8];
fill_ack_vector(payload, bits);

sendto(sock, &h, sizeof(h));
sendto(sock, payload, bits/8);
```

---

## 10. 注意事项

- `PacketSeqNum` 为 16-bit 环绕，需要窗口逻辑处理（base/ack 计算应支持 wrap-around）。
- 反馈包过大可能增加延迟，建议 64-bit 位图。
- 发送端 pacing 的精度建议保持在 1ms 级别。

---

## 11. 后续工作建议

1) 先实现 **FB 解析 + pacing 接入**（不调编码器码率）
2) 再增加 **动态码率调节**
3) 最后考虑 **FEC 自适应** 与 **日志指标**（RTT/丢包/速率）

---

如需对接 SCReAM 的具体 C++ 实现或第三方库，请提供你们计划采用的 SCReAM 版本/接口，我会给出更贴合的代码映射与最小侵入改动方案。
