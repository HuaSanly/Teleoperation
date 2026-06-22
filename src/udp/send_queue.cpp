#include "udp/send_queue.hpp"

#include <algorithm>

#include "rclcpp/rclcpp.hpp"

namespace trb::udp
{
    namespace
    {
        constexpr size_t kMaxQueuedVideoGroups = 4;

        rclcpp::Logger queueLogger()
        {
            return rclcpp::get_logger("teleop_robot_bridge.udp.send_queue");
        }
    } // namespace

    uint8_t SendQueue::normalizePriority(uint8_t priority)
    {
        return static_cast<uint8_t>(std::min<size_t>(priority, kNumPriorityLevels - 1));
    }

    void SendQueue::setLimits(size_t max_packets, size_t max_bytes)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        max_packets_ = max_packets;
        max_bytes_ = max_bytes;
    }

    void SendQueue::stop()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            running_ = false;
            queue_.clear();
            queue_bytes_ = 0;
            protected_video_group_id_ = kNoProtectedVideoGroup;
        }
        cv_.notify_all();
    }

    void SendQueue::clear()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.clear();
            queue_bytes_ = 0;
            protected_video_group_id_ = kNoProtectedVideoGroup;
        }
        cv_.notify_all();
    }

    void SendQueue::setProtectedVideoGroup(uint32_t group_id)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        protected_video_group_id_ = group_id;
    }

    void SendQueue::clearProtectedVideoGroup(uint32_t group_id)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (protected_video_group_id_ == group_id)
        {
            protected_video_group_id_ = kNoProtectedVideoGroup;
        }
    }

    void SendQueue::push(QueueItem &&item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_)
        {
            return;
        }

        if (item.kind == QueueItem::Kind::Datagram)
        {
            queue_bytes_ += item.wire_bytes;
        }
        item.priority = normalizePriority(item.priority);
        queue_.push_back(std::move(item));

        if (queue_.back().stream == QueueItem::Stream::Video && queue_.back().kind == QueueItem::Kind::GroupEnd)
        {
            trimVideoBacklogLocked(queue_.back().group_id);
        }

        enforceLimitsLocked();

        lock.unlock();
        cv_.notify_one();
    }

    void SendQueue::pushBatch(std::vector<QueueItem> &&items)
    {
        if (items.empty())
        {
            return;
        }

        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_)
        {
            return;
        }

        std::optional<uint32_t> newest_video_group_end;
        for (auto &item : items)
        {
            if (item.kind == QueueItem::Kind::Datagram)
            {
                queue_bytes_ += item.wire_bytes;
            }
            item.priority = normalizePriority(item.priority);
            if (item.stream == QueueItem::Stream::Video && item.kind == QueueItem::Kind::GroupEnd)
            {
                newest_video_group_end = item.group_id;
            }
            queue_.push_back(std::move(item));
        }

        if (newest_video_group_end.has_value())
        {
            trimVideoBacklogLocked(*newest_video_group_end);
        }

        enforceLimitsLocked();

        lock.unlock();
        cv_.notify_one();
    }

    void SendQueue::requeueFront(QueueItem &&item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_)
        {
            return;
        }

        if (item.kind == QueueItem::Kind::Datagram)
        {
            queue_bytes_ += item.wire_bytes;
        }
        item.priority = normalizePriority(item.priority);
        queue_.push_front(std::move(item));

        lock.unlock();
        cv_.notify_one();
    }

    void SendQueue::dropGroup(uint32_t group_id, QueueItem::Stream stream, const char *reason)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        dropGroupLocked(group_id, stream, reason);
    }

    bool SendQueue::dropParityForGroup(uint32_t group_id, QueueItem::Stream stream, const char *reason)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return dropParityForGroupLocked(group_id, stream, reason);
    }

    bool SendQueue::pop(QueueItem &out, int timeout_ms)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_)
        {
            return false;
        }
        if (!cv_.wait_for(lock, std::chrono::milliseconds(timeout_ms), [this]() { return !queue_.empty() || !running_; }))
        {
            return false;
        }
        if (!running_ || queue_.empty())
        {
            return false;
        }

        out = std::move(queue_.front());
        if (out.kind == QueueItem::Kind::Datagram)
        {
            queue_bytes_ = queue_bytes_ >= out.wire_bytes ? queue_bytes_ - out.wire_bytes : 0;
        }
        queue_.pop_front();
        return true;
    }

    bool SendQueue::popPrioritized(QueueItem &out, int timeout_ms)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_)
        {
            return false;
        }
        if (!cv_.wait_for(lock, std::chrono::milliseconds(timeout_ms), [this]() { return !queue_.empty() || !running_; }))
        {
            return false;
        }
        if (!running_ || queue_.empty())
        {
            return false;
        }

        auto selected = selectPrioritizedLocked();
        if (!selected.has_value())
        {
            return false;
        }
        removeItemLocked(*selected, out);
        return true;
    }

    bool SendQueue::peekPrioritized(ItemMeta &out, int timeout_ms)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_)
        {
            return false;
        }
        if (!cv_.wait_for(lock, std::chrono::milliseconds(timeout_ms), [this]() { return !queue_.empty() || !running_; }))
        {
            return false;
        }
        if (!running_ || queue_.empty())
        {
            return false;
        }

        auto selected = selectPrioritizedLocked();
        if (!selected.has_value())
        {
            return false;
        }

        const QueueItem &item = **selected;
        out.kind = item.kind;
        out.stream = item.stream;
        out.group_id = item.group_id;
        out.stream_key = item.stream_key;
        out.priority = normalizePriority(item.priority);
        out.pacing_accounted = item.pacing_accounted;
        out.wire_bytes = item.wire_bytes;
        out.enqueue_steady_us = item.enqueue_steady_us;
        return true;
    }

    bool SendQueue::waitForDataFor(std::chrono::microseconds timeout)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_)
        {
            return false;
        }
        if (timeout.count() > 0)
        {
            cv_.wait_for(lock, timeout);
        }
        return running_;
    }

    SendQueue::Status SendQueue::status()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        Status status;
        status.packets = queue_.size();
        status.bytes = queue_bytes_;
        for (const auto &item : queue_)
        {
            if (item.enqueue_steady_us > 0 &&
                (status.oldest_enqueue_steady_us == 0 || item.enqueue_steady_us < status.oldest_enqueue_steady_us))
            {
                status.oldest_enqueue_steady_us = item.enqueue_steady_us;
            }
            const size_t priority = normalizePriority(item.priority);
            status.priority_packets[priority] += 1;
            if (item.kind == QueueItem::Kind::Datagram)
            {
                status.priority_bytes[priority] += item.wire_bytes;
            }
        }
        return status;
    }

    SendQueue::Snapshot SendQueue::snapshot()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        Snapshot snapshot;
        snapshot.packets = queue_.size();
        snapshot.bytes = queue_bytes_;
        snapshot.dropped_video_groups = dropped_video_groups_;
        snapshot.dropped_video_packets = dropped_video_packets_;
        snapshot.dropped_video_bytes = dropped_video_bytes_;
        dropped_video_groups_ = 0;
        dropped_video_packets_ = 0;
        dropped_video_bytes_ = 0;
        return snapshot;
    }

    std::vector<SendQueue::VideoGroupInfo> SendQueue::collectVideoGroupsLocked() const
    {
        std::vector<VideoGroupInfo> groups;
        groups.reserve(queue_.size());
        for (const auto &item : queue_)
        {
            if (item.stream != QueueItem::Stream::Video)
            {
                continue;
            }

            auto existing = std::find_if(groups.begin(), groups.end(), [&item](const VideoGroupInfo &group) {
                return group.group_id == item.group_id;
            });
            if (existing == groups.end())
            {
                groups.push_back(VideoGroupInfo{item.group_id, item.is_keyframe});
                continue;
            }
            existing->is_keyframe = existing->is_keyframe || item.is_keyframe;
        }
        return groups;
    }

    void SendQueue::trimVideoBacklogLocked(uint32_t newest_group_id)
    {
        auto groups = collectVideoGroupsLocked();
        if (groups.size() <= kMaxQueuedVideoGroups)
        {
            return;
        }

        const auto newest = std::find_if(groups.begin(), groups.end(), [newest_group_id](const VideoGroupInfo &group) {
            return group.group_id == newest_group_id;
        });
        const bool newest_is_keyframe = newest != groups.end() && newest->is_keyframe;
        if (newest_is_keyframe)
        {
            for (const auto &group : groups)
            {
                if (group.group_id == newest_group_id ||
                    isProtectedVideoGroupLocked(group.group_id, QueueItem::Stream::Video))
                {
                    continue;
                }
                dropGroupLocked(group.group_id, QueueItem::Stream::Video, "new_keyframe");
            }
            return;
        }

        while (groups.size() > kMaxQueuedVideoGroups)
        {
            auto victim = std::find_if(groups.begin(), groups.end(), [this, newest_group_id](const VideoGroupInfo &group) {
                return group.group_id != newest_group_id &&
                       !group.is_keyframe &&
                       !isProtectedVideoGroupLocked(group.group_id, QueueItem::Stream::Video);
            });
            if (victim == groups.end())
            {
                victim = std::find_if(groups.begin(), groups.end(), [this, newest_group_id](const VideoGroupInfo &group) {
                    return group.group_id != newest_group_id &&
                           !isProtectedVideoGroupLocked(group.group_id, QueueItem::Stream::Video);
                });
            }
            if (victim == groups.end())
            {
                return;
            }

            dropGroupLocked(victim->group_id, QueueItem::Stream::Video, "backlog");
            groups = collectVideoGroupsLocked();
        }
    }

    bool SendQueue::dropOldestVideoParityLocked(const char *reason)
    {
        auto victim = std::find_if(queue_.begin(), queue_.end(), [this](const QueueItem &item) {
            return item.stream == QueueItem::Stream::Video &&
                   item.is_fec_parity &&
                   !item.is_keyframe &&
                   !isProtectedVideoGroupLocked(item.group_id, item.stream);
        });
        if (victim == queue_.end())
        {
            victim = std::find_if(queue_.begin(), queue_.end(), [this](const QueueItem &item) {
                return item.stream == QueueItem::Stream::Video &&
                       item.is_fec_parity &&
                       !isProtectedVideoGroupLocked(item.group_id, item.stream);
            });
        }
        if (victim == queue_.end())
        {
            return false;
        }
        return dropParityForGroupLocked(victim->group_id, victim->stream, reason);
    }

    bool SendQueue::dropOldestGroupLocked(const char *reason)
    {
        if (queue_.empty())
        {
            return false;
        }
        auto victim = std::find_if(queue_.begin(), queue_.end(), [this](const QueueItem &item) {
            return item.stream == QueueItem::Stream::Video && !item.is_keyframe &&
                   !isProtectedVideoGroupLocked(item.group_id, item.stream);
        });
        if (victim == queue_.end())
        {
            victim = std::find_if(queue_.begin(), queue_.end(), [this](const QueueItem &item) {
                return item.stream == QueueItem::Stream::Video &&
                       !isProtectedVideoGroupLocked(item.group_id, item.stream);
            });
        }
        if (victim == queue_.end())
        {
            victim = std::find_if(queue_.begin(), queue_.end(), [this](const QueueItem &item) {
                return !isProtectedVideoGroupLocked(item.group_id, item.stream);
            });
        }
        if (victim == queue_.end())
        {
            return false;
        }

        dropGroupLocked(victim->group_id, victim->stream, reason);
        return true;
    }

    bool SendQueue::dropParityForGroupLocked(uint32_t drop_group_id, QueueItem::Stream drop_stream, const char *reason)
    {
        if (isProtectedVideoGroupLocked(drop_group_id, drop_stream))
        {
            return false;
        }

        size_t dropped_items = 0;
        size_t dropped_bytes = 0;
        for (auto it = queue_.begin(); it != queue_.end();)
        {
            if (it->group_id == drop_group_id &&
                it->stream == drop_stream &&
                it->kind == QueueItem::Kind::Datagram &&
                it->is_fec_parity)
            {
                dropped_bytes += it->wire_bytes;
                queue_bytes_ = queue_bytes_ >= it->wire_bytes ? queue_bytes_ - it->wire_bytes : 0;
                it = queue_.erase(it);
                ++dropped_items;
            }
            else
            {
                ++it;
            }
        }

        if (dropped_items == 0)
        {
            return false;
        }

        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        RCLCPP_WARN_THROTTLE(queueLogger(), steady_clock, 1000,
                             "SendQueue DROP: reason=%s stream=%d group_id=%u items=%zu bytes=%zu remaining_queue=%zu remaining_bytes=%zu",
                             reason ? reason : "unknown", static_cast<int>(drop_stream), drop_group_id, dropped_items,
                             dropped_bytes, queue_.size(), queue_bytes_);
        return true;
    }

    void SendQueue::dropGroupLocked(uint32_t drop_group_id, QueueItem::Stream drop_stream, const char *reason)
    {
        if (isProtectedVideoGroupLocked(drop_group_id, drop_stream))
        {
            return;
        }

        size_t dropped_items = 0;
        size_t dropped_bytes = 0;
        for (auto it = queue_.begin(); it != queue_.end();)
        {
            if (it->group_id == drop_group_id && it->stream == drop_stream)
            {
                if (it->kind == QueueItem::Kind::Datagram)
                {
                    dropped_bytes += it->wire_bytes;
                    queue_bytes_ = queue_bytes_ >= it->wire_bytes ? queue_bytes_ - it->wire_bytes : 0;
                }
                it = queue_.erase(it);
                ++dropped_items;
            }
            else
            {
                ++it;
            }
        }

        if (dropped_items == 0)
        {
            return;
        }

        if (drop_stream == QueueItem::Stream::Video)
        {
            dropped_video_groups_ += 1;
            dropped_video_packets_ += dropped_items;
            dropped_video_bytes_ += dropped_bytes;
        }

        static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
        RCLCPP_WARN_THROTTLE(queueLogger(), steady_clock, 1000,
                             "SendQueue DROP: reason=%s stream=%d group_id=%u items=%zu bytes=%zu remaining_queue=%zu remaining_bytes=%zu",
                             reason ? reason : "unknown", static_cast<int>(drop_stream), drop_group_id, dropped_items,
                             dropped_bytes, queue_.size(), queue_bytes_);
    }

    bool SendQueue::isProtectedVideoGroupLocked(uint32_t group_id, QueueItem::Stream stream) const
    {
        return stream == QueueItem::Stream::Video &&
               protected_video_group_id_ != kNoProtectedVideoGroup &&
               protected_video_group_id_ == group_id;
    }

    std::optional<SendQueue::QueueIterator> SendQueue::selectPrioritizedLocked()
    {
        if (queue_.empty())
        {
            return std::nullopt;
        }

        for (size_t priority = 0; priority < kNumPriorityLevels; ++priority)
        {
            auto candidate = std::find_if(queue_.begin(), queue_.end(), [priority, this](const QueueItem &item) {
                return normalizePriority(item.priority) == priority;
            });
            if (candidate != queue_.end())
            {
                return candidate;
            }
        }
        return std::nullopt;
    }

    void SendQueue::removeItemLocked(QueueIterator iterator, QueueItem &out)
    {
        out = std::move(*iterator);
        if (out.kind == QueueItem::Kind::Datagram)
        {
            queue_bytes_ = queue_bytes_ >= out.wire_bytes ? queue_bytes_ - out.wire_bytes : 0;
        }
        queue_.erase(iterator);
    }

    void SendQueue::enforceLimitsLocked()
    {
        if (max_bytes_ > 0 && queue_bytes_ > max_bytes_)
        {
            static rclcpp::Clock steady_clock(RCL_STEADY_TIME);
            RCLCPP_WARN_THROTTLE(queueLogger(), steady_clock, 1000,
                                 "UDP send queue high water: %zu/%zu bytes (%zu packets)",
                                 queue_bytes_, max_bytes_, queue_.size());
        }

        while (!queue_.empty() &&
               ((max_packets_ > 0 && queue_.size() > max_packets_) || (max_bytes_ > 0 && queue_bytes_ > max_bytes_)))
        {
            if (!dropOldestVideoParityLocked("capacity_parity") && !dropOldestGroupLocked("capacity"))
            {
                break;
            }
        }
    }

} // namespace trb::udp
