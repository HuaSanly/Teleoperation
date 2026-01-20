#pragma once

#include <grpcpp/grpcpp.h>
#include <ros/ros.h>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "signaling.grpc.pb.h"

namespace trb
{

class SignalingClient
{
public:
    using EventCallback = std::function<void(const signaling::EventMessage &)>;

    explicit SignalingClient(std::string server_ip,
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
