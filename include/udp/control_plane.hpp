#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <string>
#include <thread>

namespace trb::udp
{

    class ControlPlane
    {
    public:
        using PeerLostCallback = std::function<void()>;

        struct Config
        {
            bool enabled{true};
            double hello_interval_sec{1.0};
            double ping_interval_sec{5.0};
            double peer_lost_timeout_sec{0.0};
        };

        explicit ControlPlane(Config config);
        ~ControlPlane();

        void start(std::function<void(const std::string &)> send_fn,
                   std::function<std::string()> hello_fn,
                   std::function<std::string()> ping_fn);
        void stop();

        void setPeerLostCallback(PeerLostCallback callback) { peer_lost_callback_ = std::move(callback); }

        void onAckReceived();
        void onPeerActivity();
        bool handshakeReady() const;
        void resetHandshake();

    private:
        void threadMain();

        Config config_;
        std::function<void(const std::string &)> send_fn_;
        std::function<std::string()> hello_fn_;
        std::function<std::string()> ping_fn_;
        PeerLostCallback peer_lost_callback_;

        std::atomic<bool> running_{false};
        std::atomic<bool> handshake_ready_{false};
        std::atomic<int64_t> last_ack_steady_us_{0};
        std::thread thread_;
    };

} // namespace trb::udp