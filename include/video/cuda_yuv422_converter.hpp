#pragma once

#include <cstdint>
#include <memory>

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

class CudaYuv422Converter
{
public:
    CudaYuv422Converter();
    ~CudaYuv422Converter();

    CudaYuv422Converter(const CudaYuv422Converter &) = delete;
    CudaYuv422Converter &operator=(const CudaYuv422Converter &) = delete;

    bool prepareOutput(NvBufSurface *dst, CudaYuv422ConverterResult *result);
    bool convert(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result);
    void reset();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

bool cudaYuv422PlanarToNv12(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result);

} // namespace trb::video
