#include "udp/fec_executor.hpp"

namespace trb::udp
{

FecExecutor::FecExecutor(size_t threads)
    : threads_(threads)
{
}

FecExecutor::~FecExecutor()
{
    stop();
}

bool FecExecutor::start()
{
    if (running_.exchange(true))
    {
        return true;
    }

    if (threads_ == 0)
    {
        threads_ = 1;
    }

    workers_.clear();
    workers_.reserve(threads_);
    for (size_t i = 0; i < threads_; ++i)
    {
        workers_.emplace_back(&FecExecutor::workerMain, this);
    }

    return true;
}

void FecExecutor::stop()
{
    if (!running_.exchange(false))
    {
        return;
    }

    queue_cv_.notify_all();
    for (auto &t : workers_)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    workers_.clear();

    std::lock_guard<std::mutex> lk(queue_mutex_);
    while (!queue_.empty())
    {
        queue_.pop();
    }
}

void FecExecutor::enqueue(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lk(queue_mutex_);
        queue_.push(std::move(task));
    }
    queue_cv_.notify_one();
}

void FecExecutor::workerMain()
{
    while (running_.load())
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lk(queue_mutex_);
            queue_cv_.wait(lk, [&]()
                           { return !queue_.empty() || !running_.load(); });
            if (!running_.load())
            {
                break;
            }
            task = std::move(queue_.front());
            queue_.pop();
        }
        if (task)
        {
            task();
        }
    }
}

} // namespace trb::udp
