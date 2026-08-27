#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#include <grpcpp/grpcpp.h>
#include "rclcpp/rclcpp.hpp"

#include "signaling.grpc.pb.h"

namespace trb
{

    struct GrpcConfig
    {
        bool enabled{true};
        std::string server_grpc_ip;
        int server_grpc_port{0};
        bool use_ssl{false};
        std::string device_id;
        std::string firmware_version;
        std::string software_version;
        std::string operating_system;
        std::string operating_system_version;
        std::string runtime_version;
        std::string build_id;
        std::vector<std::string> capabilities;
        int rpc_timeout_ms{5000};
        double register_retry_sec{3.0};
        double heartbeat_sec{15.0};
    };

    class GrpcManager
    {
    public:
        enum class HeartbeatResult
        {
            kOk,
            kSessionInvalid,
            kTransportError,
        };

        using EventCallback = std::function<void(const signaling::EventMessage &)>;
        using StreamEndCallback = std::function<void(const ::grpc::Status &)>;

        explicit GrpcManager(const GrpcConfig &config,
                             rclcpp::Logger logger = rclcpp::get_logger("teleop_robot_bridge.grpc"));
        ~GrpcManager();

        GrpcManager(const GrpcManager &) = delete;
        GrpcManager &operator=(const GrpcManager &) = delete;

        bool Register();
        std::string session_id() const;
        std::string device_type_code() const;

        bool RequestPair(const std::string &peer_session_id);
        bool AcceptPair(const std::string &peer_session_id);
        bool RejectPair(const std::string &peer_session_id);
        bool Unpair(const std::string &peer_session_id);

        bool Subscribe(const std::string &publisher_session_id,
                       const std::vector<uint8_t> &prefixes);
        bool Unsubscribe(const std::string &publisher_session_id);
        std::vector<signaling::UnpairedEndpoint> ListUnpaired(const std::string &desired_device_type_code);

        bool PublishStreamManifest(const signaling::PublishStreamManifestRequest &request);
        bool GetStreamManifest(const std::string &publisher_session_id,
                               signaling::GetStreamManifestResponse &response);
        bool PublishStreamConfig(uint8_t prefix,
                                 uint32_t schema_version,
                                 const std::string &payload,
                                 signaling::StreamConfigItem *published_item = nullptr);
        bool GetStreamConfig(const std::string &publisher_session_id,
                             uint8_t prefix,
                             signaling::StreamConfigItem &item);
        bool GetP2pInfo(signaling::GetP2pInfoResponse &response);
        HeartbeatResult Heartbeat();

        void StartEventStream(const EventCallback &callback,
                              const StreamEndCallback &on_end = {});
        void StopEventStream();

        void CancelPendingRpcs();

    private:
        std::shared_ptr<::grpc::Channel> CreateChannel() const;
        std::string BuildTarget() const;
        void ApplyDeadline(::grpc::ClientContext &context) const;

        class RpcScope
        {
        public:
            RpcScope(GrpcManager &manager, ::grpc::ClientContext &context);
            ~RpcScope();
            RpcScope(const RpcScope &) = delete;
            RpcScope &operator=(const RpcScope &) = delete;
            bool shuttingDown() const { return shutting_down_; }

        private:
            GrpcManager &manager_;
            ::grpc::ClientContext &context_;
            bool shutting_down_{false};
        };

        bool Pair(signaling::PairRequest::Operation operation,
                  const std::string &peer_session_id,
                  signaling::PairRequest::PairState state);

        GrpcConfig config_;
        rclcpp::Logger logger_;
        std::unique_ptr<signaling::Signaling::Stub> stub_;
        mutable std::mutex session_mutex_;
        std::string session_id_;
        std::string device_type_code_;

        std::atomic<bool> shutting_down_{false};
        std::mutex pending_rpc_mutex_;
        std::unordered_set<::grpc::ClientContext *> pending_rpc_contexts_;

        std::atomic<bool> stream_running_{false};
        std::shared_ptr<::grpc::ClientContext> stream_context_;
        std::thread stream_thread_;
        EventCallback stream_callback_;
        StreamEndCallback stream_end_callback_;
    };

} // namespace trb
