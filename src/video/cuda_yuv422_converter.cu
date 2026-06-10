#include "video/cuda_yuv422_converter.hpp"

#include <cstdint>

#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cudaEGL.h>

#include "nvbufsurface.h"

namespace trb::video
{
namespace
{

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

bool mapEglFrame(NvBufSurface *surface,
                 CUgraphicsResource *resource,
                 CUeglFrame *frame,
                 const char *stage,
                 CudaYuv422ConverterResult *result)
{
    if (NvBufSurfaceMapEglImage(surface, 0) != 0)
    {
        setFailure(result, stage, -1);
        return false;
    }

    const EGLImageKHR egl_image = surface->surfaceList[0].mappedAddr.eglImage;
    if (!egl_image)
    {
        (void)NvBufSurfaceUnMapEglImage(surface, 0);
        setFailure(result, stage, -2);
        return false;
    }

    CUresult cu_ret = cuGraphicsEGLRegisterImage(resource, egl_image, CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE);
    if (cu_ret != CUDA_SUCCESS)
    {
        (void)NvBufSurfaceUnMapEglImage(surface, 0);
        setFailure(result, stage, static_cast<int>(cu_ret));
        return false;
    }

    cu_ret = cuGraphicsResourceGetMappedEglFrame(frame, *resource, 0, 0);
    if (cu_ret != CUDA_SUCCESS)
    {
        (void)cuGraphicsUnregisterResource(*resource);
        *resource = nullptr;
        (void)NvBufSurfaceUnMapEglImage(surface, 0);
        setFailure(result, stage, static_cast<int>(cu_ret));
        return false;
    }

    return true;
}

void unmapEglFrame(NvBufSurface *surface, CUgraphicsResource resource)
{
    if (resource)
    {
        (void)cuGraphicsUnregisterResource(resource);
    }
    (void)NvBufSurfaceUnMapEglImage(surface, 0);
}

} // namespace

bool cudaYuv422PlanarToNv12(NvBufSurface *src, NvBufSurface *dst, CudaYuv422ConverterResult *result)
{
    if (result)
    {
        *result = CudaYuv422ConverterResult{};
    }

    if (!src || !dst || src->numFilled == 0 || dst->numFilled == 0)
    {
        setFailure(result, "validate-surface", -1);
        return false;
    }

    const auto &src_sp = src->surfaceList[0];
    const auto &dst_sp = dst->surfaceList[0];
    const auto &src_pp = src_sp.planeParams;
    const auto &dst_pp = dst_sp.planeParams;

    if (result)
    {
        result->src_color_format = static_cast<uint32_t>(src_sp.colorFormat);
        result->dst_color_format = static_cast<uint32_t>(dst_sp.colorFormat);
        result->src_plane_count = src_pp.num_planes;
        result->dst_plane_count = dst_pp.num_planes;
    }

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

    (void)cudaFree(nullptr);

    CUgraphicsResource src_resource = nullptr;
    CUgraphicsResource dst_resource = nullptr;
    CUeglFrame src_frame{};
    CUeglFrame dst_frame{};

    if (!mapEglFrame(src, &src_resource, &src_frame, "map-src-egl", result))
    {
        return false;
    }

    if (!mapEglFrame(dst, &dst_resource, &dst_frame, "map-dst-egl", result))
    {
        unmapEglFrame(src, src_resource);
        return false;
    }

    if (result)
    {
        result->src_frame_type = static_cast<uint32_t>(src_frame.frameType);
        result->dst_frame_type = static_cast<uint32_t>(dst_frame.frameType);
    }

    bool ok = true;
    if (src_frame.frameType != CU_EGL_FRAME_TYPE_PITCH ||
        dst_frame.frameType != CU_EGL_FRAME_TYPE_PITCH ||
        src_frame.planeCount < 3 ||
        dst_frame.planeCount < 2 ||
        !src_frame.frame.pPitch[0] ||
        !src_frame.frame.pPitch[1] ||
        !src_frame.frame.pPitch[2] ||
        !dst_frame.frame.pPitch[0] ||
        !dst_frame.frame.pPitch[1])
    {
        setFailure(result, "validate-egl-frame", -4);
        ok = false;
    }

    if (ok)
    {
        const int width = static_cast<int>(src_pp.width[0]);
        const int height = static_cast<int>(src_pp.height[0]);
        const int chroma_width = static_cast<int>(src_pp.width[1]);
        const int chroma_height = height / 2;

        const dim3 y_block(32, 8);
        const dim3 y_grid((width + y_block.x - 1) / y_block.x,
                          (height + y_block.y - 1) / y_block.y);
        copyYKernel<<<y_grid, y_block>>>(
            static_cast<const uint8_t *>(src_frame.frame.pPitch[0]),
            static_cast<uint8_t *>(dst_frame.frame.pPitch[0]),
            width,
            height,
            static_cast<int>(src_pp.pitch[0]),
            static_cast<int>(dst_pp.pitch[0]));

        const dim3 uv_block(32, 8);
        const dim3 uv_grid((chroma_width + uv_block.x - 1) / uv_block.x,
                           (chroma_height + uv_block.y - 1) / uv_block.y);
        yuv422PlanarToNv12UvKernel<<<uv_grid, uv_block>>>(
            static_cast<const uint8_t *>(src_frame.frame.pPitch[1]),
            static_cast<const uint8_t *>(src_frame.frame.pPitch[2]),
            static_cast<uint8_t *>(dst_frame.frame.pPitch[1]),
            chroma_width,
            chroma_height,
            static_cast<int>(src_pp.pitch[1]),
            static_cast<int>(src_pp.pitch[2]),
            static_cast<int>(dst_pp.pitch[1]));

        cudaError_t cuda_ret = cudaGetLastError();
        if (cuda_ret != cudaSuccess)
        {
            setFailure(result, "launch-kernel", static_cast<int>(cuda_ret));
            ok = false;
        }

        cuda_ret = cudaDeviceSynchronize();
        if (ok && cuda_ret != cudaSuccess)
        {
            setFailure(result, "sync-kernel", static_cast<int>(cuda_ret));
            ok = false;
        }
    }

    unmapEglFrame(dst, dst_resource);
    unmapEglFrame(src, src_resource);

    if (result)
    {
        result->ok = ok;
    }
    return ok;
}

} // namespace trb::video
