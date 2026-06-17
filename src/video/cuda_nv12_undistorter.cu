#include "video/cuda_nv12_undistorter.hpp"

#include <algorithm>
#include <chrono>
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

uint64_t elapsedUs(std::chrono::steady_clock::time_point start,
                   std::chrono::steady_clock::time_point end)
{
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
}

void setFailure(CudaNv12UndistorterResult *result, const char *stage, int error_code)
{
    if (!result)
    {
        return;
    }
    result->ok = false;
    result->error_stage = stage;
    result->error_code = error_code;
}

void fillSurfaceInfo(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result)
{
    if (!result)
    {
        return;
    }
    if (src && src->numFilled > 0)
    {
        const auto &sp = src->surfaceList[0];
        result->src_color_format = static_cast<uint32_t>(sp.colorFormat);
        result->src_plane_count = sp.planeParams.num_planes;
    }
    if (dst && dst->numFilled > 0)
    {
        const auto &sp = dst->surfaceList[0];
        result->dst_color_format = static_cast<uint32_t>(sp.colorFormat);
        result->dst_plane_count = sp.planeParams.num_planes;
    }
}

bool ensureCudaContext(bool &initialized, CudaNv12UndistorterResult *result)
{
    if (initialized)
    {
        return true;
    }
    const cudaError_t ret = cudaFree(nullptr);
    if (ret != cudaSuccess)
    {
        setFailure(result, "init-cuda", static_cast<int>(ret));
        return false;
    }
    initialized = true;
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
                 CudaNv12UndistorterResult *result)
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

bool validateOutputSurface(NvBufSurface *dst, CudaNv12UndistorterResult *result)
{
    if (!dst || dst->numFilled == 0)
    {
        setFailure(result, "validate-output", -1);
        return false;
    }
    fillSurfaceInfo(nullptr, dst, result);
    const auto &sp = dst->surfaceList[0];
    const auto &pp = sp.planeParams;
    if (sp.layout != NVBUF_LAYOUT_PITCH ||
        sp.colorFormat != NVBUF_COLOR_FORMAT_NV12 ||
        pp.num_planes < 2)
    {
        setFailure(result, "validate-output", -2);
        return false;
    }
    return true;
}

bool validateNv12Pair(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result)
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
    if (src_sp.layout != NVBUF_LAYOUT_PITCH ||
        dst_sp.layout != NVBUF_LAYOUT_PITCH ||
        src_sp.colorFormat != NVBUF_COLOR_FORMAT_NV12 ||
        dst_sp.colorFormat != NVBUF_COLOR_FORMAT_NV12 ||
        src_pp.num_planes < 2 ||
        dst_pp.num_planes < 2 ||
        src_pp.width[0] != dst_pp.width[0] ||
        src_pp.height[0] != dst_pp.height[0])
    {
        setFailure(result, "validate-nv12-format", -2);
        return false;
    }
    return true;
}

bool validateYuv422ToNv12Pair(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result)
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
    if (src_sp.layout != NVBUF_LAYOUT_PITCH ||
        dst_sp.layout != NVBUF_LAYOUT_PITCH ||
        src_sp.colorFormat != NVBUF_COLOR_FORMAT_YUV422 ||
        dst_sp.colorFormat != NVBUF_COLOR_FORMAT_NV12 ||
        src_pp.num_planes < 3 ||
        dst_pp.num_planes < 2 ||
        src_pp.width[0] != dst_pp.width[0] ||
        src_pp.height[0] != dst_pp.height[0])
    {
        setFailure(result, "validate-yuv422-format", -2);
        return false;
    }
    return true;
}

bool validateMappedFrames(const MappedEglFrame &src,
                          const MappedEglFrame &dst,
                          int src_planes,
                          CudaNv12UndistorterResult *result)
{
    if (result)
    {
        result->src_frame_type = static_cast<uint32_t>(src.frame.frameType);
        result->dst_frame_type = static_cast<uint32_t>(dst.frame.frameType);
    }

    const unsigned int expected_src_planes = static_cast<unsigned int>(std::max(src_planes, 0));
    if (src.frame.frameType != CU_EGL_FRAME_TYPE_PITCH ||
        dst.frame.frameType != CU_EGL_FRAME_TYPE_PITCH ||
        src.frame.planeCount < expected_src_planes ||
        dst.frame.planeCount < 2 ||
        !src.frame.frame.pPitch[0] ||
        !src.frame.frame.pPitch[1] ||
        (src_planes >= 3 && !src.frame.frame.pPitch[2]) ||
        !dst.frame.frame.pPitch[0] ||
        !dst.frame.frame.pPitch[1])
    {
        setFailure(result, "validate-egl-frame", -4);
        return false;
    }

    return true;
}

__device__ __forceinline__ float clampFloat(float value, float lo, float hi)
{
    return fminf(fmaxf(value, lo), hi);
}

__device__ __forceinline__ uint8_t bilinearU8(const uint8_t *plane,
                                              int pitch,
                                              int width,
                                              int height,
                                              float sx,
                                              float sy)
{
    sx = clampFloat(sx, 0.0f, static_cast<float>(width - 1));
    sy = clampFloat(sy, 0.0f, static_cast<float>(height - 1));
    const int x0 = static_cast<int>(floorf(sx));
    const int y0 = static_cast<int>(floorf(sy));
    const int x1 = min(x0 + 1, width - 1);
    const int y1 = min(y0 + 1, height - 1);
    const float fx = sx - static_cast<float>(x0);
    const float fy = sy - static_cast<float>(y0);

    const float p00 = static_cast<float>(plane[y0 * pitch + x0]);
    const float p10 = static_cast<float>(plane[y0 * pitch + x1]);
    const float p01 = static_cast<float>(plane[y1 * pitch + x0]);
    const float p11 = static_cast<float>(plane[y1 * pitch + x1]);
    const float top = p00 + (p10 - p00) * fx;
    const float bot = p01 + (p11 - p01) * fx;
    const float value = top + (bot - top) * fy;
    return static_cast<uint8_t>(clampFloat(value + 0.5f, 0.0f, 255.0f));
}

__device__ __forceinline__ uint8_t bilinearNv12Chroma(const uint8_t *uv_plane,
                                                      int pitch,
                                                      int chroma_width,
                                                      int chroma_height,
                                                      float sx,
                                                      float sy,
                                                      int channel)
{
    sx = clampFloat(sx, 0.0f, static_cast<float>(chroma_width - 1));
    sy = clampFloat(sy, 0.0f, static_cast<float>(chroma_height - 1));
    const int x0 = static_cast<int>(floorf(sx));
    const int y0 = static_cast<int>(floorf(sy));
    const int x1 = min(x0 + 1, chroma_width - 1);
    const int y1 = min(y0 + 1, chroma_height - 1);
    const float fx = sx - static_cast<float>(x0);
    const float fy = sy - static_cast<float>(y0);

    const float p00 = static_cast<float>(uv_plane[y0 * pitch + x0 * 2 + channel]);
    const float p10 = static_cast<float>(uv_plane[y0 * pitch + x1 * 2 + channel]);
    const float p01 = static_cast<float>(uv_plane[y1 * pitch + x0 * 2 + channel]);
    const float p11 = static_cast<float>(uv_plane[y1 * pitch + x1 * 2 + channel]);
    const float top = p00 + (p10 - p00) * fx;
    const float bot = p01 + (p11 - p01) * fx;
    const float value = top + (bot - top) * fy;
    return static_cast<uint8_t>(clampFloat(value + 0.5f, 0.0f, 255.0f));
}

__global__ void remapNv12YKernel(const uint8_t *src_y,
                                 uint8_t *dst_y,
                                 const float2 *map_xy,
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

    const float2 src = map_xy[y * width + x];
    dst_y[y * dst_pitch + x] = bilinearU8(src_y, src_pitch, width, height, src.x, src.y);
}

__global__ void remapNv12UvKernel(const uint8_t *src_uv,
                                  uint8_t *dst_uv,
                                  const float2 *map_xy,
                                  int width,
                                  int height,
                                  int src_pitch,
                                  int dst_pitch)
{
    const int x = static_cast<int>(blockIdx.x * blockDim.x + threadIdx.x);
    const int y = static_cast<int>(blockIdx.y * blockDim.y + threadIdx.y);
    const int chroma_width = width / 2;
    const int chroma_height = height / 2;
    if (x >= chroma_width || y >= chroma_height)
    {
        return;
    }

    const int luma_x = min(x * 2, width - 1);
    const int luma_y = min(y * 2, height - 1);
    const float2 src = map_xy[luma_y * width + luma_x];
    const float chroma_sx = src.x * 0.5f;
    const float chroma_sy = src.y * 0.5f;
    uint8_t *dst = dst_uv + y * dst_pitch + x * 2;
    dst[0] = bilinearNv12Chroma(src_uv, src_pitch, chroma_width, chroma_height, chroma_sx, chroma_sy, 0);
    dst[1] = bilinearNv12Chroma(src_uv, src_pitch, chroma_width, chroma_height, chroma_sx, chroma_sy, 1);
}

__global__ void remapYuv422ToNv12YKernel(const uint8_t *src_y,
                                         uint8_t *dst_y,
                                         const float2 *map_xy,
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
    const float2 src = map_xy[y * width + x];
    dst_y[y * dst_pitch + x] = bilinearU8(src_y, src_pitch, width, height, src.x, src.y);
}

__global__ void remapYuv422ToNv12UvKernel(const uint8_t *src_u,
                                          const uint8_t *src_v,
                                          uint8_t *dst_uv,
                                          const float2 *map_xy,
                                          int width,
                                          int height,
                                          int src_u_pitch,
                                          int src_v_pitch,
                                          int dst_pitch)
{
    const int x = static_cast<int>(blockIdx.x * blockDim.x + threadIdx.x);
    const int y = static_cast<int>(blockIdx.y * blockDim.y + threadIdx.y);
    const int dst_chroma_width = width / 2;
    const int dst_chroma_height = height / 2;
    const int src_chroma_width = width / 2;
    if (x >= dst_chroma_width || y >= dst_chroma_height)
    {
        return;
    }

    const int luma_x = min(x * 2, width - 1);
    const int luma_y = min(y * 2, height - 1);
    const float2 src = map_xy[luma_y * width + luma_x];
    const float chroma_sx = src.x * 0.5f;
    const float chroma_sy0 = src.y;
    const float chroma_sy1 = clampFloat(src.y + 1.0f, 0.0f, static_cast<float>(height - 1));
    const uint8_t u0 = bilinearU8(src_u, src_u_pitch, src_chroma_width, height, chroma_sx, chroma_sy0);
    const uint8_t u1 = bilinearU8(src_u, src_u_pitch, src_chroma_width, height, chroma_sx, chroma_sy1);
    const uint8_t v0 = bilinearU8(src_v, src_v_pitch, src_chroma_width, height, chroma_sx, chroma_sy0);
    const uint8_t v1 = bilinearU8(src_v, src_v_pitch, src_chroma_width, height, chroma_sx, chroma_sy1);

    uint8_t *dst = dst_uv + y * dst_pitch + x * 2;
    dst[0] = static_cast<uint8_t>((static_cast<unsigned>(u0) + static_cast<unsigned>(u1) + 1u) >> 1);
    dst[1] = static_cast<uint8_t>((static_cast<unsigned>(v0) + static_cast<unsigned>(v1) + 1u) >> 1);
}

} // namespace

class CudaNv12Undistorter::Impl
{
public:
    ~Impl()
    {
        reset();
    }

    bool initialize(uint32_t width, uint32_t height, const std::vector<float> &map_xy)
    {
        reset();
        width_ = width;
        height_ = height;
        if (width_ == 0 || height_ == 0 || map_xy.size() != static_cast<size_t>(width_) * height_ * 2u)
        {
            return false;
        }

        CudaNv12UndistorterResult result;
        if (!ensureCudaContext(cuda_initialized_, &result))
        {
            return false;
        }

        cudaError_t ret = cudaStreamCreateWithFlags(&stream_, cudaStreamNonBlocking);
        if (ret != cudaSuccess)
        {
            stream_ = nullptr;
            return false;
        }
        ret = cudaEventCreateWithFlags(&done_event_, cudaEventDisableTiming);
        if (ret != cudaSuccess)
        {
            cudaStreamDestroy(stream_);
            stream_ = nullptr;
            done_event_ = nullptr;
            return false;
        }

        const size_t bytes = map_xy.size() * sizeof(float);
        ret = cudaMalloc(reinterpret_cast<void **>(&map_xy_device_), bytes);
        if (ret != cudaSuccess)
        {
            map_xy_device_ = nullptr;
            reset();
            return false;
        }
        ret = cudaMemcpy(map_xy_device_, map_xy.data(), bytes, cudaMemcpyHostToDevice);
        if (ret != cudaSuccess)
        {
            reset();
            return false;
        }
        return true;
    }

    bool prepareOutput(NvBufSurface *dst, CudaNv12UndistorterResult *result)
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

    bool remapNv12(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result)
    {
        if (result)
        {
            *result = CudaNv12UndistorterResult{};
        }
        if (!map_xy_device_ || !validateNv12Pair(src, dst, result) || !prepareOutput(dst, result))
        {
            return false;
        }

        return remapCommon(src, dst, 2, false, result);
    }

    bool remapYuv422ToNv12(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result)
    {
        if (result)
        {
            *result = CudaNv12UndistorterResult{};
        }
        if (!map_xy_device_ || !validateYuv422ToNv12Pair(src, dst, result) || !prepareOutput(dst, result))
        {
            return false;
        }

        return remapCommon(src, dst, 3, true, result);
    }

    void reset()
    {
        for (auto &mapped : outputs_)
        {
            resetMappedFrame(mapped);
        }
        outputs_.clear();
        if (map_xy_device_)
        {
            cudaFree(map_xy_device_);
            map_xy_device_ = nullptr;
        }
        if (done_event_)
        {
            cudaEventDestroy(done_event_);
            done_event_ = nullptr;
        }
        if (stream_)
        {
            cudaStreamDestroy(stream_);
            stream_ = nullptr;
        }
        cuda_initialized_ = false;
        width_ = 0;
        height_ = 0;
    }

private:
    bool remapCommon(NvBufSurface *src,
                     NvBufSurface *dst,
                     int src_planes,
                     bool src_yuv422,
                     CudaNv12UndistorterResult *result)
    {
        auto *dst_frame = findOutput(dst);
        if (!dst_frame)
        {
            setFailure(result, "find-dst-egl", -5);
            return false;
        }

        MappedEglFrame src_frame;
        const auto map_start = std::chrono::steady_clock::now();
        if (!mapEglFrame(src, src_frame, "map-src-egl", result))
        {
            return false;
        }
        const auto map_end = std::chrono::steady_clock::now();

        const bool mapped_ok = validateMappedFrames(src_frame, *dst_frame, src_planes, result);
        bool kernel_ok = false;
        if (mapped_ok)
        {
            const auto kernel_start = std::chrono::steady_clock::now();
            kernel_ok = src_yuv422
                ? launchYuv422(src, dst, src_frame, *dst_frame, result)
                : launchNv12(src, dst, src_frame, *dst_frame, result);
            const auto kernel_end = std::chrono::steady_clock::now();
            if (result)
            {
                result->kernel_us = static_cast<int64_t>(elapsedUs(kernel_start, kernel_end));
            }
        }
        resetMappedFrame(src_frame);
        if (result)
        {
            result->map_us = static_cast<int64_t>(elapsedUs(map_start, map_end));
        }
        return mapped_ok && kernel_ok;
    }

    bool launchNv12(NvBufSurface *src,
                    NvBufSurface *dst,
                    const MappedEglFrame &src_frame,
                    const MappedEglFrame &dst_frame,
                    CudaNv12UndistorterResult *result)
    {
        const auto &src_pp = src->surfaceList[0].planeParams;
        const auto &dst_pp = dst->surfaceList[0].planeParams;
        const int width = static_cast<int>(src_pp.width[0]);
        const int height = static_cast<int>(src_pp.height[0]);
        if (width != static_cast<int>(width_) || height != static_cast<int>(height_))
        {
            setFailure(result, "validate-map-size", -6);
            return false;
        }

        const dim3 y_block(32, 8);
        const dim3 y_grid((width + y_block.x - 1) / y_block.x,
                          (height + y_block.y - 1) / y_block.y);
        remapNv12YKernel<<<y_grid, y_block, 0, stream_>>>(
            static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[0]),
            static_cast<uint8_t *>(dst_frame.frame.frame.pPitch[0]),
            map_xy_device_,
            width,
            height,
            static_cast<int>(src_pp.pitch[0]),
            static_cast<int>(dst_pp.pitch[0]));

        const dim3 uv_block(32, 8);
        const dim3 uv_grid(((width / 2) + uv_block.x - 1) / uv_block.x,
                           ((height / 2) + uv_block.y - 1) / uv_block.y);
        remapNv12UvKernel<<<uv_grid, uv_block, 0, stream_>>>(
            static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[1]),
            static_cast<uint8_t *>(dst_frame.frame.frame.pPitch[1]),
            map_xy_device_,
            width,
            height,
            static_cast<int>(src_pp.pitch[1]),
            static_cast<int>(dst_pp.pitch[1]));

        return syncKernel(result);
    }

    bool launchYuv422(NvBufSurface *src,
                      NvBufSurface *dst,
                      const MappedEglFrame &src_frame,
                      const MappedEglFrame &dst_frame,
                      CudaNv12UndistorterResult *result)
    {
        const auto &src_pp = src->surfaceList[0].planeParams;
        const auto &dst_pp = dst->surfaceList[0].planeParams;
        const int width = static_cast<int>(src_pp.width[0]);
        const int height = static_cast<int>(src_pp.height[0]);
        if (width != static_cast<int>(width_) || height != static_cast<int>(height_))
        {
            setFailure(result, "validate-map-size", -6);
            return false;
        }

        const dim3 y_block(32, 8);
        const dim3 y_grid((width + y_block.x - 1) / y_block.x,
                          (height + y_block.y - 1) / y_block.y);
        remapYuv422ToNv12YKernel<<<y_grid, y_block, 0, stream_>>>(
            static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[0]),
            static_cast<uint8_t *>(dst_frame.frame.frame.pPitch[0]),
            map_xy_device_,
            width,
            height,
            static_cast<int>(src_pp.pitch[0]),
            static_cast<int>(dst_pp.pitch[0]));

        const dim3 uv_block(32, 8);
        const dim3 uv_grid(((width / 2) + uv_block.x - 1) / uv_block.x,
                           ((height / 2) + uv_block.y - 1) / uv_block.y);
        remapYuv422ToNv12UvKernel<<<uv_grid, uv_block, 0, stream_>>>(
            static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[1]),
            static_cast<const uint8_t *>(src_frame.frame.frame.pPitch[2]),
            static_cast<uint8_t *>(dst_frame.frame.frame.pPitch[1]),
            map_xy_device_,
            width,
            height,
            static_cast<int>(src_pp.pitch[1]),
            static_cast<int>(src_pp.pitch[2]),
            static_cast<int>(dst_pp.pitch[1]));

        return syncKernel(result);
    }

    bool syncKernel(CudaNv12UndistorterResult *result)
    {
        cudaError_t ret = cudaGetLastError();
        if (ret != cudaSuccess)
        {
            setFailure(result, "launch-kernel", static_cast<int>(ret));
            return false;
        }
        const auto sync_start = std::chrono::steady_clock::now();
        ret = cudaEventRecord(done_event_, stream_);
        if (ret == cudaSuccess)
        {
            ret = cudaEventSynchronize(done_event_);
        }
        const auto sync_end = std::chrono::steady_clock::now();
        if (result)
        {
            result->sync_us = static_cast<int64_t>(elapsedUs(sync_start, sync_end));
        }
        if (ret != cudaSuccess)
        {
            setFailure(result, "sync-kernel", static_cast<int>(ret));
            return false;
        }
        if (result)
        {
            result->ok = true;
        }
        return true;
    }

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
    uint32_t width_ = 0;
    uint32_t height_ = 0;
    float2 *map_xy_device_ = nullptr;
    cudaStream_t stream_ = nullptr;
    cudaEvent_t done_event_ = nullptr;
    std::vector<MappedEglFrame> outputs_;
};

CudaNv12Undistorter::CudaNv12Undistorter()
    : impl_(std::make_unique<Impl>())
{
}

CudaNv12Undistorter::~CudaNv12Undistorter() = default;

bool CudaNv12Undistorter::initialize(uint32_t width, uint32_t height, const std::vector<float> &map_xy)
{
    return impl_->initialize(width, height, map_xy);
}

bool CudaNv12Undistorter::prepareOutput(NvBufSurface *dst, CudaNv12UndistorterResult *result)
{
    return impl_->prepareOutput(dst, result);
}

bool CudaNv12Undistorter::remapNv12(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result)
{
    return impl_->remapNv12(src, dst, result);
}

bool CudaNv12Undistorter::remapYuv422ToNv12(NvBufSurface *src, NvBufSurface *dst, CudaNv12UndistorterResult *result)
{
    return impl_->remapYuv422ToNv12(src, dst, result);
}

void CudaNv12Undistorter::reset()
{
    impl_->reset();
}

} // namespace trb::video
