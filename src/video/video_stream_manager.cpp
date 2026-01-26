#include "video/video_stream_manager.hpp"

#include <algorithm>
#include <chrono>

#include <ros/ros.h>

namespace trb::video
{

VideoStreamManager::VideoStreamManager(VideoStreamConfig config)
    : config_(std::move(config)),
      capturer_({config_.device,
                 config_.profile.width,
                 config_.profile.height,
                 config_.profile.fps,
                 config_.pixel_format,
                                 config_.v4l2_buffer_count}),
            decoder_({config_.profile.width,
                                config_.profile.height,
                                config_.decoder_pool_size,
                                config_.decoder_out_layout}),
            encoder_(config_.encoder)
{
}

VideoStreamManager::~VideoStreamManager()
{
    stop();
}

bool VideoStreamManager::start()
{
    if (running_.exchange(true))
    {
        return true;
    }

    if (!capturer_.start())
    {
        ROS_ERROR("VideoStreamManager: V4L2 capturer start failed");
        running_.store(false);
        return false;
    }

    if (!decoder_.start())
    {
        ROS_ERROR("VideoStreamManager: decoder start failed");
        capturer_.stop();
        running_.store(false);
        return false;
    }

    if (!encoder_.start())
    {
        ROS_ERROR("VideoStreamManager: encoder start failed");
        decoder_.stop();
        capturer_.stop();
        running_.store(false);
        return false;
    }

    capture_thread_ = std::thread(&VideoStreamManager::captureThreadMain, this);
    pipeline_thread_ = std::thread(&VideoStreamManager::pipelineThreadMain, this);
    ROS_INFO("VideoStreamManager started");
    return true;
}

void VideoStreamManager::stop()
{
    if (!running_.exchange(false))
    {
        return;
    }

    frame_cv_.notify_all();

    if (capture_thread_.joinable())
    {
        capture_thread_.join();
    }

    if (pipeline_thread_.joinable())
    {
        pipeline_thread_.join();
    }

    capturer_.stop();
    decoder_.stop();
    encoder_.stop();
    ROS_INFO("VideoStreamManager stopped");
}

void VideoStreamManager::setEncodedFrameCallback(EncodedFrameCallback cb)
{
    encoded_frame_cb_ = std::move(cb);
}

bool VideoStreamManager::isRunning() const
{
    return running_.load();
}

void VideoStreamManager::captureThreadMain()
{
    while (running_.load())
    {
        V4L2Frame frame;
        if (!capturer_.dequeue(frame))
        {
            continue;
        }

        if (!frame.data || frame.bytes_used == 0)
        {
            capturer_.requeue(frame.index);
            continue;
        }

        Frame out;
        out.data.assign(frame.data, frame.data + frame.bytes_used);
        out.timestamp_us = frame.timestamp_us;

        capturer_.requeue(frame.index);

        {
            std::lock_guard<std::mutex> lk(frame_mutex_);
            latest_frame_ = std::move(out);
        }
        frame_cv_.notify_one();
    }
}

void VideoStreamManager::pipelineThreadMain()
{
    uint64_t attempt_counter = 0;
    uint64_t decode_ok = 0;
    uint64_t encode_ok = 0;
    uint64_t decode_fail = 0;
    uint64_t encode_fail = 0;
    double decode_total_ms = 0.0;
    double encode_total_ms = 0.0;

    auto logStatsIfNeeded = [&]()
    {
        if (attempt_counter == 0 || (attempt_counter % 30) != 0)
        {
            return;
        }
        const double decode_avg = decode_ok > 0 ? (decode_total_ms / static_cast<double>(decode_ok)) : 0.0;
        const double encode_avg = encode_ok > 0 ? (encode_total_ms / static_cast<double>(encode_ok)) : 0.0;
        ROS_INFO("Video pipeline stats: attempts=%lu decode_ok=%lu decode_fail=%lu encode_ok=%lu encode_fail=%lu decode_avg=%.2fms encode_avg=%.2fms",
                 static_cast<unsigned long>(attempt_counter),
                 static_cast<unsigned long>(decode_ok),
                 static_cast<unsigned long>(decode_fail),
                 static_cast<unsigned long>(encode_ok),
                 static_cast<unsigned long>(encode_fail),
                 decode_avg,
                 encode_avg);
        decode_total_ms = 0.0;
        encode_total_ms = 0.0;
        decode_ok = 0;
        encode_ok = 0;
        decode_fail = 0;
        encode_fail = 0;
    };

    while (running_.load())
    {
        std::optional<Frame> frame;
        {
            std::unique_lock<std::mutex> lk(frame_mutex_);
            frame_cv_.wait_for(lk, std::chrono::milliseconds(50), [this]
                               { return !running_.load() || latest_frame_.has_value(); });
            if (!running_.load())
            {
                break;
            }
            if (latest_frame_)
            {
                frame = std::move(latest_frame_);
                latest_frame_.reset();
            }
        }

        if (!frame)
        {
            continue;
        }

        ++attempt_counter;

        DecodedFrame decoded;
        const auto decode_start = std::chrono::steady_clock::now();
        if (!decoder_.decode(frame->data.data(), frame->data.size(), frame->timestamp_us, decoded))
        {
            ++decode_fail;
            logStatsIfNeeded();
            continue;
        }
        const auto decode_end = std::chrono::steady_clock::now();
        const double decode_ms = std::chrono::duration_cast<std::chrono::microseconds>(decode_end - decode_start).count() / 1000.0;
        ++decode_ok;

        EncodedFrame encoded;
        const auto encode_start = std::chrono::steady_clock::now();
        const bool encoded_ok = encoder_.encode(decoded.fd, decoded.timestamp_us, encoded);
        const auto encode_end = std::chrono::steady_clock::now();
        const double encode_ms = std::chrono::duration_cast<std::chrono::microseconds>(encode_end - encode_start).count() / 1000.0;
        decoder_.releaseFd(decoded.fd);

        if (!encoded_ok)
        {
            ++encode_fail;
            logStatsIfNeeded();
            continue;
        }

        ++encode_ok;
        decode_total_ms += decode_ms;
        encode_total_ms += encode_ms;

        logStatsIfNeeded();

        if (encoded_frame_cb_)
        {
            encoded_frame_cb_(encoded.data.data(), encoded.data.size(), encoded.timestamp_us, encoded.keyframe);
        }
    }
}

} // namespace trb::video
