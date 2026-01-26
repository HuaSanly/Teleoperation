#include "video/video_encoder.hpp"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <fcntl.h>

#include <linux/videodev2.h>

#include <ros/ros.h>

#include "NvBufSurface.h"
#include "NvBuffer.h"
#include "NvVideoEncoder.h"

namespace trb::video
{

namespace
{
uint32_t clampPositive(int v)
{
    return static_cast<uint32_t>(std::max(0, v));
}

v4l2_enc_hw_preset_type hwPresetFromString(const std::string &preset)
{
    if (preset == "ultrafast")
    {
        return V4L2_ENC_HW_PRESET_ULTRAFAST;
    }
    if (preset == "fast")
    {
        return V4L2_ENC_HW_PRESET_FAST;
    }
    if (preset == "medium")
    {
        return V4L2_ENC_HW_PRESET_MEDIUM;
    }
    if (preset == "slow")
    {
        return V4L2_ENC_HW_PRESET_SLOW;
    }
    return V4L2_ENC_HW_PRESET_DISABLE;
}

bool parseRateControl(const std::string &mode, v4l2_mpeg_video_bitrate_mode &out)
{
    if (mode == "cbr")
    {
        out = V4L2_MPEG_VIDEO_BITRATE_MODE_CBR;
        return true;
    }
    if (mode == "vbr")
    {
        out = V4L2_MPEG_VIDEO_BITRATE_MODE_VBR;
        return true;
    }
#ifdef V4L2_MPEG_VIDEO_BITRATE_MODE_CQ
    if (mode == "cq")
    {
        out = V4L2_MPEG_VIDEO_BITRATE_MODE_CQ;
        return true;
    }
#endif
    return false;
}
} // namespace

VideoEncoder::VideoEncoder(VideoEncoderConfig config)
    : config_(std::move(config))
{
}

VideoEncoder::~VideoEncoder()
{
    stop();
}

bool VideoEncoder::start()
{
    if (running_)
    {
        return true;
    }

    if (config_.width == 0 || config_.height == 0)
    {
        ROS_ERROR("VideoEncoder: invalid width/height");
        return false;
    }

    auto *enc = NvVideoEncoder::createVideoEncoder("video_encoder", O_NONBLOCK);
    if (!enc)
    {
        ROS_ERROR("VideoEncoder: failed to create NvVideoEncoder");
        return false;
    }

    const uint32_t width = config_.width;
    const uint32_t height = config_.height;

    if (enc->setCapturePlaneFormat(V4L2_PIX_FMT_H264, width, height, 2 * 1024 * 1024) < 0)
    {
        ROS_ERROR("VideoEncoder: setCapturePlaneFormat failed");
        delete enc;
        return false;
    }

    if (enc->setOutputPlaneFormat(V4L2_PIX_FMT_NV12M, width, height) < 0)
    {
        ROS_ERROR("VideoEncoder: setOutputPlaneFormat failed");
        delete enc;
        return false;
    }

    if (config_.bitrate > 0)
    {
        enc->setBitrate(config_.bitrate);
    }

    if (config_.idr_interval > 0)
    {
        enc->setIDRInterval(config_.idr_interval);
    }

    if (config_.iframe_interval > 0)
    {
        enc->setIFrameInterval(config_.iframe_interval);
    }

    if (config_.fps > 0)
    {
        enc->setFrameRate(config_.fps, 1);
    }

    if (config_.intra_refresh_enabled && config_.intra_refresh_interval_slices > 0)
    {
        enc->setSliceIntrarefresh(config_.intra_refresh_interval_slices);
    }

    if (config_.virtual_buffer_size > 0)
    {
        enc->setVirtualBufferSize(config_.virtual_buffer_size);
    }

    if (config_.num_reference_frames > 0)
    {
        enc->setNumReferenceFrames(clampPositive(config_.num_reference_frames));
    }

    if (config_.num_b_frames >= 0)
    {
        enc->setNumBFrames(clampPositive(config_.num_b_frames));
    }

    if (config_.insert_sps_pps_at_idr >= 0)
    {
        enc->setInsertSpsPpsAtIdrEnabled(config_.insert_sps_pps_at_idr != 0);
    }

    if (config_.max_perf_mode)
    {
        enc->setMaxPerfMode(1);
    }

    if (!config_.hw_preset.empty())
    {
        enc->setHWPresetType(hwPresetFromString(config_.hw_preset));
    }

    if (!config_.rate_control.empty())
    {
        v4l2_mpeg_video_bitrate_mode mode;
        if (parseRateControl(config_.rate_control, mode))
        {
            enc->setRateControlMode(mode);
            if (mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR && config_.peak_bitrate > 0)
            {
                enc->setPeakBitrate(config_.peak_bitrate);
            }
        }
    }

    if (config_.qp_range_i_max > 0 && config_.qp_range_p_max > 0)
    {
        enc->setQpRange(config_.qp_range_i_min,
                        config_.qp_range_i_max,
                        config_.qp_range_p_min,
                        config_.qp_range_p_max,
                        config_.qp_range_p_min,
                        config_.qp_range_p_max);
    }

    const uint32_t out_bufs = clampBufferCount(config_.output_plane_buffers);
    const uint32_t cap_bufs = clampBufferCount(config_.capture_plane_buffers);

    if (enc->output_plane.setupPlane(V4L2_MEMORY_DMABUF, out_bufs, false, false) < 0)
    {
        ROS_ERROR("VideoEncoder: output_plane setup failed");
        delete enc;
        return false;
    }

    if (enc->capture_plane.setupPlane(V4L2_MEMORY_MMAP, cap_bufs, true, false) < 0)
    {
        ROS_ERROR("VideoEncoder: capture_plane setup failed");
        delete enc;
        return false;
    }

    if (enc->output_plane.setStreamStatus(true) < 0 || enc->capture_plane.setStreamStatus(true) < 0)
    {
        ROS_ERROR("VideoEncoder: stream on failed");
        delete enc;
        return false;
    }

    for (uint32_t i = 0; i < enc->capture_plane.getNumBuffers(); ++i)
    {
        v4l2_buffer v4l2_buf;
        v4l2_plane planes[MAX_PLANES];
        std::memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        std::memset(planes, 0, sizeof(planes));
        v4l2_buf.index = i;
        v4l2_buf.m.planes = planes;
        if (enc->capture_plane.qBuffer(v4l2_buf, nullptr) < 0)
        {
            ROS_ERROR("VideoEncoder: capture_plane qBuffer failed");
            delete enc;
            return false;
        }
    }

    encoder_ = enc;
    running_ = true;

    output_fd_by_index_.assign(enc->output_plane.getNumBuffers(), -1);
    free_output_indices_.clear();
    for (uint32_t i = 0; i < enc->output_plane.getNumBuffers(); ++i)
    {
        free_output_indices_.push_back(i);
    }

    frame_count_ = 0;
    last_low_freq_idr_us_ = 0;

    return true;
}

void VideoEncoder::stop()
{
    if (!running_)
    {
        return;
    }

    auto *enc = static_cast<NvVideoEncoder *>(encoder_);
    if (enc)
    {
        enc->output_plane.setStreamStatus(false);
        enc->capture_plane.setStreamStatus(false);
        delete enc;
    }

    encoder_ = nullptr;
    running_ = false;
    output_fd_by_index_.clear();
    free_output_indices_.clear();
}

bool VideoEncoder::encode(int nv12_fd, uint64_t timestamp_us, EncodedFrame &out)
{
    out = EncodedFrame{};

    if (!running_ || !encoder_ || nv12_fd < 0)
    {
        return false;
    }

    auto *enc = static_cast<NvVideoEncoder *>(encoder_);

    drainOutputPlane(false);

    if (free_output_indices_.empty())
    {
        drainOutputPlane(true);
    }

    if (free_output_indices_.empty())
    {
        ROS_WARN_THROTTLE(2.0, "VideoEncoder output buffers exhausted");
        return false;
    }

    const uint32_t index = free_output_indices_.back();
    free_output_indices_.pop_back();

    v4l2_buffer v4l2_out;
    v4l2_plane planes[MAX_PLANES];
    std::memset(&v4l2_out, 0, sizeof(v4l2_out));
    std::memset(planes, 0, sizeof(planes));
    v4l2_out.index = index;
    v4l2_out.m.planes = planes;

    if (enc->output_plane.mapOutputBuffers(v4l2_out, nv12_fd) < 0)
    {
        free_output_indices_.push_back(index);
        return false;
    }

    NvBufSurface *surf = nullptr;
    if (NvBufSurfaceFromFd(nv12_fd, reinterpret_cast<void **>(&surf)) == 0 && surf)
    {
        const uint32_t num_planes = surf->surfaceList[0].planeParams.num_planes;
        for (uint32_t i = 0; i < num_planes; ++i)
        {
            v4l2_out.m.planes[i].bytesused = surf->surfaceList[0].planeParams.psize[i];
        }
    }

    if (shouldForceIdr(timestamp_us))
    {
        enc->forceIDR();
    }

    if (enc->output_plane.qBuffer(v4l2_out, nullptr) < 0)
    {
        enc->output_plane.unmapOutputBuffers(index, nv12_fd);
        free_output_indices_.push_back(index);
        return false;
    }

    output_fd_by_index_[index] = nv12_fd;

    v4l2_buffer v4l2_cap;
    v4l2_plane cap_planes[MAX_PLANES];
    std::memset(&v4l2_cap, 0, sizeof(v4l2_cap));
    std::memset(cap_planes, 0, sizeof(cap_planes));
    v4l2_cap.m.planes = cap_planes;

    NvBuffer *cap_buffer = nullptr;
    if (enc->capture_plane.dqBuffer(v4l2_cap, &cap_buffer, nullptr, 0) < 0)
    {
        return false;
    }

    if (cap_buffer && cap_buffer->planes[0].bytesused > 0)
    {
        out.data.assign(cap_buffer->planes[0].data,
                        cap_buffer->planes[0].data + cap_buffer->planes[0].bytesused);
        out.timestamp_us = timestamp_us;
        out.keyframe = (v4l2_cap.flags & V4L2_BUF_FLAG_KEYFRAME) != 0;
    }

    enc->capture_plane.qBuffer(v4l2_cap, nullptr);

    drainOutputPlane(false);

    return !out.data.empty();
}

bool VideoEncoder::isRunning() const
{
    return running_;
}

void VideoEncoder::drainOutputPlane(bool blocking)
{
    auto *enc = static_cast<NvVideoEncoder *>(encoder_);
    if (!enc)
    {
        return;
    }

    while (true)
    {
        v4l2_buffer v4l2_out;
        v4l2_plane planes[MAX_PLANES];
        std::memset(&v4l2_out, 0, sizeof(v4l2_out));
        std::memset(planes, 0, sizeof(planes));
        v4l2_out.m.planes = planes;

        NvBuffer *buffer = nullptr;
        const int timeout = blocking ? 1000 : 0;
        const int ret = enc->output_plane.dqBuffer(v4l2_out, &buffer, nullptr, timeout);
        if (ret < 0)
        {
            break;
        }

        const uint32_t index = v4l2_out.index;
        if (index < output_fd_by_index_.size())
        {
            const int fd = output_fd_by_index_[index];
            if (fd >= 0)
            {
                enc->output_plane.unmapOutputBuffers(index, fd);
                output_fd_by_index_[index] = -1;
            }
        }

        free_output_indices_.push_back(index);

        if (!blocking)
        {
            continue;
        }
    }
}

uint32_t VideoEncoder::clampBufferCount(uint32_t v) const
{
    return std::max<uint32_t>(2, v);
}

bool VideoEncoder::shouldForceIdr(uint64_t timestamp_us)
{
    ++frame_count_;

    if (config_.force_idr_every_n > 0 && (frame_count_ % config_.force_idr_every_n) == 0)
    {
        return true;
    }

    if (config_.low_freq_idr_enabled && config_.low_freq_idr_interval_sec > 0.0)
    {
        if (last_low_freq_idr_us_ == 0 ||
            (timestamp_us - last_low_freq_idr_us_) >=
                static_cast<uint64_t>(config_.low_freq_idr_interval_sec * 1e6))
        {
            last_low_freq_idr_us_ = timestamp_us;
            return true;
        }
    }

    return false;
}

} // namespace trb::video
