#pragma once

#include <array>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <mutex>
#include <optional>
#include <vector>

namespace trb::udp
{

    struct QueueItem
    {
        enum class Kind
        {
            Datagram,
            GroupEnd,
        };
        enum class Stream
        {
            Video,
            Audio,
            Other,
        };

        static constexpr uint8_t kHighestPriority = 0;
        static constexpr uint8_t kLowestPriority = 4;

        Kind kind{Kind::Datagram};
        Stream stream{Stream::Other};
        uint32_t group_id{0};
        uint16_t packet_seq{0};
        uint32_t stream_key{0};
        uint8_t priority{kLowestPriority};
        bool pacing_accounted{true};
        bool is_keyframe{false};
        bool is_fec_parity{false};
        uint64_t enqueue_steady_us{0};
        uint64_t frame_capture_steady_us{0};
        std::vector<uint8_t> bytes;
        size_t wire_bytes{0};
    };

    class SendQueue
    {
    public:
        static constexpr size_t kNumPriorityLevels = 5;

        struct Snapshot
        {
            size_t packets{0};
            size_t bytes{0};
            uint64_t dropped_video_groups{0};
            uint64_t dropped_video_packets{0};
            uint64_t dropped_video_bytes{0};
        };

        struct Status
        {
            size_t packets{0};
            size_t bytes{0};
            uint64_t oldest_enqueue_steady_us{0};
            std::array<size_t, kNumPriorityLevels> priority_packets{};
            std::array<size_t, kNumPriorityLevels> priority_bytes{};
        };

        struct ItemMeta
        {
            QueueItem::Kind kind{QueueItem::Kind::Datagram};
            QueueItem::Stream stream{QueueItem::Stream::Other};
            uint32_t group_id{0};
            uint32_t stream_key{0};
            uint8_t priority{QueueItem::kLowestPriority};
            bool pacing_accounted{true};
            size_t wire_bytes{0};
            uint64_t enqueue_steady_us{0};
        };

        void setLimits(size_t max_packets, size_t max_bytes);
        void stop();
        void clear();
        void setProtectedVideoGroup(uint32_t group_id);
        void clearProtectedVideoGroup(uint32_t group_id);

        void push(QueueItem &&item);
        void requeueFront(QueueItem &&item);
        void dropGroup(uint32_t group_id, QueueItem::Stream stream, const char *reason);
        bool dropParityForGroup(uint32_t group_id, QueueItem::Stream stream, const char *reason);
        bool pop(QueueItem &out, int timeout_ms);
        bool popPrioritized(QueueItem &out, int timeout_ms);
        bool peekPrioritized(ItemMeta &out, int timeout_ms);
        bool waitForDataFor(std::chrono::microseconds timeout);
        Status status();
        Snapshot snapshot();

    private:
        using QueueIterator = std::deque<QueueItem>::iterator;

        struct VideoGroupInfo
        {
            uint32_t group_id{0};
            bool is_keyframe{false};
        };

        std::optional<QueueIterator> selectPrioritizedLocked();
        std::vector<VideoGroupInfo> collectVideoGroupsLocked() const;
        void trimVideoBacklogLocked(uint32_t newest_group_id);
        bool dropOldestVideoParityLocked(const char *reason);
        bool dropOldestGroupLocked(const char *reason);
        bool dropParityForGroupLocked(uint32_t group_id, QueueItem::Stream stream, const char *reason);
        void dropGroupLocked(uint32_t group_id, QueueItem::Stream stream, const char *reason);
        void removeItemLocked(QueueIterator iterator, QueueItem &out);
        bool isProtectedVideoGroupLocked(uint32_t group_id, QueueItem::Stream stream) const;
        static uint8_t normalizePriority(uint8_t priority);
        static constexpr uint32_t kNoProtectedVideoGroup = UINT32_MAX;

        std::mutex mutex_;
        std::condition_variable cv_;
        std::deque<QueueItem> queue_;
        uint32_t protected_video_group_id_{kNoProtectedVideoGroup};
        size_t queue_bytes_{0};
        size_t max_packets_{0};
        size_t max_bytes_{0};
        bool running_{true};
        uint64_t dropped_video_groups_{0};
        uint64_t dropped_video_packets_{0};
        uint64_t dropped_video_bytes_{0};
    };

} // namespace trb::udp