#pragma once

#include <cstdint>

struct NvBufSurface;

namespace trb::video
{

struct CudaYuv422ConverterResult
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
};

bool cudaYuv422PlanarToNv12(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result);

} // namespace trb::video
