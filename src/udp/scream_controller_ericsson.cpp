#include "udp/scream_controller_ericsson.hpp"

#include <algorithm>
#include <chrono>

#include "scream/code/ScreamTx.h"
#include "scream/code/RtpQueue.h"

namespace trb::udp
{

    struct ScreamControllerEricsson::Impl
    {
        ScreamV2Tx tx;

        class RtpQueueMinimal : public RtpQueueIface
        {
        public:
            int clear() override
            {
                return 0;
            }

            int sizeOfNextRtp() override
            {
                return size_of_next_;
            }

            int seqNrOfNextRtp() override
            {
                return has_seq_ ? static_cast<int>(last_seq_) : -1;
            }

            int seqNrOfLastRtp() override
            {
                return has_seq_ ? static_cast<int>(last_seq_) : -1;
            }

            int bytesInQueue() override
            {
                return 0;
            }

            int sizeOfQueue() override
            {
                return 0;
            }

            float getDelay(float) override
            {
                return 0.0f;
            }

            int getSizeOfLastFrame() override
            {
                return size_of_last_frame_;
            }

            void onPacket(uint16_t seq, size_t bytes)
            {
                last_seq_ = seq;
                size_of_next_ = static_cast<int>(bytes);
                has_seq_ = true;
            }

            void onFrame(size_t bytes)
            {
                size_of_last_frame_ = static_cast<int>(bytes);
            }

        private:
            bool has_seq_{false};
            uint16_t last_seq_{0};
            int size_of_next_{0};
            int size_of_last_frame_{0};
        } rtp_queue;
    };

    ScreamControllerEricsson::ScreamControllerEricsson()
        : impl_(std::make_unique<Impl>())
    {
    }

    ScreamControllerEricsson::~ScreamControllerEricsson() = default;

    void ScreamControllerEricsson::setConfig(const ScreamControllerConfig &config)
    {
        config_ = config;
        const uint32_t now_ntp = toNtpQ16Now();
        ensureStreamRegistered(now_ntp);

        if (stream_registered_)
        {
            const uint64_t min_bps = config_.min_target_bitrate_bps;
            const uint64_t max_bps = config_.max_target_bitrate_bps;
            impl_->tx.updateBitrateStream(ssrc_, static_cast<float>(min_bps),
                                          static_cast<float>(max_bps > 0 ? max_bps : min_bps));
        }

        updateRates(now_ntp);
    }

    void ScreamControllerEricsson::onFrameEncoded(size_t bytes, uint64_t)
    {
        if (!config_.enabled)
        {
            return;
        }

        const uint32_t now_ntp = toNtpQ16Now();
        ensureStreamRegistered(now_ntp);
        impl_->rtp_queue.onFrame(bytes);
        impl_->tx.newMediaFrame(now_ntp, ssrc_, static_cast<int>(bytes), true);
        updateRates(now_ntp);
    }

    void ScreamControllerEricsson::onPacketSent(uint16_t seq, size_t bytes, uint64_t)
    {
        if (!config_.enabled)
        {
            return;
        }

        const uint32_t now_ntp = toNtpQ16Now();
        ensureStreamRegistered(now_ntp);
        impl_->rtp_queue.onPacket(seq, bytes);
        impl_->tx.addTransmitted(now_ntp, ssrc_, static_cast<int>(bytes), seq, false, 0.0f, 0);
        updateRates(now_ntp);
    }

    void ScreamControllerEricsson::onFeedback(const ScreamFeedback &fb)
    {
        if (!config_.enabled)
        {
            return;
        }

        const uint32_t now_ntp = toNtpQ16Now();
        ensureStreamRegistered(now_ntp);

        const uint16_t bits = fb.ack_vector_bits;
        if (bits == 0 || fb.ack_vector.empty())
        {
            return;
        }

        const uint32_t rx_time_ntp = toNtpQ16FromNtp64(fb.rx_timestamp_ntp);

        bool any = false;
        uint16_t last_seq = 0;
        std::vector<uint16_t> acked;
        acked.reserve(bits);

        for (uint16_t i = 0; i < bits; ++i)
        {
            const size_t byte_idx = static_cast<size_t>(i / 8);
            const uint8_t mask = static_cast<uint8_t>(1u << (i % 8));
            if (byte_idx >= fb.ack_vector.size())
            {
                break;
            }
            if (fb.ack_vector[byte_idx] & mask)
            {
                const uint16_t seq = static_cast<uint16_t>(fb.base_seq + i);
                acked.push_back(seq);
                last_seq = seq;
                any = true;
            }
        }

        if (!any)
        {
            return;
        }

        for (uint16_t seq : acked)
        {
            const bool is_last = (seq == last_seq);
            impl_->tx.incomingStandardizedFeedback(now_ntp, stream_id_, rx_time_ntp, seq, 0, is_last);
        }

        updateRates(now_ntp);
    }

    uint64_t ScreamControllerEricsson::pacingRateBps() const
    {
        if (!config_.enabled)
        {
            return 0;
        }
        return last_pacing_bps_;
    }

    uint64_t ScreamControllerEricsson::targetBitrateBps() const
    {
        if (!config_.enabled)
        {
            return 0;
        }
        return last_target_bps_;
    }

    uint32_t ScreamControllerEricsson::toNtpQ16Now() const
    {
        using clock = std::chrono::system_clock;
        const auto now = clock::now();
        const auto dur = now.time_since_epoch();
        const auto sec = std::chrono::duration_cast<std::chrono::seconds>(dur);
        const auto usec = std::chrono::duration_cast<std::chrono::microseconds>(dur - sec);

        const uint32_t ntp_seconds = static_cast<uint32_t>(sec.count() + 2208988800U);
        const uint32_t ntp_fraction = static_cast<uint32_t>((usec.count() * 4294967296.0) / 1000000.0);
        const uint64_t ntp64 = (static_cast<uint64_t>(ntp_seconds) << 32) | ntp_fraction;

        return static_cast<uint32_t>((ntp64 >> 16) & 0xFFFFFFFFu);
    }

    uint32_t ScreamControllerEricsson::toNtpQ16FromNtp64(uint64_t ntp64) const
    {
        return static_cast<uint32_t>((ntp64 >> 16) & 0xFFFFFFFFu);
    }

    uint64_t ScreamControllerEricsson::clampBps(uint64_t v, uint64_t min_v, uint64_t max_v) const
    {
        if (min_v > 0)
        {
            v = std::max(v, min_v);
        }
        if (max_v > 0)
        {
            v = std::min(v, max_v);
        }
        return v;
    }

    void ScreamControllerEricsson::ensureStreamRegistered(uint32_t now_ntp)
    {
        if (stream_registered_)
        {
            return;
        }

        const uint64_t min_bps = config_.min_target_bitrate_bps > 0 ? config_.min_target_bitrate_bps : 100000;
        const uint64_t max_bps = config_.max_target_bitrate_bps > 0 ? config_.max_target_bitrate_bps : 20000000;
        uint64_t start_bps = config_.fallback_pacing_bps > 0 ? config_.fallback_pacing_bps : max_bps;
        start_bps = clampBps(start_bps, min_bps, max_bps);

        impl_->tx.registerNewStream(&impl_->rtp_queue,
                                    ssrc_,
                                    1.0f,
                                    static_cast<float>(min_bps),
                                    static_cast<float>(start_bps),
                                    static_cast<float>(max_bps));

        stream_registered_ = true;
        updateRates(now_ntp);
    }

    void ScreamControllerEricsson::updateRates(uint32_t now_ntp)
    {
        if (!stream_registered_)
        {
            return;
        }

        float target = impl_->tx.getTargetBitrate(now_ntp, ssrc_);
        if (target > 0)
        {
            uint64_t target_bps = static_cast<uint64_t>(target);
            last_target_bps_ = clampBps(target_bps, config_.min_target_bitrate_bps, config_.max_target_bitrate_bps);
        }
        else if (last_target_bps_ == 0)
        {
            last_target_bps_ = clampBps(config_.fallback_pacing_bps,
                                        config_.min_target_bitrate_bps,
                                        config_.max_target_bitrate_bps);
        }

        uint64_t pacing = last_target_bps_ > 0 ? last_target_bps_ : config_.fallback_pacing_bps;
        if (pacing == 0)
        {
            pacing = last_target_bps_;
        }
        last_pacing_bps_ = clampBps(pacing, config_.min_pacing_bps, config_.max_pacing_bps);
    }

} // namespace trb::udp
