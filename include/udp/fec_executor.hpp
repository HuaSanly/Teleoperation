#pragma once

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace trb::udp
{

class FecExecutor
{
public:
    explicit FecExecutor(size_t threads);
    ~FecExecutor();

    bool start();
    void stop();

    template <typename F>
    void parallelFor(size_t count, F &&fn)
    {
        if (count == 0)
        {
            return;
        }
        if (threads_ <= 1)
        {
            for (size_t i = 0; i < count; ++i)
            {
                fn(i);
            }
            return;
        }

        auto group = std::make_shared<TaskGroup>();
        group->remaining.store(count);

        for (size_t i = 0; i < count; ++i)
        {
            enqueue([group, fn, i]() mutable
                    {
                        fn(i);
                        if (group->remaining.fetch_sub(1) == 1)
                        {
                            std::lock_guard<std::mutex> lk(group->mutex);
                            group->cv.notify_all();
                        }
                    });
        }

        std::unique_lock<std::mutex> lk(group->mutex);
        group->cv.wait(lk, [&]()
                       { return group->remaining.load() == 0; });
    }

private:
    struct TaskGroup
    {
        std::mutex mutex;
        std::condition_variable cv;
        std::atomic<size_t> remaining{0};
    };

    void enqueue(std::function<void()> task);
    void workerMain();

    size_t threads_{0};
    std::atomic<bool> running_{false};
    std::vector<std::thread> workers_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::queue<std::function<void()>> queue_;
};

} // namespace trb::udp
