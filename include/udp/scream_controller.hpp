#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace trb::udp
{

    struct ScreamFeedback
    {
        uint16_t base_seq{0};
        uint16_t ack_vector_bits{0};
        std::vector<uint8_t> ack_vector;
        uint64_t rx_timestamp_ntp{0};
    };

    struct ScreamControllerConfig
    {
        bool enabled{false};
        uint64_t fallback_pacing_bps{0};
        uint64_t min_pacing_bps{0};
        uint64_t max_pacing_bps{0};
        uint64_t min_target_bitrate_bps{0};
        uint64_t max_target_bitrate_bps{0};
    };

    class IScreamController
    {
    public:
        virtual ~IScreamController() = default;

        virtual void setConfig(const ScreamControllerConfig &config) = 0;
        virtual void onFrameEncoded(size_t bytes, uint64_t capture_timestamp_us) = 0;
        virtual void onPacketSent(uint16_t seq, size_t bytes, uint64_t send_time_us) = 0;
        virtual void onFeedback(const ScreamFeedback &fb) = 0;

        virtual uint64_t pacingRateBps() const = 0;
        virtual uint64_t targetBitrateBps() const = 0;
    };

    // Minimal, non-invasive stub controller. It exposes SCReAM-like interfaces
    // while keeping behavior deterministic and independent of transport logic.
    class ScreamControllerSimple : public IScreamController
    {
    public:
        ScreamControllerSimple();

        void setConfig(const ScreamControllerConfig &config) override;
        void onFrameEncoded(size_t bytes, uint64_t capture_timestamp_us) override;
        void onPacketSent(uint16_t seq, size_t bytes, uint64_t send_time_us) override;
        void onFeedback(const ScreamFeedback &fb) override;

        uint64_t pacingRateBps() const override;
        uint64_t targetBitrateBps() const override;

    private:
        ScreamControllerConfig config_{};
        uint64_t last_pacing_bps_{0};
        uint64_t last_target_bps_{0};
        uint64_t last_feedback_ntp_{0};
    };

} // namespace trb::udp
