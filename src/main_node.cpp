#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cinttypes>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <vector>
#include <functional>
#include <unordered_map>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "main_node.hpp"
#include "utils/teleop_logger.hpp"
#include "udp/scream_controller_ericsson.hpp"
#include "video/video_v4l2_capturer.hpp"

#include <linux/videodev2.h>

namespace trb
{

    namespace
    {
        enum class H264StreamFormat
        {
            AnnexB,
            Avcc,
            Unknown,
        };

        static bool hasAnnexBStartCode(const uint8_t *data, size_t size)
        {
            if (!data || size < 4)
            {
                return false;
            }
            for (size_t i = 0; i + 3 < size; ++i)
            {
                if (data[i] == 0x00 && data[i + 1] == 0x00 && data[i + 2] == 0x01)
                {
                    return true;
                }
                if (i + 4 < size && data[i] == 0x00 && data[i + 1] == 0x00 && data[i + 2] == 0x00 && data[i + 3] == 0x01)
                {
                    return true;
                }
            }
            return false;
        }

        static bool looksLikeAvcc(const uint8_t *data, size_t size)
        {
            if (!data || size < 8)
            {
                return false;
            }
            size_t off = 0;
            int nal_count = 0;
            while (off + 4 <= size && nal_count < 3)
            {
                const uint32_t n = (static_cast<uint32_t>(data[off]) << 24) |
                                   (static_cast<uint32_t>(data[off + 1]) << 16) |
                                   (static_cast<uint32_t>(data[off + 2]) << 8) |
                                   (static_cast<uint32_t>(data[off + 3]));
                off += 4;
                if (n == 0 || off + n > size)
                {
                    return false;
                }
                if (n < 1)
                {
                    return false;
                }
                off += n;
                ++nal_count;
            }
            return nal_count > 0;
        }

        static H264StreamFormat detectH264Format(const uint8_t *data, size_t size)
        {
            if (hasAnnexBStartCode(data, size))
            {
                return H264StreamFormat::AnnexB;
            }
            if (looksLikeAvcc(data, size))
            {
                return H264StreamFormat::Avcc;
            }
            return H264StreamFormat::Unknown;
        }

        template <typename Fn>
        static void forEachNal(const uint8_t *data, size_t size, H264StreamFormat fmt, Fn &&fn)
        {
            if (!data || size < 1)
            {
                return;
            }

            if (fmt == H264StreamFormat::AnnexB)
            {
                auto is_start_code = [&](size_t i, size_t &sc_len) -> bool
                {
                    if (i + 3 <= size && data[i] == 0x00 && data[i + 1] == 0x00 && data[i + 2] == 0x01)
                    {
                        sc_len = 3;
                        return true;
                    }
                    if (i + 4 <= size && data[i] == 0x00 && data[i + 1] == 0x00 && data[i + 2] == 0x00 && data[i + 3] == 0x01)
                    {
                        sc_len = 4;
                        return true;
                    }
                    return false;
                };

                size_t i = 0;
                while (i + 3 < size)
                {
                    size_t sc_len = 0;
                    if (!is_start_code(i, sc_len))
                    {
                        ++i;
                        continue;
                    }
                    i += sc_len;
                    const size_t nal_start = i;

                    while (i + 3 < size)
                    {
                        size_t next_sc = 0;
                        if (is_start_code(i, next_sc))
                        {
                            break;
                        }
                        ++i;
                    }

                    const size_t nal_end = i;
                    if (nal_end > nal_start)
                    {
                        fn(data + nal_start, nal_end - nal_start);
                    }
                }
            }
            else if (fmt == H264StreamFormat::Avcc)
            {
                size_t off = 0;
                while (off + 4 <= size)
                {
                    const uint32_t n = (static_cast<uint32_t>(data[off]) << 24) |
                                       (static_cast<uint32_t>(data[off + 1]) << 16) |
                                       (static_cast<uint32_t>(data[off + 2]) << 8) |
                                       (static_cast<uint32_t>(data[off + 3]));
                    off += 4;
                    if (n == 0 || off + n > size)
                    {
                        break;
                    }
                    fn(data + off, n);
                    off += n;
                }
            }
        }
    }

    MainNode::MainNode() : Node("main_node")
    {
        if (!selfCheckCamera())
        {
            RCLCPP_ERROR(this->get_logger(), "Camera self-check failed. Skip gRPC registration and streaming startup.");
            return;
        }

        this->initGrpc();
        if (this->signaling_client_->connect() != 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to connect gRPC signaling server");
            return;
        }
        if (this->signaling_client_->registerRobot() != 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to register to gRPC signaling server");
            return;
        }

        bool paired_ok = false;
        if (pair_mode_ == "active")
        {
            paired_ok = runActivePairing();
        }
        else
        {
            paired_ok = waitForPairing();
        }

        if (!paired_ok)
        {
            RCLCPP_ERROR(this->get_logger(), "Pairing not completed. Skip UDP/video startup.");
            return;
        }

        this->initUdp();
        this->initPoseUdp();
        this->initVideo();

        if (this->udp_stream_manager_ && this->signaling_client_)
        {
            this->udp_stream_manager_->setSessionId(this->signaling_client_->sessionId());
        }
    }
    // -----------------thread handles------------------

    // ------------------init methods-------------------

    void MainNode::initVideo()
    {
        if (!video_stream_manager_)
        {
            video_stream_manager_ = std::make_unique<trb::video::VideoStreamManager>(*this);
        }

        video_stream_manager_->setEncodedFrameCallback(
            [this](const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)
            {
                if (!this->video_config_acked_.load(std::memory_order_relaxed))
                {
                    this->updateSpsPpsFromEncodedFrame(data, size);
                    return;
                }
                if (this->udp_stream_manager_)
                {
                    this->udp_stream_manager_->sendH264Frame(data, size, timestamp_us, keyframe);
                }
            });

        if (!video_stream_manager_->start())
        {
            RCLCPP_ERROR(this->get_logger(), "VideoStreamManager start failed");
        }
        else
        {
            startVideoConfigPublisher();
        }
    }

    void MainNode::initUdp()
    {
        std::string udp_ip = this->declare_parameter<std::string>("udp_ip", "192.168.3.2");
        int udp_port = this->declare_parameter<int>("udp_port", 7778);

        // Optional: unified logging file sink (selective topics).
        const bool log_file_enabled = this->declare_parameter<bool>("logging.file.enabled", false);
        const std::string log_file_path = this->declare_parameter<std::string>("logging.file.path", "/tmp/teleop_robot_bridge.log");
        const std::vector<std::string> log_file_topics = this->declare_parameter<std::vector<std::string>>("logging.file.topics", std::vector<std::string>{});
        const uint32_t log_topic_mask = trb::utils::TeleopLogger::fileTopicsFromStrings(log_file_topics, this->get_logger());
        trb::utils::TeleopLogger::instance().configureFileLogging(log_file_enabled, log_file_path, log_topic_mask);

        const bool stop_after_frames_enabled = this->declare_parameter<bool>("udp.stop_after_frames.enabled", false);
        const int stop_after_frames_max_frames_param = this->declare_parameter<int>("udp.stop_after_frames.max_frames", 0);
        const uint32_t stop_after_frames_max_frames = static_cast<uint32_t>(std::max(0, stop_after_frames_max_frames_param));

        const int header_log_max_packets_param = this->declare_parameter<int>("udp.header_log.max_packets", 8);
        const uint64_t header_log_max_packets = static_cast<uint64_t>(std::max(0, header_log_max_packets_param));

        // FEC (V2): selected by FecTableId only. Current sender supports only table_id=1.
        const bool fec_enabled = this->declare_parameter<bool>("udp.fec.enabled", true);
        const int fec_table_id_param = this->declare_parameter<int>("udp.fec.table_id", 1);

        uint8_t fec_table_id = static_cast<uint8_t>(fec_table_id_param & 0xFF);

        // Validate table_id.
        if (fec_enabled)
        {
            if (fec_table_id == 1)
            {
                RCLCPP_INFO(
                    this->get_logger(),
                    "FEC enabled: table_id=%u (V2 implicit grouping)",
                    static_cast<unsigned>(fec_table_id));
            }
            else
            {
                RCLCPP_WARN(
                    this->get_logger(),
                    "FEC enabled but unsupported table_id=%u; disabling FEC (only table_id=1 supported)",
                    static_cast<unsigned>(fec_table_id));
                fec_table_id = 0;
            }
        }
        else
        {
            fec_table_id = 0;
        }

        // UDP pacing (smooth sending) defaults.
        // If video.encoder.bitrate is available, use it to derive a reasonable on-wire pacing rate.
        int64_t encoder_bitrate_bps = 20000000;
        this->get_parameter_or("video.encoder.bitrate", encoder_bitrate_bps, encoder_bitrate_bps);

        double overhead = 1.0;
        if (fec_table_id != 0)
        {
            // Conservative overhead estimate for pacing: assume a worst-case redundancy.
            // Roughly 1.25x payload.
            overhead *= 1.25;
        }
        // Add header overhead (V2 header is 26 bytes over a 1200B payload).
        overhead *= ((1200.0 + 26.0) / 1200.0);
        // Small safety margin for variability.
        overhead *= 1.05;

        const uint64_t default_pacing_bps = static_cast<uint64_t>(std::llround(static_cast<double>(encoder_bitrate_bps) * overhead));
        const bool pacing_enabled = this->declare_parameter<bool>("udp.pacing.enabled", true);
        const int64_t pacing_bps = this->declare_parameter<int64_t>("udp.pacing.bps", static_cast<int64_t>(default_pacing_bps));
        const int pacing_queue_max_packets = this->declare_parameter<int>("udp.pacing.queue_max_packets", 1024);
        const int pacing_queue_max_bytes = this->declare_parameter<int>("udp.pacing.queue_max_bytes", 1024 * 1024);

        const bool udp_send_nonblocking = this->declare_parameter<bool>("udp.send.nonblocking", true);
        const int udp_send_sndbuf_bytes = this->declare_parameter<int>("udp.send.sndbuf_bytes", 0);

        udp_stream_manager_ = std::make_unique<trb::udp::UdpStreamManager>(udp_ip, udp_port);
        if (!udp_stream_manager_->start())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to start UDP stream manager");
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "UDP stream manager started on %s:%d", udp_ip.c_str(), udp_port);
        }

        if (udp_stream_manager_)
        {
            udp_stream_manager_->setPacingEnabled(pacing_enabled);
            udp_stream_manager_->setPacingRateBps(pacing_bps > 0 ? static_cast<uint64_t>(pacing_bps) : 0ULL);
            udp_stream_manager_->setQueueLimits(
                pacing_queue_max_packets > 0 ? static_cast<size_t>(pacing_queue_max_packets) : 0ULL,
                pacing_queue_max_bytes > 0 ? static_cast<size_t>(pacing_queue_max_bytes) : 0ULL);

            udp_stream_manager_->setSendNonBlocking(udp_send_nonblocking);
            if (udp_send_sndbuf_bytes > 0)
            {
                udp_stream_manager_->setSendBufferBytes(udp_send_sndbuf_bytes);
            }

            udp_stream_manager_->setStopAfterFramesMaxFrames(stop_after_frames_max_frames);
            udp_stream_manager_->setStopAfterFramesEnabled(stop_after_frames_enabled);

            udp_stream_manager_->setHeaderLogMaxPackets(header_log_max_packets);
        }

        if (udp_stream_manager_)
        {
            const bool scream_enabled = this->declare_parameter<bool>("udp.scream.enabled", false);
            const int64_t scream_fallback_bps = this->declare_parameter<int64_t>(
                "udp.scream.fallback_pacing_bps",
                pacing_bps > 0 ? pacing_bps : static_cast<int64_t>(0));
            const int64_t scream_min_pacing_bps = this->declare_parameter<int64_t>("udp.scream.min_pacing_bps", 0);
            const int64_t scream_max_pacing_bps = this->declare_parameter<int64_t>("udp.scream.max_pacing_bps", 0);
            const int64_t scream_min_target_bps = this->declare_parameter<int64_t>("udp.scream.min_target_bitrate_bps", 0);
            const int64_t scream_max_target_bps = this->declare_parameter<int64_t>("udp.scream.max_target_bitrate_bps", 0);

            std::unique_ptr<trb::udp::IScreamController> scream;
            if (scream_enabled)
            {
                scream = std::make_unique<trb::udp::ScreamControllerEricsson>();
            }
            else
            {
                scream.reset();
            }
            trb::udp::ScreamControllerConfig cfg;
            cfg.enabled = scream_enabled;
            cfg.fallback_pacing_bps = static_cast<uint64_t>(std::max<int64_t>(0, scream_fallback_bps));
            cfg.min_pacing_bps = static_cast<uint64_t>(std::max<int64_t>(0, scream_min_pacing_bps));
            cfg.max_pacing_bps = static_cast<uint64_t>(std::max<int64_t>(0, scream_max_pacing_bps));
            cfg.min_target_bitrate_bps = static_cast<uint64_t>(std::max<int64_t>(0, scream_min_target_bps));
            cfg.max_target_bitrate_bps = static_cast<uint64_t>(std::max<int64_t>(0, scream_max_target_bps));
            if (scream)
            {
                scream->setConfig(cfg);
                udp_stream_manager_->setScreamController(std::move(scream));
            }
            udp_stream_manager_->setScreamEnabled(scream_enabled);

            udp_stream_manager_->setTargetBitrateCallback(
                [this](uint64_t bps)
                {
                    if (this->video_stream_manager_)
                    {
                        this->video_stream_manager_->setTargetBitrate(static_cast<uint32_t>(bps));
                    }
                });
        }

        if (udp_stream_manager_)
        {
            udp_stream_manager_->setFecTableId(fec_table_id);
        }
    }

    void MainNode::initPoseUdp()
    {
        const bool enabled = this->declare_parameter<bool>("pose_udp.enabled", false);
        if (!enabled)
        {
            RCLCPP_INFO(this->get_logger(), "Pose UDP receiver disabled (pose_udp.enabled=false)");
            return;
        }

        if (!udp_stream_manager_)
        {
            RCLCPP_ERROR(this->get_logger(), "Pose UDP receiver enabled but udp_stream_manager_ is null");
            return;
        }

        trb::udp::PoseUdpReceiverConfig cfg;
        // NOTE: We reuse UdpStreamManager's socket/recv thread; these bind/timeout settings are kept
        // for backward compatibility with standalone mode, but are not used in shared-socket mode.
        cfg.bind_ip = this->declare_parameter<std::string>("pose_udp.bind_ip", cfg.bind_ip);
        cfg.bind_port = this->declare_parameter<int>("pose_udp.bind_port", cfg.bind_port);
        cfg.allowed_remote_ip = this->declare_parameter<std::string>("pose_udp.allowed_remote_ip", cfg.allowed_remote_ip);
        cfg.recv_timeout_ms = this->declare_parameter<int>("pose_udp.recv_timeout_ms", cfg.recv_timeout_ms);
        cfg.qos_depth = this->declare_parameter<int>("pose_udp.qos.depth", cfg.qos_depth);

        cfg.frame_id_hmd = this->declare_parameter<std::string>("pose_udp.frame_id.hmd", cfg.frame_id_hmd);
        cfg.frame_id_left_controller = this->declare_parameter<std::string>("pose_udp.frame_id.left_controller", cfg.frame_id_left_controller);
        cfg.frame_id_right_controller = this->declare_parameter<std::string>("pose_udp.frame_id.right_controller", cfg.frame_id_right_controller);
        cfg.frame_id_left_aim = this->declare_parameter<std::string>("pose_udp.frame_id.left_aim", cfg.frame_id_left_aim);
        cfg.frame_id_right_aim = this->declare_parameter<std::string>("pose_udp.frame_id.right_aim", cfg.frame_id_right_aim);

        cfg.publish_euler = this->declare_parameter<bool>("pose_udp.publish_euler", true);
        cfg.publish_buttons = this->declare_parameter<bool>("pose_udp.publish_buttons", true);
        cfg.publish_aim = this->declare_parameter<bool>("pose_udp.publish_aim", true);

        pose_udp_receiver_ = std::make_unique<trb::udp::PoseUdpReceiver>(*this, cfg);

        // Hook into the existing UDP receive loop.
        udp_stream_manager_->setPoseDatagramCallback(
            [this](const uint8_t *data, size_t size)
            {
                if (this->pose_udp_receiver_)
                {
                    this->pose_udp_receiver_->handleDatagram(data, size);
                }
            });

        RCLCPP_INFO(this->get_logger(), "Pose UDP receiver enabled (shared socket via UdpStreamManager)");
    }

    void MainNode::initGrpc()
    {
        // Get parameters
        std::string server_ip = this->declare_parameter<std::string>("server_ip", "127.0.0.1");
        int server_port = this->declare_parameter<int>("server_port", 8000);
        bool use_ssl = this->declare_parameter<bool>("use_ssl", false);
        std::string device_id = this->declare_parameter<std::string>("device_id", "robot_001");
        std::string token = this->declare_parameter<std::string>("token", "default_token");
        subscribe_vr_pose_flag_ = this->declare_parameter<bool>("subscribe_vr_pose_flag", false);

        // Pairing parameters
        pair_mode_ = this->declare_parameter<std::string>("pair.mode", "passive");
        {
            std::transform(pair_mode_.begin(), pair_mode_.end(), pair_mode_.begin(), [](unsigned char c)
                           { return static_cast<char>(std::tolower(c)); });
            if (pair_mode_ != "active" && pair_mode_ != "passive")
            {
                RCLCPP_WARN(this->get_logger(), "Invalid pair.mode='%s', falling back to 'passive'", pair_mode_.c_str());
                pair_mode_ = "passive";
            }
        }
        desired_peer_session_id_ = this->declare_parameter<std::string>("pair.peer_session_id", "");
        pair_auto_accept_ = this->declare_parameter<bool>("pair.auto_accept", true);
        pair_auto_request_ = this->declare_parameter<bool>("pair.auto_request", true);
        pair_list_unpaired_on_start_ = this->declare_parameter<bool>("pair.list_unpaired_on_start", false);

        RCLCPP_INFO(this->get_logger(), "Initializing SignalingClient with IP: %s, Port: %d, SSL: %s, DeviceID: %s",
                    server_ip.c_str(), server_port, use_ssl ? "true" : "false", device_id.c_str());

        // Initialize signaling client
        signaling_client_ = std::make_shared<SignalingClient>(
            this->get_logger(),
            server_ip,
            server_port,
            token,
            device_id,
            use_ssl);

        // Create heartbeat timer (1 second interval)
        heartbeat_timer_ = this->create_wall_timer(
            std::chrono::seconds(15),
            std::bind(&MainNode::heartbeatTimerCallback, this));

        // Start event stream
        signaling_client_->startEventStream(std::bind(&MainNode::onSignalingEvent, this, std::placeholders::_1));
    }

    bool MainNode::selfCheckCamera()
    {
        // Unified profile: [width, height, framerate]
        std::vector<int64_t> profile = {3840, 1520, 30};
        this->get_parameter_or("video.profile", profile, profile);
        uint32_t width = 3840;
        uint32_t height = 1520;
        uint32_t framerate = 30;
        if (profile.size() == 3 && profile[0] > 0 && profile[1] > 0 && profile[2] > 0)
        {
            width = static_cast<uint32_t>(profile[0]);
            height = static_cast<uint32_t>(profile[1]);
            framerate = static_cast<uint32_t>(profile[2]);
        }

        video_width_ = width;
        video_height_ = height;
        video_fps_ = framerate;

        std::string video_device = "/dev/video0";
        std::string pixel_format_str = "mjpeg";
        int64_t v4l2_buffer_count_param = 8;
        this->get_parameter_or("video.device", video_device, video_device);
        this->get_parameter_or("video.pixel_format", pixel_format_str, pixel_format_str);
        this->get_parameter_or("video.v4l2.buffer_count", v4l2_buffer_count_param, v4l2_buffer_count_param);
        const uint32_t v4l2_buffer_count = (v4l2_buffer_count_param > 0) ? static_cast<uint32_t>(v4l2_buffer_count_param) : 8;

        trb::video::VideoV4L2Capturer::Config cap_cfg;
        cap_cfg.width = width;
        cap_cfg.height = height;
        cap_cfg.framerate = framerate;
        cap_cfg.device_path = video_device;
        cap_cfg.buffer_count = v4l2_buffer_count;

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
            RCLCPP_WARN(this->get_logger(), "Unknown video.pixel_format='%s', falling back to mjpeg", pixel_format_str.c_str());
            cap_cfg.pixel_format = V4L2_PIX_FMT_MJPEG;
        }

        trb::video::VideoV4L2Capturer capturer;
        if (!capturer.initialize(cap_cfg))
        {
            RCLCPP_ERROR(this->get_logger(), "Camera self-check: failed to initialize V4L2 capturer (%s)", video_device.c_str());
            return false;
        }

        if (!capturer.start())
        {
            RCLCPP_ERROR(this->get_logger(), "Camera self-check: failed to start V4L2 capturer (%s)", video_device.c_str());
            return false;
        }

        bool got_frame = false;
        for (int i = 0; i < 3; ++i)
        {
            trb::video::VideoV4L2Capturer::Frame frame;
            if (capturer.dequeue(frame, 500))
            {
                capturer.requeue(frame.v4l2_buf);
                got_frame = true;
                break;
            }
        }

        capturer.stop();

        if (!got_frame)
        {
            RCLCPP_ERROR(this->get_logger(), "Camera self-check: no frame received from %s", video_device.c_str());
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "Camera self-check passed (%s)", video_device.c_str());
        }

        return got_frame;
    }

    bool MainNode::runActivePairing()
    {
        if (!signaling_client_)
        {
            return false;
        }

        if (!pair_auto_request_)
        {
            RCLCPP_WARN(this->get_logger(), "pair.auto_request is false; switching to passive wait");
            return waitForPairing();
        }

        while (rclcpp::ok())
        {
            auto list = signaling_client_->listUnpaired(signaling::RegisterRequest::VR);

            if (list.empty())
            {
                RCLCPP_WARN(this->get_logger(), "No unpaired VR endpoints found. Retrying in 2s...");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                continue;
            }

            std::cout << "\nUnpaired VR endpoints:" << std::endl;
            for (size_t i = 0; i < list.size(); ++i)
            {
                std::cout << "  [" << (i + 1) << "] session=" << list[i].session_id()
                          << " device=" << list[i].device_id() << std::endl;
            }
            std::cout << "Select index (1-" << list.size() << ", 0 to refresh): " << std::flush;

            std::string line;
            if (!std::getline(std::cin, line))
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to read selection from stdin");
                return false;
            }

            int choice = 0;
            try
            {
                choice = std::stoi(line);
            }
            catch (...)
            {
                RCLCPP_WARN(this->get_logger(), "Invalid input. Please enter a number.");
                continue;
            }

            if (choice == 0)
            {
                continue;
            }

            if (choice < 1 || static_cast<size_t>(choice) > list.size())
            {
                RCLCPP_WARN(this->get_logger(), "Invalid selection index: %d", choice);
                continue;
            }

            const auto &peer_session_id = list[static_cast<size_t>(choice - 1)].session_id();
            RCLCPP_INFO(this->get_logger(), "Requesting pair with %s", peer_session_id.c_str());
            signaling_client_->requestPair(peer_session_id);

            std::unique_lock<std::mutex> lk(pair_mutex_);
            const bool ok = pair_cv_.wait_for(lk, std::chrono::seconds(20), [this]()
                                              { return paired_ready_; });
            if (ok)
            {
                return true;
            }

            RCLCPP_WARN(this->get_logger(), "Pairing timeout. Please select again.");
        }

        return false;
    }

    bool MainNode::waitForPairing()
    {
        RCLCPP_INFO(this->get_logger(), "Waiting for pairing (passive mode)...");
        std::unique_lock<std::mutex> lk(pair_mutex_);
        while (!paired_ready_ && rclcpp::ok() && !shutting_down_.load())
        {
            pair_cv_.wait_for(lk, std::chrono::milliseconds(200));
        }
        return paired_ready_ && !shutting_down_.load();
    }

    void MainNode::startVideoConfigPublisher()
    {
        if (video_config_running_.exchange(true))
        {
            return;
        }
        video_config_acked_.store(false, std::memory_order_relaxed);
        video_config_thread_ = std::thread(&MainNode::videoConfigPublisherLoop, this);
    }

    void MainNode::stopVideoConfigPublisher()
    {
        video_config_running_.store(false, std::memory_order_relaxed);
        video_config_cv_.notify_all();
        if (video_config_thread_.joinable())
        {
            if (std::this_thread::get_id() != video_config_thread_.get_id())
            {
                video_config_thread_.join();
            }
        }
    }

    void MainNode::resetVideoConfigState()
    {
        std::lock_guard<std::mutex> lk(video_config_mutex_);
        video_sps_.clear();
        video_pps_.clear();
        video_vps_.clear();
        last_video_config_id_.clear();
        video_config_acked_.store(false, std::memory_order_relaxed);
        video_config_cv_.notify_all();
    }

    std::string MainNode::makeVideoConfigId()
    {
        const uint64_t seq = video_config_seq_.fetch_add(1, std::memory_order_relaxed) + 1;
        const auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::system_clock::now().time_since_epoch())
                                .count();
        const std::string sid = (signaling_client_ && !signaling_client_->sessionId().empty())
                                    ? signaling_client_->sessionId()
                                    : "unknown";
        std::ostringstream oss;
        oss << sid << "-" << now_ms << "-" << seq;
        return oss.str();
    }

    void MainNode::updateSpsPpsFromEncodedFrame(const uint8_t *data, size_t size)
    {
        if (!data || size == 0)
        {
            return;
        }

        {
            std::lock_guard<std::mutex> lk(video_config_mutex_);
            if (!video_sps_.empty() && !video_pps_.empty())
            {
                return;
            }
        }

        const H264StreamFormat fmt = detectH264Format(data, size);
        if (fmt == H264StreamFormat::Unknown)
        {
            return;
        }

        bool ready = false;
        forEachNal(data, size, fmt, [&](const uint8_t *nal, size_t nal_size)
                   {
                       if (nal_size < 1)
                           return;
                       const uint8_t nal_unit_type = static_cast<uint8_t>(nal[0] & 0x1Fu);
                       if (nal_unit_type != 7 && nal_unit_type != 8)
                           return;

                       std::lock_guard<std::mutex> lk(video_config_mutex_);
                       if (nal_unit_type == 7 && video_sps_.empty())
                       {
                           video_sps_.assign(nal, nal + nal_size);
                       }
                       else if (nal_unit_type == 8 && video_pps_.empty())
                       {
                           video_pps_.assign(nal, nal + nal_size);
                       }

                       if (!video_sps_.empty() && !video_pps_.empty())
                       {
                           ready = true;
                       } });

        if (ready)
        {
            video_config_cv_.notify_all();
        }
    }

    void MainNode::videoConfigPublisherLoop()
    {
        while (video_config_running_.load(std::memory_order_relaxed) && rclcpp::ok() && !shutting_down_.load())
        {
            std::unique_lock<std::mutex> lk(video_config_mutex_);
            video_config_cv_.wait_for(lk, std::chrono::milliseconds(200), [this]()
                                      { return !video_config_running_.load(std::memory_order_relaxed) ||
                                               (paired_ready_ && !video_sps_.empty() && !video_pps_.empty()); });

            if (!video_config_running_.load(std::memory_order_relaxed))
            {
                break;
            }

            if (!paired_ready_ || video_sps_.empty() || video_pps_.empty())
            {
                continue;
            }

            if (!signaling_client_)
            {
                lk.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            signaling::VideoConfig config;
            config.set_codec(signaling::VideoConfig::H264);
            config.set_width(static_cast<int32_t>(video_width_));
            config.set_height(static_cast<int32_t>(video_height_));
            config.set_fps(static_cast<int32_t>(video_fps_));
            config.set_sps(video_sps_.data(), video_sps_.size());
            config.set_pps(video_pps_.data(), video_pps_.size());
            const std::string config_id = makeVideoConfigId();
            config.set_config_id(config_id);
            last_video_config_id_ = config_id;

            lk.unlock();

            while (video_config_running_.load(std::memory_order_relaxed))
            {
                if (!paired_ready_)
                {
                    break;
                }
                if (signaling_client_->publishVideoConfig(config) == 0)
                {
                    video_config_acked_.store(true, std::memory_order_relaxed);
                    RCLCPP_INFO(this->get_logger(), "VideoConfig ACK received, start streaming video");
                    break;
                }
                RCLCPP_WARN(this->get_logger(), "PublishVideoConfig no-ack, retrying in 3s...");
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }

            if (video_config_acked_.load(std::memory_order_relaxed))
            {
                break;
            }
        }
    }

    bool MainNode::reRegisterAndWaitForPairing()
    {
        if (reconnecting_.exchange(true))
        {
            RCLCPP_WARN(this->get_logger(), "Reconnect already in progress; skipping");
            return false;
        }

        if (!signaling_client_)
        {
            reconnecting_.store(false, std::memory_order_relaxed);
            return false;
        }

        stopVideoConfigPublisher();

        {
            std::lock_guard<std::mutex> lk(pair_mutex_);
            paired_ready_ = false;
            paired_peer_session_id_.clear();
        }
        pair_cv_.notify_all();

        signaling_client_->stopEventStream();
        resetVideoConfigState();

        bool registered = false;
        while (rclcpp::ok() && !shutting_down_.load())
        {
            if (signaling_client_->connect() == 0 && signaling_client_->registerRobot() == 0)
            {
                registered = true;
                break;
            }
            RCLCPP_WARN(this->get_logger(), "Re-register failed. Retrying in 3s...");
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        if (!registered)
        {
            reconnecting_.store(false, std::memory_order_relaxed);
            return false;
        }

        signaling_client_->startEventStream(std::bind(&MainNode::onSignalingEvent, this, std::placeholders::_1));

        bool paired_ok = false;
        if (pair_mode_ == "active")
        {
            paired_ok = runActivePairing();
        }
        else
        {
            paired_ok = waitForPairing();
        }

        if (paired_ok && udp_stream_manager_)
        {
            udp_stream_manager_->setSessionId(signaling_client_->sessionId());
        }

        if (paired_ok)
        {
            startVideoConfigPublisher();
        }

        reconnecting_.store(false, std::memory_order_relaxed);
        return paired_ok;
    }

    void MainNode::onSignalingEvent(const signaling::EventMessage &msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received EventMessage from %s", msg.sender_session_id().c_str());

        if (msg.has_pair())
        {
            const auto &pair_event = msg.pair();
            switch (pair_event.op())
            {
            case signaling::PairEvent::REQUEST:
            {
                const auto &peer = pair_event.peer_session_id();
                const bool peer_matches = desired_peer_session_id_.empty() || (peer == desired_peer_session_id_);
                if (pair_auto_accept_ && peer_matches)
                {
                    RCLCPP_INFO(this->get_logger(), "Pair Request from %s. Auto-accepting...", peer.c_str());
                    signaling_client_->acceptPair(peer);
                    paired_peer_session_id_ = peer;

                    {
                        std::lock_guard<std::mutex> lk(pair_mutex_);
                        paired_ready_ = true;
                    }
                    pair_cv_.notify_all();

                    video_config_acked_.store(false, std::memory_order_relaxed);
                    startVideoConfigPublisher();

                    if (subscribe_vr_pose_flag_)
                    {
                        signaling_client_->subscribeVrPose(peer);
                    }
                }
                else
                {
                    RCLCPP_WARN(this->get_logger(), "Pair Request from %s rejected (auto_accept=%s, desired_peer=%s)",
                                peer.c_str(), pair_auto_accept_ ? "true" : "false", desired_peer_session_id_.c_str());
                    signaling_client_->rejectPair(peer);
                }
                break;
            }
            case signaling::PairEvent::ACCEPT:
            {
                const auto &peer = pair_event.peer_session_id();
                RCLCPP_INFO(this->get_logger(), "Pair Accepted by %s", peer.c_str());
                paired_peer_session_id_ = peer;
                {
                    std::lock_guard<std::mutex> lk(pair_mutex_);
                    paired_ready_ = true;
                }
                pair_cv_.notify_all();
                video_config_acked_.store(false, std::memory_order_relaxed);
                startVideoConfigPublisher();
                if (subscribe_vr_pose_flag_)
                {
                    signaling_client_->subscribeVrPose(peer);
                }
                break;
            }
            case signaling::PairEvent::REJECT:
            {
                const auto &peer = pair_event.peer_session_id();
                RCLCPP_WARN(this->get_logger(), "Pair Rejected by %s", peer.c_str());
                if (paired_peer_session_id_ == peer)
                {
                    paired_peer_session_id_.clear();
                }
                {
                    std::lock_guard<std::mutex> lk(pair_mutex_);
                    paired_ready_ = false;
                }
                pair_cv_.notify_all();
                stopVideoConfigPublisher();
                break;
            }
            case signaling::PairEvent::UNPAIR:
            {
                const auto &peer = pair_event.peer_session_id();
                RCLCPP_INFO(this->get_logger(), "Unpaired by %s", peer.c_str());
                if (paired_peer_session_id_ == peer)
                {
                    paired_peer_session_id_.clear();
                }
                {
                    std::lock_guard<std::mutex> lk(pair_mutex_);
                    paired_ready_ = false;
                }
                pair_cv_.notify_all();
                stopVideoConfigPublisher();
                if (subscribe_vr_pose_flag_)
                {
                    signaling_client_->unsubscribe(peer);
                }
                break;
            }
            default:
                break;
            }
        }
        else if (msg.has_system())
        {
            const auto &sys_cmd = msg.system();
            switch (sys_cmd.action())
            {
            case signaling::SystemCommand::REQUEST_UDP_HELLO:
                RCLCPP_WARN(this->get_logger(), "Server requested UDP HELLO resend");
                // TODO: Trigger UDP HELLO resend in UdpStreamManager
                // if (udp_stream_manager_) udp_stream_manager_->forceSendHello();
                break;
            default:
                RCLCPP_INFO(this->get_logger(), "Received SystemCommand: %d", sys_cmd.action());
                break;
            }
        }
    }

    void MainNode::heartbeatTimerCallback()
    {
        if (signaling_client_)
        {
            signaling_client_->tickHeartbeat();
        }
    }

    MainNode::~MainNode()
    {
        RCLCPP_INFO(this->get_logger(), "Shutting down MainNode...");

        {
            std::lock_guard<std::mutex> lk(pair_mutex_);
            shutting_down_.store(true);
            paired_ready_ = false;
        }
        pair_cv_.notify_all();

        // 1. Cancel timers
        if (heartbeat_timer_)
        {
            heartbeat_timer_->cancel();
            heartbeat_timer_.reset();
        }

        stopVideoConfigPublisher();

        // 2. Stop Video Pipeline (Producers)
        // This ensures no new frames are sent to UDP manager
        stopVideo();

        // 2.5 Stop Pose UDP receiver (input)
        if (udp_stream_manager_)
        {
            udp_stream_manager_->setPoseDatagramCallback(nullptr);
        }
        if (pose_udp_receiver_)
        {
            pose_udp_receiver_->stop();
            pose_udp_receiver_.reset();
        }

        // 3. Stop UDP Manager (Transport)
        if (udp_stream_manager_)
        {
            udp_stream_manager_->stop();
            udp_stream_manager_.reset();
        }

        // 4. Stop Signaling Client (Control/Events)
        if (signaling_client_)
        {
            signaling_client_->stopEventStream();
            signaling_client_.reset();
        }

        RCLCPP_INFO(this->get_logger(), "MainNode shutdown complete.");
    }

    void MainNode::stopVideo()
    {
        if (video_stream_manager_)
        {
            video_stream_manager_->stop();
            video_stream_manager_.reset();
        }
    }
}
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<trb::MainNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
