#include "audio/audio_module.hpp"

#include <algorithm>
#include <utility>

namespace trb::audio
{

    namespace
    {

        template <typename T>
        T declareOrGet(rclcpp::Node &node, const std::string &name, const T &default_value)
        {
            if (!node.has_parameter(name))
            {
                return node.declare_parameter<T>(name, default_value);
            }
            T value{};
            node.get_parameter(name, value);
            return value;
        }

    } // namespace

    AudioModule::Config AudioModule::configFromRosParam(rclcpp::Node &node)
    {
        Config cfg;
        cfg.enabled = declareOrGet<bool>(node, "audio.enabled", false);
        cfg.uplink_enabled = declareOrGet<bool>(node, "audio.uplink_enabled", true);
        cfg.downlink_enabled = declareOrGet<bool>(node, "audio.downlink_enabled", true);
        cfg.aec_enabled = declareOrGet<bool>(node, "audio.aec_enabled", false);
        cfg.capture_device = declareOrGet<std::string>(node, "audio.capture_device", "");
        cfg.playback_device = declareOrGet<std::string>(node, "audio.playback_device", "");
        cfg.playback_volume = std::max(0.0, declareOrGet<double>(node, "audio.playback_volume", 1.0));

        cfg.sample_rate = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.sample_rate", 48000)));
        cfg.channels = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.channels", 1)));
        cfg.frame_duration_ms = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.frame_duration_ms", 20)));
        cfg.samples_per_channel = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.samples_per_channel", 960)));
        cfg.bitrate_bps = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.bitrate_bps", 64000)));
        cfg.opus_inband_fec_enabled = declareOrGet<bool>(node, "audio.opus_inband_fec_enabled", true);
        cfg.opus_dtx_enabled = declareOrGet<bool>(node, "audio.opus_dtx_enabled", false);
        return cfg;
    }

    AudioModule::AudioModule(rclcpp::Node &node, const Config &config)
        : logger_(node.get_logger()), config_(config), receiver_config_(AudioReceiver::configFromRosParam(node, config.frame_duration_ms))
    {
    }

    AudioModule::~AudioModule()
    {
        stop();
        manager_.reset();
    }

    bool AudioModule::initialize()
    {
        if (!config_.enabled)
        {
            RCLCPP_INFO(logger_, "AudioModule disabled");
            return false;
        }

        manager_ = std::make_unique<AudioManager>(logger_);
        if (encoded_cb_)
        {
            manager_->setEncodedPacketCallback(encoded_cb_);
        }
        if (!manager_->initialize(config_))
        {
            RCLCPP_WARN(logger_, "AudioManager initialize failed");
            manager_.reset();
            return false;
        }
        receiver_ = std::make_unique<AudioReceiver>(logger_, receiver_config_);
        receiver_->setPlaybackCallback(
            [this](const uint8_t *data, size_t size, uint64_t timestamp_ntp) {
                return manager_ && manager_->pushRemoteOpusPacket(data, size, timestamp_ntp);
            });

        RCLCPP_INFO(logger_, "AudioModule initialized (will start after AV negotiation)");
        return true;
    }

    bool AudioModule::start()
    {
        if (!manager_)
        {
            return false;
        }
        if (started_.load(std::memory_order_acquire))
        {
            return true;
        }
        if (!config_published_.load(std::memory_order_acquire))
        {
            RCLCPP_WARN(logger_, "AudioConfig not negotiated yet; AudioModule will not start");
            return false;
        }
        if (!manager_->start())
        {
            RCLCPP_WARN(logger_, "AudioManager start failed");
            return false;
        }
        if (receiver_)
        {
            receiver_->reset("audio module start");
        }

        started_.store(true, std::memory_order_release);
        RCLCPP_INFO(logger_,
                    "AudioModule started (capture_device=%s playback_device=%s playback_volume=%.2f)",
                    config_.capture_device.empty() ? "<default>" : config_.capture_device.c_str(),
                    config_.playback_device.empty() ? "<default>" : config_.playback_device.c_str(),
                    config_.playback_volume);
        return true;
    }

    void AudioModule::stop()
    {
        if (manager_ && started_.exchange(false, std::memory_order_acq_rel))
        {
            manager_->stop();
        }
    }

    void AudioModule::setEncodedPacketCallback(EncodedPacketCallback callback)
    {
        encoded_cb_ = std::move(callback);
        if (manager_)
        {
            manager_->setEncodedPacketCallback(encoded_cb_);
        }
    }

    bool AudioModule::pushRemoteOpusPacket(const uint8_t *data, size_t size, uint64_t timestamp_ntp)
    {
        if (!manager_)
        {
            return false;
        }
        return manager_->pushRemoteOpusPacket(data, size, timestamp_ntp);
    }

    bool AudioModule::receiveRemotePacket(uint16_t seq, const uint8_t *data, size_t size, uint64_t timestamp_ntp)
    {
        if (!manager_ || !receiver_ || !started_.load(std::memory_order_acquire))
        {
            return false;
        }
        if (!remote_config_ready_.load(std::memory_order_acquire))
        {
            static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
            RCLCPP_WARN_THROTTLE(logger_, steady_clock, 5000, "Dropping remote audio packet because remote AudioConfig is not ready");
            return false;
        }
        return receiver_->pushPacket(seq, data, size, timestamp_ntp);
    }

    bool AudioModule::applyRemoteConfig(const Config &remote_config, const std::string &config_id)
    {
        if (!manager_ || !receiver_)
        {
            return false;
        }
        if (remote_config.sample_rate != config_.sample_rate ||
            remote_config.channels != config_.channels ||
            remote_config.frame_duration_ms != config_.frame_duration_ms ||
            remote_config.samples_per_channel != config_.samples_per_channel)
        {
            RCLCPP_WARN(logger_,
                        "Remote AudioConfig does not match local playback config: remote=%uHz/%uch/%ums/%usamples local=%uHz/%uch/%ums/%usamples",
                        remote_config.sample_rate,
                        remote_config.channels,
                        remote_config.frame_duration_ms,
                        remote_config.samples_per_channel,
                        config_.sample_rate,
                        config_.channels,
                        config_.frame_duration_ms,
                        config_.samples_per_channel);
            resetRemoteConfig("remote config mismatch");
            return false;
        }

        remote_config_id_ = config_id;
        remote_config_ready_.store(true, std::memory_order_release);
        receiver_->reset("remote AudioConfig accepted");
        manager_->resetPlaybackTimeline();
        RCLCPP_INFO(logger_, "Remote AudioConfig accepted: config_id=%s", remote_config_id_.empty() ? "<empty>" : remote_config_id_.c_str());
        return true;
    }

    void AudioModule::resetRemoteConfig(const std::string &reason)
    {
        remote_config_ready_.store(false, std::memory_order_release);
        remote_config_id_.clear();
        if (receiver_)
        {
            receiver_->reset(reason.empty() ? "remote config reset" : reason);
        }
        if (manager_)
        {
            manager_->resetPlaybackTimeline();
        }
    }

} // namespace trb::audio