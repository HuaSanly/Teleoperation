#include "udp/packet_codec.hpp"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <sstream>

namespace trb::udp
{
    namespace
    {
        void writeU8(std::vector<uint8_t> &out, uint8_t value) { out.push_back(value); }

        void writeU16LE(std::vector<uint8_t> &out, uint16_t value)
        {
            out.push_back(static_cast<uint8_t>(value & 0xFF));
            out.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
        }

        void writeU32LE(std::vector<uint8_t> &out, uint32_t value)
        {
            out.push_back(static_cast<uint8_t>(value & 0xFF));
            out.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
            out.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
            out.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
        }

        void writeU64LE(std::vector<uint8_t> &out, uint64_t value)
        {
            writeU32LE(out, static_cast<uint32_t>(value & 0xFFFFFFFFULL));
            writeU32LE(out, static_cast<uint32_t>((value >> 32) & 0xFFFFFFFFULL));
        }

        void writeI16LE(std::vector<uint8_t> &out, int16_t value)
        {
            writeU16LE(out, static_cast<uint16_t>(value));
        }

        void writeF32LE(std::vector<uint8_t> &out, float value)
        {
            uint32_t bits = 0;
            static_assert(sizeof(bits) == sizeof(value));
            std::memcpy(&bits, &value, sizeof(bits));
            writeU32LE(out, bits);
        }

        void writeBytes(std::vector<uint8_t> &out, const uint8_t *data, size_t size)
        {
            if (data && size > 0)
            {
                out.insert(out.end(), data, data + size);
            }
        }

        std::string truncateU8String(const std::string &value)
        {
            if (value.size() <= 0xFFu)
            {
                return value;
            }
            return value.substr(0, 0xFFu);
        }

        void writeTelemetryHeader(const TelemetryPacketHeaderV1 &header,
                                  const std::string &session_id,
                                  const std::string &device_id,
                                  std::vector<uint8_t> &out)
        {
            writeU8(out, header.Type);
            writeU16LE(out, header.Seq);
            writeU64LE(out, header.TxTimestampMs);
            writeU8(out, static_cast<uint8_t>(session_id.size()));
            writeU8(out, static_cast<uint8_t>(device_id.size()));
            writeBytes(out, reinterpret_cast<const uint8_t *>(session_id.data()), session_id.size());
            writeBytes(out, reinterpret_cast<const uint8_t *>(device_id.data()), device_id.size());
        }
    } // namespace

    PacketCodec::PacketCodec(size_t max_payload_bytes) : max_payload_bytes_(max_payload_bytes) {}

    void PacketCodec::setSessionId(const std::string &session_id)
    {
        session_id_ = session_id;
    }

    void PacketCodec::setDeviceId(const std::string &device_id)
    {
        device_id_ = device_id;
    }

    size_t PacketCodec::maxPayloadBytes() const
    {
        return max_payload_bytes_;
    }

    std::string PacketCodec::buildHelloMessage() const
    {
        if (session_id_.empty())
        {
            return {};
        }
        const auto now = std::chrono::system_clock::now();
        const auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
        return "HELLO|" + session_id_ + "|" + timestamp + "|" + generateSignature("HELLO", timestamp);
    }

    std::string PacketCodec::buildPingMessage() const
    {
        if (session_id_.empty())
        {
            return {};
        }
        const auto now = std::chrono::system_clock::now();
        const auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
        return "PING|" + session_id_ + "|" + timestamp + "|" + generateSignature("PING", timestamp);
    }

    void PacketCodec::buildVideoPacket(const VideoPacketHeaderV2 &header,
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
        if (payload_bytes > 0 && payload)
        {
            out.insert(out.end(), payload, payload + payload_bytes);
        }
    }

    void PacketCodec::buildAudioPacket(const AudioPacketHeaderV2 &header,
                                       const uint8_t *payload,
                                       size_t payload_bytes,
                                       std::vector<uint8_t> &out) const
    {
        out.clear();
        out.reserve(11 + payload_bytes);
        writeU8(out, header.Type);
        writeU16LE(out, header.Seq);
        writeU64LE(out, header.TimestampNtp);
        if (payload_bytes > 0 && payload)
        {
            out.insert(out.end(), payload, payload + payload_bytes);
        }
    }

    void PacketCodec::buildRobotTelemetryPacket(const TelemetryPacketHeaderV1 &header,
                                                const telemetry::RobotTelemetrySnapshot &snapshot,
                                                std::vector<uint8_t> &out) const
    {
        const std::string session_id = truncateU8String(header.SessionId.empty() ? session_id_ : header.SessionId);
        const std::string device_id = truncateU8String(header.DeviceId.empty() ? device_id_ : header.DeviceId);
        const std::string fault_code = truncateU8String(snapshot.fault_code);
        const std::string network_quality = truncateU8String(snapshot.network_quality);
        const std::string model = truncateU8String(snapshot.model);
        const std::string firmware_version = truncateU8String(snapshot.firmware_version);

        out.clear();
        out.reserve(24 + session_id.size() + device_id.size() +
                    fault_code.size() + network_quality.size() + model.size() + firmware_version.size());
        writeTelemetryHeader(header, session_id, device_id, out);
        writeU8(out, snapshot.version);
        writeU16LE(out, snapshot.battery_voltage_mv);
        writeI16LE(out, snapshot.battery_current_ma);
        writeI16LE(out, snapshot.battery_temperature_deci_c);
        writeU8(out, static_cast<uint8_t>(fault_code.size()));
        writeU8(out, static_cast<uint8_t>(network_quality.size()));
        writeU8(out, static_cast<uint8_t>(model.size()));
        writeU8(out, static_cast<uint8_t>(firmware_version.size()));
        writeBytes(out, reinterpret_cast<const uint8_t *>(fault_code.data()), fault_code.size());
        writeBytes(out, reinterpret_cast<const uint8_t *>(network_quality.data()), network_quality.size());
        writeBytes(out, reinterpret_cast<const uint8_t *>(model.data()), model.size());
        writeBytes(out, reinterpret_cast<const uint8_t *>(firmware_version.data()), firmware_version.size());
    }

    void PacketCodec::buildRobotJointTelemetryPacket(const TelemetryPacketHeaderV1 &header,
                                                     const telemetry::RobotJointTelemetrySnapshot &snapshot,
                                                     std::vector<uint8_t> &out) const
    {
        constexpr size_t kMaxJointCount = 0xFFu;
        const std::string session_id = truncateU8String(header.SessionId.empty() ? session_id_ : header.SessionId);
        const std::string device_id = truncateU8String(header.DeviceId.empty() ? device_id_ : header.DeviceId);
        const size_t joint_count = std::min(snapshot.joints.size(), kMaxJointCount);

        uint32_t valid_mask = 0;
        const size_t mask_joint_count = std::min<size_t>(joint_count, 32);
        for (size_t joint_index = 0; joint_index < mask_joint_count; ++joint_index)
        {
            if (snapshot.joints[joint_index].valid)
            {
                valid_mask |= static_cast<uint32_t>(1u << joint_index);
            }
        }

        out.clear();
        out.reserve(29 + session_id.size() + device_id.size() + joint_count * 12);
        writeTelemetryHeader(header, session_id, device_id, out);
        writeU8(out, snapshot.version);
        writeU16LE(out, snapshot.schema_id);
        writeU64LE(out, snapshot.sample_timestamp_ms);
        writeU8(out, static_cast<uint8_t>(joint_count));
        writeU32LE(out, valid_mask);
        for (size_t joint_index = 0; joint_index < joint_count; ++joint_index)
        {
            const auto &joint = snapshot.joints[joint_index];
            writeF32LE(out, joint.position_rad);
            writeF32LE(out, joint.velocity_rad_s);
            writeF32LE(out, joint.effort_nm);
        }
    }

    std::string PacketCodec::generateSignature(const std::string &type, const std::string &timestamp) const
    {
        const std::string data = type + session_id_ + timestamp;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        unsigned int len = SHA256_DIGEST_LENGTH;

        HMAC(EVP_sha256(), session_id_.c_str(), session_id_.length(),
             reinterpret_cast<const unsigned char *>(data.c_str()), data.length(), hash, &len);

        std::stringstream stream;
        for (unsigned int index = 0; index < len; ++index)
        {
            stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[index]);
        }
        return stream.str();
    }

} // namespace trb::udp