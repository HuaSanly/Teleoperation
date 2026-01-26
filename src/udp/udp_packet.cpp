#include "udp/udp_packet.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>

#include <openssl/hmac.h>
#include <openssl/sha.h>

namespace trb::udp
{

namespace
{
inline void writeU8(std::vector<uint8_t> &out, uint8_t v)
{
    out.push_back(v);
}

inline void writeU16LE(std::vector<uint8_t> &out, uint16_t v)
{
    out.push_back(static_cast<uint8_t>(v & 0xFF));
    out.push_back(static_cast<uint8_t>((v >> 8) & 0xFF));
}

inline void writeU32LE(std::vector<uint8_t> &out, uint32_t v)
{
    out.push_back(static_cast<uint8_t>(v & 0xFF));
    out.push_back(static_cast<uint8_t>((v >> 8) & 0xFF));
    out.push_back(static_cast<uint8_t>((v >> 16) & 0xFF));
    out.push_back(static_cast<uint8_t>((v >> 24) & 0xFF));
}

inline void writeU64LE(std::vector<uint8_t> &out, uint64_t v)
{
    writeU32LE(out, static_cast<uint32_t>(v & 0xFFFFFFFFULL));
    writeU32LE(out, static_cast<uint32_t>((v >> 32) & 0xFFFFFFFFULL));
}

inline void writeBytes(std::vector<uint8_t> &out, const uint8_t *data, size_t size)
{
    out.insert(out.end(), data, data + size);
}
} // namespace

UdpPacketBuilder::UdpPacketBuilder(size_t max_payload_bytes)
    : max_payload_bytes_(max_payload_bytes)
{
}

void UdpPacketBuilder::setSessionId(const std::string &session_id)
{
    session_id_ = session_id;
}

std::string UdpPacketBuilder::buildHelloMessage() const
{
    if (session_id_.empty())
    {
        return {};
    }

    auto now = std::chrono::system_clock::now();
    auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
    std::string signature = generateSignature("HELLO", timestamp);

    return "HELLO|" + session_id_ + "|" + timestamp + "|" + signature;
}

std::string UdpPacketBuilder::buildPingMessage() const
{
    if (session_id_.empty())
    {
        return {};
    }

    auto now = std::chrono::system_clock::now();
    auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
    std::string signature = generateSignature("PING", timestamp);

    return "PING|" + session_id_ + "|" + timestamp + "|" + signature;
}

void UdpPacketBuilder::buildVideoPacket(const VideoPacketHeaderV2 &header,
                                        const uint8_t *payload,
                                        size_t payload_bytes,
                                        std::vector<uint8_t> &out) const
{
    out.clear();
    out.reserve(27 + payload_bytes);

    writeU8(out, header.Type);
    writeU16LE(out, header.PacketSeqNum);
    writeU64LE(out, header.Timestamp);
    writeU32LE(out, header.FrameId);
    writeU16LE(out, header.FragmentIndex);
    writeU16LE(out, header.TotalFragments);
    writeU16LE(out, header.PayloadLength);
    writeU32LE(out, header.FramePayloadLength);
    writeU8(out, header.FecTableId);
    writeU8(out, header.KeyframeFlag);

    if (payload_bytes > 0)
    {
        writeBytes(out, payload, payload_bytes);
    }
}

std::string UdpPacketBuilder::generateSignature(const std::string &type, const std::string &timestamp) const
{
    std::string data = type + session_id_ + timestamp;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int len = SHA256_DIGEST_LENGTH;

    HMAC(EVP_sha256(), session_id_.c_str(), session_id_.length(),
         reinterpret_cast<const unsigned char *>(data.c_str()), data.length(),
         hash, &len);

    std::stringstream ss;
    for (unsigned int i = 0; i < len; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

} // namespace trb::udp
