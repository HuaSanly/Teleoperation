#include "video/video_stream_manager.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cctype>
#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#include <linux/v4l2-controls.h>
#include <linux/videodev2.h>

#include "video/video_converter.hpp"
#include "video/video_encoder.hpp"
#include "video/video_recorder.hpp"
#include "video/video_v4l2_capturer.hpp"

namespace trb::video
{

    class VideoStreamManager::Impl
    {
    public:
        explicit Impl(rclcpp::Node &node)
            : node_(node), logger_(node.get_logger())
        {
        }

        ~Impl()
        {
            stop();
        }

        void setEncodedFrameCallback(EncodedFrameCallback callback)
        {
            std::lock_guard<std::mutex> lk(callback_mutex_);
            encoded_frame_callback_ = callback;
        }

        void setTargetBitrate(uint32_t bitrate_bps)
        {
            if (bitrate_bps == 0)
            {
                return;
            }

            const auto now = std::chrono::steady_clock::now();
            {
                std::lock_guard<std::mutex> lk(bitrate_mutex_);
                const auto elapsed = now - last_bitrate_update_;
                if (last_bitrate_bps_ == bitrate_bps && elapsed < std::chrono::milliseconds(200))
                {
                    return;
                }
                if (elapsed < std::chrono::milliseconds(100))
                {
                    return;
                }
                last_bitrate_update_ = now;
                last_bitrate_bps_ = bitrate_bps;
            }

            if (encoder_)
            {
                const bool ok = encoder_->setBitrate(bitrate_bps);
                if (!ok)
                {
                    RCLCPP_WARN(logger_, "VideoEncoder setBitrate failed: %u bps", bitrate_bps);
                }
            }
        }

        bool start()
        {
            if (running_.load())
                return true;

            capturer_ = std::make_shared<trb::video::VideoV4L2Capturer>();
            recorder_ = std::make_shared<trb::video::VideoRecorder>(logger_);

            // Unified profile: [width, height, framerate]
            const std::vector<int64_t> profile = node_.declare_parameter<std::vector<int64_t>>("video.profile", {3840, 1520, 30});
            uint32_t width = 3840;
            uint32_t height = 1520;
            uint32_t framerate = 30;
            if (profile.size() == 3 && profile[0] > 0 && profile[1] > 0 && profile[2] > 0)
            {
                width = static_cast<uint32_t>(profile[0]);
                height = static_cast<uint32_t>(profile[1]);
                framerate = static_cast<uint32_t>(profile[2]);
            }
            else
            {
                RCLCPP_WARN(logger_, "Invalid video.profile; expected [width,height,framerate]. Using defaults.");
            }

            const std::string video_device = node_.declare_parameter<std::string>("video.device", "/dev/video0");
            const std::string pixel_format_str = node_.declare_parameter<std::string>("video.pixel_format", "mjpeg");
            const int64_t v4l2_buffer_count_param = node_.declare_parameter<int64_t>("video.v4l2.buffer_count", 8);
            const uint32_t v4l2_buffer_count = (v4l2_buffer_count_param > 0) ? static_cast<uint32_t>(v4l2_buffer_count_param) : 8;

            const int64_t conv_pool_param = node_.declare_parameter<int64_t>("video.converter.buffer_pool_size", 12);
            const uint32_t conv_pool_size = (conv_pool_param > 0) ? static_cast<uint32_t>(conv_pool_param) : 12;

            // Recording parameters
            const bool enable_recording = node_.declare_parameter<bool>("video.recording.enabled", false);
            const std::string recording_output_dir = node_.declare_parameter<std::string>("video.recording.output_dir", "");

            trb::video::VideoRecorder::Config rec_config;
            rec_config.enabled = enable_recording;
            rec_config.output_dir = recording_output_dir;
            recorder_->initialize(rec_config);

            trb::video::VideoV4L2Capturer::Config cap_cfg;
            cap_cfg.width = width;
            cap_cfg.height = height;
            cap_cfg.framerate = framerate;
            cap_cfg.device_path = video_device;
            cap_cfg.buffer_count = v4l2_buffer_count;

            // Pixel format mapping
            std::string fmt = pixel_format_str;
            std::transform(fmt.begin(), fmt.end(), fmt.begin(), [](unsigned char c)
                           { return static_cast<char>(std::tolower(c)); });
            if (fmt == "mjpeg" || fmt == "mjpg")
            {
                cap_cfg.pixel_format = V4L2_PIX_FMT_MJPEG;
            }
            else if (fmt == "yuyv" || fmt == "yuy2")
            {
                cap_cfg.pixel_format = V4L2_PIX_FMT_YUYV;
            }
            else
            {
                RCLCPP_WARN(logger_, "Unknown video.pixel_format='%s', falling back to mjpeg", pixel_format_str.c_str());
                cap_cfg.pixel_format = V4L2_PIX_FMT_MJPEG;
            }

            if (!capturer_->initialize(cap_cfg))
            {
                RCLCPP_ERROR(logger_, "Failed to initialize V4L2 capturer");
                return false;
            }

            // Use negotiated device format for downstream
            const uint32_t actual_w = capturer_->width();
            const uint32_t actual_h = capturer_->height();
            if (actual_w > 0 && actual_h > 0 && (actual_w != width || actual_h != height))
            {
                RCLCPP_WARN(logger_,
                            "V4L2 negotiated format differs from requested: requested=%ux%u, actual=%ux%u. Using actual for converter/encoder.",
                            width, height, actual_w, actual_h);
                width = actual_w;
                height = actual_h;
            }

            if (!capturer_->start())
            {
                RCLCPP_ERROR(logger_, "Failed to start V4L2 capturer");
            }
            else
            {
                RCLCPP_INFO(logger_, "V4L2 capturer started");
            }

            // Configure Converter (MJPEG -> NV12 dmabuf)
            converter_ = std::make_shared<trb::video::VideoConverter>();
            trb::video::VideoConverter::Config conv_cfg;
            conv_cfg.width = width;
            conv_cfg.height = height;
            conv_cfg.buffer_pool_size = conv_pool_size;

            auto parse_layout = [](const std::string &v) -> int32_t
            {
                std::string s = v;
                std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                               { return static_cast<char>(std::tolower(c)); });
                if (s == "block" || s == "blocklinear" || s == "block-linear")
                    return 1;
                return 0;
            };

            // Converter surface layout
            const std::string conv_dec_layout = node_.declare_parameter<std::string>("video.converter.dec_layout", "__unset__");
            const std::string conv_out_layout = node_.declare_parameter<std::string>("video.converter.out_layout", "__unset__");
            const std::string conv_layout_legacy = node_.declare_parameter<std::string>("video.converter.layout", "__unset__");

            if (conv_dec_layout != "__unset__")
            {
                conv_cfg.decode_surface_layout = parse_layout(conv_dec_layout);
            }
            else if (conv_layout_legacy != "__unset__")
            {
                conv_cfg.decode_surface_layout = parse_layout(conv_layout_legacy);
            }

            if (conv_out_layout != "__unset__")
            {
                conv_cfg.output_surface_layout = parse_layout(conv_out_layout);
            }
            else
            {
                // Default to pitch for encoder-facing output unless explicitly overridden.
                conv_cfg.output_surface_layout = 0;
            }

            // Converter compute device (Jetson): default|vic|gpu
            const std::string conv_compute = node_.declare_parameter<std::string>("video.converter.compute", "default");
            {
                std::string s = conv_compute;
                std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                               { return static_cast<char>(std::tolower(c)); });
                if (s == "gpu")
                    conv_cfg.transform_compute_mode = 1;
                else if (s == "vic")
                    conv_cfg.transform_compute_mode = 2;
                else
                    conv_cfg.transform_compute_mode = 0;
            }

            if (!converter_->initialize(conv_cfg))
            {
                RCLCPP_WARN(logger_, "VideoConverter initialize failed (Jetson MM API missing?), decode will be skipped");
            }
            else
            {
                // Initialize Encoder
                encoder_ = std::make_shared<trb::video::VideoEncoder>();
                trb::video::VideoEncoder::Config enc_cfg;
                enc_cfg.width = width;
                enc_cfg.height = height;
                enc_cfg.framerate = framerate;
                enc_cfg.bitrate = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.bitrate", 20000000));
                enc_cfg.idr_interval = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.idr_interval", 30));
                enc_cfg.idr_interval_gops = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.idr_interval_gops", 1));
                enc_cfg.force_idr_every_n = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.force_idr_every_n", 0));

                // Intra refresh ("I-frame smoothing").
                // Implemented via NvVideoEncoder::setSliceIntrarefresh(interval_slices).
                const bool intra_refresh_enabled = node_.declare_parameter<bool>("video.encoder.intra_refresh.enabled", false);
                const int64_t intra_refresh_interval_slices_param = node_.declare_parameter<int64_t>("video.encoder.intra_refresh.interval_slices", 0);
                if (intra_refresh_enabled)
                {
                    const uint32_t interval_slices = (intra_refresh_interval_slices_param > 0)
                                                         ? static_cast<uint32_t>(intra_refresh_interval_slices_param)
                                                         : 1u;
                    enc_cfg.slice_intra_refresh_interval_slices = interval_slices;
                }
                else
                {
                    enc_cfg.slice_intra_refresh_interval_slices = 0;
                }

                // Low-frequency IDR (recommended when intra refresh is enabled):
                // keep a periodic IDR as a clean recovery / join point.
                const bool low_freq_idr_enabled = node_.declare_parameter<bool>("video.encoder.low_freq_idr.enabled", false);
                const int64_t low_freq_idr_interval_sec = node_.declare_parameter<int64_t>("video.encoder.low_freq_idr.interval_sec", 2);
                if (low_freq_idr_enabled && low_freq_idr_interval_sec > 0)
                {
                    const uint64_t frames_u64 = static_cast<uint64_t>(low_freq_idr_interval_sec) * static_cast<uint64_t>(framerate);
                    const uint32_t frames = static_cast<uint32_t>(std::max<uint64_t>(1, frames_u64));

                    // Make every I-frame an IDR, but only at low frequency.
                    enc_cfg.idr_interval = frames;      // I-frame interval (GOP size)
                    enc_cfg.idr_interval_gops = frames; // IDR interval (frames)

                    // Avoid forcing extra IDRs unless explicitly configured.
                    // (If user sets force_idr_every_n in config, we keep it.)
                }
                enc_cfg.qp_range_i_min = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.qp_range_i_min", enc_cfg.qp_range_i_min));
                enc_cfg.qp_range_i_max = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.qp_range_i_max", enc_cfg.qp_range_i_max));
                enc_cfg.qp_range_p_min = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.qp_range_p_min", enc_cfg.qp_range_p_min));
                enc_cfg.qp_range_p_max = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.qp_range_p_max", enc_cfg.qp_range_p_max));
                enc_cfg.output_plane_buffers = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.output_plane_buffers", enc_cfg.output_plane_buffers));
                enc_cfg.capture_plane_buffers = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.capture_plane_buffers", enc_cfg.capture_plane_buffers));

                enc_cfg.max_perf_mode = node_.declare_parameter<bool>("video.encoder.max_perf_mode", false);

                const std::string hw_preset_str = node_.declare_parameter<std::string>("video.encoder.hw_preset", "");
                {
                    std::string s = hw_preset_str;
                    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                                   { return static_cast<char>(std::tolower(c)); });
                    if (s.empty() || s == "default")
                    {
                        enc_cfg.hw_preset_type = -1;
                    }
                    else if (s == "ultrafast")
                    {
                        enc_cfg.hw_preset_type = static_cast<int32_t>(V4L2_ENC_HW_PRESET_ULTRAFAST);
                    }
                    else if (s == "fast")
                    {
                        enc_cfg.hw_preset_type = static_cast<int32_t>(V4L2_ENC_HW_PRESET_FAST);
                    }
                    else if (s == "medium")
                    {
                        enc_cfg.hw_preset_type = static_cast<int32_t>(V4L2_ENC_HW_PRESET_MEDIUM);
                    }
                    else if (s == "slow")
                    {
                        enc_cfg.hw_preset_type = static_cast<int32_t>(V4L2_ENC_HW_PRESET_SLOW);
                    }
                    else if (s == "disable")
                    {
                        enc_cfg.hw_preset_type = static_cast<int32_t>(V4L2_ENC_HW_PRESET_DISABLE);
                    }
                    else
                    {
                        RCLCPP_WARN(logger_, "Unknown video.encoder.hw_preset='%s' (use: ultrafast|fast|medium|slow|disable|default). Ignoring.", hw_preset_str.c_str());
                        enc_cfg.hw_preset_type = -1;
                    }
                }

                const std::string rc_str = node_.declare_parameter<std::string>("video.encoder.rate_control", "");
                {
                    std::string s = rc_str;
                    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                                   { return static_cast<char>(std::tolower(c)); });
                    if (s.empty() || s == "default")
                    {
                        enc_cfg.rate_control_mode = -1;
                    }
                    else if (s == "cbr")
                    {
                        enc_cfg.rate_control_mode = static_cast<int32_t>(V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);
                    }
                    else if (s == "vbr")
                    {
                        enc_cfg.rate_control_mode = static_cast<int32_t>(V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
                    }
                    else if (s == "cq")
                    {
                        enc_cfg.rate_control_mode = static_cast<int32_t>(V4L2_MPEG_VIDEO_BITRATE_MODE_CQ);
                    }
                    else
                    {
                        RCLCPP_WARN(logger_, "Unknown video.encoder.rate_control='%s' (use: cbr|vbr|cq|default). Ignoring.", rc_str.c_str());
                        enc_cfg.rate_control_mode = -1;
                    }
                }

                enc_cfg.peak_bitrate = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.peak_bitrate", 0));
                enc_cfg.virtual_buffer_size = static_cast<uint32_t>(node_.declare_parameter<int64_t>("video.encoder.virtual_buffer_size", 0));
                enc_cfg.num_reference_frames = static_cast<int32_t>(node_.declare_parameter<int64_t>("video.encoder.num_reference_frames", -1));
                enc_cfg.num_b_frames = static_cast<int32_t>(node_.declare_parameter<int64_t>("video.encoder.num_b_frames", -1));
                enc_cfg.insert_sps_pps_at_idr = static_cast<int32_t>(node_.declare_parameter<int64_t>("video.encoder.insert_sps_pps_at_idr", -1));

                if (!encoder_->initialize(enc_cfg))
                {
                    RCLCPP_WARN(logger_, "VideoEncoder initialize failed");
                }
                else
                {
                    // Release converter buffers when the encoder is done consuming them.
                    encoder_->setInputDoneCallback(std::bind(&Impl::onEncoderInputDone, this, std::placeholders::_1));
                    encoder_->setCallback(std::bind(&Impl::onEncoderPacket, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
                }

                // Set Converter Callback (Output of conversion)
                converter_->setCallback(std::bind(&Impl::onConverterOutput, this, std::placeholders::_1, std::placeholders::_2));
            }

            running_.store(true);

            // Capture thread: DQBUF as fast as possible. Keep only the latest dequeued buffer.
            capture_thread_ = std::thread(&Impl::captureThreadMain, this);

            // Pipeline thread: convert + encode. Requeue the V4L2 buffer immediately after MJPEG decode completes.
            pipeline_thread_ = std::thread(&Impl::pipelineThreadMain, this);

            return true;
        }

        void stop()
        {
            const bool was_running = running_.exchange(false);
            if (!was_running)
                return;

            latest_cv_.notify_all();

            if (capture_thread_.joinable())
                capture_thread_.join();
            if (pipeline_thread_.joinable())
                pipeline_thread_.join();

            // If a frame is still dequeued, requeue it before shutting down the device.
            if (capturer_)
            {
                std::lock_guard<std::mutex> lk(latest_mutex_);
                if (latest_valid_)
                {
                    (void)capturer_->requeue(latest_frame_.v4l2_buf);
                    latest_valid_ = false;
                }
                capturer_->stop();
            }

            encoder_.reset();
            converter_.reset();
            recorder_.reset();
            capturer_.reset();

            {
                std::lock_guard<std::mutex> lk(enc_timing_mutex_);
                enc_start_steady_us_by_ts_.clear();
            }

            latest_valid_ = false;
        }

        bool isRunning() const
        {
            return running_.load();
        }

    private:
        void onEncoderInputDone(int dmabuf_fd)
        {
            if (converter_)
                converter_->releaseFd(dmabuf_fd);
        }

        void onEncoderPacket(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)
        {
            const uint64_t count = enc_frame_count_.fetch_add(1) + 1;

            const auto now_tp = std::chrono::steady_clock::now();
            const int64_t now_us = std::chrono::duration_cast<std::chrono::microseconds>(now_tp.time_since_epoch()).count();
            const int64_t chain_latency_us = now_us - static_cast<int64_t>(timestamp_us);

            int64_t cost_us = -1;
            {
                std::lock_guard<std::mutex> lk(enc_timing_mutex_);
                auto it = enc_start_steady_us_by_ts_.find(timestamp_us);
                if (it != enc_start_steady_us_by_ts_.end())
                {
                    cost_us = now_us - it->second;
                    enc_start_steady_us_by_ts_.erase(it);
                }
            }

            if (count <= 5 || (count % 30 == 0))
            {
                RCLCPP_INFO(logger_, "Encoder output: size=%zu bytes, cost=%" PRId64 " us, chain_latency=%" PRId64 " us",
                            size, cost_us, chain_latency_us);
            }

            if (recorder_)
            {
                recorder_->writeFrame(count, data, size, keyframe);
            }

            // TODO: Send to WebRTC/gRPC
            {
                std::lock_guard<std::mutex> lk(callback_mutex_);
                if (encoded_frame_callback_)
                {
                    encoded_frame_callback_(data, size, timestamp_us, keyframe);
                }
            }
        }

        bool onConverterOutput(int dmabuf_fd, uint64_t timestamp_us)
        {
            if (encoder_)
            {
                // Returning true transfers buffer ownership to the encoder,
                // which will release it via setInputDoneCallback().
                const auto enc_t0 = std::chrono::steady_clock::now();
                const int64_t enc_t0_us = std::chrono::duration_cast<std::chrono::microseconds>(enc_t0.time_since_epoch()).count();
                {
                    std::lock_guard<std::mutex> lk(enc_timing_mutex_);
                    enc_start_steady_us_by_ts_[timestamp_us] = enc_t0_us;
                }

                const bool result = encoder_->encodeFrame(dmabuf_fd, timestamp_us);
                if (!result)
                {
                    std::lock_guard<std::mutex> lk(enc_timing_mutex_);
                    enc_start_steady_us_by_ts_.erase(timestamp_us);
                }
                return result;
            }
            return false;
        }

        void captureThreadMain()
        {
            while (running_.load())
            {
                trb::video::VideoV4L2Capturer::Frame frame;
                if (!capturer_ || !capturer_->dequeue(frame, 1000))
                {
                    continue;
                }

                // Drop policy: if a previous frame is pending processing, requeue it and replace with the new one.
                {
                    std::lock_guard<std::mutex> lk(latest_mutex_);
                    if (latest_valid_ && capturer_)
                    {
                        (void)capturer_->requeue(latest_frame_.v4l2_buf);
                        latest_valid_ = false;
                    }
                    latest_frame_ = frame;
                    latest_valid_ = true;
                }
                latest_cv_.notify_one();
            }
        }

        void pipelineThreadMain()
        {
            while (running_.load())
            {
                trb::video::VideoV4L2Capturer::Frame frame;
                {
                    std::unique_lock<std::mutex> lk(latest_mutex_);
                    latest_cv_.wait(lk, [this]
                                    { return !running_.load() || latest_valid_; });
                    if (!running_.load())
                        break;
                    frame = latest_frame_;
                    latest_valid_ = false;
                }

                // Timestamp sanity (keep same behavior as before)
                auto now = std::chrono::steady_clock::now();
                auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
                int64_t latency = now_us - static_cast<int64_t>(frame.timestamp_us);
                if (std::abs(latency) > 3600000000LL)
                {
                    frame.timestamp_us = now_us;
                    latency = 0;
                }

                const uint64_t frame_id = video_frame_count_.fetch_add(1) + 1;
                if (frame_id <= 5 || (frame_id % 30 == 0))
                {
                    RCLCPP_INFO(logger_, "MJPEG frame #%" PRIu64 ": size=%zu bytes, latency=%" PRId64 " us", frame_id, frame.size, latency);
                }

                if (converter_)
                {
                    const auto conv_t0 = std::chrono::steady_clock::now();
                    converter_->processFrame(frame.data, frame.size, frame.timestamp_us);
                    const auto conv_t1 = std::chrono::steady_clock::now();

                    if (frame_id <= 5 || (frame_id % 30 == 0))
                    {
                        const int64_t conv_cost_us = std::chrono::duration_cast<std::chrono::microseconds>(conv_t1 - conv_t0).count();
                        const int64_t conv_done_us = std::chrono::duration_cast<std::chrono::microseconds>(conv_t1.time_since_epoch()).count();
                        const int64_t chain_to_conv_done_us = conv_done_us - static_cast<int64_t>(frame.timestamp_us);
                        RCLCPP_INFO(logger_, "Converter stage: cost=%" PRId64 " us, chain_latency=%" PRId64 " us", conv_cost_us, chain_to_conv_done_us);
                    }
                }

                if (capturer_)
                {
                    (void)capturer_->requeue(frame.v4l2_buf);
                }
            }
        }

    private:
        rclcpp::Node &node_;
        rclcpp::Logger logger_;

        std::shared_ptr<trb::video::VideoV4L2Capturer> capturer_;
        std::shared_ptr<trb::video::VideoConverter> converter_;
        std::shared_ptr<trb::video::VideoEncoder> encoder_;
        std::shared_ptr<trb::video::VideoRecorder> recorder_;

        std::atomic<uint64_t> video_frame_count_{0};
        std::atomic<uint64_t> conv_frame_count_{0};
        std::atomic<uint64_t> enc_frame_count_{0};

        std::mutex enc_timing_mutex_;
        std::unordered_map<uint64_t, int64_t> enc_start_steady_us_by_ts_;

        std::atomic<bool> running_{false};
        std::thread capture_thread_;
        std::thread pipeline_thread_;

        std::mutex latest_mutex_;
        std::condition_variable latest_cv_;
        bool latest_valid_ = false;
        trb::video::VideoV4L2Capturer::Frame latest_frame_;

        std::mutex callback_mutex_;
        EncodedFrameCallback encoded_frame_callback_;

        std::mutex bitrate_mutex_;
        uint32_t last_bitrate_bps_{0};
        std::chrono::steady_clock::time_point last_bitrate_update_{std::chrono::steady_clock::time_point::min()};
    };

    VideoStreamManager::VideoStreamManager(rclcpp::Node &node)
        : impl_(std::make_unique<Impl>(node))
    {
    }

    VideoStreamManager::~VideoStreamManager() = default;

    bool VideoStreamManager::start()
    {
        return impl_->start();
    }

    void VideoStreamManager::stop()
    {
        impl_->stop();
    }

    bool VideoStreamManager::isRunning() const
    {
        return impl_->isRunning();
    }

    void VideoStreamManager::setEncodedFrameCallback(EncodedFrameCallback callback)
    {
        impl_->setEncodedFrameCallback(callback);
    }

    void VideoStreamManager::setTargetBitrate(uint32_t bitrate_bps)
    {
        impl_->setTargetBitrate(bitrate_bps);
    }

} // namespace trb::video
