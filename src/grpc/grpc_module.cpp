#include "grpc/grpc_module.hpp"

#include <algorithm>
#include <cstdio>

#include "signaling.pb.h"

GrpcModule::Config GrpcModule::configFromRosParam(ros::NodeHandle& nh) {
  Config cfg;
  nh.param<std::string>("grpc/server_grpc_ip", cfg.server_grpc_ip, "");
  nh.param<int>("grpc/server_grpc_port", cfg.server_grpc_port, 0);
  nh.param<bool>("grpc/use_ssl", cfg.use_ssl, false);
  nh.param<std::string>("grpc/device_id", cfg.device_id, "");
  nh.param<int>("grpc/robot_generation", cfg.robot_generation, 1);
  nh.param<std::string>("grpc/token", cfg.token, "");
  nh.param<int>("grpc/rpc_timeout_ms", cfg.rpc_timeout_ms, 5000);
  nh.param<double>("grpc/register_retry_sec", cfg.register_retry_sec, 3.0);
  nh.param<double>("grpc/heartbeat_sec", cfg.heartbeat_sec, 15.0);
  return cfg;
}

GrpcModule::GrpcModule(ros::NodeHandle& nh, const Config& config)
    : nh_(nh), config_(config) {
  manager_ = std::make_unique<GrpcManager>(config_);
}

GrpcModule::~GrpcModule() {
  stop();
  manager_.reset();
}

void GrpcModule::start() {
  tryRegister();
  if (!registered_.load() && !register_retry_timer_.hasStarted()) {
    register_retry_timer_ = nh_.createTimer(
        ros::Duration(config_.register_retry_sec),
        &GrpcModule::onRegisterRetry,
        this);
    ROS_WARN("gRPC register failed, entering pending state. Will retry every %.1f seconds.",
             config_.register_retry_sec);
  }
}

void GrpcModule::stop() {
  // Cancel any in-flight RPC first so timer callbacks currently mid-RPC
  // return immediately; otherwise ros::Timer::stop() would block on the
  // running callback for up to rpc_timeout_ms (~5s).
  if (manager_) {
    manager_->CancelPendingRpcs();
  }
  if (register_retry_timer_.hasStarted()) {
    register_retry_timer_.stop();
  }
  if (heartbeat_timer_.hasStarted()) {
    heartbeat_timer_.stop();
  }
  if (manager_) {
    manager_->StopEventStream();
  }
}

const std::string& GrpcModule::sessionId() const {
  static const std::string empty;
  return manager_ ? manager_->session_id() : empty;
}

void GrpcModule::tryRegister() {
  if (registered_.load() || !manager_) {
    return;
  }
  if (manager_->Register()) {
    registered_.store(true);
    if (register_retry_timer_.hasStarted()) {
      register_retry_timer_.stop();
    }
    if (!heartbeat_timer_.hasStarted()) {
      heartbeat_timer_ = nh_.createTimer(
          ros::Duration(config_.heartbeat_sec),
          &GrpcModule::onHeartbeat,
          this);
    }
    ROS_INFO_STREAM("gRPC register success. session_id=" << manager_->session_id());
    if (on_registered_) {
      on_registered_();
    }
  } else {
    ROS_WARN("gRPC register failed, will retry...");
  }
}

void GrpcModule::onRegisterRetry(const ros::TimerEvent& /*event*/) {
  tryRegister();
}

void GrpcModule::onHeartbeat(const ros::TimerEvent& /*event*/) {
  if (!manager_ || !registered_.load()) {
    return;
  }
  if (manager_->Heartbeat()) {
    return;
  }
  ROS_WARN("gRPC heartbeat failed, will re-register");
  registered_.store(false);
  manager_->StopEventStream();
  if (heartbeat_timer_.hasStarted()) {
    heartbeat_timer_.stop();
  }
  if (on_heartbeat_fail_) {
    on_heartbeat_fail_();
  }
  if (!register_retry_timer_.hasStarted()) {
    register_retry_timer_ = nh_.createTimer(
        ros::Duration(config_.register_retry_sec),
        &GrpcModule::onRegisterRetry,
        this);
  }
}

void GrpcModule::startEventStream() {
  if (!manager_) return;
  manager_->StartEventStream(
      [this](const signaling::EventMessage& msg) {
        if (on_event_) on_event_(msg);
      },
      [this](const grpc::Status& status) {
        ROS_WARN("gRPC EventStream ended unexpectedly: code=%d message=%s",
                 static_cast<int>(status.error_code()),
                 status.error_message().c_str());
        if (on_stream_end_) on_stream_end_();
      });
}

bool GrpcModule::acceptPair(const std::string& peer_session_id) {
  if (!manager_) return false;
  return manager_->AcceptPair(peer_session_id);
}

bool GrpcModule::publishVideoConfig(uint32_t width, uint32_t height, uint32_t fps,
                                    Codec codec,
                                    const std::vector<uint8_t>& sps,
                                    const std::vector<uint8_t>& pps,
                                    const std::vector<uint8_t>& vps,
                                    bool has_fov, float hfov_deg,
                                    float vfov_deg, float dfov_deg) {
  if (!manager_) {
    ROS_WARN("gRPC manager not available, cannot send VideoConfig");
    return false;
  }

  const bool is_h265 = (codec == Codec::kH265);
  if (is_h265 && vps.empty()) {
    ROS_WARN("VideoConfig codec=H265 but VPS is empty; aborting publish");
    return false;
  }

  signaling::VideoConfig config;
  config.set_codec(is_h265 ? signaling::VideoConfig::H265
                           : signaling::VideoConfig::H264);
  config.set_width(static_cast<int32_t>(width));
  config.set_height(static_cast<int32_t>(height));
  config.set_fps(static_cast<int32_t>(fps));
  config.set_sps(sps.data(), sps.size());
  config.set_pps(pps.data(), pps.size());
  if (is_h265) {
    config.set_vps(vps.data(), vps.size());
  }
  if (has_fov) {
    auto* fov = config.mutable_fov();
    fov->set_hfov(hfov_deg);
    fov->set_vfov(vfov_deg);
    fov->set_dfov(dfov_deg);
  }

  ROS_INFO("========== VideoConfig ==========");
  ROS_INFO("  codec: %s", is_h265 ? "H265" : "H264");
  ROS_INFO("  width: %u", width);
  ROS_INFO("  height: %u", height);
  ROS_INFO("  fps: %u", fps);
  ROS_INFO("  sps_size: %zu bytes", sps.size());
  ROS_INFO("  pps_size: %zu bytes", pps.size());
  if (is_h265) {
    ROS_INFO("  vps_size: %zu bytes", vps.size());
  }
  if (has_fov) {
    ROS_INFO("  fov: hfov=%.2f vfov=%.2f dfov=%.2f deg",
             hfov_deg, vfov_deg, dfov_deg);
  } else {
    ROS_INFO("  fov: <not set>");
  }

  std::string sps_hex;
  for (size_t i = 0; i < std::min(sps.size(), size_t(32)); ++i) {
    char buf[4];
    snprintf(buf, sizeof(buf), "%02X ", sps[i]);
    sps_hex += buf;
  }
  if (sps.size() > 32) sps_hex += "...";
  ROS_INFO("  sps: %s", sps_hex.c_str());

  std::string pps_hex;
  for (size_t i = 0; i < std::min(pps.size(), size_t(32)); ++i) {
    char buf[4];
    snprintf(buf, sizeof(buf), "%02X ", pps[i]);
    pps_hex += buf;
  }
  if (pps.size() > 32) pps_hex += "...";
  ROS_INFO("  pps: %s", pps_hex.c_str());

  if (is_h265) {
    std::string vps_hex;
    for (size_t i = 0; i < std::min(vps.size(), size_t(32)); ++i) {
      char buf[4];
      snprintf(buf, sizeof(buf), "%02X ", vps[i]);
      vps_hex += buf;
    }
    if (vps.size() > 32) vps_hex += "...";
    ROS_INFO("  vps: %s", vps_hex.c_str());
  }
  ROS_INFO("==================================");

  signaling::VideoConfigAck ack;
  if (!manager_->PublishVideoConfig(config, ack)) {
    ROS_WARN("VideoConfig publish failed");
    return false;
  }
  ROS_INFO("VideoConfig published successfully");
  return true;
}

bool GrpcModule::publishAudioConfig(const trb::audio::AudioManager::Config& cfg) {
  if (!manager_) return false;
  signaling::AudioConfig config;
  config.set_codec(signaling::AudioConfig::OPUS);
  config.set_sample_rate(static_cast<int32_t>(cfg.sample_rate));
  config.set_channels(static_cast<int32_t>(cfg.channels));
  config.set_frame_duration_ms(static_cast<int32_t>(cfg.frame_duration_ms));
  config.set_samples_per_channel(static_cast<int32_t>(cfg.samples_per_channel));
  config.set_bitrate_bps(static_cast<int32_t>(cfg.bitrate_bps));
  config.set_opus_inband_fec_enabled(cfg.opus_inband_fec_enabled);
  config.set_opus_dtx_enabled(cfg.opus_dtx_enabled);

  signaling::AudioConfigAck ack;
  if (!manager_->PublishAudioConfig(config, ack)) {
    ROS_WARN("PublishAudioConfig failed");
    return false;
  }
  ROS_INFO("AudioConfig published successfully");
  return true;
}
