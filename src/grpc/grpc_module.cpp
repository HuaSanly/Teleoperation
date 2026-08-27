#include "grpc/grpc_module.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <limits>
#include <sstream>
#include <utility>

#include <google/protobuf/struct.pb.h>
#include <google/protobuf/util/json_util.h>
#include <openssl/evp.h>

namespace trb
{
    namespace
    {
        constexpr uint32_t kMaxTransientHeartbeatFailuresBeforeReregister = 3;
        constexpr uint8_t kVideoPrefix = 0x01;
        constexpr uint8_t kAudioPrefix = 0x04;
        constexpr uint8_t kLowRateTelemetryPrefix = 0x05;
        constexpr uint8_t kHighRateTelemetryPrefix = 0x06;
        constexpr uint32_t kMediaConfigSchemaVersion = 1;

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

        std::string base64Encode(const std::vector<uint8_t> &bytes)
        {
            if (bytes.empty())
            {
                return {};
            }
            const size_t encoded_size = 4 * ((bytes.size() + 2) / 3);
            std::string encoded(encoded_size + 1, '\0');
            const int written = EVP_EncodeBlock(
                reinterpret_cast<unsigned char *>(encoded.data()),
                bytes.data(),
                static_cast<int>(bytes.size()));
            if (written <= 0)
            {
                return {};
            }
            encoded.resize(static_cast<size_t>(written));
            return encoded;
        }

        bool serializeJson(const google::protobuf::Struct &document, std::string &payload)
        {
            google::protobuf::util::JsonPrintOptions options;
            options.add_whitespace = false;
            options.preserve_proto_field_names = true;
            return google::protobuf::util::MessageToJsonString(document, &payload, options).ok();
        }

        const google::protobuf::Value *findJsonField(const google::protobuf::Struct &document,
                                                      const char *name)
        {
            const auto iterator = document.fields().find(name);
            return iterator == document.fields().end() ? nullptr : &iterator->second;
        }

        bool readJsonString(const google::protobuf::Struct &document,
                            const char *name,
                            std::string &value)
        {
            const auto *field = findJsonField(document, name);
            if (!field || field->kind_case() != google::protobuf::Value::kStringValue)
            {
                return false;
            }
            value = field->string_value();
            return true;
        }

        bool readJsonUint32(const google::protobuf::Struct &document,
                            const char *name,
                            uint32_t &value)
        {
            const auto *field = findJsonField(document, name);
            if (!field || field->kind_case() != google::protobuf::Value::kNumberValue)
            {
                return false;
            }
            const double number = field->number_value();
            if (!std::isfinite(number) || number <= 0.0 ||
                number > static_cast<double>(std::numeric_limits<uint32_t>::max()) ||
                std::floor(number) != number)
            {
                return false;
            }
            value = static_cast<uint32_t>(number);
            return true;
        }

        bool readJsonBool(const google::protobuf::Struct &document,
                          const char *name,
                          bool &value)
        {
            const auto *field = findJsonField(document, name);
            if (!field || field->kind_case() != google::protobuf::Value::kBoolValue)
            {
                return false;
            }
            value = field->bool_value();
            return true;
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
        config.enabled = declareOrGet<bool>(node, "grpc.enabled", true);
        config.server_grpc_ip = declareOrGet<std::string>(node, "grpc.server_grpc_ip", "");
        config.server_grpc_port = declareOrGet<int>(node, "grpc.server_grpc_port", 0);
        config.use_ssl = declareOrGet<bool>(node, "grpc.use_ssl", false);
        config.device_id = declareOrGet<std::string>(node, "grpc.device_id", "");
        config.firmware_version = declareOrGet<std::string>(node, "grpc.runtime.firmware_version", "");
        config.software_version = declareOrGet<std::string>(node, "grpc.runtime.software_version", "teleop_robot_bridge");
        config.operating_system = declareOrGet<std::string>(node, "grpc.runtime.operating_system", "Linux");
        config.operating_system_version = declareOrGet<std::string>(node, "grpc.runtime.operating_system_version", "");
        config.runtime_version = declareOrGet<std::string>(node, "grpc.runtime.runtime_version", "ROS 2");
        config.build_id = declareOrGet<std::string>(node, "grpc.runtime.build_id", "");
        config.capabilities = declareOrGet<std::vector<std::string>>(
            node, "grpc.runtime.capabilities", std::vector<std::string>{"publisher_streams"});
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
        if (!config_.enabled)
        {
            registered_.store(false);
            RCLCPP_INFO(logger_, "gRPC signaling is disabled by grpc.enabled");
            return;
        }
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

    std::string GrpcModule::sessionId() const
    {
        return manager_ ? manager_->session_id() : std::string{};
    }

    std::string GrpcModule::deviceTypeCode() const
    {
        return manager_ ? manager_->device_type_code() : std::string{};
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

    bool GrpcModule::subscribe(const std::string &publisher_session_id, const std::vector<uint8_t> &prefixes)
    {
        return manager_ && manager_->Subscribe(publisher_session_id, prefixes);
    }

    bool GrpcModule::unsubscribe(const std::string &publisher_session_id)
    {
        return manager_ && manager_->Unsubscribe(publisher_session_id);
    }

    std::vector<signaling::UnpairedEndpoint> GrpcModule::listUnpaired(const std::string &desired_device_type_code)
    {
        if (!manager_)
        {
            return {};
        }
        return manager_->ListUnpaired(desired_device_type_code);
    }

    bool GrpcModule::getStreamPrefixes(const std::string &publisher_session_id, std::vector<uint8_t> &prefixes)
    {
        prefixes.clear();
        if (!manager_)
        {
            return false;
        }

        signaling::GetStreamManifestResponse response;
        if (!manager_->GetStreamManifest(publisher_session_id, response))
        {
            return false;
        }

        prefixes.reserve(static_cast<size_t>(response.items_size()));
        for (const auto &item : response.items())
        {
            if (item.prefix() <= 0xFFu)
            {
                prefixes.push_back(static_cast<uint8_t>(item.prefix()));
            }
        }
        std::sort(prefixes.begin(), prefixes.end());
        prefixes.erase(std::unique(prefixes.begin(), prefixes.end()), prefixes.end());
        return true;
    }

    bool GrpcModule::publishRobotStreamManifest(bool audio_enabled,
                                                bool low_rate_telemetry_enabled,
                                                bool high_rate_telemetry_enabled)
    {
        if (!manager_)
        {
            return false;
        }

        signaling::PublishStreamManifestRequest request;
        auto add_stream = [&request](uint8_t prefix,
                                     const char *stream_code,
                                     const char *display_name,
                                     const char *description,
                                     const char *class_code,
                                     const char *protocol_code) {
            auto *stream = request.add_streams();
            stream->set_prefix(prefix);
            stream->set_stream_code(stream_code);
            stream->set_display_name(display_name);
            stream->set_description(description);
            stream->set_stream_class_code(class_code);
            stream->set_protocol_code(protocol_code);
        };

        add_stream(kVideoPrefix, "video", "Robot Video", "Encoded robot camera video", "video", "video");
        if (audio_enabled)
        {
            add_stream(kAudioPrefix, "audio_opus", "Robot Audio", "Opus robot audio", "audio", "audio_opus");
        }
        if (low_rate_telemetry_enabled)
        {
            add_stream(kLowRateTelemetryPrefix,
                       "robot_telemetry_low_rate",
                       "Robot Telemetry",
                       "Low-rate robot state snapshot",
                       "telemetry",
                       "robot_telemetry_low_rate");
        }
        if (high_rate_telemetry_enabled)
        {
            add_stream(kHighRateTelemetryPrefix,
                       "robot_joint_telemetry_high_rate",
                       "Robot Joint Telemetry",
                       "High-rate robot joint state",
                       "telemetry",
                       "robot_joint_telemetry_high_rate");
        }

        if (!manager_->PublishStreamManifest(request))
        {
            return false;
        }
        RCLCPP_INFO(logger_, "Published robot stream manifest with %d stream(s)", request.streams_size());
        return true;
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

        google::protobuf::Struct document;
        auto *fields = document.mutable_fields();
        (*fields)["codec"].set_string_value(is_h265 ? "H265" : "H264");
        (*fields)["width"].set_number_value(width);
        (*fields)["height"].set_number_value(height);
        (*fields)["fps"].set_number_value(fps);
        (*fields)["sps"].set_string_value(base64Encode(sps));
        (*fields)["pps"].set_string_value(base64Encode(pps));
        (*fields)["vps"].set_string_value(base64Encode(vps));
        if (has_fov)
        {
            auto *fov = (*fields)["fov"].mutable_struct_value()->mutable_fields();
            (*fov)["hfov"].set_number_value(hfov_deg);
            (*fov)["vfov"].set_number_value(vfov_deg);
            (*fov)["dfov"].set_number_value(dfov_deg);
        }

        std::string payload;
        if (!serializeJson(document, payload))
        {
            RCLCPP_WARN(logger_, "Failed to serialize video StreamConfig JSON");
            return false;
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

        if (!manager_->PublishStreamConfig(kVideoPrefix,
                                           kMediaConfigSchemaVersion,
                                           payload))
        {
            RCLCPP_WARN(logger_, "Video StreamConfig publish failed");
            return false;
        }
        RCLCPP_INFO(logger_, "Video StreamConfig published successfully");
        return true;
    }

    bool GrpcModule::publishAudioConfig(const AudioConfig &audio_config)
    {
        if (!manager_)
        {
            RCLCPP_WARN(logger_, "gRPC manager not available, cannot send AudioConfig");
            return false;
        }

        google::protobuf::Struct document;
        auto *fields = document.mutable_fields();
        (*fields)["codec"].set_string_value("OPUS");
        (*fields)["sample_rate"].set_number_value(audio_config.sample_rate);
        (*fields)["channels"].set_number_value(audio_config.channels);
        (*fields)["frame_duration_ms"].set_number_value(audio_config.frame_duration_ms);
        (*fields)["samples_per_channel"].set_number_value(audio_config.samples_per_channel);
        (*fields)["bitrate_bps"].set_number_value(audio_config.bitrate_bps);
        (*fields)["opus_inband_fec_enabled"].set_bool_value(audio_config.opus_inband_fec_enabled);
        (*fields)["opus_dtx_enabled"].set_bool_value(audio_config.opus_dtx_enabled);

        std::string payload;
        if (!serializeJson(document, payload))
        {
            RCLCPP_WARN(logger_, "Failed to serialize audio StreamConfig JSON");
            return false;
        }

        if (!manager_->PublishStreamConfig(kAudioPrefix,
                                           kMediaConfigSchemaVersion,
                                           payload))
        {
            RCLCPP_WARN(logger_, "Publish audio StreamConfig failed");
            return false;
        }
        RCLCPP_INFO(logger_, "Audio StreamConfig published successfully");
        return true;
    }

    bool GrpcModule::fetchAudioConfig(const std::string &publisher_session_id,
                                      AudioConfig &audio_config,
                                      std::string &config_id)
    {
        if (!manager_)
        {
            return false;
        }

        signaling::StreamConfigItem item;
        if (!manager_->GetStreamConfig(publisher_session_id, kAudioPrefix, item))
        {
            return false;
        }

        if (item.prefix() != kAudioPrefix ||
            item.schema_version() != kMediaConfigSchemaVersion)
        {
            RCLCPP_WARN(logger_,
                        "Unsupported remote audio StreamConfig: prefix=0x%02X schema=%u",
                        item.prefix(),
                        item.schema_version());
            return false;
        }

        google::protobuf::Struct document;
        if (!google::protobuf::util::JsonStringToMessage(item.payload(), &document).ok())
        {
            RCLCPP_WARN(logger_, "Remote audio StreamConfig contains invalid JSON");
            return false;
        }

        std::string codec;
        if (!readJsonString(document, "codec", codec) || codec != "OPUS" ||
            !readJsonUint32(document, "sample_rate", audio_config.sample_rate) ||
            !readJsonUint32(document, "channels", audio_config.channels) ||
            !readJsonUint32(document, "frame_duration_ms", audio_config.frame_duration_ms) ||
            !readJsonUint32(document, "samples_per_channel", audio_config.samples_per_channel) ||
            !readJsonUint32(document, "bitrate_bps", audio_config.bitrate_bps) ||
            !readJsonBool(document, "opus_inband_fec_enabled", audio_config.opus_inband_fec_enabled) ||
            !readJsonBool(document, "opus_dtx_enabled", audio_config.opus_dtx_enabled))
        {
            RCLCPP_WARN(logger_, "Remote audio StreamConfig JSON does not match schema version 1");
            return false;
        }

        config_id = item.config_id();
        return true;
    }

} // namespace trb
