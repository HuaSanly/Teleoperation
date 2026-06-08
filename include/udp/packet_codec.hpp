#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "telemetry/robot_telemetry_types.hpp"

namespace trb::udp
{

    constexpr uint8_t kVideoPacketType = 0x01;
    constexpr uint8_t kAudioPacketType = 0x04;
    constexpr uint8_t kRobotTelemetryLowRateType = 0x05;
    constexpr uint8_t kRobotTelemetryHighRateType = 0x06;

    struct VideoPacketHeaderV2
    {
        uint8_t Type{kVideoPacketType};
        uint16_t PacketSeqNum{0};
        uint64_t Timestamp{0};
        uint32_t FrameId{0};
        uint16_t FragmentIndex{0};
        uint16_t TotalFragments{0};
        uint16_t PayloadLength{0};
        uint32_t FramePayloadLength{0};
        uint8_t FecTableId{0};
        uint8_t KeyframeFlag{0};
    };

    struct AudioPacketHeaderV2
    {
        uint8_t Type{0};
        uint16_t Seq{0};
        uint64_t TimestampNtp{0};
    };

    struct TelemetryPacketHeaderV1
    {
        uint8_t Type{kRobotTelemetryLowRateType};
        uint16_t Seq{0};
        uint64_t TxTimestampMs{0};
        std::string SessionId;
        std::string DeviceId;
    };

    class PacketCodec
    {
    public:
        explicit PacketCodec(size_t max_payload_bytes);

        void setSessionId(const std::string &session_id);
        void setDeviceId(const std::string &device_id);
        size_t maxPayloadBytes() const;

        std::string buildHelloMessage() const;
        std::string buildPingMessage() const;

        void buildVideoPacket(const VideoPacketHeaderV2 &header,
                              const uint8_t *payload,
                              size_t payload_bytes,
                              std::vector<uint8_t> &out) const;

        void buildAudioPacket(const AudioPacketHeaderV2 &header,
                              const uint8_t *payload,
                              size_t payload_bytes,
                              std::vector<uint8_t> &out) const;

        void buildRobotTelemetryPacket(const TelemetryPacketHeaderV1 &header,
                           const telemetry::RobotTelemetrySnapshot &snapshot,
                           std::vector<uint8_t> &out) const;

        void buildRobotJointTelemetryPacket(const TelemetryPacketHeaderV1 &header,
                            const telemetry::RobotJointTelemetrySnapshot &snapshot,
                            std::vector<uint8_t> &out) const;

    private:
        std::string generateSignature(const std::string &type, const std::string &timestamp) const;

        size_t max_payload_bytes_{1200};
        std::string session_id_;
        std::string device_id_;
    };

} // namespace trb::udp