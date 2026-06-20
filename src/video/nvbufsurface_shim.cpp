#include "NvBufSurface.h"

int NvBufSurf::NvDestroy(int fd)
{
    if (fd <= 0)
    {
        return -1;
    }
    NvBufSurface *surface = nullptr;
    if (NvBufSurfaceFromFd(fd, reinterpret_cast<void **>(&surface)) != 0 || !surface)
    {
        return -1;
    }
    return NvBufSurfaceDestroy(surface);
}

int NvBufSurf::NvAllocate(NvCommonAllocateParams *allocateParams, uint32_t numBuffers, int *fd)
{
    if (!allocateParams || !fd || numBuffers < 1)
    {
        return -1;
    }

    for (uint32_t index = 0; index < numBuffers; ++index)
    {
        NvBufSurfaceAllocateParams input_params{};
        input_params.params.width = allocateParams->width;
        input_params.params.height = allocateParams->height;
        input_params.params.memType = allocateParams->memType;
        input_params.params.layout = allocateParams->layout;
        input_params.params.colorFormat = allocateParams->colorFormat;
        input_params.memtag = allocateParams->memtag;
        input_params.chromaSubsampling.chromaLocHoriz = allocateParams->chromaSubsampling.chromaLocHoriz;
        input_params.chromaSubsampling.chromaLocVert = allocateParams->chromaSubsampling.chromaLocVert;

        NvBufSurface *surface = nullptr;
        if (NvBufSurfaceAllocate(&surface, 1, &input_params) != 0 || !surface)
        {
            fd[index] = -1;
            return -1;
        }
        surface->numFilled = 1;
        fd[index] = surface->surfaceList[0].bufferDesc;
    }

    return 0;
}

int NvBufSurf::NvCopy(int src_fd, int dst_fd)
{
    NvBufSurface *src = nullptr;
    NvBufSurface *dst = nullptr;
    if (NvBufSurfaceFromFd(src_fd, reinterpret_cast<void **>(&src)) != 0 || !src ||
        NvBufSurfaceFromFd(dst_fd, reinterpret_cast<void **>(&dst)) != 0 || !dst)
    {
        return -1;
    }
    return NvBufSurfaceCopy(src, dst);
}

NvBufSurface *NvBufSurf::NvGetSurfaceFromFd(int fd)
{
    NvBufSurface *surface = nullptr;
    if (NvBufSurfaceFromFd(fd, reinterpret_cast<void **>(&surface)) != 0)
    {
        return nullptr;
    }
    return surface;
}
