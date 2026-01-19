#include "udp/udp_socket.hpp"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

namespace trb::udp
{

    UdpSocket::UdpSocket(const std::string &dest_ip, int dest_port)
        : dest_ip_(dest_ip), dest_port_(dest_port), sockfd_(-1)
    {
        std::memset(&dest_addr_, 0, sizeof(dest_addr_));
    }

    UdpSocket::~UdpSocket()
    {
        close();
    }

    bool UdpSocket::open()
    {
        if (sockfd_ >= 0)
        {
            return true;
        }

        sockfd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd_ < 0)
        {
            std::cerr << "Failed to create UDP socket" << std::endl;
            return false;
        }

        std::memset(&dest_addr_, 0, sizeof(dest_addr_));
        dest_addr_.sin_family = AF_INET;
        dest_addr_.sin_port = htons(dest_port_);
        if (inet_pton(AF_INET, dest_ip_.c_str(), &dest_addr_.sin_addr) <= 0)
        {
            std::cerr << "Invalid UDP dest address" << std::endl;
            close();
            return false;
        }

        return true;
    }

    void UdpSocket::close()
    {
        if (sockfd_ >= 0)
        {
            ::close(sockfd_);
            sockfd_ = -1;
        }
    }

    void UdpSocket::setSendNonBlocking(bool enabled)
    {
        send_nonblocking_ = enabled;
    }

    void UdpSocket::setSendBufferBytes(int bytes)
    {
        if (sockfd_ < 0 || bytes <= 0)
        {
            return;
        }
        ::setsockopt(sockfd_, SOL_SOCKET, SO_SNDBUF, &bytes, sizeof(bytes));
    }

    int UdpSocket::send(const void *data, size_t size)
    {
        if (sockfd_ < 0)
            return -1;

        const int flags = send_nonblocking_ ? MSG_DONTWAIT : 0;
        return ::sendto(sockfd_, data, size, flags, reinterpret_cast<sockaddr *>(&dest_addr_), sizeof(dest_addr_));
    }

    int UdpSocket::receive(void *buffer, size_t size, int timeout_ms)
    {
        if (sockfd_ < 0)
            return -1;

        if (timeout_ms > 0)
        {
            timeval tv;
            tv.tv_sec = timeout_ms / 1000;
            tv.tv_usec = (timeout_ms % 1000) * 1000;
            ::setsockopt(sockfd_, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&tv), sizeof(tv));
        }

        sockaddr_in src_addr;
        socklen_t addr_len = sizeof(src_addr);
        return ::recvfrom(sockfd_, buffer, size, 0, reinterpret_cast<sockaddr *>(&src_addr), &addr_len);
    }

} // namespace trb::udp
