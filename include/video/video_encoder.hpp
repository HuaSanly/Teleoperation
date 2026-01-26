#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace trb::video
{

struct VideoEncoderConfig
{
    uint32_t width{0};
    uint32_t height{0};
    uint32_t fps{0};

    uint32_t bitrate{0};
    uint32_t idr_interval{0};
    uint32_t iframe_interval{0};
    uint32_t force_idr_every_n{0};

    bool intra_refresh_enabled{false};
    uint32_t intra_refresh_interval_slices{0};

    bool low_freq_idr_enabled{false};
    double low_freq_idr_interval_sec{0.0};

    uint32_t qp_range_i_min{0};
    uint32_t qp_range_i_max{0};
    uint32_t qp_range_p_min{0};
    uint32_t qp_range_p_max{0};

    uint32_t output_plane_buffers{4};
    uint32_t capture_plane_buffers{4};

    bool max_perf_mode{false};
    std::string hw_preset;
    std::string rate_control;
    uint32_t peak_bitrate{0};
    uint32_t virtual_buffer_size{0};

    int num_reference_frames{-1};
    int num_b_frames{-1};
    int insert_sps_pps_at_idr{-1};
};

struct EncodedFrame
{
    std::vector<uint8_t> data;
    uint64_t timestamp_us{0};
    bool keyframe{false};
};

class VideoEncoder
{
public:
    explicit VideoEncoder(VideoEncoderConfig config);
    ~VideoEncoder();

    bool start();
    void stop();

    bool encode(int nv12_fd, uint64_t timestamp_us, EncodedFrame &out);

    bool isRunning() const;

private:
    void drainOutputPlane(bool blocking);
    uint32_t clampBufferCount(uint32_t v) const;
    bool shouldForceIdr(uint64_t timestamp_us);

    VideoEncoderConfig config_{};
    void *encoder_{nullptr};
    bool running_{false};

    std::vector<int> output_fd_by_index_;
    std::vector<uint32_t> free_output_indices_;

    uint64_t frame_count_{0};
    uint64_t last_low_freq_idr_us_{0};
};

} // namespace trb::video
