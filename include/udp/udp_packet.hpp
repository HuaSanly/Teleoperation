#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace trb::udp
{

// Video header V2 (26 bytes). All multi-byte fields are Little-Endian on wire.
struct VideoPacketHeaderV2
{
    uint8_t Type{0x01};
    uint16_t PacketSeqNum{0};
    uint64_t Timestamp{0};
    uint32_t FrameId{0};
    uint16_t FragmentIndex{0};
    uint16_t TotalFragments{0};
    uint16_t PayloadLength{0};
    uint32_t FramePayloadLength{0};
    uint8_t FecTableId{0};
};

class UdpPacketBuilder
{
public:
    explicit UdpPacketBuilder(size_t max_payload_bytes);

    void setSessionId(const std::string &session_id);

    size_t maxPayloadBytes() const { return max_payload_bytes_; }

    // Control-plane signaling messages (text).
    std::string buildHelloMessage() const;
    std::string buildPingMessage() const;

    // Data-plane packet: header + payload.
    void buildVideoPacket(const VideoPacketHeaderV2 &header,
                          const uint8_t *payload,
                          size_t payload_bytes,
                          std::vector<uint8_t> &out) const;

private:
    std::string generateSignature(const std::string &type, const std::string &timestamp) const;

    size_t max_payload_bytes_;
    std::string session_id_;
};

} // namespace trb::udp
