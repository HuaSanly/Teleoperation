#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace trb::udp
{

    // Video header V2 (final) based on doc/PROTOCOL_UDP_VIDEO_V2.md.
    // Total header size: 26 bytes. All multi-byte fields are Little-Endian on wire.
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

        // V2 fields: implicit grouping.
        // When FecTableId==0, the packet does not participate in FEC.
        uint8_t FecTableId{0};
    };

    enum class FecScheme : uint8_t
    {
        GF256_Cauchy_RS = 1,
        XOR_Parity = 2,
    };

    struct FecStaticProfile
    {
        uint8_t table_id{0};
        uint8_t profile_id{0};
        FecScheme scheme{FecScheme::GF256_Cauchy_RS};
        uint8_t k{0};
        uint8_t r{0};
        uint16_t symbol_bytes{0};

        // For GF256_Cauchy_RS: row-major r*k coefficients.
        // For XOR_Parity: empty.
        std::vector<uint8_t> coef;

        bool isValid() const;
    };

    // Lookup static-table FEC profile (FecTableId=1) defined by doc/FEC_COEFFICIENT_PROFILE_PROTOCOL(1).md.
    // Returns false if (table_id, profile_id) is unknown.
    bool lookupFecStaticProfile(uint8_t table_id, uint8_t profile_id, uint16_t symbol_bytes, FecStaticProfile &out);

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
