#include "udp/udp_packet.hpp"
#include "udp/gf256.hpp"

#include <chrono>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <sstream>

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

        inline uint8_t cauchyCoef(uint8_t j, uint8_t i)
        {
            // Doc rule (FecTableId=1, Scheme=GF256_Cauchy_RS):
            // X[i]=i, Y[j]=0x80+j, a[j,i]=(X[i] xor Y[j])^{-1} in GF(256) with prim poly 0x11D.
            const uint8_t x = i;
            const uint8_t y = static_cast<uint8_t>(0x80u + static_cast<uint8_t>(j));
            return gf256::inv(static_cast<uint8_t>(x ^ y));
        }

    } // namespace

    bool FecStaticProfile::isValid() const
    {
        if (table_id == 0 || profile_id == 0 || symbol_bytes == 0 || k == 0 || r == 0)
        {
            return false;
        }
        if (scheme == FecScheme::GF256_Cauchy_RS)
        {
            return coef.size() == static_cast<size_t>(k) * static_cast<size_t>(r);
        }
        if (scheme == FecScheme::XOR_Parity)
        {
            return coef.empty();
        }
        return false;
    }

    bool lookupFecStaticProfile(uint8_t table_id, uint8_t profile_id, uint16_t symbol_bytes, FecStaticProfile &out)
    {
        out = FecStaticProfile{};

        // This package implements the doc-defined static table only.
        if (table_id != 1)
        {
            return false;
        }

        out.table_id = table_id;
        out.profile_id = profile_id;
        out.symbol_bytes = symbol_bytes;

        switch (profile_id)
        {
        case 0x10: // RS_K32_R8_CAUCHY_V1
            out.scheme = FecScheme::GF256_Cauchy_RS;
            out.k = 32;
            out.r = 8;
            break;
        case 0x11: // RS_K16_R2_CAUCHY_V1
            out.scheme = FecScheme::GF256_Cauchy_RS;
            out.k = 16;
            out.r = 2;
            break;
        case 0x20: // XOR_K8_R1_V1
            out.scheme = FecScheme::XOR_Parity;
            out.k = 8;
            out.r = 1;
            break;
        case 0x21: // XOR_K4_R1_V1
            out.scheme = FecScheme::XOR_Parity;
            out.k = 4;
            out.r = 1;
            break;
        case 0x22: // XOR_K3_R1_V1
            out.scheme = FecScheme::XOR_Parity;
            out.k = 3;
            out.r = 1;
            break;
        case 0x23: // XOR_K2_R1_V1
            out.scheme = FecScheme::XOR_Parity;
            out.k = 2;
            out.r = 1;
            break;
        default:
            return false;
        }

        // Protocol-fixed constraints.
        if (out.symbol_bytes != 1200)
        {
            // Current doc fixes SymbolBytes=1200.
            return false;
        }
        if ((static_cast<uint16_t>(out.k) + static_cast<uint16_t>(out.r)) > 256)
        {
            return false;
        }

        if (out.scheme == FecScheme::GF256_Cauchy_RS)
        {
            out.coef.resize(static_cast<size_t>(out.k) * static_cast<size_t>(out.r));
            for (uint8_t j = 0; j < out.r; ++j)
            {
                for (uint8_t i = 0; i < out.k; ++i)
                {
                    out.coef[static_cast<size_t>(j) * static_cast<size_t>(out.k) + static_cast<size_t>(i)] = cauchyCoef(j, i);
                }
            }
        }
        else
        {
            out.coef.clear();
        }

        return out.isValid();
    }

    UdpPacketBuilder::UdpPacketBuilder(size_t max_payload_bytes) : max_payload_bytes_(max_payload_bytes) {}

    void UdpPacketBuilder::setSessionId(const std::string &session_id)
    {
        session_id_ = session_id;
    }

    std::string UdpPacketBuilder::buildHelloMessage() const
    {
        if (session_id_.empty())
            return {};

        auto now = std::chrono::system_clock::now();
        auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
        std::string signature = generateSignature("HELLO", timestamp);

        return "HELLO|" + session_id_ + "|" + timestamp + "|" + signature;
    }

    std::string UdpPacketBuilder::buildPingMessage() const
    {
        if (session_id_.empty())
            return {};

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
        out.reserve(26 + payload_bytes);

        writeU8(out, header.Type);
        writeU16LE(out, header.PacketSeqNum);
        writeU64LE(out, header.Timestamp);
        writeU32LE(out, header.FrameId);
        writeU16LE(out, header.FragmentIndex);
        writeU16LE(out, header.TotalFragments);
        writeU16LE(out, header.PayloadLength);
        writeU32LE(out, header.FramePayloadLength);
        writeU8(out, header.FecTableId);

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
