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
        ~UdpSocket();

        bool open();
        void close();

        // If enabled, send() uses MSG_DONTWAIT and returns immediately.
        // On EAGAIN/EWOULDBLOCK, send() returns -1 and sets errno.
        void setSendNonBlocking(bool enabled);

        // Optional: set socket send buffer size (bytes). Must be called after open().
        void setSendBufferBytes(int bytes);

        int send(const void *data, size_t size);
        int receive(void *buffer, size_t size, int timeout_ms);

    private:
        std::string dest_ip_;
        int dest_port_;
        int sockfd_;
        sockaddr_in dest_addr_;

        bool send_nonblocking_{false};
    };

} // namespace trb::udp
