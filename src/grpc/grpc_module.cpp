#include "grpc/grpc_module.hpp"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <sstream>
#include <utility>

namespace trb
{
    namespace
    {
        constexpr uint32_t kMaxTransientHeartbeatFailuresBeforeReregister = 3;

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

        std::chrono::nanoseconds periodFromSeconds(double seconds)
        {
            const double bounded_seconds = std::max(0.001, seconds);
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(bounded_seconds));
        }

        std::chrono::nanoseconds heartbeatPeriodFromSeconds(double seconds)
        {
            const double bounded_seconds = std::max(0.001, seconds);
            // Keep a small margin before the nominal heartbeat deadline so the
            // first and subsequent pings do not land exactly on the server's
            // session-expiry boundary.
            const double margin_seconds = std::min(2.0, bounded_seconds * 0.2);
            const double effective_seconds = std::max(0.001, bounded_seconds - margin_seconds);
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(effective_seconds));
        }

        std::string bytesPreview(const std::vector<uint8_t> &bytes)
        {
            std::string preview;
            const size_t preview_size = std::min(bytes.size(), static_cast<size_t>(32));
            for (size_t index = 0; index < preview_size; ++index)
            {
                char buffer[4];
                std::snprintf(buffer, sizeof(buffer), "%02X ", bytes[index]);
                preview += buffer;
            }
            if (bytes.size() > preview_size)
            {
                preview += "...";
            }
            return preview;
        }

        bool hasValidContext(rclcpp::Node &node)
        {
            const auto base = node.get_node_base_interface();
            const auto context = base ? base->get_context() : rclcpp::Context::SharedPtr{};
            return context && context->is_valid();
        }
    } // namespace

    GrpcModule::Config GrpcModule::configFromRosParam(rclcpp::Node &node)
    {
        Config config;
        config.server_grpc_ip = declareOrGet<std::string>(node, "grpc.server_grpc_ip", "");
        config.server_grpc_port = declareOrGet<int>(node, "grpc.server_grpc_port", 0);
        config.use_ssl = declareOrGet<bool>(node, "grpc.use_ssl", false);
        config.device_id = declareOrGet<std::string>(node, "grpc.device_id", "");
        config.robot_generation = declareOrGet<int>(node, "grpc.robot_generation", 2);
        config.token = declareOrGet<std::string>(node, "grpc.token", "");
        config.rpc_timeout_ms = declareOrGet<int>(node, "grpc.rpc_timeout_ms", 5000);
        config.register_retry_sec = declareOrGet<double>(node, "grpc.register_retry_sec", 3.0);
        config.heartbeat_sec = declareOrGet<double>(node, "grpc.heartbeat_sec", 15.0);
        return config;
    }

    GrpcModule::AudioConfig GrpcModule::audioConfigFromRosParam(rclcpp::Node &node)
    {
        AudioConfig config;
        config.sample_rate = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.sample_rate", 48000)));
        config.channels = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.channels", 1)));
        config.frame_duration_ms = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.frame_duration_ms", 20)));
        config.samples_per_channel = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.samples_per_channel", 960)));
        config.bitrate_bps = static_cast<uint32_t>(std::max(1, declareOrGet<int>(node, "audio.bitrate_bps", 64000)));
        config.opus_inband_fec_enabled = declareOrGet<bool>(node, "audio.opus_inband_fec_enabled", true);
        config.opus_dtx_enabled = declareOrGet<bool>(node, "audio.opus_dtx_enabled", false);
        return config;
    }

    GrpcModule::GrpcModule(rclcpp::Node &node, const Config &config)
        : node_(node), logger_(node.get_logger()), config_(config)
    {
        manager_ = std::make_unique<GrpcManager>(config_, logger_);
    }

    GrpcModule::~GrpcModule()
    {
        stop();
        manager_.reset();
    }

    void GrpcModule::start()
    {
        shutting_down_.store(false, std::memory_order_release);
        tryRegister();
        if (!registered_.load())
        {
            startRegisterRetryTimer();
            RCLCPP_WARN(logger_, "gRPC register failed, entering pending state. Will retry every %.1f seconds.",
                        config_.register_retry_sec);
        }
    }

    void GrpcModule::stop()
    {
        shutting_down_.store(true, std::memory_order_release);
        on_registered_ = nullptr;
        on_event_ = nullptr;
        on_heartbeat_fail_ = nullptr;
        on_stream_end_ = nullptr;
        if (manager_)
        {
            manager_->CancelPendingRpcs();
        }
        if (register_retry_timer_)
        {
            register_retry_timer_->cancel();
            register_retry_timer_.reset();
        }
        if (heartbeat_timer_)
        {
            heartbeat_timer_->cancel();
            heartbeat_timer_.reset();
        }
        if (manager_)
        {
            manager_->StopEventStream();
        }
        registered_.store(false);
        consecutive_heartbeat_transport_failures_ = 0;
    }

    const std::string &GrpcModule::sessionId() const
    {
        static const std::string empty;
        return manager_ ? manager_->session_id() : empty;
    }

    void GrpcModule::tryRegister()
    {
        if (shutting_down_.load(std::memory_order_acquire) || registered_.load() || !manager_)
        {
            return;
        }
        if (manager_->Register())
        {
            registered_.store(true);
            consecutive_heartbeat_transport_failures_ = 0;
            if (register_retry_timer_)
            {
                register_retry_timer_->cancel();
            }
            startHeartbeatTimer();
            RCLCPP_INFO(logger_, "gRPC register success. session_id=%s", manager_->session_id().c_str());
            if (on_registered_)
            {
                on_registered_();
            }
        }
        else
        {
            RCLCPP_WARN(logger_, "gRPC register failed, will retry...");
        }
    }

    void GrpcModule::onRegisterRetry()
    {
        if (shutting_down_.load(std::memory_order_acquire))
        {
            return;
        }

        tryRegister();
    }

    void GrpcModule::onHeartbeat()
    {
        if (shutting_down_.load(std::memory_order_acquire) || !manager_ || !registered_.load())
        {
            return;
        }

        const auto heartbeat_result = manager_->Heartbeat();
        if (heartbeat_result == GrpcManager::HeartbeatResult::kOk)
        {
            consecutive_heartbeat_transport_failures_ = 0;
            return;
        }

        if (heartbeat_result == GrpcManager::HeartbeatResult::kTransportError)
        {
            ++consecutive_heartbeat_transport_failures_;
            if (consecutive_heartbeat_transport_failures_ < kMaxTransientHeartbeatFailuresBeforeReregister)
            {
                RCLCPP_WARN(logger_,
                            "gRPC heartbeat transport failure (%u/%u), keeping current session_id=%s",
                            consecutive_heartbeat_transport_failures_,
                            kMaxTransientHeartbeatFailuresBeforeReregister,
                            manager_->session_id().c_str());
                return;
            }

            RCLCPP_WARN(logger_,
                        "gRPC heartbeat transport failure reached limit (%u), will re-register session_id=%s",
                        consecutive_heartbeat_transport_failures_,
                        manager_->session_id().c_str());
        }
        else
        {
            RCLCPP_WARN(logger_, "gRPC heartbeat indicates session is invalid, will re-register session_id=%s",
                        manager_->session_id().c_str());
        }

        consecutive_heartbeat_transport_failures_ = 0;
        registered_.store(false);
        manager_->StopEventStream();
        if (heartbeat_timer_)
        {
            heartbeat_timer_->cancel();
        }
        if (on_heartbeat_fail_)
        {
            on_heartbeat_fail_();
        }
        startRegisterRetryTimer();
    }

    void GrpcModule::startRegisterRetryTimer()
    {
        if (shutting_down_.load(std::memory_order_acquire) || !hasValidContext(node_))
        {
            return;
        }

        if (!register_retry_timer_)
        {
            try
            {
                register_retry_timer_ = node_.create_wall_timer(periodFromSeconds(config_.register_retry_sec), [this]() { onRegisterRetry(); });
            }
            catch (const rclcpp::exceptions::RCLError &ex)
            {
                if (!shutting_down_.load(std::memory_order_acquire))
                {
                    RCLCPP_WARN(logger_, "Skip gRPC register retry timer creation: %s", ex.what());
                }
            }
            return;
        }
        try
        {
            register_retry_timer_->reset();
        }
        catch (const rclcpp::exceptions::RCLError &ex)
        {
            if (!shutting_down_.load(std::memory_order_acquire))
            {
                RCLCPP_WARN(logger_, "Skip gRPC register retry timer reset: %s", ex.what());
            }
        }
    }

    void GrpcModule::startHeartbeatTimer()
    {
        if (shutting_down_.load(std::memory_order_acquire) || !hasValidContext(node_))
        {
            return;
        }

        if (!heartbeat_timer_)
        {
            try
            {
                heartbeat_timer_ = node_.create_wall_timer(heartbeatPeriodFromSeconds(config_.heartbeat_sec), [this]() { onHeartbeat(); });
            }
            catch (const rclcpp::exceptions::RCLError &ex)
            {
                if (!shutting_down_.load(std::memory_order_acquire))
                {
                    RCLCPP_WARN(logger_, "Skip gRPC heartbeat timer creation: %s", ex.what());
                }
            }
            return;
        }
        try
        {
            heartbeat_timer_->reset();
        }
        catch (const rclcpp::exceptions::RCLError &ex)
        {
            if (!shutting_down_.load(std::memory_order_acquire))
            {
                RCLCPP_WARN(logger_, "Skip gRPC heartbeat timer reset: %s", ex.what());
            }
        }
    }

    void GrpcModule::startEventStream()
    {
        if (shutting_down_.load(std::memory_order_acquire) || !manager_)
        {
            return;
        }
        manager_->StartEventStream(
            [this](const signaling::EventMessage &message) {
                if (!shutting_down_.load(std::memory_order_acquire) && on_event_)
                {
                    on_event_(message);
                }
            },
            [this](const ::grpc::Status &status) {
                if (shutting_down_.load(std::memory_order_acquire))
                {
                    return;
                }
                RCLCPP_WARN(logger_, "gRPC EventStream ended unexpectedly: code=%d message=%s",
                            static_cast<int>(status.error_code()), status.error_message().c_str());
                if (on_stream_end_)
                {
                    on_stream_end_();
                }
            });
    }

    bool GrpcModule::requestPair(const std::string &peer_session_id)
    {
        return manager_ && manager_->RequestPair(peer_session_id);
    }

    bool GrpcModule::acceptPair(const std::string &peer_session_id)
    {
        return manager_ && manager_->AcceptPair(peer_session_id);
    }

    bool GrpcModule::rejectPair(const std::string &peer_session_id)
    {
        return manager_ && manager_->RejectPair(peer_session_id);
    }

    bool GrpcModule::unpair(const std::string &peer_session_id)
    {
        return manager_ && manager_->Unpair(peer_session_id);
    }

    bool GrpcModule::subscribe(const std::string &publisher_session_id, bool sub_video, bool sub_pose, bool sub_audio)
    {
        return manager_ && manager_->Subscribe(publisher_session_id, sub_video, sub_pose, sub_audio);
    }

    bool GrpcModule::unsubscribe(const std::string &publisher_session_id)
    {
        return manager_ && manager_->Unsubscribe(publisher_session_id);
    }

    std::vector<signaling::UnpairedEndpoint> GrpcModule::listUnpaired(signaling::RegisterRequest::EndpointType desired_role)
    {
        if (!manager_)
        {
            return {};
        }
        return manager_->ListUnpaired(desired_role);
    }

    bool GrpcModule::publishVideoConfig(uint32_t width,
                                        uint32_t height,
                                        uint32_t fps,
                                        Codec codec,
                                        const std::vector<uint8_t> &sps,
                                        const std::vector<uint8_t> &pps,
                                        const std::vector<uint8_t> &vps,
                                        bool has_fov,
                                        float hfov_deg,
                                        float vfov_deg,
                                        float dfov_deg)
    {
        if (!manager_)
        {
            RCLCPP_WARN(logger_, "gRPC manager not available, cannot send VideoConfig");
            return false;
        }

        const bool is_h265 = (codec == Codec::kH265);
        if (is_h265 && vps.empty())
        {
            RCLCPP_WARN(logger_, "VideoConfig codec=H265 but VPS is empty; aborting publish");
            return false;
        }

        signaling::VideoConfig config;
        config.set_codec(is_h265 ? signaling::VideoConfig::H265 : signaling::VideoConfig::H264);
        config.set_width(static_cast<int32_t>(width));
        config.set_height(static_cast<int32_t>(height));
        config.set_fps(static_cast<int32_t>(fps));
        config.set_sps(sps.data(), sps.size());
        config.set_pps(pps.data(), pps.size());
        if (is_h265)
        {
            config.set_vps(vps.data(), vps.size());
        }
        if (has_fov)
        {
            auto *fov = config.mutable_fov();
            fov->set_hfov(hfov_deg);
            fov->set_vfov(vfov_deg);
            fov->set_dfov(dfov_deg);
        }

        RCLCPP_INFO(logger_, "========== VideoConfig ==========");
        RCLCPP_INFO(logger_, "  codec: %s", is_h265 ? "H265" : "H264");
        RCLCPP_INFO(logger_, "  width: %u", width);
        RCLCPP_INFO(logger_, "  height: %u", height);
        RCLCPP_INFO(logger_, "  fps: %u", fps);
        RCLCPP_INFO(logger_, "  sps_size: %zu bytes", sps.size());
        RCLCPP_INFO(logger_, "  pps_size: %zu bytes", pps.size());
        if (is_h265)
        {
            RCLCPP_INFO(logger_, "  vps_size: %zu bytes", vps.size());
        }
        if (has_fov)
        {
            RCLCPP_INFO(logger_, "  fov: hfov=%.2f vfov=%.2f dfov=%.2f deg", hfov_deg, vfov_deg, dfov_deg);
        }
        else
        {
            RCLCPP_INFO(logger_, "  fov: <not set>");
        }
        RCLCPP_INFO(logger_, "  sps: %s", bytesPreview(sps).c_str());
        RCLCPP_INFO(logger_, "  pps: %s", bytesPreview(pps).c_str());
        if (is_h265)
        {
            RCLCPP_INFO(logger_, "  vps: %s", bytesPreview(vps).c_str());
        }
        RCLCPP_INFO(logger_, "==================================");

        signaling::VideoConfigAck ack;
        if (!manager_->PublishVideoConfig(config, ack))
        {
            RCLCPP_WARN(logger_, "VideoConfig publish failed");
            return false;
        }
        RCLCPP_INFO(logger_, "VideoConfig published successfully");
        return true;
    }

    bool GrpcModule::publishAudioConfig(const AudioConfig &audio_config)
    {
        if (!manager_)
        {
            RCLCPP_WARN(logger_, "gRPC manager not available, cannot send AudioConfig");
            return false;
        }

        signaling::AudioConfig config;
        config.set_codec(signaling::AudioConfig::OPUS);
        config.set_sample_rate(static_cast<int32_t>(audio_config.sample_rate));
        config.set_channels(static_cast<int32_t>(audio_config.channels));
        config.set_frame_duration_ms(static_cast<int32_t>(audio_config.frame_duration_ms));
        config.set_samples_per_channel(static_cast<int32_t>(audio_config.samples_per_channel));
        config.set_bitrate_bps(static_cast<int32_t>(audio_config.bitrate_bps));
        config.set_opus_inband_fec_enabled(audio_config.opus_inband_fec_enabled);
        config.set_opus_dtx_enabled(audio_config.opus_dtx_enabled);

        signaling::AudioConfigAck ack;
        if (!manager_->PublishAudioConfig(config, ack))
        {
            RCLCPP_WARN(logger_, "PublishAudioConfig failed");
            return false;
        }
        RCLCPP_INFO(logger_, "AudioConfig published successfully");
        return true;
    }

    bool GrpcModule::ackAudioConfig(bool success, const std::string &message, const std::string &config_id)
    {
        if (!manager_)
        {
            RCLCPP_WARN(logger_, "gRPC manager not available, cannot ACK AudioConfig");
            return false;
        }

        signaling::AudioConfigAck ack;
        ack.set_success(success);
        ack.set_message(message);
        ack.set_config_id(config_id);
        if (!manager_->AckAudioConfig(ack))
        {
            RCLCPP_WARN(logger_, "AckAudioConfig failed");
            return false;
        }
        RCLCPP_INFO(logger_, "AudioConfig ACK sent: success=%d config_id=%s", success ? 1 : 0, config_id.c_str());
        return true;
    }

} // namespace trb