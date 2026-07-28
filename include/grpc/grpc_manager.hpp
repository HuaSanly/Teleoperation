#ifndef TELEOP_ROBOT_BRIDGE_GRPC_MANAGER_HPP_
#define TELEOP_ROBOT_BRIDGE_GRPC_MANAGER_HPP_

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_set>

#include <grpcpp/grpcpp.h>

#include "signaling.grpc.pb.h"

struct GrpcConfig {
  std::string server_grpc_ip;
  int server_grpc_port = 0;
  bool use_ssl = false;
  std::string device_id;
  int robot_generation = 1;
  std::string token;
  int rpc_timeout_ms = 5000;
  double register_retry_sec = 3.0;
  double heartbeat_sec = 15.0;
};

class GrpcManager {
 public:
  explicit GrpcManager(const GrpcConfig &config);
  ~GrpcManager();

  bool Register();
  const std::string &session_id() const;

  bool AcceptPair(const std::string &peer_session_id);
  bool PublishVideoConfig(const signaling::VideoConfig &config, signaling::VideoConfigAck &ack);
  bool PublishAudioConfig(const signaling::AudioConfig &config, signaling::AudioConfigAck &ack);
  bool Heartbeat();
  using EventCallback = std::function<void(const signaling::EventMessage &)>;
  using StreamEndCallback = std::function<void(const grpc::Status &)>;
  void StartEventStream(const EventCallback &callback,
                        const StreamEndCallback &on_end = {});
  void StopEventStream();

  // Cancel any in-flight unary RPC (Register / Heartbeat / AcceptPair /
  // PublishVideoConfig / PublishAudioConfig) and mark the manager as shutting
  // down so subsequent RPCs return false immediately. Idempotent. Intended
  // for fast Ctrl+C tear-down.
  void CancelPendingRpcs();

 private:
  std::shared_ptr<grpc::Channel> CreateChannel() const;
  std::string BuildTarget() const;
    void ApplyDeadline(grpc::ClientContext &context) const;

  // RAII helper that publishes a ClientContext so CancelPendingRpcs() can
  // TryCancel it, and removes it on scope exit.
  class RpcScope {
   public:
    RpcScope(GrpcManager &mgr, grpc::ClientContext &ctx);
    ~RpcScope();
    RpcScope(const RpcScope &) = delete;
    RpcScope &operator=(const RpcScope &) = delete;
    bool shuttingDown() const { return shutting_down_; }

   private:
    GrpcManager &mgr_;
    grpc::ClientContext &ctx_;
    bool shutting_down_{false};
  };

  GrpcConfig config_;
  std::unique_ptr<signaling::Signaling::Stub> stub_;
  std::string session_id_;

  // Shutdown + pending-RPC tracking for fast Ctrl+C exit.
  std::atomic<bool> shutting_down_{false};
  std::mutex pending_rpc_mu_;
  std::unordered_set<grpc::ClientContext *> pending_rpc_ctxs_;

  std::atomic<bool> stream_running_{false};
  std::shared_ptr<grpc::ClientContext> stream_context_;
  std::thread stream_thread_;
  EventCallback stream_callback_;
  StreamEndCallback stream_end_callback_;
};

#endif  // TELEOP_ROBOT_BRIDGE_GRPC_MANAGER_HPP_
