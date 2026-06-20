#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace trb::video
{

    // Stereo undistort + rectify on Jetson using in-tree CUDA kernels over a
    // side-by-side frame. Runtime fuses decoded planar YUV422 -> rectified
    // NV12 so the encoder and eye-image publisher receive NV12 DMA-BUFs
    // without an intermediate converter pass.
    //
    // Lifecycle:
    //   1. construct, then initialize(cfg). initialize() reads the calibration
    //      YAML, runs cv::initUndistortRectifyMap() once per eye on the host,
    //      hconcat's the two per-eye dense maps into a single full-frame map
    //      (right-eye dst x is offset by +single_eye_width), uploads it once
    //      to CUDA, and creates a pool of NV12 output NvBufSurface dmabufs
    //      (same pitch-linear NV12 layout as VideoConverter output).
    //   2. processYuv422(in_fd, out_fd) runs decoded-YUV422 -> rectified-NV12.
    //      process(in_fd, out_fd) remains available only as a test hook for
    //      CUDA NV12 remap. The caller owns the input fd lifecycle and must
    //      return the output fd via releaseFd().
    //   3. destruction tears down CUDA resources and destroys the pool.
    //
    // Calibration YAML schema (see config/calibration_stereo.yaml.example):
    //   calibration_image_size: [W_calib, H_calib]
    //   runtime_image_size:     [W_run,   H_run]      # single-eye, e.g. 2560x1440
    //   distortion_model: "rational"                  # plumb_bob | rational
    //   alpha: 0.0                                    # 0=no black border, 1=keep FOV
    //   left:
    //     K: [9 floats]
    //     D: [4..14 floats]
    //     R: [9 floats]   # optional, defaults to identity
    //     P: [12 floats]  # optional, defaults to getOptimalNewCameraMatrix(...)
    //   right: { ... same ... }
    class VideoUndistorter
    {
    public:
        struct Config
        {
            // Full SBS frame size emitted by CUDA post-processing (e.g. 5120x1440).
            uint32_t width = 5120;
            uint32_t height = 1440;

            // Output buffer pool depth. Mirror the encoder path so we never
            // become the bottleneck of the encode thread.
            uint32_t buffer_pool_size = 4;

            // Path (absolute or relative to package share) to the stereo
            // calibration YAML.
            std::string calibration_file;

            // Optional profile/session selector for YAML files that contain a
            // stereo_calibrations list. Empty means auto-match stream_image_size.
            std::string profile;

            // If true and calibration cannot be loaded, initialize() returns
            // false and the pipeline startup fails. If false, initialize()
            // uses an identity map for debug only.
            bool require_calibration = true;
        };

        struct StatsSnapshot
        {
            uint64_t processed_frames = 0;
            uint64_t pool_drops = 0;
            uint64_t failed_frames = 0;
            uint64_t fallback_frames = 0;
            int64_t  remap_us_total = 0;
            int64_t  map_us_total = 0;
            int64_t  kernel_us_total = 0;
            int64_t  sync_us_total = 0;
            std::string backend;
        };

        VideoUndistorter();
        ~VideoUndistorter();

        VideoUndistorter(const VideoUndistorter &) = delete;
        VideoUndistorter &operator=(const VideoUndistorter &) = delete;

        bool initialize(const Config &config);

        // CUDA-remap one full-frame SBS NV12 dmabuf into a freshly acquired
        // NV12 dmabuf. Kept as a test hook; the runtime path uses processYuv422().
        bool process(int nv12_fd_in, int &nv12_fd_out);

        // Fused path: decoded pitch-linear planar YUV422 DMA-BUF
        // directly to rectified pitch-linear NV12 DMA-BUF.
        bool processYuv422(int yuv422_fd_in, int &nv12_fd_out);

        bool supportsFusedYuv422() const;
        const std::string &backendName() const;

        // Return a previously emitted dmabuf fd back to the internal pool.
        void releaseFd(int dmabuf_fd);

        StatsSnapshot consumeStats();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };

} // namespace trb::video
