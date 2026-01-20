#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "udp/scream_controller.hpp"

namespace trb::udp
{

    class ScreamControllerEricsson : public IScreamController
    {
    public:
        ScreamControllerEricsson();
        ~ScreamControllerEricsson() override;

        void setConfig(const ScreamControllerConfig &config) override;
        void onFrameEncoded(size_t bytes, uint64_t capture_timestamp_us) override;
        void onPacketSent(uint16_t seq, size_t bytes, uint64_t send_time_us) override;
        void onFeedback(const ScreamFeedback &fb) override;

        uint64_t pacingRateBps() const override;
        uint64_t targetBitrateBps() const override;

    private:
        uint32_t toNtpQ16Now() const;
        uint32_t toNtpQ16FromNtp64(uint64_t ntp64) const;
        uint64_t clampBps(uint64_t v, uint64_t min_v, uint64_t max_v) const;
        void ensureStreamRegistered(uint32_t now_ntp);
        void updateRates(uint32_t now_ntp);

        ScreamControllerConfig config_{};
        uint64_t last_pacing_bps_{0};
        uint64_t last_target_bps_{0};

        uint32_t ssrc_{0x12345678u};
        int stream_id_{0};
        bool stream_registered_{false};

        struct Impl;
        std::unique_ptr<Impl> impl_;
    };

} // namespace trb::udp
