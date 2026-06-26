# UDP Type `0x05`: Low-Rate Robot Telemetry

Direction: Robot -> server/VR

Purpose: sends low-rate robot status such as battery, temperature, fault state,
network quality, model, and firmware version.

Recommended period: `1 Hz`.

All integer fields are little-endian. Text fields are UTF-8 byte strings truncated
to `uint8_t` length, so each text field is at most 255 bytes.

## Datagram Layout

```c
struct TelemetryDatagramHeaderV1 {
  uint8_t  Type;           // 0x05
  uint16_t Seq;            // LE
  uint64_t TxTimestampMs;  // LE, Unix ms
  uint8_t  SessionIdBytes;
  uint8_t  DeviceIdBytes;
  uint8_t  IdentifierTable[]; // SessionId bytes, then DeviceId bytes
};

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

Wire order:

```text
TelemetryDatagramHeaderV1
RobotTelemetryLowRatePayloadV1
```

## Fields

| Field | Meaning |
|---|---|
| `Type` | Fixed `0x05`. |
| `Seq` | Telemetry sequence number shared by robot telemetry packets. |
| `TxTimestampMs` | Sender wall-clock Unix timestamp in milliseconds. |
| `SessionIdBytes` / `DeviceIdBytes` | Byte lengths for the identifier table. |
| `Version` | Low-rate telemetry payload version, currently `1`. |
| `BatteryVoltageMv` | Battery voltage in millivolts; `0xFFFF` means unknown. |
| `BatteryCurrentMa` | Battery current in milliamps; `INT16_MIN` means unknown. |
| `BatteryTemperatureDeciC` | Battery temperature in 0.1 Celsius; `INT16_MIN` means unknown. |
| `FaultCodeBytes` | Byte length of `FaultCode`. |
| `NetworkQualityBytes` | Byte length of `NetworkQuality`. |
| `ModelBytes` | Byte length of `Model`. |
| `FirmwareVersionBytes` | Byte length of `FirmwareVersion`. |
| `TextTable` | Concatenated text fields in the length order above. |

## Current Robot-Side Sources

The bridge currently fills this packet from ROS status topics:

| Packet field | ROS topic | Source field |
|---|---|---|
| `BatteryVoltageMv` | `/agv_battery_state` | `battery_state.voltage * 1000` |
| `BatteryCurrentMa` | `/agv_battery_state` | `battery_state.current * 1000` |
| `BatteryTemperatureDeciC` | `/temperature` | `temperature.temperature * 10` |
| `FaultCode` | `/agv_device_state` | `error_domain`, mapped to text |
| `FirmwareVersion` | `/agv_device_state` | `firmware_version` |
| `Model` | ROS param `telemetry.low_rate.model` | configured string |
| `NetworkQuality` | internal fallback string | configured/default string |
