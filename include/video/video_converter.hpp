#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <atomic>

namespace trb::video
{
    class CudaYuv422Converter;

    class VideoConverter
    {
    public:
        struct StatsSnapshot
        {
            uint64_t processed_frames = 0;
            uint64_t malformed_frames = 0;
            uint64_t pool_drops = 0;
            uint64_t failed_frames = 0;
            int64_t decode_us_total = 0;
            int64_t transform_us_total = 0;
            int64_t map_us_total = 0;
            int64_t transform_wait_us_total = 0;
            int64_t transform_call_us_total = 0;
        };

        struct Config
        {
            uint32_t width = 3840;
            uint32_t height = 1520;
            uint32_t input_width = 0;
            uint32_t input_height = 0;
            uint32_t buffer_pool_size = 4;
        };

        VideoConverter();
        ~VideoConverter();

        VideoConverter(const VideoConverter &) = delete;
        VideoConverter &operator=(const VideoConverter &) = delete;

        bool initialize(const Config &config);

        // Synchronously convert one decoded YUV DMA-BUF to an encoder input DMA-BUF.
        // On success, fills |output_fd_out| with a pool-owned fd; caller must
        // return it via releaseFd() after the downstream consumer (encoder)
        // has finished with it.
        // Returns false if the pool is exhausted or the transform failed.
        bool transformSync(int yuv_dmabuf_fd,
                           uint64_t timestamp_us,
                           uint64_t decode_us,
                           int &output_fd_out);

        // Return a previously emitted dmabuf fd back to the internal pool.
        // Safe to call from any thread.
        void releaseFd(int dmabuf_fd);

        // Consume and reset converter statistics accumulated since the last snapshot.
        StatsSnapshot consumeStats();

        const char *outputFormatName() const;

    private:
        void destroyBuffers();

        Config config_;

        // Store NvBufSurface pointers to manage memory
        // Using void* to avoid including nvbufsurface.h in header
        std::vector<void *> surfaces_;
        std::vector<int> dmabuf_fds_;
        std::unique_ptr<CudaYuv422Converter> cuda_converter_;

        std::mutex pool_mutex_;
        std::queue<size_t> free_indices_;
        std::unordered_map<int, size_t> fd_to_index_;

        std::atomic<bool> logged_mode_{false};
        std::atomic<uint64_t> stats_processed_frames_{0};
        std::atomic<uint64_t> stats_malformed_frames_{0};
        std::atomic<uint64_t> stats_pool_drops_{0};
        std::atomic<uint64_t> stats_failed_frames_{0};
        std::atomic<int64_t> stats_decode_us_total_{0};
        std::atomic<int64_t> stats_transform_us_total_{0};
        std::atomic<int64_t> stats_map_us_total_{0};
        std::atomic<int64_t> stats_transform_wait_us_total_{0};
        std::atomic<int64_t> stats_transform_call_us_total_{0};
        std::atomic<bool> logged_surface_details_{false};
    };

} // namespace trb::video
