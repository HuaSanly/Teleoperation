#include "grpc/grpc_manager.hpp"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <utility>

#include <google/protobuf/empty.pb.h>

namespace trb
{
    namespace
    {
        int deadlineMs(const GrpcConfig &config)
        {
            return std::max(1, config.rpc_timeout_ms);
        }
    } // namespace

    GrpcManager::GrpcManager(const GrpcConfig &config, rclcpp::Logger logger)
        : config_(config), logger_(std::move(logger))
    {
        auto channel = CreateChannel();
        stub_ = signaling::Signaling::NewStub(channel);
    }

    GrpcManager::~GrpcManager()
    {
        CancelPendingRpcs();
        StopEventStream();
    }

    GrpcManager::RpcScope::RpcScope(GrpcManager &manager, ::grpc::ClientContext &context)
        : manager_(manager), context_(context)
    {
        std::lock_guard<std::mutex> lock(manager_.pending_rpc_mutex_);
        if (manager_.shutting_down_.load())
        {
            shutting_down_ = true;
            return;
        }
        manager_.pending_rpc_contexts_.insert(&context_);
    }

    GrpcManager::RpcScope::~RpcScope()
    {
        if (shutting_down_)
        {
            return;
        }
        std::lock_guard<std::mutex> lock(manager_.pending_rpc_mutex_);
        manager_.pending_rpc_contexts_.erase(&context_);
    }

    void GrpcManager::CancelPendingRpcs()
    {
        shutting_down_.store(true);
        {
            std::lock_guard<std::mutex> lock(pending_rpc_mutex_);
            for (auto *context : pending_rpc_contexts_)
            {
                if (context)
                {
                    context->TryCancel();
                }
            }
        }
        if (stream_context_)
        {
            stream_context_->TryCancel();
        }
    }

    std::shared_ptr<::grpc::Channel> GrpcManager::CreateChannel() const
    {
        const std::string target = BuildTarget();

        const char *existing_no_proxy = std::getenv("no_proxy");
        const std::string no_proxy_prefix = existing_no_proxy ? std::string(existing_no_proxy) + "," : std::string();
        const std::string no_proxy_value = no_proxy_prefix + config_.server_grpc_ip;
        setenv("no_proxy", no_proxy_value.c_str(), 1);
        setenv("NO_PROXY", no_proxy_value.c_str(), 1);

        ::grpc::ChannelArguments args;
        args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 5000);
        args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 2000);
        args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

        std::shared_ptr<::grpc::ChannelCredentials> credentials;
        if (config_.use_ssl)
        {
            ::grpc::SslCredentialsOptions ssl_options;
            credentials = ::grpc::SslCredentials(ssl_options);
        }
        else
        {
            credentials = ::grpc::InsecureChannelCredentials();
        }

        return ::grpc::CreateCustomChannel(target, credentials, args);
    }

    std::string GrpcManager::BuildTarget() const
    {
        return config_.server_grpc_ip + ":" + std::to_string(config_.server_grpc_port);
    }

    void GrpcManager::ApplyDeadline(::grpc::ClientContext &context) const
    {
        context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(deadlineMs(config_)));
    }

    bool GrpcManager::Register()
    {
        if (!stub_ || shutting_down_.load())
        {
            return false;
        }

        signaling::RegisterRequest request;
        request.set_token(config_.token);
        request.set_role(signaling::RegisterRequest::ROBOT);
        request.set_device_id(config_.device_id);
        request.set_robot_generation(config_.robot_generation);

        signaling::RegisterResponse response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        RCLCPP_INFO(logger_, "Attempting gRPC Register to %s with timeout=%d ms", BuildTarget().c_str(), deadlineMs(config_));
        const ::grpc::Status status = stub_->Register(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC Register RPC failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        if (!response.success())
        {
            RCLCPP_WARN(logger_, "gRPC Register rejected by server: %s", response.message().c_str());
            return false;
        }

        session_id_ = response.session_id();
        return true;
    }

    const std::string &GrpcManager::session_id() const
    {
        return session_id_;
    }

    bool GrpcManager::Pair(signaling::PairRequest::Operation operation,
                           const std::string &peer_session_id,
                           signaling::PairRequest::PairState state)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        signaling::PairRequest request;
        request.set_op(operation);
        request.set_peer_session_id(peer_session_id);
        request.set_state(state);

        signaling::PairResponse response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->Pair(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC Pair RPC failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        if (!response.success())
        {
            RCLCPP_WARN(logger_, "gRPC Pair rejected by server: %s", response.message().c_str());
            return false;
        }
        return true;
    }

    bool GrpcManager::RequestPair(const std::string &peer_session_id)
    {
        return Pair(signaling::PairRequest::PAIR, peer_session_id, signaling::PairRequest::REQUEST);
    }

    bool GrpcManager::AcceptPair(const std::string &peer_session_id)
    {
        return Pair(signaling::PairRequest::PAIR, peer_session_id, signaling::PairRequest::ACCEPT);
    }

    bool GrpcManager::RejectPair(const std::string &peer_session_id)
    {
        return Pair(signaling::PairRequest::PAIR, peer_session_id, signaling::PairRequest::REJECT);
    }

    bool GrpcManager::Unpair(const std::string &peer_session_id)
    {
        return Pair(signaling::PairRequest::UNPAIR, peer_session_id, signaling::PairRequest::REQUEST);
    }

    bool GrpcManager::Subscribe(const std::string &publisher_session_id,
                                bool sub_video,
                                bool sub_pose,
                                bool sub_audio)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        signaling::SubscribeRequest request;
        request.set_op(signaling::SubscribeRequest::SUBSCRIBE);
        request.set_publisher_session_id(publisher_session_id);
        request.set_sub_video(sub_video);
        request.set_sub_pose(sub_pose);
        request.set_sub_audio(sub_audio);

        signaling::SubscribeResponse response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->Subscribe(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC Subscribe failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        return response.success();
    }

    bool GrpcManager::Unsubscribe(const std::string &publisher_session_id)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        signaling::SubscribeRequest request;
        request.set_op(signaling::SubscribeRequest::UNSUBSCRIBE);
        request.set_publisher_session_id(publisher_session_id);

        signaling::SubscribeResponse response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->Subscribe(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC Unsubscribe failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        return response.success();
    }

    std::vector<signaling::UnpairedEndpoint> GrpcManager::ListUnpaired(signaling::RegisterRequest::EndpointType desired_role)
    {
        std::vector<signaling::UnpairedEndpoint> endpoints;
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return endpoints;
        }

        signaling::ListUnpairedRequest request;
        request.set_desired_role(desired_role);

        signaling::ListUnpairedResponse response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return endpoints;
        }

        const ::grpc::Status status = stub_->ListUnpaired(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC ListUnpaired failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return endpoints;
        }

        endpoints.reserve(static_cast<size_t>(response.endpoints_size()));
        for (const auto &endpoint : response.endpoints())
        {
            endpoints.push_back(endpoint);
        }
        return endpoints;
    }

    bool GrpcManager::PublishVideoConfig(const signaling::VideoConfig &config, signaling::VideoConfigAck &ack)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->PublishVideoConfig(&context, config, &ack);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC PublishVideoConfig failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        return ack.success();
    }

    bool GrpcManager::AckVideoConfig(const signaling::VideoConfigAck &ack)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        google::protobuf::Empty response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->AckVideoConfig(&context, ack, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC AckVideoConfig failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        return true;
    }

    bool GrpcManager::PublishAudioConfig(const signaling::AudioConfig &config, signaling::AudioConfigAck &ack)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->PublishAudioConfig(&context, config, &ack);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC PublishAudioConfig failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        return ack.success();
    }

    bool GrpcManager::AckAudioConfig(const signaling::AudioConfigAck &ack)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        google::protobuf::Empty response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->AckAudioConfig(&context, ack, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC AckAudioConfig failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        return true;
    }

    bool GrpcManager::GetP2pInfo(signaling::GetP2pInfoResponse &response)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return false;
        }

        google::protobuf::Empty request;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return false;
        }

        const ::grpc::Status status = stub_->GetP2pInfo(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC GetP2pInfo failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            return false;
        }
        return response.ready();
    }

    GrpcManager::HeartbeatResult GrpcManager::Heartbeat()
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return HeartbeatResult::kSessionInvalid;
        }

        const auto now = std::chrono::system_clock::now().time_since_epoch();
        signaling::Heartbeat request;
        request.set_client_time(std::chrono::duration_cast<std::chrono::milliseconds>(now).count());

        signaling::HeartbeatAck response;
        ::grpc::ClientContext context;
        ApplyDeadline(context);
        context.AddMetadata("session-id", session_id_);
        RpcScope scope(*this, context);
        if (scope.shuttingDown())
        {
            return HeartbeatResult::kTransportError;
        }

        const ::grpc::Status status = stub_->Ping(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "gRPC Ping failed: code=%d message=%s",
                        static_cast<int>(status.error_code()), status.error_message().c_str());
            switch (status.error_code())
            {
            case ::grpc::StatusCode::NOT_FOUND:
            case ::grpc::StatusCode::UNAUTHENTICATED:
            case ::grpc::StatusCode::PERMISSION_DENIED:
                return HeartbeatResult::kSessionInvalid;
            default:
                return HeartbeatResult::kTransportError;
            }
        }
        return HeartbeatResult::kOk;
    }

    void GrpcManager::StartEventStream(const EventCallback &callback, const StreamEndCallback &on_end)
    {
        if (!stub_ || session_id_.empty() || shutting_down_.load())
        {
            return;
        }
        if (stream_running_.exchange(true))
        {
            return;
        }
        if (stream_thread_.joinable() && stream_thread_.get_id() != std::this_thread::get_id())
        {
            stream_thread_.join();
        }

        stream_callback_ = callback;
        stream_end_callback_ = on_end;
        stream_context_ = std::make_shared<::grpc::ClientContext>();
        stream_context_->AddMetadata("session-id", session_id_);

        stream_thread_ = std::thread([this]() {
            signaling::EventSubscribe request;
            request.set_session_id(session_id_);

            std::unique_ptr<::grpc::ClientReader<signaling::EventMessage>> reader(
                stub_->EventStream(stream_context_.get(), request));

            signaling::EventMessage message;
            while (stream_running_.load() && reader->Read(&message))
            {
                if (stream_callback_)
                {
                    stream_callback_(message);
                }
            }

            const ::grpc::Status status = reader->Finish();
            const bool unexpected = stream_running_.exchange(false);
            if (unexpected && stream_end_callback_)
            {
                stream_end_callback_(status);
            }
        });
    }

    void GrpcManager::StopEventStream()
    {
        stream_running_.store(false);
        if (stream_context_)
        {
            stream_context_->TryCancel();
        }
        if (stream_thread_.joinable())
        {
            if (stream_thread_.get_id() == std::this_thread::get_id())
            {
                stream_thread_.detach();
            }
            else
            {
                stream_thread_.join();
            }
        }
        stream_context_.reset();
        stream_callback_ = nullptr;
        stream_end_callback_ = nullptr;
    }

} // namespace trb