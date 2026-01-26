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
    std::string remote_ip;
    int remote_port{0};

    std::string bind_ip{"0.0.0.0"};
    int bind_port{0};
    std::string allowed_remote_ip;

    int recv_timeout_ms{0};

    bool enable_receive{false};
    bool control_enabled{false};
    double control_hello_interval_sec{1.0};
    double control_ping_interval_sec{5.0};
    double control_timeout_sec{10.0};

    size_t max_payload_bytes{1200};
    bool send_nonblocking{true};
};

class UdpManager
{
public:
    using DatagramCallback = std::function<void(const uint8_t *, size_t)>;

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

    UdpConfig config_{};
    UdpPacketBuilder packet_builder_;

    std::atomic<bool> running_{false};
    int sockfd_{-1};

    std::thread recv_thread_;
    std::thread control_thread_;

    DatagramCallback datagram_callback_;

    std::atomic<bool> handshake_success_{false};
    std::atomic<int64_t> last_rx_steady_us_{0};
};

} // namespace trb::udp
