#include "udp/scream_controller.hpp"

#include <algorithm>

namespace trb::udp
{

    ScreamControllerSimple::ScreamControllerSimple()
    {
        last_pacing_bps_ = 0;
        last_target_bps_ = 0;
        last_feedback_ntp_ = 0;
    }

    void ScreamControllerSimple::setConfig(const ScreamControllerConfig &config)
    {
        config_ = config;
        if (!config_.enabled)
        {
            last_pacing_bps_ = 0;
            last_target_bps_ = 0;
            return;
        }

        const uint64_t fallback = config_.fallback_pacing_bps;
        const uint64_t min_pacing = config_.min_pacing_bps;
        const uint64_t max_pacing = config_.max_pacing_bps;
        if (fallback > 0)
        {
            uint64_t v = fallback;
            if (min_pacing > 0)
            {
                v = std::max(v, min_pacing);
            }
            if (max_pacing > 0)
            {
                v = std::min(v, max_pacing);
            }
            last_pacing_bps_ = v;
        }

        const uint64_t min_target = config_.min_target_bitrate_bps;
        const uint64_t max_target = config_.max_target_bitrate_bps;
        if (min_target > 0)
        {
            uint64_t v = min_target;
            if (max_target > 0)
            {
                v = std::min(v, max_target);
            }
            last_target_bps_ = v;
        }
    }

    void ScreamControllerSimple::onFrameEncoded(size_t, uint64_t)
    {
        // Stub: no-op.
    }

    void ScreamControllerSimple::onPacketSent(uint16_t, size_t, uint64_t)
    {
        // Stub: keep last rates unchanged.
    }

    void ScreamControllerSimple::onFeedback(const ScreamFeedback &fb)
    {
        // Stub: record feedback timestamp for diagnostics/extension.
        last_feedback_ntp_ = fb.rx_timestamp_ntp;
    }

    uint64_t ScreamControllerSimple::pacingRateBps() const
    {
        if (!config_.enabled)
        {
            return 0;
        }
        return last_pacing_bps_;
    }

    uint64_t ScreamControllerSimple::targetBitrateBps() const
    {
        if (!config_.enabled)
        {
            return 0;
        }
        return last_target_bps_;
    }

} // namespace trb::udp
