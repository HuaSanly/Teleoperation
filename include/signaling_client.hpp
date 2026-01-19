#ifndef SIGNALING_CLIENT_H
#define SIGNALING_CLIENT_H

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>

#include <functional>
#include <thread>
#include <atomic>
#include <vector>

#include <grpcpp/grpcpp.h>
#include "rclcpp/rclcpp.hpp"

#include "signaling.grpc.pb.h"

namespace trb
{
    class SignalingClient
    {
    public:
        using EventCallback = std::function<void(const signaling::EventMessage &)>;

        explicit SignalingClient(rclcpp::Logger logger,
                                 std::string server_ip,
                                 int server_port,
                                 std::string token,
                                 std::string device_id,
                                 bool use_ssl = false);
        ~SignalingClient();

        int connect();

        // 1. Register
        int registerRobot();

        // 2. Heartbeat
        void tickHeartbeat();

        // 3. Pair
        int requestPair(const std::string &peer_session_id);
        int acceptPair(const std::string &peer_session_id);
        int rejectPair(const std::string &peer_session_id);
        int unpair(const std::string &peer_session_id);

        // 4. Subscribe
        int subscribeVrPose(const std::string &peer_session_id);
        int unsubscribe(const std::string &peer_session_id);

        // 7. List Unpaired
        std::vector<signaling::UnpairedEndpoint> listUnpaired(signaling::RegisterRequest::EndpointType desired_role);

        // 8. Event Stream
        void startEventStream(EventCallback callback);
        void stopEventStream();

        const std::string &sessionId() const;

    private:
        void eventStreamThread();

        rclcpp::Logger logger_;

        std::string server_ip_;
        int server_port_ = 0;
        bool use_ssl_ = false;
        std::string token_;
        std::string device_id_;
        std::string session_id_;

        std::unique_ptr<signaling::Signaling::Stub> stub_;

        std::thread event_thread_;
        std::atomic<bool> event_running_{false};
        EventCallback event_callback_;
        std::unique_ptr<grpc::ClientContext> event_context_;
    };
} // namespace trb

#endif // SIGNALING_CLIENT_H