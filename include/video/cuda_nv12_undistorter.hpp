#pragma once

#include <cstdint>
#include <memory>
#include <vector>

struct NvBufSurface;

namespace trb::video
{

struct CudaNv12UndistorterResult
{
    bool ok = false;
    int error_code = 0;
    const char *error_stage = "";
    uint32_t src_frame_type = 0;
    uint32_t dst_frame_type = 0;
    uint32_t src_color_format = 0;
    uint32_t dst_color_format = 0;
    uint32_t src_plane_count = 0;
    uint32_t dst_plane_count = 0;
    int64_t map_us = 0;
    int64_t kernel_us = 0;
    int64_t sync_us = 0;
};

class CudaNv12Undistorter
{
public:
    CudaNv12Undistorter();
    ~CudaNv12Undistorter();

    CudaNv12Undistorter(const CudaNv12Undistorter &) = delete;
    CudaNv12Undistorter &operator=(const CudaNv12Undistorter &) = delete;

    bool initialize(uint32_t width, uint32_t height, const std::vector<float> &map_xy);
    bool prepareOutput(NvBufSurface *dst, CudaNv12UndistorterResult *result);
    bool remapNv12(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result);
    bool remapYuv422ToNv12(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result);
    void reset();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace trb::video
