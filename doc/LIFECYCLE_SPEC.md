# 生命周期与状态流转规格

> 状态：草案  
> 目标：定义新机器人端的 session、transport 和业务流生命周期。  
> 原则：session 生命周期和各业务流生命周期分离，单一路流异常不得扩散到其他流。

## 1. 生命周期层次

新架构分三层生命周期：

```text
Process lifecycle
  -> Session lifecycle
     -> Stream lifecycles
  -> Transport lifecycle
```

含义：

- Process 管进程启动、配置加载、全局资源释放。
- Session 管 gRPC 注册、配对、协商、运行、恢复。
- Stream 管视频、音频、遥测、控制等业务流。
- Transport 管 UDP socket、队列、pacing、收发线程。

## 2. Process lifecycle

```text
Created
  -> Initializing
  -> Running
  -> ShuttingDown
  -> Stopped
```

### Initializing

动作：

- 读取配置。
- 创建 `SessionController`。
- 创建 `SignalingClient`。
- 创建 `UdpTransport`。
- 创建 `StreamSupervisor` 和各 stream module。

### Running

动作：

- gRPC registration retry 可以运行。
- UDP transport 按 session 状态启动。
- 各 stream 按配置和 session 状态启动。

### ShuttingDown

停止顺序：

1. 禁止新的 session work。
2. 停止 stream producers。
3. 清空 transport queues。
4. 停止 UDP transport。
5. 停止 gRPC client。
6. 释放 ROS/GStreamer/音频资源。

## 3. Session lifecycle

建议 session 状态：

```text
Connecting
  -> Registered
  -> UdpReady
  -> Pairing
  -> Negotiating
  -> Running
```

可恢复回退：

```text
Running -> Pairing       on unpair / UDP peer lost
Running -> Registered    on EventStream ended
Running -> Connecting    on heartbeat invalid / gRPC reconnect
Negotiating -> Pairing   on pair reject / negotiation cancel
```

### Connecting

含义：

- 尚未完成 gRPC 注册。

进入动作：

- 启动或重试 `Register`。
- 停止 session-bound streams。

退出条件：

- `RegisterResponse.success == true` 且获得 `session_id`。

### Registered

含义：

- gRPC session 已建立。
- 本会话的 Publisher Manifest 可以声明。

进入动作：

- 启动 heartbeat。
- 声明 enabled 的 `0x01/0x04/0x05/0x06` Publisher-local streams。
- Manifest 成功后启动 UDP transport。
- ControlStream 开始发送 HELLO。

退出条件：

- UDP 收到 ACK，handshake ready。

### UdpReady

含义：

- UDP 控制面已就绪。

进入动作：

- 可以启动 `EventStream`。
- 可以进入 Pairing。

### Pairing

含义：

- 等待或发起配对。

进入动作：

- 启动 `EventStream`。
- passive mode 等待 `PairEvent.REQUEST`。
- active mode 可按 `desired_device_type_code` 执行 `ListUnpaired` 并 `Pair(REQUEST)`。

退出条件：

- pair accepted -> `Negotiating`
- gRPC error -> `Connecting`

### Negotiating

含义：

- 已配对，正在同步媒体配置。

进入动作：

- 启动 `VideoStream` 以获得 SPS/PPS。
- 拉取对端 Manifest 并显式订阅 `0x02/0x09`，需要音频下行时同时订阅 `0x04`。姿态 Prefix 暂未发布时不阻塞视频进入 Running，运行态后台继续重试并补齐订阅。
- 发布 `0x01` 视频 JSON StreamConfig。
- 若音频上行启用，发布 `0x04` 音频 JSON StreamConfig。
- 若音频下行启用，主动拉取并校验对端 `0x04` StreamConfig。

退出条件：

- 必需订阅与 StreamConfig 发布/拉取成功 -> `Running`
- pair reject / unpair -> `Pairing`
- gRPC invalid -> `Connecting`

### Running

含义：

- session 已配对并完成必要协商。
- 各 enabled streams 按独立配置运行。

进入动作：

- 确保 ControlStream 运行。
- 启动或保持 VideoStream。
- 启动 enabled AudioStream。
- 启动 enabled Telemetry streams。
- 启动 PoseInputStream if enabled。

退出条件：

- unpair -> `Pairing`
- UDP peer lost -> `Pairing`
- gRPC stream ended -> `Registered` or `Pairing`
- heartbeat invalid -> `Connecting`

## 4. Transport lifecycle

```text
Stopped
  -> Starting
  -> HelloPhase
  -> Ready
  -> Error
  -> Stopping
```

### Starting

动作：

- 创建 UDP socket。
- bind local address。
- 配置 send/recv options。
- 启动 receive loop。
- 启动 scheduler loop。

### HelloPhase

动作：

- ControlStream 周期性发送 HELLO。
- media/audio/telemetry 可生产数据，但 transport 不应发送 session-bound payload，或应按配置丢弃。

### Ready

条件：

- 收到 ACK。
- 当前会话已经成功声明对应 Prefix 的 Manifest。

动作：

- 允许发送 `0x01` / `0x04` / `0x05` / `0x06`。
- 周期性发送 PING。

### Error

动作：

- 尝试重开 socket。
- 清理队列，避免旧 session 数据污染。
- 必要时通知 SessionController 回退。

## 5. Stream lifecycle

每一路业务流独立维护：

```text
Stopped
  -> Starting
  -> Running
  -> Stopping
  -> Stopped

Running
  -> Error
  -> Backoff
  -> Starting
```

统一语义：

- `Stopped`: 未运行。
- `Starting`: 初始化本流资源。
- `Running`: 正常运行。
- `Stopping`: 正在释放本流资源。
- `Error`: 本流发生错误。
- `Backoff`: 等待独立重试。

### 5.1 线程与事件所有权

生命周期状态必须由单一 `session_event_loop` 串行修改。其他线程只能投递事件，不直接改变 session 状态，也不直接停止无关 stream。

建议线程归属：

```text
main thread:
  process start/exit/signal handling

session_event_loop thread:
  session state transitions
  stream start/stop/retry commands
  transport-level recovery decisions

gRPC/EventStream thread(s):
  receive Register/Heartbeat/EventStream callbacks
  post events only

UDP recv thread:
  recvfrom on single shared UDP socket
  classify ACK/PING/binary Type
  post events or dispatch payload

UDP send thread:
  drain other_queue and video_queue
  apply global pacing
  sendto on single shared UDP socket

VideoStream worker thread:
  drain encoded_frame_queue
  parse H.264 SPS/PPS/IDR
  packetize/FEC
  enqueue video_queue

GStreamer internal threads:
  v4l2src/nvjpegdec/nvvidconv/nvv4l2h264enc

AudioStream worker thread:
  audio capture/encode or receive/playback
  enqueue other_queue

Telemetry timers / ROS executor thread(s):
  collect latest robot state
  enqueue 0x05 / 0x06 datagrams

PoseInput thread:
  receive Type 0x02 if configured
  publish ROS pose/joy topics
```

硬约束：

- `appsink` callback 不做 packetize、FEC、pacing 或 `sendto()`。
- 只有 UDP send thread 可以调用共享媒体/遥测 socket 的 `sendto()`。
- stream worker 失败只上报本 stream 错误，由 `StreamSupervisor` 和 `session_event_loop` 决定是否重试。
- gRPC callback 不直接启动或停止媒体流。
- UDP recv thread 不直接做 session teardown。

## 6. VideoStream lifecycle

```text
Stopped
  -> Starting
     create GStreamer pipeline
     set appsink callbacks
     start pipeline
  -> Running
     appsink pushes H.264 AU to encoded_frame_queue
     VideoStream worker packetize/FEC
     enqueue video_queue
```

`appsink` callback 行为：

```text
get H.264 AU sample
copy/ref sample into EncodedFrame
push encoded_frame_queue(max=1)
return immediately
```

`VideoStream worker` 行为：

```text
encoded_frame_queue
  -> parse SPS/PPS/IDR/keyframe
  -> update video StreamConfig readiness
  -> VideoPacketizer
  -> optional FEC
  -> video_queue
```

错误处理：

```text
GStreamer error / no frame timeout / encoder stall
  -> Error
  -> stop pipeline
  -> clear video_queue video epoch
  -> Backoff
  -> Starting
```

不得执行：

- 不停止 AudioStream。
- 不停止 Telemetry streams。
- 不停止 ControlStream。
- 不关闭 UDP socket。
- 不重注册 gRPC。

## 7. AudioStream lifecycle

```text
Stopped
  -> Starting
     init capture/playback/codec
  -> Running
     output 0x04 packets to other_queue
```

错误处理：

- 重启音频设备或 codec。
- 清理音频本地 buffer。
- 不影响视频和遥测。

## 8. Telemetry lifecycle

### Low-rate telemetry

```text
Stopped -> Starting -> Running
  every 1s build 0x05
```

### High-rate telemetry

```text
Stopped -> Starting -> Running
  every 20ms build 0x06
```

错误处理：

- 单一路 telemetry timer/subscription 异常只影响该路。
- 低频和高频可独立启停。

## 9. ControlStream lifecycle

```text
Stopped
  -> Starting
  -> HelloPhase
  -> Ready
```

行为：

- HelloPhase 周期发送 HELLO。
- Ready 后周期发送 PING。
- 收到 ACK 更新 peer activity。
- peer lost 可通知 SessionController，但不直接停止所有 stream。

## 10. PoseInputStream lifecycle

```text
Stopped
  -> Starting
     bind pose UDP port
  -> Running
     receive Type 0x02
     publish ROS topics
```

规则：

- 与视频发送无依赖。
- 视频异常时姿态输入继续运行。
- 如使用独立 pose socket，pose socket 异常只影响姿态输入。

## 11. StreamSupervisor

`StreamSupervisor` 管理 stream，但不承载业务细节。

职责：

- 按配置 start/stop streams。
- 监听 stream error。
- 执行独立 backoff retry。
- 汇总状态。
- 在 session teardown 时按顺序停止 session-bound streams。

禁止：

- 不直接编码 H.264。
- 不直接处理 Opus。
- 不直接做 FEC。
- 不直接 sendto。

## 12. 故障隔离矩阵

| 故障 | 影响范围 | 恢复动作 |
|---|---|---|
| VideoStream pipeline error | Video only | restart VideoStream, clear video_queue |
| Audio device error | Audio only | restart AudioStream |
| Low-rate telemetry source error | `0x05` only | restart low-rate telemetry |
| High-rate telemetry source error | `0x06` only | restart high-rate telemetry |
| Pose UDP bind/recv error | Pose input only | restart PoseInputStream |
| UDP socket error | All UDP sending | restart UdpTransport, reset handshake |
| gRPC heartbeat invalid | Session | stop session-bound streams, re-register |
| Pair rejected | Session pairing | return Pairing |
| Unpair | Session | stop session-bound streams, keep process alive |

## 13. Teardown order

Session teardown:

```text
1. mark session stopping
2. stop VideoStream / AudioStream / Telemetry streams
3. keep or stop PoseInputStream according to config
4. clear video_queue and other_queue for session
5. reset media config state
6. reset UDP handshake if returning to Pairing
7. keep gRPC if still registered
```

Process shutdown:

```text
1. stop accepting callbacks
2. stop all streams
3. stop UdpTransport
4. stop SignalingClient
5. release global resources
```
