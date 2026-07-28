#include "grpc/grpc_manager.hpp"

#include <chrono>

#include <grpc/grpc.h>
#include <ros/ros.h>

GrpcManager::GrpcManager(const GrpcConfig &config)
    : config_(config) {
  auto channel = CreateChannel();
  stub_ = signaling::Signaling::NewStub(channel);
}

GrpcManager::~GrpcManager() {
  CancelPendingRpcs();
  StopEventStream();
}

GrpcManager::RpcScope::RpcScope(GrpcManager &mgr, grpc::ClientContext &ctx)
    : mgr_(mgr), ctx_(ctx) {
  if (mgr_.shutting_down_.load()) {
    shutting_down_ = true;
    return;
  }
  std::lock_guard<std::mutex> lk(mgr_.pending_rpc_mu_);
  mgr_.pending_rpc_ctxs_.insert(&ctx_);
}

GrpcManager::RpcScope::~RpcScope() {
  if (shutting_down_) return;
  std::lock_guard<std::mutex> lk(mgr_.pending_rpc_mu_);
  mgr_.pending_rpc_ctxs_.erase(&ctx_);
}

void GrpcManager::CancelPendingRpcs() {
  shutting_down_.store(true);
  {
    std::lock_guard<std::mutex> lk(pending_rpc_mu_);
    for (grpc::ClientContext *ctx : pending_rpc_ctxs_) {
      if (ctx) ctx->TryCancel();
    }
  }
  // Also kick the long-lived event stream so its blocking Read returns.
  if (stream_context_) {
    stream_context_->TryCancel();
  }
}

std::shared_ptr<grpc::Channel> GrpcManager::CreateChannel() const {
  std::string target = BuildTarget();
  grpc::ChannelArguments args;
  args.SetInt(GRPC_ARG_ENABLE_HTTP_PROXY, 0);
  if (config_.use_ssl) {
    grpc::SslCredentialsOptions ssl_opts;
    return grpc::CreateCustomChannel(target, grpc::SslCredentials(ssl_opts), args);
  }
  return grpc::CreateCustomChannel(target, grpc::InsecureChannelCredentials(), args);
}

std::string GrpcManager::BuildTarget() const {
  return config_.server_grpc_ip + ":" + std::to_string(config_.server_grpc_port);
}

void GrpcManager::ApplyDeadline(grpc::ClientContext &context) const {
  const int timeout_ms = std::max(1, config_.rpc_timeout_ms);
  context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(timeout_ms));
}

bool GrpcManager::Register() {
  if (!stub_ || shutting_down_.load()) {
    return false;
  }

  signaling::RegisterRequest request;
  request.set_token(config_.token);
  request.set_role(signaling::RegisterRequest::ROBOT);
  request.set_device_id(config_.device_id);
  request.set_robot_generation(config_.robot_generation);

  signaling::RegisterResponse response;
  grpc::ClientContext context;
  ApplyDeadline(context);
  RpcScope scope(*this, context);
  if (scope.shuttingDown()) return false;
  ROS_INFO("Attempting gRPC Register to %s with timeout=%d ms",
           BuildTarget().c_str(), config_.rpc_timeout_ms);
  grpc::Status status = stub_->Register(&context, request, &response);

  if (!status.ok()) {
    ROS_WARN("gRPC Register RPC failed: code=%d message=%s",
             static_cast<int>(status.error_code()), status.error_message().c_str());
    return false;
  }

  if (!response.success()) {
    ROS_WARN("gRPC Register rejected by server");
    return false;
  }

  session_id_ = response.session_id();
  return true;
}

const std::string &GrpcManager::session_id() const {
  return session_id_;
}

bool GrpcManager::AcceptPair(const std::string &peer_session_id) {
  if (!stub_ || session_id_.empty() || shutting_down_.load()) {
    return false;
  }

  signaling::PairRequest request;
  request.set_op(signaling::PairRequest::PAIR);
  request.set_peer_session_id(peer_session_id);
  request.set_state(signaling::PairRequest::ACCEPT);

  signaling::PairResponse response;
  grpc::ClientContext context;
  ApplyDeadline(context);
  context.AddMetadata("session-id", session_id_);
  RpcScope scope(*this, context);
  if (scope.shuttingDown()) return false;
  grpc::Status status = stub_->Pair(&context, request, &response);

  if (!status.ok()) {
    ROS_WARN("gRPC Pair RPC failed: code=%d message=%s",
             static_cast<int>(status.error_code()), status.error_message().c_str());
    return false;
  }

  return response.success();
}

bool GrpcManager::PublishVideoConfig(const signaling::VideoConfig &config, signaling::VideoConfigAck &ack) {
  if (!stub_ || session_id_.empty() || shutting_down_.load()) {
    return false;
  }

  grpc::ClientContext context;
  ApplyDeadline(context);
  context.AddMetadata("session-id", session_id_);
  RpcScope scope(*this, context);
  if (scope.shuttingDown()) return false;
  grpc::Status status = stub_->PublishVideoConfig(&context, config, &ack);
  if (!status.ok()) {
    ROS_WARN("gRPC PublishVideoConfig failed: code=%d message=%s",
             static_cast<int>(status.error_code()), status.error_message().c_str());
    return false;
  }

  return ack.success();
}

bool GrpcManager::PublishAudioConfig(const signaling::AudioConfig &config, signaling::AudioConfigAck &ack) {
  if (!stub_ || session_id_.empty() || shutting_down_.load()) {
    return false;
  }

  grpc::ClientContext context;
  ApplyDeadline(context);
  context.AddMetadata("session-id", session_id_);
  RpcScope scope(*this, context);
  if (scope.shuttingDown()) return false;
  grpc::Status status = stub_->PublishAudioConfig(&context, config, &ack);
  if (!status.ok()) {
    ROS_WARN("gRPC PublishAudioConfig failed: code=%d message=%s",
             static_cast<int>(status.error_code()), status.error_message().c_str());
    return false;
  }

  return ack.success();
}

bool GrpcManager::Heartbeat() {
  if (!stub_ || session_id_.empty() || shutting_down_.load()) {
    return false;
  }

  signaling::Heartbeat request;
  request.set_client_time(static_cast<int64_t>(ros::Time::now().toNSec() / 1000000));

  signaling::HeartbeatAck response;
  grpc::ClientContext context;
  ApplyDeadline(context);
  context.AddMetadata("session-id", session_id_);
  RpcScope scope(*this, context);
  if (scope.shuttingDown()) return false;
  grpc::Status status = stub_->Ping(&context, request, &response);
  if (!status.ok()) {
    ROS_WARN("gRPC Ping failed: code=%d message=%s",
             static_cast<int>(status.error_code()), status.error_message().c_str());
    return false;
  }
  return true;
}

void GrpcManager::StartEventStream(const EventCallback &callback,
                                   const StreamEndCallback &on_end) {
  if (stream_running_.exchange(true)) {
    return;
  }

  // Defensive: a previous stream thread may have exited on its own (e.g.
  // server closed the socket) without StopEventStream() being called. In
  // that case stream_thread_ is still joinable but no longer running; we
  // must join it before move-assigning a fresh std::thread below, otherwise
  // the move-assign would invoke std::terminate.
  if (stream_thread_.joinable() &&
      stream_thread_.get_id() != std::this_thread::get_id()) {
    stream_thread_.join();
  }

  stream_callback_ = callback;
  stream_end_callback_ = on_end;
  stream_context_ = std::make_shared<grpc::ClientContext>();
  if (!session_id_.empty()) {
    stream_context_->AddMetadata("session-id", session_id_);
  }

  stream_thread_ = std::thread([this]() {
    signaling::EventSubscribe request;
    request.set_session_id(session_id_);

    std::unique_ptr<grpc::ClientReader<signaling::EventMessage>> reader(
        stub_->EventStream(stream_context_.get(), request));

    signaling::EventMessage msg;
    while (stream_running_.load() && reader->Read(&msg)) {
      if (stream_callback_) {
        stream_callback_(msg);
      }
    }

    const grpc::Status status = reader->Finish();
    // If the stream ended while we were still expecting events (i.e. the
    // server or network dropped us), surface that to the caller exactly
    // once. Subsequent StopEventStream() will become a no-op.
    const bool unexpected = stream_running_.exchange(false);
    if (unexpected && stream_end_callback_) {
      stream_end_callback_(status);
    }
  });
}

void GrpcManager::StopEventStream() {
  if (!stream_running_.exchange(false)) {
    // Still join an already-finished worker thread to avoid leaks.
    if (stream_thread_.joinable()) {
      stream_thread_.join();
    }
    stream_context_.reset();
    stream_callback_ = nullptr;
    stream_end_callback_ = nullptr;
    return;
  }

  if (stream_context_) {
    stream_context_->TryCancel();
  }

  if (stream_thread_.joinable()) {
    stream_thread_.join();
  }

  stream_context_.reset();
  stream_callback_ = nullptr;
  stream_end_callback_ = nullptr;
}
