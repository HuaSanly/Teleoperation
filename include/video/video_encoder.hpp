#pragma once

#include <functional>
#include <memory>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <deque>
#include <map>

#include "NvVideoEncoder.h"

namespace trb::video
{

    class VideoEncoder
    {
    public:
        struct Config
        {
            uint32_t width;
            uint32_t height;
            uint32_t framerate;
            uint32_t bitrate; // bits per second
            // GOP size in frames (distance between I-frames).
            uint32_t idr_interval = 30;

            // IDR interval in frames (distance between two IDR frames).
            // NOTE: This maps to NvVideoEncoder::setIDRInterval(interval_frames).
            uint32_t idr_interval_gops = 30;

            // Slice intra-refresh ("I-frame smoothing"): gradually refreshes
            // the picture using intra-coded slices instead of full I/IDR frames.
            // 0 disables.
            // NOTE: This maps to NvVideoEncoder::setSliceIntrarefresh(interval_slices).
            uint32_t slice_intra_refresh_interval_slices = 0;

            // Debug/diagnostic knob: force an IDR every N input frames.
            // 0 disables.
            uint32_t force_idr_every_n = 0;
            uint32_t qp_range_i_min = 10;
            uint32_t qp_range_i_max = 40;
            uint32_t qp_range_p_min = 10;
            uint32_t qp_range_p_max = 40;

            // -------- Jetson NvVideoEncoder tuning knobs (optional) --------
            // These map to Jetson Multimedia API (NvVideoEncoder) controls.
            // Most of them MUST be set after setFormat on both planes and
            // before requestBuffers/setupPlane.

            // V4L2_CID_MPEG_VIDEO_MAX_PERFORMANCE
            bool max_perf_mode = false;

            // V4L2_CID_MPEG_VIDEOENC_HW_PRESET_TYPE_PARAM
            // -1 means "don't touch". Otherwise cast to enum v4l2_enc_hw_preset_type.
            int32_t hw_preset_type = -1;

            // V4L2_CID_MPEG_VIDEO_BITRATE_MODE
            // -1 means "don't touch". Otherwise cast to enum v4l2_mpeg_video_bitrate_mode.
            int32_t rate_control_mode = -1;

            // V4L2_CID_MPEG_VIDEO_BITRATE_PEAK (optional)
            // 0 means "don't touch".
            uint32_t peak_bitrate = 0;

            // V4L2_CID_MPEG_VIDEOENC_VIRTUALBUFFER_SIZE (bytes).
            // 0 means "don't touch". Smaller values generally reduce latency.
            uint32_t virtual_buffer_size = 0;

            // V4L2_CID_MPEG_VIDEOENC_NUM_REFERENCE_FRAMES
            // -1 means "don't touch".
            int32_t num_reference_frames = -1;

            // V4L2_CID_MPEG_VIDEO_B_FRAMES
            // -1 means "don't touch". For low latency, usually set to 0.
            int32_t num_b_frames = -1;

            // V4L2_CID_MPEG_VIDEOENC_INSERT_SPS_PPS_AT_IDR
            // -1 means "don't touch". 0 disable, 1 enable.
            int32_t insert_sps_pps_at_idr = -1;

            // NvVideoEncoder plane buffer counts.
            // Larger values can improve throughput but add buffering/latency.
            uint32_t output_plane_buffers = 10;
            uint32_t capture_plane_buffers = 10;
        };

        using EncodedPacketCallback = std::function<void(const uint8_t *data, size_t size, uint64_t timestamp_us, bool keyframe)>;
        using InputDoneCallback = std::function<void(int dmabuf_fd)>;

        VideoEncoder();
        ~VideoEncoder();

        bool initialize(const Config &config);
        void setCallback(EncodedPacketCallback callback);

        // Called when the encoder is finished consuming an input dmabuf.
        // Useful to release dmabuf back to a pool.
        void setInputDoneCallback(InputDoneCallback callback);

        // Feed a frame to be encoded.
        // dmabuf_fd: The DMA buffer file descriptor containing the raw frame (NV12).
        // timestamp_us: Timestamp of the frame.
        bool encodeFrame(int dmabuf_fd, uint64_t timestamp_us);

    private:
        static bool encoderCapturePlaneDqCallback(struct v4l2_buffer *v4l2_buf, NvBuffer *buffer, NvBuffer *shared_buffer, void *arg);
        static bool encoderOutputPlaneDqCallback(struct v4l2_buffer *v4l2_buf, NvBuffer *buffer, NvBuffer *shared_buffer, void *arg);

        Config config_;
        EncodedPacketCallback callback_;
        InputDoneCallback input_done_callback_;
        std::unique_ptr<NvVideoEncoder> encoder_;

        std::mutex input_mutex_;
        std::queue<int> free_output_indices_;

        std::mutex map_mutex_;
        std::map<int, int> index_to_fd_;
        std::map<int, uint64_t> index_to_timestamp_;

        std::mutex ts_queue_mutex_;
        std::queue<uint64_t> timestamp_queue_;

        std::atomic<uint64_t> input_frame_count_{0};
    };

} // namespace trb::video
