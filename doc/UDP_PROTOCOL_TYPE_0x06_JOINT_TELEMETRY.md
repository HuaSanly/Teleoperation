# UDP Type `0x06`: High-Rate Joint Telemetry

Direction: Robot -> server/VR

Purpose: sends high-rate robot joint states. The packet carries joint arrays
without names, so `SchemaId` defines the joint count and index mapping.

Recommended period: `20 ms` / `50 Hz`.

All integer and float fields are little-endian. Float fields are IEEE-754
`float32`.

## Datagram Layout

```c
struct TelemetryDatagramHeaderV1 {
  uint8_t  Type;           // 0x06
  uint16_t Seq;            // LE
  uint64_t TxTimestampMs;  // LE, Unix ms
  uint8_t  SessionIdBytes;
  uint8_t  DeviceIdBytes;
  uint8_t  IdentifierTable[]; // SessionId bytes, then DeviceId bytes
};

struct RobotJointTelemetryHighRatePayloadV1 {
  uint8_t  Version;           // 1
  uint16_t SchemaId;          // LE, 2
  uint64_t SampleTimestampMs; // LE, source sample Unix ms
  uint8_t  JointCount;        // 19
  uint32_t ValidMask;         // LE, bit i set means JointStates[i] is valid
  struct {
    float PositionRad;
    float VelocityRadS;
    float EffortNm;
  } JointStates[JointCount];
};
```

Wire order:

```text
TelemetryDatagramHeaderV1
RobotJointTelemetryHighRatePayloadV1
```

## Fields

| Field | Meaning |
|---|---|
| `Type` | Fixed `0x06`. |
| `Seq` | Telemetry sequence number shared by robot telemetry packets. |
| `TxTimestampMs` | Sender wall-clock Unix timestamp in milliseconds. |
| `SessionIdBytes` / `DeviceIdBytes` | Byte lengths for the identifier table. |
| `Version` | High-rate joint telemetry payload version, currently `1`. |
| `SchemaId` | Joint mapping identifier, currently `2`. |
| `SampleTimestampMs` | Timestamp of the ROS joint sample; falls back to current Unix ms if missing. |
| `JointCount` | Number of joint entries, currently `19`. |
| `ValidMask` | Validity bitmask for indices `0..31`; bit `i` covers `JointStates[i]`. |
| `PositionRad` | Joint position in radians. |
| `VelocityRadS` | Joint velocity in radians per second; `0` when source velocity is absent. |
| `EffortNm` | Joint effort in Nm; `0` when source effort is absent. |

## `SchemaId == 2` Joint Order

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
| 17 | `Head02_Joint` |
| 18 | `Head03_Joint` |

## Current Robot-Side Source

The bridge currently builds this packet from IK output topic `/joint_states`
(`sensor_msgs/msg/JointState`). It matches entries by joint name and ignores
extra joints not listed in the schema table.

For each schema joint:

- `PositionRad` comes from `JointState.position[i]`.
- `VelocityRadS` comes from `JointState.velocity[i]` when present, otherwise `0`.
- `EffortNm` comes from `JointState.effort[i]` when present, otherwise `0`.
- The `ValidMask` bit is set only when the source position exists and is finite.
