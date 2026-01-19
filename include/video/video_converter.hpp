#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <atomic>

// Forward declarations for Jetson Multimedia API classes
class NvJPEGDecoder;

namespace trb::video
{

    class VideoConverter
    {
    public:
        struct Config
        {
            uint32_t width = 3840;
            uint32_t height = 1520;
            uint32_t buffer_pool_size = 4;

            // NvBufSurface layout controls:
            // 0 = PITCH (linear), 1 = BLOCK_LINEAR.
            // On Jetson, BLOCK_LINEAR can be faster for some HW paths, but NVENC input
            // often behaves best with PITCH. Therefore we allow separate layouts.

            // Layout for the converter output NV12 surfaces (fed to encoder).
            int32_t output_surface_layout = 0;

            // Layout for the decoder output YUV422 surfaces (fed into transform).
            int32_t decode_surface_layout = 0;

            // Legacy (kept for API/backward compatibility). If you still set this,
            // it is treated as a default for decode surfaces only.
            int32_t surface_layout = 0;

            // NvBufSurfTransform compute device:
            // 0=Default, 1=GPU, 2=VIC (Jetson).
            // -1 means "use default".
            int32_t transform_compute_mode = -1;
        };

        // Callback providing the DMA buffer FD and timestamp.
        // Return true if the consumer took ownership and will later call releaseFd(fd).
        // Return false to indicate the buffer should be returned to the pool immediately.
        using OutputCallback = std::function<bool(int dmabuf_fd, uint64_t timestamp_us)>;

        VideoConverter();
        ~VideoConverter();

        VideoConverter(const VideoConverter &) = delete;
        VideoConverter &operator=(const VideoConverter &) = delete;

        bool initialize(const Config &config);
        void setCallback(OutputCallback callback);

        // Return a previously emitted dmabuf fd back to the internal pool.
        // Safe to call from any thread.
        void releaseFd(int dmabuf_fd);

        // Process a frame (MJPEG -> DMA Buffer)
        void processFrame(const uint8_t *data, size_t size, uint64_t timestamp_us);

    private:
        void destroyBuffers();

        Config config_;
        OutputCallback callback_;

        std::unique_ptr<NvJPEGDecoder> jpeg_decoder_;

        // Store NvBufSurface pointers to manage memory
        // Using void* to avoid including nvbufsurface.h in header
        std::vector<void *> surfaces_;
        std::vector<int> dmabuf_fds_;

        // Decode pool for MJPEG that decodes to 4:2:2 (YUV422).
        std::vector<void *> decode_surfaces_;
        std::vector<int> decode_dmabuf_fds_;

        std::mutex pool_mutex_;
        std::queue<size_t> free_indices_;
        std::unordered_map<int, size_t> fd_to_index_;

        std::queue<size_t> free_decode_indices_;
        std::unordered_map<int, size_t> decode_fd_to_index_;

        std::atomic<bool> logged_mode_{false};
    };

} // namespace trb::video
