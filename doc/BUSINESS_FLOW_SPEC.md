# 业务流程规格

> 状态：草案  
> 目标：提取机器人端从启动到运行、收发媒体、遥测、姿态和异常处理的业务流程。  
> 原则：协议对外不变，内部模块化，各业务流独立管理。

## 1. 角色

```text
Robot endpoint:
  采集视频、音频、机器人遥测
  发送 UDP 媒体和遥测
  接收 VR 姿态/控制输入
  通过 gRPC 完成注册、配对和配置同步

VR endpoint:
  接收机器人视频/音频/遥测
  发送姿态和控制输入
  通过 gRPC 完成配对和订阅

Signaling server:
  注册和 session 管理
  配对事件转发
  配置转发和 ACK
  辅助 UDP endpoint 建链
```

## 2. 启动流程

```text
Process start
  -> load config
  -> create SessionController
  -> create UdpTransport
  -> create stream modules
  -> start gRPC SignalingClient
```

启动时不应立即强制启动所有业务流。每一路流是否启动由配置和 session 状态决定。

## 3. 注册流程

```text
SignalingClient.start()
  -> Register(token, role=ROBOT, device_id, robot_generation)
  -> receive session_id
  -> start heartbeat timer
  -> notify SessionController registered
```

失败处理：

- 注册失败进入 retry。
- retry 周期由 `grpc.register_retry_sec` 控制。
- 未注册成功前，不启动 session-bound media streams。

## 4. UDP 建链流程

```text
gRPC registered
  -> UdpTransport.start(session_id)
  -> ControlStream sends HELLO periodically
  -> receive ACK
  -> UDP handshake ready
```

规则：

- HELLO / PING / ACK 使用现有 UDP 文本控制面。
- UDP handshake ready 后才允许发送 session-bound media payload。
- 低频诊断可以按配置决定是否允许在 handshake 前产生，但不应实际发送到 wire。

## 5. 配对流程

### Passive mode

```text
registered + UDP ready
  -> start EventStream
  -> wait PairEvent.REQUEST
  -> if auto_accept: AcceptPair(peer)
  -> state = Negotiating
```

### Active mode

```text
registered + UDP ready
  -> ListUnpaired(optional)
  -> RequestPair(peer)
  -> wait PairEvent.ACCEPT / REJECT
```

Pair accepted:

```text
store paired_peer_session_id
state = Negotiating
start video negotiation path
```

Pair rejected:

```text
clear pending peer
return to Pairing
```

Unpair:

```text
stop session-bound streams
clear queues for session
return to Pairing
```

## 6. 媒体协商流程

### Video

```text
Negotiating
  -> VideoStream.start()
  -> wait encoder SPS/PPS
  -> PublishVideoConfig(width, height, fps, codec, sps, pps, vps)
  -> wait / infer config accepted by RPC result
```

规则：

- 第一版推荐 H.264。
- 没有 SPS/PPS 时不能发布 VideoConfig。
- 启动超时可以只重启 VideoStream，不影响其他流。

### Audio

```text
if audio enabled:
  -> publish AudioConfig
  -> start AudioStream after config published
```

规则：

- AudioStream 与 VideoStream 生命周期独立。
- 音频配置失败不应阻塞视频，除非业务配置要求音视频必须同时可用。

## 7. Running 流程

运行态中：

```text
VideoStream:
  GStreamer H.264 AU
    -> encoded_frame_queue
    -> VideoStream worker
    -> packetizer/FEC
    -> video_queue

AudioStream:
  Opus packet -> other_queue

TelemetryLowRateStream:
  snapshot 1Hz -> other_queue

TelemetryHighRateStream:
  joint snapshot 50Hz -> other_queue

ControlStream:
  PING / control datagrams -> other_queue

UdpTransport:
  other_queue first, then video_queue
  global pacing
  single socket sendto

PoseInputStream:
  receive Type 0x02
  publish ROS pose/joy topics
```

## 8. 视频业务流程

```text
USB 3.0 dual camera
  MJPEG 4:2:2, side-by-side stereo, 3840x1520@30
  -> GStreamer hardware pipeline
     v4l2src
     -> nvjpegdec
     -> nvvidconv
     -> nvv4l2h264enc
     -> h264parse(stream-format=byte-stream, alignment=au)
     -> appsink
  -> H.264 access unit
  -> encoded_frame_queue(max=1)
  -> VideoStream worker
  -> parse keyframe and SPS/PPS
  -> VideoPacketizer
  -> optional FEC
  -> video_queue
```

关键策略：

- 第一版固定 H.264，不切 H.265。
- 双目 SBS 作为一路视频流，不拆左右眼。
- `appsink` 回调只 copy/ref H.264 AU 并入 `encoded_frame_queue`，不做 packetize、FEC、pacing 或 `sendto()`。
- appsink 不积压旧帧。
- `VideoStream worker` 从 `encoded_frame_queue` 取最新 AU，解析 SPS/PPS/IDR，再生成现有 `0x01` UDP 视频分片。
- SPS/PPS 可用后，通过现有 gRPC `VideoConfig` 流程发布。
- video_queue 只保留 1 到 2 帧。
- 新 keyframe 入队时清旧视频帧。
- 网络压力下先丢 FEC parity，再丢旧 P 帧。
- 视频流异常只重启视频流。

## 9. 音频业务流程

```text
Audio capture
  -> Opus encode
  -> AudioPacketHeaderV2
  -> other_queue
```

接收方向如需支持：

```text
UdpTransport recv Type 0x04
  -> AudioStream receive path
  -> jitter buffer / decode / playback
```

音频异常隔离：

- 停止或重启 AudioStream。
- 不影响 VideoStream。
- 不影响 telemetry 和 control。

## 10. 遥测业务流程

Low-rate telemetry:

```text
ROS battery/device/temperature state
  -> latest snapshot
  -> every 1s build Type 0x05
  -> other_queue
```

High-rate telemetry:

```text
ROS IK /joint_states
  -> latest 19-joint snapshot
  -> every 20ms build Type 0x06
  -> other_queue
```

遥测异常隔离：

- 单一路 telemetry timer 或 subscription 异常，不影响音视频。
- `0x05` 和 `0x06` 可以独立启停。

## 11. VR 姿态输入流程

```text
Pose UDP socket bind
  -> receive Type 0x02 HMD/controller datagram
  -> validate header and optional sections
  -> publish:
       teleop/pose/hmd
       teleop/pose/left_controller
       teleop/pose/right_controller
       teleop/controller/left_joy
       teleop/controller/right_joy

Pose UDP socket bind
  -> receive Type 0x09 Body24Raw datagram
  -> validate header and body24 blocks
  -> publish:
       teleop/pose/joint24
       teleop/pose/joint24_valid_mask
       teleop/pose/joint24_waist
       teleop/pose/joint24_waist_valid_mask
```

姿态输入应作为独立输入流，不应依赖视频流是否正常。

`0x02` 只承载 HMD/手柄位姿和按键；`0x09` 承载 PICO Body24Raw。`teleop/pose/joint24` 发布 `0x09` 中的原始 24 关节数据；`teleop/pose/joint24_waist` 由机器人端接收逻辑基于 `Pelvis` 本地转换得到。

## 12. 发送调度业务规则

内部只有两个发送队列：

```text
other_queue strict priority over video_queue
```

调度规则：

```text
if other_queue has packet:
  send one other packet
else if video_queue has packet:
  send one video packet
```

发送所有权：

- 只有 `UdpTransport` 的 UDP send thread 可以对共享媒体/遥测 socket 执行 `sendto()`。
- `VideoStream` / `AudioStream` / `TelemetryStream` / `ControlStream` 都只是 producer。
- 所有包经过同一个 global pacer。
- HELLO / PING / ACK、`0x04`、`0x05`、`0x06` 进入 `other_queue`。
- `0x01` 视频源分片和 FEC parity 进入 `video_queue`。
- 不为音频、遥测、控制再拆更多发送队列；这些流量总和远小于视频。

原因：

- 其他流量远小于视频。
- 避免视频 keyframe burst 阻塞音频、遥测、控制。
- 避免复杂多队列过度设计。

事件所有权：

- gRPC callback、UDP recv、GStreamer bus、stream worker 错误都只投递事件。
- session 状态流转由 `session_event_loop` 串行处理。
- 任何 stream 不直接停止其他 stream。

## 13. 异常流程

### VideoStream error

```text
VideoStream -> Error
  -> stop GStreamer pipeline
  -> clear video_queue for current video epoch
  -> backoff
  -> restart VideoStream if configured
```

不得影响：

- AudioStream
- Telemetry streams
- ControlStream
- UdpTransport socket
- gRPC registration

### UdpTransport error

UDP socket 是共享出口。异常会影响所有发送。

```text
UdpTransport error
  -> try reopen socket
  -> reset UDP handshake if needed
  -> producers continue but must not accumulate unbounded queues
```

### gRPC session error

```text
Heartbeat invalid / stream ended / reconnect command
  -> SessionController handles session-level recovery
  -> stop session-bound streams if needed
  -> re-register or return to pairing
```

## 14. Direct running mode

Direct running mode is a local/debug mode:

```text
skip normal pairing
mark media configs as published
start UDP transport
start selected streams directly
```

该模式不得改变协议规格，只是绕过部分信令流程。

## 15. 验收流程

第一里程碑：

```text
GStreamer video -> compatible UDP 0x01 -> existing VR video
```

第二里程碑：

```text
VideoStream restart while Audio/Telemetry/Control continue
```

第三里程碑：

```text
Full session flow: register -> UDP ready -> pair -> negotiate -> running -> unpair/recover
```
