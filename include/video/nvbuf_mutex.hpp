/**
 * @file nvbuf_mutex.hpp
 * @brief Global mutex for serializing selected NvBufSurface operations.
 * 
 * Some Jetson NvBufSurface helper calls touch process-global bookkeeping.
 * Keep those calls serialized while CUDA kernels run outside this lock.
 */

#pragma once

#include <mutex>

namespace trb::video
{

/**
 * @brief Global mutex for NvBufSurface metadata/helper operations.
 * 
 * Use this lock around any of the following operations:
 * - NvBufSurfaceMap() / NvBufSurfaceUnMap()
 * - NvBufSurfaceSyncForCpu() / NvBufSurfaceSyncForDevice()
 * - NvBufSurfaceFromFd()
 */
inline std::mutex& getNvBufMutex()
{
    static std::mutex mutex;
    return mutex;
}

} // namespace trb::video
