#pragma once

#include <cstdint>
#include <mutex>
#include <vector>

#include "NvBufSurface.h"

namespace trb::video
{

struct VideoConverterConfig
{
    uint32_t width{0};
    uint32_t height{0};
    uint32_t buffer_count{4};
    NvBufSurfaceColorFormat out_color_format{NVBUF_COLOR_FORMAT_NV12};
    NvBufSurfaceLayout out_layout{NVBUF_LAYOUT_PITCH};
    NvBufSurfaceMemType out_mem_type{NVBUF_MEM_SURFACE_ARRAY};
    NvBufSurfaceTag out_mem_tag{NvBufSurfaceTag_VIDEO_CONVERT};
};

struct ConvertedFrame
{
    int fd{-1};
    uint64_t timestamp_us{0};
};

class VideoConverter
{
public:
    explicit VideoConverter(VideoConverterConfig config);
    ~VideoConverter();

    bool start();
    void stop();

    bool convert(int src_fd, uint64_t timestamp_us, ConvertedFrame &out);
    void releaseFd(int fd);

    bool isRunning() const;

private:
    VideoConverterConfig config_{};
    bool running_{false};

    std::vector<int> fds_;
    std::vector<int> free_fds_;
    std::mutex mutex_;

    NvBufSurf::NvCommonTransformParams transform_params_{};
};

} // namespace trb::video
