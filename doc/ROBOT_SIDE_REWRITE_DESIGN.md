# 机器人端重写方案设计草案

> 状态：草案  
> 范围：新机器人端仓库设计。服务器端和 VR 端协议保持完全不变。

## 1. 结论摘要

新仓库的目标不是重新设计整套线上协议，而是把机器人端内部实现重写得更自然、更清晰、更稳定。

核心方向：

```text
USB 3.0 双目 UVC 摄像头
  -> GStreamer 硬件加速 H.264 编码
  -> 现有 UDP wire protocol
  -> 视频队列 + 其他队列
  -> 全局 pacing
  -> 单 UDP socket 发送
```

外部保持透明：

- 服务器端无需修改。
- VR 端无需修改。
- gRPC 信令协议不变。
- UDP 包格式不变。
- `0x01` / `0x04` / `0x05` / `0x06` 等 Type 定义不变。
- FEC 表语义不变。
- HELLO / PING / ACK 控制面不变。

内部重写重点：

- 视频采集、MJPEG 硬解、格式转换、H.264 硬编交给 GStreamer。
- UDP 层保留现有 wire format，但重新拆分 packetizer、FEC、队列、pacing、socket。
- 队列架构从复杂多队列收敛为两个队列：`video_queue` 和 `other_queue`。
- pacing 保留，但只做简单、可解释、可测试的全局 token bucket，不自研复杂 WebRTC-like 拥塞控制。
- 流生命周期分层：视频、音频、遥测、控制各自独立启停、配置、健康检查和重试；发送层只做统一调度，不把某一路流的异常扩散到其他流。

## 2. 初步计划

### Phase 0：冻结兼容性契约

把现有协议当作 ABI，不在第一版重写里修改。

必须保持不变：

- `proto/signaling.proto`
- UDP 视频包头
- UDP 音频包头
- UDP 遥测包格式
- UDP text control plane
- session ID 逻辑
- FEC table ID 语义
- MTU / payload 预算
- 单远端 UDP endpoint 模型

建议先从当前实现抓一批 golden packet：

- 小 H.264 帧
- 大 H.264 帧
- keyframe
- non-keyframe
- FEC disabled
- FEC enabled
- audio packet
- telemetry packet
- HELLO / PING / ACK

后续新实现必须能对同样输入产生兼容输出。

### Phase 1：验证 Jetson GStreamer 视频链路

先不要写复杂业务代码，直接在 Jetson 上用 `gst-launch-1.0` 和小测试程序验证链路。

目标：

- `v4l2src` 能稳定采集 USB 3.0 摄像头。
- `nvjpegdec` 能硬解 MJPEG 4:2:2。
- `nvvidconv` 能完成格式转换。
- `nvv4l2h264enc` 能稳定硬件 H.264 编码。
- 3840x1520@30fps side-by-side 双目流能持续运行。
- CPU 占用、编码延迟、掉帧、码率稳定性可接受。

### Phase 2：实现新的视频编码模块

新增 `GstH264Encoder` 模块。

职责：

- 创建和管理 GStreamer pipeline。
- 通过 `appsink` 输出完整 H.264 access unit。
- 输出 transport 需要的元信息：
  - timestamp
  - keyframe flag
  - frame size
  - SPS/PPS 是否可用
- 支持请求 IDR。
- 统计基础性能数据。

### Phase 3：实现兼容 UDP packetizer

新增 `VideoPacketizer`。

职责：

- 将一个 H.264 access unit 切成现有 `0x01` UDP 视频分片。
- 填充现有 `VideoPacketHeaderV2` 字段。
- 在 FEC 启用时生成兼容的 parity 包。
- 输出本帧所有待发送 datagram。

要求：

- `FecTableId == 0` 时完全不做 FEC。
- `FecTableId != 0` 时保持现有 FEC 字节兼容。
- packetizer 不负责 socket、不负责线程、不负责 pacing。

### Phase 4：实现两个队列的 UDP sender

内部只保留两个队列：

```text
video_queue:
  0x01 视频源分片
  0x01 视频 FEC parity 分片

other_queue:
  HELLO / PING / ACK
  0x04 audio
  0x05 low-rate telemetry
  0x06 high-rate telemetry
  future non-video packets
```

发送侧：

```text
video_queue + other_queue
  -> SendScheduler
  -> global token-bucket pacer
  -> single UDP socket
```

### Phase 5：接入 gRPC 信令和 ROS bridge

保持协议行为兼容，但降低耦合。

建议拆成：

```text
SignalingClient:
  register / heartbeat / event stream / pair / publish config

SessionController:
  session 状态机
  启停 media pipeline
  启停 UDP transport
  处理 peer lost / force keyframe

MediaPipeline:
  GStreamer 编码输出 H.264 AU

UdpTransport:
  packetize / FEC / queue / pacing / socket

RosBridge:
  ROS 输入输出和 telemetry 收集
```

同时建立独立流控制：

- `VideoStream` 独立启动、停止、请求 IDR、重试 GStreamer pipeline。
- `AudioStream` 独立启动、停止、重试音频采集/播放。
- `TelemetryStream` 独立启停低频 `0x05` 和高频 `0x06`。
- `ControlStream` 独立维护 HELLO / PING / ACK 和必要控制消息。
- 任一业务流异常时，只清理该流自己的资源和队列数据，不重启整个进程，不重建无关流。

### Phase 6：兼容性和实机测试

测试顺序：

1. golden packet 单元测试。
2. LAN 环境现有 VR 端无修改收流。
3. 检查首帧、关键帧、SPS/PPS、frame ID、fragment index。
4. 检查音频、遥测是否被视频 keyframe burst 阻塞。
5. 人为限速或制造丢包，确认延迟不会持续增长。
6. 再进入公网/弱网测试。

## 3. 目标运行环境

```text
Jetson Linux / L4T: R39.2.0
Ubuntu: 24.04.4
Kernel: 6.8.12-1021-tegra
Jetson Multimedia API: nvidia-l4t-jetson-multimedia-api 39.2.0-20260601141651
GStreamer: 1.24.2
```

可用 GStreamer 插件：

```text
v4l2src
nvjpegdec
nvvidconv
nvv4l2h264enc
h264parse
rtph264pay
opusenc
webrtcbin
```

不可用：

```text
nvvideoconvert
```

摄像头输入：

```text
USB 3.0 camera
MJPEG 4:2:2
side-by-side stereo
3840x1520
minimum 30fps
```

## 4. 非目标

第一版重写不要做：

- 不改服务器端协议。
- 不改 VR 端协议。
- 不新增第二条 WebRTC transport。
- 不把现有 UDP wire format 换成 RTP。
- 不实现完整 WebRTC congestion control。
- 不设计复杂多队列优先级系统。
- 不新增新的 FEC 方案。
- 不把畸变矫正、eye image、录制、调试图像输出作为核心启动功能。

这些功能可以后续作为独立模块加入，但不应该阻塞基础视频链路。

## 5. 总体架构

```text
+--------------------+
| ROS / Robot inputs |
+----------+---------+
           |
           v
+--------------------+        +----------------------+
| Signaling/session  |        | GStreamer H264 video |
| gRPC-compatible    |        | encoder              |
+----------+---------+        +----------+-----------+
           |                             |
           |                             v
           |                  +----------------------+
           |                  | VideoPacketizer      |
           |                  | H264 AU -> 0x01 UDP  |
           |                  +----------+-----------+
           |                             |
           v                             v
+--------------------+        +----------------------+
| Non-video producer |        | Video producer       |
| 0x04/0x05/0x06/etc |        | 0x01 + optional FEC  |
+----------+---------+        +----------+-----------+
           |                             |
           v                             v
      +------------+              +-------------+
      | other_queue|              | video_queue |
      +------+-----+              +------+------+
             |                           |
             +-------------+-------------+
                           |
                           v
                +----------------------+
                | SendScheduler        |
                | 2 queues + pacing    |
                +----------+-----------+
                           |
                           v
                +----------------------+
                | Single UDP socket    |
                +----------------------+
```

## 6. 模块化与独立流生命周期

两个发送队列只是 transport 层的调度实现，不代表业务流生命周期要合并。

新架构必须做到：

- 每一路业务流有独立模块。
- 每一路业务流有独立配置。
- 每一路业务流可独立 start / stop / restart。
- 每一路业务流有独立健康检查和重试策略。
- 某一路业务流失败时，不影响其他流继续运行。

### 6.1 流模块划分

建议至少拆成这些运行单元：

```text
VideoStream:
  GStreamer video pipeline
  H.264 AU output
  video packetizer
  optional video FEC
  writes to video_queue

AudioStream:
  audio capture / encode
  audio receive / playback if needed
  writes 0x04 packets to other_queue

TelemetryLowRateStream:
  robot low-rate telemetry
  writes 0x05 packets to other_queue

TelemetryHighRateStream:
  robot high-rate telemetry
  writes 0x06 packets to other_queue

ControlStream:
  HELLO / PING / ACK
  peer liveness
  writes control datagrams to other_queue

UdpTransport:
  owns queues
  owns scheduler
  owns pacer
  owns single UDP socket
```

`UdpTransport` 是共享发送出口，但它不拥有视频、音频、遥测的业务生命周期。业务流只把已经编码好的 datagram 投递给 transport。

### 6.2 统一流接口

每个流模块可以实现类似接口：

```cpp
class StreamRuntime {
public:
  virtual bool configure(const StreamConfig& config) = 0;
  virtual bool start(const SessionContext& session) = 0;
  virtual void stop(const std::string& reason) = 0;
  virtual bool restart(const std::string& reason) = 0;
  virtual StreamState state() const = 0;
  virtual StreamStats stats() const = 0;
};
```

接口重点不是形式，而是边界：

- `start()` 只启动本流资源。
- `stop()` 只释放本流资源。
- `restart()` 不触碰其他流。
- stats 只报告本流状态。
- 流模块不直接操作 socket。
- 流模块不直接操作其他流队列。

### 6.3 流状态机

每一路流维护自己的状态机：

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

建议状态语义：

- `Stopped`：未运行，可再次启动。
- `Starting`：正在初始化本流资源。
- `Running`：正常运行。
- `Stopping`：正在释放本流资源。
- `Error`：本流出现错误，已经隔离。
- `Backoff`：等待重试。

不要把单个流的 `Error` 映射成整个 session error。只有共享层失败，例如 gRPC session 无效或 UDP transport 无法恢复，才进入 session-level teardown。

### 6.4 独立配置

配置应按流分组，而不是把所有参数铺在一个大 node 下。

示例：

```yaml
streams:
  video:
    enabled: true
    start_on_session: true
    restart_on_error: true
    retry_initial_ms: 300
    retry_max_ms: 5000
    retry_max_attempts: 0   # 0 means infinite
    device: "/dev/video0"
    width: 3840
    height: 1520
    fps: 30
    bitrate_bps: 30000000
    fec_enabled: false

  audio:
    enabled: true
    start_on_session: true
    restart_on_error: true
    retry_initial_ms: 300
    retry_max_ms: 3000

  telemetry_low_rate:
    enabled: true
    period_ms: 1000

  telemetry_high_rate:
    enabled: true
    period_ms: 20

  control:
    enabled: true
    hello_interval_ms: 1000
    ping_interval_ms: 5000
```

关键点：

- 可以只停止视频流，不停止音频和遥测。
- 可以只重试视频流，不重试 UDP transport。
- 可以只关闭高频遥测，不影响低频遥测。
- 可以在调试时只启用视频或只启用非视频。

### 6.5 异常隔离规则

视频流异常时：

- 停止当前 GStreamer pipeline。
- 清空 `video_queue` 中属于当前 video epoch 的旧视频包。
- 如配置允许，按 backoff 重启 `VideoStream`。
- 不停止 `AudioStream`。
- 不停止 telemetry。
- 不停止 `ControlStream`。
- 不关闭 UDP socket。
- 不重新注册 gRPC。

音频流异常时：

- 停止或重启音频采集/播放。
- 清理本流音频缓冲。
- 不影响视频。
- 不影响 telemetry。
- 不影响 control。

遥测流异常时：

- 停止对应 telemetry timer 或订阅。
- 保留其他 telemetry 流。
- 不影响音视频。

UDP transport 异常时：

- 这是共享出口异常，会影响所有发送。
- 由 `UdpTransport` 自己尝试重开 socket 或进入 transport error。
- 业务流可以继续运行，但投递时要按各自策略丢弃或限流，不能无限积压。

gRPC / session 异常时：

- 这是 session-level 事件。
- `SessionController` 决定是否停止所有 session-bound streams。
- 停止顺序应清晰：先停 producers，再清队列，再停 transport。

### 6.6 supervisor 设计

建议增加 `StreamSupervisor`，但它只负责监督，不承载业务逻辑。

职责：

- 根据配置启动 enabled streams。
- 接收流错误事件。
- 按独立 retry policy 安排重试。
- 汇总流状态给日志或诊断接口。
- 在 session stop 时按顺序停止所有流。

不要让 `StreamSupervisor` 直接处理 H.264、Opus、FEC 或 socket 细节。

### 6.7 与两队列发送层的关系

业务流独立，不等于发送队列无限拆分。

最终关系是：

```text
VideoStream ---------------------> video_queue

AudioStream ----------------------+
TelemetryLowRateStream ----------+
TelemetryHighRateStream ---------+-> other_queue
ControlStream --------------------+

video_queue + other_queue
  -> SendScheduler
  -> Pacer
  -> UDP socket
```

这样可以同时满足两件事：

- 生命周期上，各流互不拖累。
- 网络发送上，队列保持简单，避免过度设计。

## 7. GStreamer 视频编码设计

建议 pipeline 草案：

```bash
v4l2src device=/dev/video0 do-timestamp=true !
  image/jpeg,width=3840,height=1520,framerate=30/1 !
  queue max-size-buffers=2 leaky=downstream !
  nvjpegdec !
  nvvidconv !
  video/x-raw(memory:NVMM),format=NV12 !
  nvv4l2h264enc bitrate=30000000 insert-sps-pps=true iframeinterval=30 idrinterval=30 !
  h264parse stream-format=byte-stream alignment=au config-interval=-1 !
  appsink name=h264_sink sync=false max-buffers=1 drop=true
```

注意：

- `nvv4l2h264enc` 的具体属性名必须在目标 Jetson 上用 `gst-inspect-1.0 nvv4l2h264enc` 确认。
- `h264parse alignment=au` 很关键，packetizer 需要完整 access unit。
- `stream-format=byte-stream` 便于解析 Annex-B start code、SPS/PPS、IDR。
- `appsink` 不允许堆积，sender 慢时宁可丢旧帧。
- 第一版固定 H.264，不引入 H.265。

### 7.1 最终编码管线确认

第一版整体编码方案固定为：

```text
USB 3.0 双目 UVC 摄像头
  MJPEG 4:2:2, side-by-side stereo, 3840x1520@30
    -> GStreamer hardware pipeline
       v4l2src
       -> nvjpegdec
       -> nvvidconv
       -> nvv4l2h264enc
       -> h264parse
       -> appsink
    -> H.264 access unit
    -> existing UDP Video V2 packetizer
       Type 0x01
       fragment
       optional compatible FEC
    -> video_queue
    -> global pacing
    -> single UDP socket
```

明确约束：

- 双目 SBS 作为一个完整视频流处理，第一版不拆左右眼两路。
- 编码输出必须是 H.264 AU，不是裸 NAL 零散回调。
- `h264parse` 输出使用 `stream-format=byte-stream` 和 `alignment=au`。
- 从 H.264 NAL 中解析 SPS / PPS / IDR，并通过现有 `VideoConfig` 语义发布。
- UDP payload 继续走现有 `0x01` 视频协议，不切换 RTP，不切换 WebRTC transport。
- 第一版不引入 H.265，避免同时改变编码格式和机器人端架构。

### 7.2 appsink 回调边界

`appsink` 回调必须保持极轻量，不承担 packetize、FEC、排队发送或 `sendto()`。

```text
appsink callback:
  get H.264 AU sample
  copy/ref sample into EncodedFrame
  push encoded_frame_queue(max=1)
  return immediately
```

真正的视频业务处理放到 `VideoStream` worker：

```text
encoded_frame_queue
  -> parse SPS/PPS/IDR/keyframe
  -> update VideoConfig readiness
  -> VideoPacketizer
  -> optional FEC
  -> video_queue
```

这样 GStreamer 内部线程不会被 UDP、FEC 或 pacing 反向拖住。网络慢时，丢旧 encoded frame 或丢旧视频包，不让摄像头和编码器积压。

## 8. UDP packetizer 设计

现有视频包头保持不变：

```text
Type
PacketSeqNum
Timestamp
FrameId
FragmentIndex
TotalFragments
PayloadLength
FramePayloadLength
FecTableId
KeyframeFlag
```

packetizer 输入：

```text
EncodedFrame {
  data
  size
  timestamp
  keyframe
}
```

packetizer 输出：

```text
vector<Datagram>
```

规则：

- 每个 H.264 AU 对应一个 `FrameId`。
- 按 `max_payload_bytes` 切片，默认 1200 bytes。
- 源分片 `FragmentIndex` 从 0 开始。
- FEC parity 分片继续使用现有索引语义。
- `KeyframeFlag` 和现有实现保持一致。
- `PacketSeqNum` 继续递增并按现有宽度回绕。

## 9. 两队列发送架构

### `video_queue`

放所有 `0x01` 视频包：

- H.264 源分片。
- H.264 FEC parity 分片。

`video_queue` 必须按帧管理，而不是普通无限 FIFO。

建议限制：

```text
max_video_frames: 1 or 2
max_video_queue_delay_ms: 50 to 100
```

丢弃策略：

1. 新 keyframe 入队时，清理旧视频帧。
2. 超过限制时，优先丢旧 non-keyframe。
3. 网络压力大时，优先丢 FEC parity。
4. 仍然超限时，保留最新帧，丢旧帧。
5. 不允许视频队列积压成持续延迟。

### `other_queue`

放所有非视频 UDP 包：

- HELLO / PING / ACK。
- `0x04` audio。
- `0x05` low-rate telemetry。
- `0x06` high-rate telemetry。
- 未来其他非视频包。

因为这些流量总和远小于视频，第一版可以使用简单 FIFO。

建议限制：

```text
max_other_packets: 128 to 256
max_other_queue_delay_ms: 100 to 200
```

如果满了：

- 第一版可以直接丢旧包。
- 后续如确实需要，再细分 telemetry stale-drop 策略。

### scheduler 规则

简单严格优先：

```text
while running:
  if other_queue not empty:
      send one other packet
      continue

  if video_queue not empty:
      send one video packet
      continue
```

理由：

- 其他流量非常小，不值得拆成更多队列。
- 其他包不能被视频 keyframe burst 堵住。
- 视频占绝大多数带宽，应当吃剩余发送机会。

## 10. pacing 设计

pacing 保留。

原因：

- 视频按帧产生，不 pacing 会形成瞬时 burst。
- 30 Mbps / 30fps 平均每帧约 125 KB。
- 每帧按 1200 bytes 切片可能有 100 多个 UDP 包。
- keyframe 可能更大。
- 如果短时间内全部 `sendto`，容易造成内核 buffer、交换机、Wi-Fi、VR 接收端瞬时丢包。

第一版使用简单全局 token bucket：

```text
target_bitrate_bps
max_burst_bytes
max_debt_ms
max_queue_delay_ms
```

原则：

- 一个 UDP socket，所以只需要一个全局 pacer。
- `video_queue` 和 `other_queue` 都经过同一个 pacer。
- 默认所有包都计入 pacing。
- 小控制包可以允许少量透支，但不要绕过全局发送模型。
- 不实现复杂自适应拥塞控制。

这套 pacing 的目标是控制 burst，不是完整网络拥塞控制。

## 11. FEC 设计

FEC wire behavior 保持兼容。

内部实现建议：

- FEC 属于 packetizer 阶段。
- FEC 不单独拥有长期排队线程。
- FEC 输出的 parity 包进入 `video_queue`。
- parity 包在发送压力下优先被丢弃。
- `FecTableId == 0` 时完全跳过 FEC 计算。
- `FecTableId != 0` 时必须和现有 FEC table 字节兼容。

建议测试策略：

- LAN 首先用 FEC disabled 验证最低延迟。
- 公网/弱网再启用 FEC。
- 如果 FEC 造成排队延迟，优先降低码率或增加 IDR 频率，而不是加大队列。

## 12. 单 UDP socket

即使内部有两个队列，对外仍然只使用一个 UDP socket。

不建议多个 socket 绑定同一端口：

- receive 分发不可控。
- NAT 行为更难预测。
- 全局 pacing 会被破坏。
- 调试抓包复杂。

推荐模型：

```text
all producers
  -> queues
  -> scheduler
  -> one socket sendto

one socket recvfrom
  -> classify text control / Type
  -> dispatch
```

## 13. 时间戳和统计

时间戳策略：

- 优先使用 GStreamer buffer PTS。
- 转换到当前 UDP 协议期望的 timestamp 域。
- frame ID 保持单调递增，不依赖 wall clock。
- 音视频时间戳行为要和现有 VR 端兼容。

统计建议：

- capture fps
- encode fps
- encoded bitrate
- keyframe count
- packetized frames
- video queue frames / bytes
- other queue packets / bytes
- pacing wait time
- send bitrate
- dropped video frames
- dropped FEC parity
- dropped other packets
- socket send errors

## 14. 兼容性测试

### golden packet tests

对固定输入验证：

- packet type。
- header length。
- little-endian 字段编码。
- frame ID。
- packet sequence。
- fragment count。
- fragment index。
- payload length。
- FEC table ID。
- keyframe flag。
- FEC parity 数量和内容。

### live compatibility tests

使用现有 VR 端，完全不修改。

检查：

- 正常配对。
- 正常发送 VideoConfig / AudioConfig。
- UDP HELLO / PING / ACK 正常。
- 首个可解码画面从 keyframe 开始。
- keyframe burst 时 audio / telemetry 不被明显阻塞。
- 网络变慢时延迟不会持续增长。

### performance tests

检查：

- 3840x1520@30fps 持续编码。
- 30 Mbps baseline。
- keyframe burst。
- LAN 下队列深度。
- 限速下队列丢弃行为。
- CPU / GPU / VIC / NVENC 使用情况。

## 15. 建议新仓库结构

```text
robot_media_bridge/
  CMakeLists.txt
  README.md
  config/
    default.yaml
    gst_video_profiles.yaml
    fec_table_v1.json
  proto/
    signaling.proto
  doc/
    ROBOT_SIDE_REWRITE_DESIGN.md
    UDP_PROTOCOL_SPEC.md
    GRPC_SIGNALING_SPEC.md
    BUSINESS_FLOW_SPEC.md
    LIFECYCLE_SPEC.md
  include/
    app/
    signaling/
    video/
    audio/
    telemetry/
    control/
    pose/
    transport/
    ros/
    utils/
  src/
    app/
      main.cpp
      session_controller.cpp
      stream_supervisor.cpp
    signaling/
      grpc_signaling_client.cpp
      grpc_signaling_types.cpp
    video/
      video_stream.cpp
      gst_h264_encoder.cpp
      video_packetizer.cpp
      fec_v2.cpp
      h264_nal_parser.cpp
    audio/
      audio_stream.cpp
      gst_audio_opus.cpp
      audio_packetizer.cpp
    telemetry/
      telemetry_low_rate_stream.cpp
      telemetry_high_rate_stream.cpp
      telemetry_codec.cpp
      telemetry_sources.cpp
    control/
      control_stream.cpp
      control_plane.cpp
    pose/
      pose_input_stream.cpp
      pose_codec.cpp
      pose_publishers.cpp
    transport/
      udp_socket.cpp
      udp_transport.cpp
      send_scheduler.cpp
      token_bucket_pacer.cpp
    ros/
      ros_runtime.cpp
    utils/
      logger.cpp
      time.cpp
  tests/
    golden_packets/
    video/
    audio/
    telemetry/
    control/
    pose/
    transport/
    scheduler/
    lifecycle/
```

### 15.1 模块边界

```text
app/
  只负责总流程、session 状态机、生命周期编排。
  不处理 H.264 NAL、UDP 包头、FEC 字节细节。

signaling/
  只负责 gRPC 注册、心跳、配对、EventStream、媒体配置发布。
  对外 proto contract 不变。

video/
  负责 VideoStream、GStreamer H.264 编码、H.264 NAL 解析、0x01 packetizer、兼容 FEC。
  输出 datagram 到 video_queue，不直接 sendto。

audio/
  负责 AudioStream、Opus 编码/解码、0x04 packetizer。
  输出 datagram 到 other_queue。

telemetry/
  负责低频 0x05、高频 0x06、机器人状态采样、telemetry codec。
  低频和高频可独立启停。

control/
  负责 HELLO / PING / ACK、peer liveness、本地控制面状态。
  控制包进入 other_queue。

pose/
  负责 Type 0x02 姿态 UDP 输入、payload 校验、ROS pose/joy 发布适配。
  与视频发送生命周期独立。

transport/
  拥有 UDP socket、recv loop、send scheduler、video_queue、other_queue、pacer。
  不读取摄像头，不订阅 ROS topic，不理解 H.264/Opus/telemetry 业务细节。

ros/
  只保留 ROS runtime/executor/node glue。
  具体 telemetry source 和 pose publisher 放在对应业务目录。
```

依赖方向：

```text
app -> signaling / video / audio / telemetry / control / pose / transport
video -> transport
audio -> transport
telemetry -> transport / ros
control -> transport
pose -> ros
transport -> utils
ros -> utils
```

边界原则：

- `video/`、`audio/`、`telemetry/`、`control/`、`pose/` 是业务垂直切片，stream、codec、packetizer 和本业务测试尽量放在同一个目录族。
- `transport/` 只做发送/接收调度，不持有业务生命周期。
- domain 模块可以依赖 `transport/` 投递 datagram，但 `transport/` 不反向依赖 domain 模块。
- domain 模块之间不直接互相启停；跨模块协调只经过 `SessionController` / `StreamSupervisor`。

运行时关系：

```text
SessionController
  -> SignalingClient
  -> UdpTransport
  -> StreamSupervisor
       -> VideoStream
       -> AudioStream
       -> TelemetryLowRateStream
       -> TelemetryHighRateStream
       -> ControlStream
       -> PoseInputStream
```

### 15.2 线程模型

第一版建议线程模型如下，重点是少而清晰：

```text
main thread
  process start/exit/signal handling

session_event_loop thread
  serialize all session state transitions

gRPC/EventStream thread(s)
  receive gRPC callback
  post events only

UDP recv thread
  single socket recvfrom
  classify ACK / PING / binary Type
  post events or dispatch payload

UDP send thread
  drain other_queue + video_queue
  apply global pacing
  single socket sendto

VideoStream worker thread
  drain encoded_frame_queue
  parse H.264 metadata
  packetize/FEC
  enqueue video_queue

GStreamer internal threads
  v4l2src / nvjpegdec / nvvidconv / nvv4l2h264enc

AudioStream worker thread
  audio capture/encode or receive/playback
  enqueue other_queue

Telemetry timers / ROS executor thread(s)
  collect latest robot state
  timed 0x05 / 0x06 enqueue other_queue

PoseInput thread
  receive independent pose UDP if configured
  publish ROS pose/joy topics
```

硬规则：

- 所有生命周期状态流转进入 `session_event_loop` 串行处理。
- gRPC callback、UDP recv、GStreamer bus error、stream worker error 都只投递事件，不直接改全局 session 状态。
- 只有 `UDP send thread` 可以对共享媒体/遥测 socket 执行 `sendto()`。
- 业务流是 producer，不拥有 socket，也不自己做 pacing。
- `appsink callback` 不做 packetize / FEC / queue send / `sendto()`。
- 单个 stream 失败只触发该 stream 的 stop/retry，除非明确升级为 session-level 或 transport-level error。

## 16. 第一里程碑

第一里程碑应该刻意小：

```text
GStreamer H.264 encoder
  -> compatible 0x01 UDP video packetizer
  -> video_queue + other_queue
  -> global pacing
  -> existing VR receives video unchanged
```

第一里程碑不要求：

- audio 完整接入。
- telemetry 完整接入。
- ROS 全量接入。
- undistort。
- recording。
- eye image publisher。
- WebRTC transport。

先证明：**现有 VR 端可以无修改收到新机器人端的视频流，并且延迟不会因队列积压持续增长。**

第二里程碑再证明：

```text
VideoStream 异常重启时，
AudioStream / TelemetryStream / ControlStream 继续运行。
```

这条要做成明确验收项，不然新仓库很容易重新退化成“大总管式”生命周期。

## 17. 待确认问题

- `nvv4l2h264enc` 在 L4T R39.2.0 上的低延迟属性名和行为。
- `nvjpegdec -> nvvidconv -> nvv4l2h264enc` 对当前 MJPEG 4:2:2 摄像头是否完全稳定。
- `h264parse` 输出的 AU 是否满足当前 packetizer 对 SPS/PPS/IDR 的需求。
- 现有 VR 端是否依赖某些 startup quirk，例如 SPS/PPS 提前发布时序。
- audio 是否沿用当前实现，还是也整理为 GStreamer + appsink/appsrc 模块。
- LAN 默认是否关闭 FEC，公网测试默认是否开启 FEC。
