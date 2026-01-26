#include "udp/udp_manager.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <cstring>

#include <ros/ros.h>

namespace trb::udp
{

namespace
{
bool ipMatchesAllowed(const sockaddr_in &src, const std::string &allowed_ip)
{
    if (allowed_ip.empty())
    {
        return true;
    }
    char src_ip[INET_ADDRSTRLEN] = {0};
    if (::inet_ntop(AF_INET, &src.sin_addr, src_ip, sizeof(src_ip)) == nullptr)
    {
        return false;
    }
    return allowed_ip == src_ip;
}
} // namespace

UdpManager::UdpManager(UdpConfig config)
    : config_(std::move(config)),
      packet_builder_(config_.max_payload_bytes)
{
}

UdpManager::~UdpManager()
{
    stop();
}

bool UdpManager::start()
{
    if (running_.exchange(true))
    {
        return true;
    }

    sockfd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0)
    {
        running_.store(false);
        ROS_ERROR("UdpManager: socket() failed: %s", std::strerror(errno));
        return false;
    }

    int reuse = 1;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    int sndbuf = 64 * 1024 * 1024;
    if (::setsockopt(sockfd_, SOL_SOCKET, SO_SNDBUF, &sndbuf, sizeof(sndbuf)) != 0)
    {
        ROS_WARN("UdpManager: setsockopt(SO_SNDBUF) failed: %s", std::strerror(errno));
    }
    else
    {
        int actual = 0;
        socklen_t len = sizeof(actual);
        if (::getsockopt(sockfd_, SOL_SOCKET, SO_SNDBUF, &actual, &len) == 0)
        {
            ROS_INFO("UdpManager: SO_SNDBUF set to %d bytes", actual);
        }
    }

    if (config_.recv_timeout_ms > 0)
    {
        timeval tv;
        tv.tv_sec = config_.recv_timeout_ms / 1000;
        tv.tv_usec = (config_.recv_timeout_ms % 1000) * 1000;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&tv), sizeof(tv));
    }

    if (config_.bind_port > 0)
    {
        sockaddr_in addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(static_cast<uint16_t>(config_.bind_port));
        if (::inet_pton(AF_INET, config_.bind_ip.c_str(), &addr.sin_addr) <= 0)
        {
            ROS_ERROR("UdpManager: invalid bind_ip=%s", config_.bind_ip.c_str());
            ::close(sockfd_);
            sockfd_ = -1;
            running_.store(false);
            return false;
        }

        if (::bind(sockfd_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
        {
            ROS_ERROR("UdpManager: bind(%s:%d) failed: %s", config_.bind_ip.c_str(), config_.bind_port, std::strerror(errno));
            ::close(sockfd_);
            sockfd_ = -1;
            running_.store(false);
            return false;
        }
    }

    if (config_.enable_receive || config_.control_enabled)
    {
        recv_thread_ = std::thread(&UdpManager::recvThreadMain, this);
    }

    if (config_.control_enabled)
    {
        control_thread_ = std::thread(&UdpManager::controlThreadMain, this);
    }

    ROS_INFO("UdpManager started: remote=%s:%d bind=%s:%d recv=%s",
             config_.remote_ip.c_str(),
             config_.remote_port,
             config_.bind_ip.c_str(),
             config_.bind_port,
             config_.enable_receive ? "on" : "off");

    return true;
}

void UdpManager::stop()
{
    if (!running_.exchange(false))
    {
        return;
    }

    if (sockfd_ >= 0)
    {
        ::close(sockfd_);
        sockfd_ = -1;
    }

    if (recv_thread_.joinable())
    {
        recv_thread_.join();
    }
    if (control_thread_.joinable())
    {
        control_thread_.join();
    }
}

bool UdpManager::sendToRemote(const uint8_t *data, size_t size)
{
    if (sockfd_ < 0 || !data || size == 0)
    {
        return false;
    }

    sockaddr_in dst;
    std::memset(&dst, 0, sizeof(dst));
    dst.sin_family = AF_INET;
    dst.sin_port = htons(static_cast<uint16_t>(config_.remote_port));
    if (::inet_pton(AF_INET, config_.remote_ip.c_str(), &dst.sin_addr) <= 0)
    {
        ROS_ERROR("UdpManager: invalid remote_ip=%s", config_.remote_ip.c_str());
        return false;
    }

    const int flags = config_.send_nonblocking ? MSG_DONTWAIT : 0;
    const ssize_t sent = ::sendto(sockfd_, data, size, flags, reinterpret_cast<sockaddr *>(&dst), sizeof(dst));
    if (sent < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return false;
        }
        ROS_WARN_THROTTLE(2.0, "UdpManager: sendto failed: %s", std::strerror(errno));
        return false;
    }
    return sent == static_cast<ssize_t>(size);
}

void UdpManager::setDatagramCallback(DatagramCallback cb)
{
    datagram_callback_ = std::move(cb);
}

void UdpManager::setSessionId(const std::string &session_id)
{
    packet_builder_.setSessionId(session_id);
}

bool UdpManager::isHandshakeReady() const
{
    if (!config_.control_enabled)
    {
        return true;
    }
    return handshake_success_.load();
}

void UdpManager::recvThreadMain()
{
    std::array<uint8_t, 2048> buf;

    while (running_.load())
    {
        sockaddr_in src;
        socklen_t slen = sizeof(src);
        const int n = ::recvfrom(sockfd_, buf.data(), buf.size(), 0, reinterpret_cast<sockaddr *>(&src), &slen);
        if (n < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                continue;
            }
            if (!running_.load())
            {
                break;
            }
            ROS_WARN("UdpManager: recvfrom failed: %s", std::strerror(errno));
            continue;
        }

        if (!ipMatchesAllowed(src, config_.allowed_remote_ip))
        {
            continue;
        }

        const auto now_tp = std::chrono::steady_clock::now();
        const int64_t now_us = std::chrono::duration_cast<std::chrono::microseconds>(now_tp.time_since_epoch()).count();
        last_rx_steady_us_.store(now_us, std::memory_order_relaxed);

        if (config_.control_enabled && n >= 3 && buf[0] == 'A' && buf[1] == 'C' && buf[2] == 'K')
        {
            if (!handshake_success_.exchange(true))
            {
                ROS_INFO("UDP handshake: ACK received, streaming enabled");
            }
            continue;
        }

        if (datagram_callback_)
        {
            datagram_callback_(buf.data(), static_cast<size_t>(n));
        }
    }
}

void UdpManager::controlThreadMain()
{
    auto last_send = std::chrono::steady_clock::now() - std::chrono::seconds(10);
    while (running_.load())
    {
        if (handshake_success_.load())
        {
            if (config_.control_timeout_sec > 0.0)
            {
                const auto now = std::chrono::steady_clock::now();
                const int64_t now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
                const int64_t last_rx = last_rx_steady_us_.load(std::memory_order_relaxed);
                if (last_rx > 0)
                {
                    const double idle_sec = static_cast<double>(now_us - last_rx) / 1e6;
                    if (idle_sec > config_.control_timeout_sec)
                    {
                        handshake_success_.store(false);
                        ROS_WARN("UDP handshake timeout (idle %.1fs). Re-entering HELLO state.", idle_sec);
                        continue;
                    }
                }
            }

            const auto now = std::chrono::steady_clock::now();
            if (now - last_send >= std::chrono::duration<double>(config_.control_ping_interval_sec))
            {
                const std::string ping = packet_builder_.buildPingMessage();
                if (!ping.empty())
                {
                    sendToRemote(reinterpret_cast<const uint8_t *>(ping.data()), ping.size());
                }
                last_send = now;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        const std::string hello = packet_builder_.buildHelloMessage();
        if (!hello.empty())
        {
            sendToRemote(reinterpret_cast<const uint8_t *>(hello.data()), hello.size());
        }
        std::this_thread::sleep_for(std::chrono::duration<double>(config_.control_hello_interval_sec));
    }
}

} // namespace trb::udp
