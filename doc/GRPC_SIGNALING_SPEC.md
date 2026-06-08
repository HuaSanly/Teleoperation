# gRPC 信令协议规格

> 状态：草案  
> 来源：`proto/signaling.proto`。  
> 原则：机器人端重写必须保持 gRPC service 和 message wire contract 不变。

## 1. Service

Package:

```text
signaling
```

Service:

```proto
service Signaling {
  rpc Register (RegisterRequest) returns (RegisterResponse);
  rpc Pair (PairRequest) returns (PairResponse);
  rpc Subscribe (SubscribeRequest) returns (SubscribeResponse);
  rpc ListUnpaired (ListUnpairedRequest) returns (ListUnpairedResponse);
  rpc Ping (Heartbeat) returns (HeartbeatAck);
  rpc GetP2pInfo (google.protobuf.Empty) returns (GetP2pInfoResponse);
  rpc PublishVideoConfig (VideoConfig) returns (VideoConfigAck);
  rpc AckVideoConfig (VideoConfigAck) returns (google.protobuf.Empty);
  rpc PublishAudioConfig (AudioConfig) returns (AudioConfigAck);
  rpc AckAudioConfig (AudioConfigAck) returns (google.protobuf.Empty);
  rpc EventStream (EventSubscribe) returns (stream EventMessage);
}
```

## 2. Endpoint identity

### RegisterRequest

```proto
message RegisterRequest {
  string token = 1;
  EndpointType role = 2;
  string device_id = 3;
  int32 robot_generation = 4;
  string vr_version = 5;
}
```

`EndpointType`:

| Value | Name | Meaning |
|---:|---|---|
| 0 | `UNKNOWN` | Unknown |
| 1 | `ROBOT` | Robot endpoint |
| 2 | `VR` | VR endpoint |

Robot registration rules:

- `role = ROBOT`
- `device_id` comes from robot config.
- `robot_generation` comes from robot config.
- `vr_version` should be empty for robot.
- `token` is used for authentication.

### RegisterResponse

```proto
message RegisterResponse {
  bool success = 1;
  string message = 2;
  string session_id = 3;
  string client_ip = 4;
  int32 client_port = 5;
}
```

Rules:

- `session_id` is required for UDP HELLO / PING and telemetry identity.
- `client_ip` and `client_port` describe the server-observed public endpoint.
- Registration failure enters retry flow.

## 3. Heartbeat

### Heartbeat

```proto
message Heartbeat {
  int64 client_time = 1;
}
```

### HeartbeatAck

```proto
message HeartbeatAck {
  int64 server_time = 1;
  bool push_connected = 2;
}
```

Rules:

- Robot sends heartbeat after successful registration.
- Heartbeat period comes from config.
- Transient transport failures may be tolerated briefly.
- Repeated transport failure or invalid session triggers re-registration.

## 4. Pairing

### PairRequest

```proto
message PairRequest {
  Operation op = 1;
  string peer_session_id = 2;
  PairState state = 3;
}
```

`Operation`:

| Value | Name |
|---:|---|
| 0 | `PAIR` |
| 1 | `UNPAIR` |

`PairState`:

| Value | Name |
|---:|---|
| 0 | `REQUEST` |
| 1 | `PENDING` |
| 2 | `ACCEPT` |
| 3 | `REJECT` |

Robot behavior:

- Active pairing mode may call `Pair(PAIR, peer_session_id, REQUEST)`.
- Passive mode waits for `EventStream` pair events.
- On accepted pair, robot enters media negotiation.
- On reject, robot returns to pairing state.
- On unpair, robot tears down active session-bound streams.

### ListUnpaired

```proto
message ListUnpairedRequest {
  RegisterRequest.EndpointType desired_role = 1;
}

message ListUnpairedResponse {
  repeated UnpairedEndpoint endpoints = 1;
}
```

Used by active pairing to discover candidate peers.

## 5. Subscribe

```proto
message SubscribeRequest {
  Operation op = 1;
  string publisher_session_id = 2;
  bool sub_video = 3;
  bool sub_pose = 4;
  bool sub_audio = 5;
}
```

`Operation`:

| Value | Name |
|---:|---|
| 0 | `SUBSCRIBE` |
| 1 | `UNSUBSCRIBE` |

Rules:

- Used by a subscriber to request resources from a publisher.
- Existing semantics must remain unchanged.

## 6. EventStream

### EventSubscribe

```proto
message EventSubscribe {
  string session_id = 1;
}
```

### EventMessage

```proto
message EventMessage {
  string sender_session_id = 1;
  string target_session_id = 2;
  int64 timestamp = 3;

  oneof payload {
    PairEvent pair = 10;
    SystemCommand system = 11;
    VideoConfig video_config = 12;
    AudioConfig audio_config = 13;
  }
}
```

Rules:

- Robot starts `EventStream` after registration and UDP handshake readiness.
- Events are handled asynchronously.
- Stream end should not crash the process; it should trigger recovery according to lifecycle spec.

### PairEvent

```proto
message PairEvent {
  Op op = 1;
  EndpointInfo peer = 2;
}
```

`Op`:

| Value | Name |
|---:|---|
| 0 | `REQUEST` |
| 1 | `ACCEPT` |
| 2 | `REJECT` |
| 3 | `UNPAIR` |

### SystemCommand

```proto
message SystemCommand {
  Action action = 1;
}
```

`Action`:

| Value | Name | Robot behavior |
|---:|---|---|
| 0 | `UNKNOWN` | Ignore |
| 1 | `RECONNECT_GRPC` | Reconnect / re-register gRPC |
| 2 | `REQUEST_PING` | Send or accelerate heartbeat/ping |
| 3 | `REQUEST_UDP_HELLO` | Reset UDP handshake and resend HELLO |

## 7. VideoConfig

```proto
message VideoConfig {
  CodecType codec = 1;
  int32 width = 2;
  int32 height = 3;
  int32 fps = 4;
  bytes sps = 5;
  bytes pps = 6;
  bytes vps = 7;
  string config_id = 8;
  VideoFov fov = 9;
}
```

`CodecType`:

| Value | Name |
|---:|---|
| 0 | `H264` |
| 1 | `H265` |

Rules:

- Robot publishes `VideoConfig` after encoder has SPS/PPS ready.
- H.264 must include `sps` and `pps`.
- H.265 must include `vps`, `sps`, and `pps`.
- `config_id` may be filled by server when forwarding.
- Receiver uses `AckVideoConfig` to acknowledge.

New rewrite recommendation:

- First implementation uses H.264.
- GStreamer output must still provide SPS/PPS compatible with existing receiver expectations.

## 8. AudioConfig

```proto
message AudioConfig {
  CodecType codec = 1;
  int32 sample_rate = 2;
  int32 channels = 3;
  int32 frame_duration_ms = 4;
  int32 samples_per_channel = 5;
  int32 bitrate_bps = 6;
  bool opus_inband_fec_enabled = 7;
  bool opus_dtx_enabled = 8;
  string config_id = 9;
}
```

`CodecType`:

| Value | Name |
|---:|---|
| 0 | `OPUS` |

Recommended values:

```text
sample_rate: 48000
channels: 1
frame_duration_ms: 20
samples_per_channel: 960
bitrate_bps: 64000
opus_inband_fec_enabled: true
opus_dtx_enabled: false
```

Rules:

- Robot publishes `AudioConfig` before sending audio payloads.
- Receiver uses `AckAudioConfig` to acknowledge.

## 9. GetP2pInfo

```proto
message GetP2pInfoResponse {
  bool ready = 1;
  string peer_session_id = 2;
  string peer_public_ip = 3;
  int32 peer_public_port = 4;
  bytes shared_key = 5;
}
```

Rules:

- Used to retrieve peer endpoint information when ready.
- Existing behavior must remain unchanged.

## 10. Metadata / session-id

Existing comments indicate several RPCs use metadata/header `session-id` to identify sender session. New implementation must preserve this behavior when calling:

- `GetP2pInfo`
- `PublishVideoConfig`
- `AckVideoConfig`
- `PublishAudioConfig`
- `AckAudioConfig`
- `EventStream`

## 11. gRPC lifecycle rules

- Register first.
- Start heartbeat after registration.
- Start EventStream when entering pairing phase.
- Publish media configs during negotiation.
- Treat heartbeat invalidation as session-level recovery.
- Do not let a single media stream error force gRPC re-registration.

