#include "signaling_client.hpp"

#include <cstdlib>
#include <utility>
#include <chrono>

namespace trb
{
    SignalingClient::SignalingClient(rclcpp::Logger logger,
                                     std::string server_ip,
                                     int server_port,
                                     std::string token,
                                     std::string device_id,
                                     bool use_ssl)
        : logger_(logger),
          server_ip_(std::move(server_ip)),
          server_port_(server_port),
          use_ssl_(use_ssl),
          token_(std::move(token)),
          device_id_(std::move(device_id))
    {
    }

    SignalingClient::~SignalingClient()
    {
        stopEventStream();
    }

    int SignalingClient::connect()
    {
        const std::string address = this->server_ip_ + ":" + std::to_string(this->server_port_);
        RCLCPP_INFO(this->logger_, "Connecting to gRPC server at %s", address.c_str());

        // 设置环境变量以避免代理干扰 (必须在创建 Channel 之前设置)
        std::string current_no_proxy = "";
        const char *env_no_proxy = std::getenv("no_proxy");
        if (env_no_proxy)
        {
            current_no_proxy = std::string(env_no_proxy) + ",";
        }
        const std::string new_no_proxy = current_no_proxy + this->server_ip_;
        setenv("no_proxy", new_no_proxy.c_str(), 1);
        setenv("NO_PROXY", new_no_proxy.c_str(), 1);

        grpc::ChannelArguments args;
        args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 5000);
        args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 2000);
        args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

        std::shared_ptr<grpc::ChannelCredentials> creds;
        if (this->use_ssl_)
        {
            grpc::SslCredentialsOptions ssl_opts;
            creds = grpc::SslCredentials(ssl_opts);
            RCLCPP_INFO(this->logger_, "Using SSL/TLS credentials");
        }
        else
        {
            creds = grpc::InsecureChannelCredentials();
            RCLCPP_INFO(this->logger_, "Using Insecure credentials");
        }

        auto channel = grpc::CreateCustomChannel(address, creds, args);
        this->stub_ = signaling::Signaling::NewStub(channel);
        return 0;
    }

    int SignalingClient::registerRobot()
    {
        if (!stub_)
        {
            RCLCPP_ERROR(logger_, "Stub not initialized. Call connect() first.");
            return -1;
        }

        grpc::ClientContext context;
        signaling::RegisterRequest request;
        request.set_token(token_);
        request.set_role(signaling::RegisterRequest::ROBOT);
        request.set_device_id(device_id_);

        signaling::RegisterResponse response;
        grpc::Status status = stub_->Register(&context, request, &response);

        if (status.ok() && response.success())
        {
            session_id_ = response.session_id();
            RCLCPP_INFO(logger_, "Registered successfully. Session ID: %s", session_id_.c_str());
            return 0;
        }
        else
        {
            RCLCPP_ERROR(logger_, "Registration failed: %s (gRPC code: %d, msg: %s)",
                         response.message().c_str(), status.error_code(), status.error_message().c_str());
            return -1;
        }
    }

    int SignalingClient::subscribeVrPose(const std::string &peer_session_id)
    {
        if (!stub_)
            return -1;

        grpc::ClientContext context;
        signaling::SubscribeRequest request;
        request.set_op(signaling::SubscribeRequest::SUBSCRIBE);
        request.set_publisher_session_id(peer_session_id);
        request.set_sub_pose(true);

        signaling::SubscribeResponse response;
        grpc::Status status = stub_->Subscribe(&context, request, &response);

        if (status.ok() && response.success())
        {
            RCLCPP_INFO(logger_, "Subscribed to VR pose of %s", peer_session_id.c_str());
            return 0;
        }
        else
        {
            RCLCPP_ERROR(logger_, "Subscribe failed: %s", response.message().c_str());
            return -1;
        }
    }

    void SignalingClient::tickHeartbeat()
    {
        if (!stub_)
            return;

        grpc::ClientContext context;
        signaling::Heartbeat request;
        auto now = std::chrono::system_clock::now().time_since_epoch();
        request.set_client_time(std::chrono::duration_cast<std::chrono::milliseconds>(now).count());

        signaling::HeartbeatAck response;
        context.AddMetadata("session-id", this->session_id_);
        context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(1000));

        grpc::Status status = stub_->Ping(&context, request, &response);
        if (!status.ok())
        {
            RCLCPP_WARN(logger_, "Heartbeat failed: %s", status.error_message().c_str());
        }
    }

    const std::string &SignalingClient::sessionId() const
    {
        return session_id_;
    }

    int SignalingClient::publishVideoConfig(const signaling::VideoConfig &config)
    {
        if (!stub_)
            return -1;

        grpc::ClientContext context;
        context.AddMetadata("session-id", session_id_);
        context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(2000));

        signaling::VideoConfigAck response;
        grpc::Status status = stub_->PublishVideoConfig(&context, config, &response);

        if (status.ok() && response.success())
        {
            const std::string &sent_id = config.config_id();
            const std::string &ack_id = response.config_id();
            if (!sent_id.empty() && !ack_id.empty() && sent_id != ack_id)
            {
                RCLCPP_WARN(logger_, "PublishVideoConfig ack mismatch: sent=%s ack=%s", sent_id.c_str(), ack_id.c_str());
                return -1;
            }
            RCLCPP_INFO(logger_, "PublishVideoConfig acked: %s (config_id=%s)", response.message().c_str(), ack_id.c_str());
            return 0;
        }

        RCLCPP_WARN(logger_, "PublishVideoConfig failed: %s (gRPC code: %d, msg: %s)",
                    response.message().c_str(), status.error_code(), status.error_message().c_str());
        return -1;
    }

    // --- New Methods ---

    int SignalingClient::requestPair(const std::string &peer_session_id)
    {
        if (!stub_)
            return -1;
        grpc::ClientContext context;
        context.AddMetadata("session-id", session_id_);

        signaling::PairRequest request;
        request.set_op(signaling::PairRequest::PAIR);
        request.set_peer_session_id(peer_session_id);
        request.set_state(signaling::PairRequest::REQUEST);

        signaling::PairResponse response;
        grpc::Status status = stub_->Pair(&context, request, &response);

        if (status.ok() && response.success())
        {
            RCLCPP_INFO(logger_, "Pair requested with %s", peer_session_id.c_str());
            return 0;
        }
        else
        {
            RCLCPP_ERROR(logger_, "Pair request failed: %s", response.message().c_str());
            return -1;
        }
    }

    int SignalingClient::acceptPair(const std::string &peer_session_id)
    {
        if (!stub_)
            return -1;
        grpc::ClientContext context;
        context.AddMetadata("session-id", session_id_);

        signaling::PairRequest request;
        request.set_op(signaling::PairRequest::PAIR);
        request.set_peer_session_id(peer_session_id);
        request.set_state(signaling::PairRequest::ACCEPT);

        signaling::PairResponse response;
        grpc::Status status = stub_->Pair(&context, request, &response);

        if (status.ok() && response.success())
        {
            RCLCPP_INFO(logger_, "Pair accepted with %s", peer_session_id.c_str());
            return 0;
        }
        else
        {
            RCLCPP_ERROR(logger_, "Pair accept failed: %s", response.message().c_str());
            return -1;
        }
    }

    int SignalingClient::rejectPair(const std::string &peer_session_id)
    {
        if (!stub_)
            return -1;
        grpc::ClientContext context;
        context.AddMetadata("session-id", session_id_);

        signaling::PairRequest request;
        request.set_op(signaling::PairRequest::PAIR);
        request.set_peer_session_id(peer_session_id);
        request.set_state(signaling::PairRequest::REJECT);

        signaling::PairResponse response;
        grpc::Status status = stub_->Pair(&context, request, &response);

        if (status.ok() && response.success())
        {
            RCLCPP_INFO(logger_, "Pair rejected with %s", peer_session_id.c_str());
            return 0;
        }
        else
        {
            RCLCPP_ERROR(logger_, "Pair reject failed: %s", response.message().c_str());
            return -1;
        }
    }

    int SignalingClient::unpair(const std::string &peer_session_id)
    {
        if (!stub_)
            return -1;
        grpc::ClientContext context;
        context.AddMetadata("session-id", session_id_);

        signaling::PairRequest request;
        request.set_op(signaling::PairRequest::UNPAIR);
        request.set_peer_session_id(peer_session_id);

        signaling::PairResponse response;
        grpc::Status status = stub_->Pair(&context, request, &response);

        if (status.ok() && response.success())
        {
            RCLCPP_INFO(logger_, "Unpaired with %s", peer_session_id.c_str());
            return 0;
        }
        else
        {
            RCLCPP_ERROR(logger_, "Unpair failed: %s", response.message().c_str());
            return -1;
        }
    }

    int SignalingClient::unsubscribe(const std::string &peer_session_id)
    {
        if (!stub_)
            return -1;
        grpc::ClientContext context;
        context.AddMetadata("session-id", session_id_);

        signaling::SubscribeRequest request;
        request.set_op(signaling::SubscribeRequest::UNSUBSCRIBE);
        request.set_publisher_session_id(peer_session_id);

        signaling::SubscribeResponse response;
        grpc::Status status = stub_->Subscribe(&context, request, &response);

        if (status.ok() && response.success())
        {
            RCLCPP_INFO(logger_, "Unsubscribed from %s", peer_session_id.c_str());
            return 0;
        }
        else
        {
            RCLCPP_ERROR(logger_, "Unsubscribe failed: %s", response.message().c_str());
            return -1;
        }
    }

    std::vector<signaling::UnpairedEndpoint> SignalingClient::listUnpaired(signaling::RegisterRequest::EndpointType desired_role)
    {
        std::vector<signaling::UnpairedEndpoint> result;
        if (!stub_)
            return result;

        grpc::ClientContext context;
        context.AddMetadata("session-id", session_id_);

        signaling::ListUnpairedRequest request;
        request.set_desired_role(desired_role);

        signaling::ListUnpairedResponse response;
        grpc::Status status = stub_->ListUnpaired(&context, request, &response);

        if (status.ok())
        {
            for (const auto &ep : response.endpoints())
            {
                result.push_back(ep);
            }
        }
        else
        {
            RCLCPP_ERROR(logger_, "ListUnpaired failed: %s", status.error_message().c_str());
        }
        return result;
    }

    void SignalingClient::startEventStream(EventCallback callback)
    {
        if (event_running_)
            return;
        event_callback_ = callback;
        event_running_ = true;
        event_thread_ = std::thread(&SignalingClient::eventStreamThread, this);
    }

    void SignalingClient::stopEventStream()
    {
        event_running_ = false;
        if (event_context_)
        {
            event_context_->TryCancel();
        }
        if (event_thread_.joinable())
        {
            event_thread_.join();
        }
    }

    void SignalingClient::eventStreamThread()
    {
        while (event_running_)
        {
            if (!stub_ || session_id_.empty())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            event_context_ = std::make_unique<grpc::ClientContext>();
            event_context_->AddMetadata("session-id", session_id_);

            signaling::EventSubscribe request;
            request.set_session_id(session_id_);

            std::unique_ptr<grpc::ClientReader<signaling::EventMessage>> reader(
                stub_->EventStream(event_context_.get(), request));

            signaling::EventMessage msg;
            while (reader->Read(&msg))
            {
                if (event_callback_)
                {
                    event_callback_(msg);
                }
            }

            grpc::Status status = reader->Finish();
            if (!status.ok() && event_running_)
            {
                RCLCPP_WARN(logger_, "EventStream disconnected: %s. Retrying in 3s...", status.error_message().c_str());
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        }
    }

}