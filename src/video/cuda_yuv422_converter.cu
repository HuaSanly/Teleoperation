#include "video/cuda_yuv422_converter.hpp"

#include <cstdint>
#include <memory>
#include <vector>

#include <EGL/egl.h>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cudaEGL.h>

#include "nvbufsurface.h"

namespace trb::video
{
namespace
{

struct MappedEglFrame
{
    NvBufSurface *surface = nullptr;
    int fd = -1;
    CUgraphicsResource resource = nullptr;
    CUeglFrame frame{};
    bool valid = false;
};

void setFailure(CudaYuv422ConverterResult *result, const char *stage, int error_code)
{
    if (!result)
    {
        return;
    }
    result->ok = false;
    result->error_stage = stage;
    result->error_code = error_code;
}

void fillSurfaceInfo(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result)
{
    if (!result)
    {
        return;
    }
    if (src && src->numFilled > 0)
    {
        const auto &src_sp = src->surfaceList[0];
        result->src_color_format = static_cast<uint32_t>(src_sp.colorFormat);
        result->src_plane_count = src_sp.planeParams.num_planes;
    }
    if (dst && dst->numFilled > 0)
    {
        const auto &dst_sp = dst->surfaceList[0];
        result->dst_color_format = static_cast<uint32_t>(dst_sp.colorFormat);
        result->dst_plane_count = dst_sp.planeParams.num_planes;
    }
}

bool validateSurfacePair(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result)
{
    if (!src || !dst || src->numFilled == 0 || dst->numFilled == 0)
    {
        setFailure(result, "validate-surface", -1);
        return false;
    }

    fillSurfaceInfo(src, dst, result);

    const auto &src_sp = src->surfaceList[0];
    const auto &dst_sp = dst->surfaceList[0];
    const auto &src_pp = src_sp.planeParams;
    const auto &dst_pp = dst_sp.planeParams;

    if (src_sp.layout != NVBUF_LAYOUT_PITCH || dst_sp.layout != NVBUF_LAYOUT_PITCH ||
        src_sp.colorFormat != NVBUF_COLOR_FORMAT_YUV422 ||
        dst_sp.colorFormat != NVBUF_COLOR_FORMAT_NV12 ||
        src_pp.num_planes < 3 || dst_pp.num_planes < 2 ||
        src_pp.width[0] != dst_pp.width[0] ||
        src_pp.height[0] != dst_pp.height[0] ||
        src_pp.height[0] < 2 || (src_pp.height[0] & 1u))
    {
        setFailure(result, "validate-format", -2);
        return false;
    }

    return true;
}

bool validateOutputSurface(NvBufSurface *dst, CudaYuv422ConverterResult *result)
{
    if (!dst || dst->numFilled == 0)
    {
        setFailure(result, "validate-output", -1);
        return false;
    }

    fillSurfaceInfo(nullptr, dst, result);

    const auto &dst_sp = dst->surfaceList[0];
    const auto &dst_pp = dst_sp.planeParams;
    if (dst_sp.layout != NVBUF_LAYOUT_PITCH ||
        dst_sp.colorFormat != NVBUF_COLOR_FORMAT_NV12 ||
        dst_pp.num_planes < 2)
    {
        setFailure(result, "validate-output", -2);
        return false;
    }
    return true;
}

void resetMappedFrame(MappedEglFrame &mapped)
{
    if (mapped.resource)
    {
        (void)cuGraphicsUnregisterResource(mapped.resource);
    }
    if (mapped.surface)
    {
        (void)NvBufSurfaceUnMapEglImage(mapped.surface, 0);
    }
    mapped = MappedEglFrame{};
}

bool mapEglFrame(NvBufSurface *surface,
                 MappedEglFrame &mapped,
                 const char *stage,
                 CudaYuv422ConverterResult *result)
{
    if (!surface || surface->numFilled == 0)
    {
        setFailure(result, stage, -1);
        return false;
    }

    const int fd = surface->surfaceList[0].bufferDesc;
    if (mapped.valid && mapped.surface == surface && mapped.fd == fd)
    {
        return true;
    }

    resetMappedFrame(mapped);

    if (NvBufSurfaceMapEglImage(surface, 0) != 0)
    {
        setFailure(result, stage, -2);
        return false;
    }

    const EGLImageKHR egl_image = static_cast<EGLImageKHR>(surface->surfaceList[0].mappedAddr.eglImage);
    if (!egl_image)
    {
        (void)NvBufSurfaceUnMapEglImage(surface, 0);
        setFailure(result, stage, -3);
        return false;
    }

    CUgraphicsResource resource = nullptr;
    CUresult cu_ret = cuGraphicsEGLRegisterImage(&resource, egl_image, CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE);
    if (cu_ret != CUDA_SUCCESS)
    {
        (void)NvBufSurfaceUnMapEglImage(surface, 0);
        setFailure(result, stage, static_cast<int>(cu_ret));
        return false;
    }

    CUeglFrame frame{};
    cu_ret = cuGraphicsResourceGetMappedEglFrame(&frame, resource, 0, 0);
    if (cu_ret != CUDA_SUCCESS)
    {
        (void)cuGraphicsUnregisterResource(resource);
        (void)NvBufSurfaceUnMapEglImage(surface, 0);
        setFailure(result, stage, static_cast<int>(cu_ret));
        return false;
    }

    mapped.surface = surface;
    mapped.fd = fd;
    mapped.resource = resource;
    mapped.frame = frame;
    mapped.valid = true;
    return true;
}

bool ensureCudaContext(bool &initialized, CudaYuv422ConverterResult *result)
{
    if (initialized)
    {
        return true;
    }

    const cudaError_t cuda_ret = cudaFree(nullptr);
    if (cuda_ret != cudaSuccess)
    {
        setFailure(result, "init-cuda", static_cast<int>(cuda_ret));
        return false;
    }

    initialized = true;
    return true;
}

bool validateMappedFrames(const MappedEglFrame &src,
                          const MappedEglFrame &dst,
                          CudaYuv422ConverterResult *result)
{
    if (result)
    {
        result->src_frame_type = static_cast<uint32_t>(src.frame.frameType);
        result->dst_frame_type = static_cast<uint32_t>(dst.frame.frameType);
    }

    if (src.frame.frameType != CU_EGL_FRAME_TYPE_PITCH ||
        dst.frame.frameType != CU_EGL_FRAME_TYPE_PITCH ||
        src.frame.planeCount < 3 ||
        dst.frame.planeCount < 2 ||
        !src.frame.frame.pPitch[0] ||
        !src.frame.frame.pPitch[1] ||
        !src.frame.frame.pPitch[2] ||
        !dst.frame.frame.pPitch[0] ||
        !dst.frame.frame.pPitch[1])
    {
        setFailure(result, "validate-egl-frame", -4);
        return false;
    }

    return true;
}

__global__ void copyYKernel(const uint8_t *src_y,
                            uint8_t *dst_y,
                            int width,
                            int height,
                            int src_pitch,
                            int dst_pitch)
{
    const int x = static_cast<int>(blockIdx.x * blockDim.x + threadIdx.x);
    const int y = static_cast<int>(blockIdx.y * blockDim.y + threadIdx.y);
    if (x >= width || y >= height)
    {
        return;
    }

    dst_y[y * dst_pitch + x] = src_y[y * src_pitch + x];
}

__global__ void yuv422PlanarToNv12UvKernel(const uint8_t *src_u,
                                           const uint8_t *src_v,
                                           uint8_t *dst_uv,
                                           int chroma_width,
                                           int chroma_height,
                                           int src_u_pitch,
                                           int src_v_pitch,
                                           int dst_uv_pitch)
{
    const int x = static_cast<int>(blockIdx.x * blockDim.x + threadIdx.x);
    const int y = static_cast<int>(blockIdx.y * blockDim.y + threadIdx.y);
    if (x >= chroma_width || y >= chroma_height)
    {
        return;
    }

    const int src_y0 = y * 2;
    const int src_y1 = src_y0 + 1;
    const uint8_t u0 = src_u[src_y0 * src_u_pitch + x];
    const uint8_t u1 = src_u[src_y1 * src_u_pitch + x];
    const uint8_t v0 = src_v[src_y0 * src_v_pitch + x];
    const uint8_t v1 = src_v[src_y1 * src_v_pitch + x];
    uint8_t *uv = dst_uv + y * dst_uv_pitch + x * 2;
    uv[0] = static_cast<uint8_t>((static_cast<unsigned>(u0) + static_cast<unsigned>(u1) + 1u) >> 1);
    uv[1] = static_cast<uint8_t>((static_cast<unsigned>(v0) + static_cast<unsigned>(v1) + 1u) >> 1);
}

bool launchConversion(NvBufSurface *src,
                      NvBufSurface *dst,
                      const MappedEglFrame &src_frame,
                      const MappedEglFrame &dst_frame,
                      CudaYuv422ConverterResult *result)
{
    const auto &src_pp = src->surfaceList[0].planeParams;
    const auto &dst_pp = dst->surfaceList[0].planeParams;
    const int width = static_cast<int>(src_pp.width[0]);
    const int height = static_cast<int>(src_pp.height[0]);
    const int chroma_width = static_cast<int>(src_pp.width[1]);
    const int chroma_height = height / 2;

    const dim3 y_block(32, 8);
    const dim3 y_grid((width + y_block.x - 1) / y_block.x,
                      (height + y_block.y - 1) / y_block.y);
    copyYKernel<<<y_grid, y_block>>>(
        static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[0]),
        static_cast<uint8_t *>(dst_frame.frame.frame.pPitch[0]),
        width,
        height,
        static_cast<int>(src_pp.pitch[0]),
        static_cast<int>(dst_pp.pitch[0]));

    const dim3 uv_block(32, 8);
    const dim3 uv_grid((chroma_width + uv_block.x - 1) / uv_block.x,
                       (chroma_height + uv_block.y - 1) / uv_block.y);
    yuv422PlanarToNv12UvKernel<<<uv_grid, uv_block>>>(
        static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[1]),
        static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[2]),
        static_cast<uint8_t *>(dst_frame.frame.frame.pPitch[1]),
        chroma_width,
        chroma_height,
        static_cast<int>(src_pp.pitch[1]),
        static_cast<int>(src_pp.pitch[2]),
        static_cast<int>(dst_pp.pitch[1]));

    cudaError_t cuda_ret = cudaGetLastError();
    if (cuda_ret != cudaSuccess)
    {
        setFailure(result, "launch-kernel", static_cast<int>(cuda_ret));
        return false;
    }

    cuda_ret = cudaDeviceSynchronize();
    if (cuda_ret != cudaSuccess)
    {
        setFailure(result, "sync-kernel", static_cast<int>(cuda_ret));
        return false;
    }

    if (result)
    {
        result->ok = true;
    }
    return true;
}

} // namespace

class CudaYuv422Converter::Impl
{
public:
    ~Impl()
    {
        reset();
    }

    bool prepareOutput(NvBufSurface *dst, CudaYuv422ConverterResult *result)
    {
        if (!validateOutputSurface(dst, result) || !ensureCudaContext(cuda_initialized_, result))
        {
            return false;
        }

        if (findOutput(dst))
        {
            return true;
        }

        outputs_.emplace_back();
        MappedEglFrame &mapped = outputs_.back();
        if (!mapEglFrame(dst, mapped, "map-dst-egl", result))
        {
            outputs_.pop_back();
            return false;
        }

        if (mapped.frame.frameType != CU_EGL_FRAME_TYPE_PITCH ||
            mapped.frame.planeCount < 2 ||
            !mapped.frame.frame.pPitch[0] ||
            !mapped.frame.frame.pPitch[1])
        {
            if (result)
            {
                result->dst_frame_type = static_cast<uint32_t>(mapped.frame.frameType);
            }
            setFailure(result, "validate-dst-egl-frame", -4);
            resetMappedFrame(mapped);
            outputs_.pop_back();
            return false;
        }

        return true;
    }

    bool convert(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result)
    {
        if (result)
        {
            *result = CudaYuv422ConverterResult{};
        }

        if (!validateSurfacePair(src, dst, result) || !prepareOutput(dst, result))
        {
            return false;
        }

        MappedEglFrame *dst_frame = findOutput(dst);
        if (!dst_frame)
        {
            setFailure(result, "find-dst-egl", -5);
            return false;
        }

        MappedEglFrame src_frame;
        if (!mapEglFrame(src, src_frame, "map-src-egl", result))
        {
            return false;
        }

        const bool ok = validateMappedFrames(src_frame, *dst_frame, result) &&
                        launchConversion(src, dst, src_frame, *dst_frame, result);
        resetMappedFrame(src_frame);
        return ok;
    }

    void reset()
    {
        for (auto &mapped : outputs_)
        {
            resetMappedFrame(mapped);
        }
        outputs_.clear();
        cuda_initialized_ = false;
    }

private:
    MappedEglFrame *findOutput(NvBufSurface *surface)
    {
        if (!surface || surface->numFilled == 0)
        {
            return nullptr;
        }

        const int fd = surface->surfaceList[0].bufferDesc;
        for (auto &mapped : outputs_)
        {
            if (mapped.valid && mapped.surface == surface && mapped.fd == fd)
            {
                return &mapped;
            }
        }
        return nullptr;
    }

    bool cuda_initialized_ = false;
    std::vector<MappedEglFrame> outputs_;
};

CudaYuv422Converter::CudaYuv422Converter()
    : impl_(std::make_unique<Impl>())
{
}

CudaYuv422Converter::~CudaYuv422Converter() = default;

bool CudaYuv422Converter::prepareOutput(NvBufSurface *dst, CudaYuv422ConverterResult *result)
{
    return impl_->prepareOutput(dst, result);
}

bool CudaYuv422Converter::convert(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result)
{
    return impl_->convert(src, dst, result);
}

void CudaYuv422Converter::reset()
{
    impl_->reset();
}

bool cudaYuv422PlanarToNv12(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result)
{
    CudaYuv422Converter converter;
    if (!converter.prepareOutput(dst, result))
    {
        return false;
    }
    return converter.convert(src, dst, result);
}

} // namespace trb::video
