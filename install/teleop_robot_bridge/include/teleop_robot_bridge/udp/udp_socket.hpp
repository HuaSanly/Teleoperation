#pragma once

#include <cstddef>
#include <cstdint>
#include <netinet/in.h>
#include <string>

namespace trb::udp
{

    class UdpSocket
    {
    public:
        UdpSocket(const std::string &dest_ip, int dest_port);
        UdpSocket(const std::string &dest_ip, int dest_port, const std::string &bind_ip, int bind_port);
        ~UdpSocket();

        bool open();
        void close();
        void setRemote(const std::string &dest_ip, int dest_port);

        // If enabled, send() uses MSG_DONTWAIT and returns immediately.
        // On EAGAIN/EWOULDBLOCK, send() returns -1 and sets errno.
        void setSendNonBlocking(bool enabled);

        // Optional: set socket send buffer size (bytes). Must be called after open().
        void setSendBufferBytes(int bytes);
        int sendBufferBytes() const;
        void setRecvTimeoutMs(int timeout_ms);
        bool waitWritable(int timeout_ms) const;

        int send(const void *data, size_t size);
        int receive(void *buffer, size_t size);
        int receive(void *buffer, size_t size, int timeout_ms);

    private:
        void resetRemote();

        std::string dest_ip_;
        int dest_port_;
        std::string bind_ip_;
        int bind_port_{0};
        int sockfd_;
        sockaddr_in dest_addr_;

        bool send_nonblocking_{false};
        int recv_timeout_ms_{100};
    };

} // namespace trb::udp
