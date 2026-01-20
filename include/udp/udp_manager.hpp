#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <thread>

#include "udp/udp_packet.hpp"

namespace trb::udp
{

struct UdpConfig
{
    std::string remote_ip{"127.0.0.1"};
    int remote_port{7778};

    std::string bind_ip{"0.0.0.0"};
    int bind_port{0};

    int recv_timeout_ms{100};
    std::string allowed_remote_ip{};

    bool enable_receive{false};

    // Control-plane (HELLO/ACK/PING)
    bool control_enabled{true};
    double control_hello_interval_sec{1.0};
    double control_ping_interval_sec{5.0};
    double control_timeout_sec{10.0};
    size_t max_payload_bytes{1200};
};

class UdpManager
{
public:
    using DatagramCallback = std::function<void(const uint8_t *data, size_t size)>;

    explicit UdpManager(UdpConfig config);
    ~UdpManager();

    bool start();
    void stop();

    bool sendToRemote(const uint8_t *data, size_t size);

    void setDatagramCallback(DatagramCallback cb);
    void setSessionId(const std::string &session_id);
    bool isHandshakeReady() const;

private:
    void recvThreadMain();
    void controlThreadMain();

    UdpConfig config_;

    int sockfd_{-1};
    std::atomic<bool> running_{false};
    std::thread recv_thread_;
    std::thread control_thread_;

    std::atomic<bool> handshake_success_{false};
    std::atomic<int64_t> last_rx_steady_us_{0};
    UdpPacketBuilder packet_builder_;

    DatagramCallback datagram_callback_;
};

} // namespace trb::udp
