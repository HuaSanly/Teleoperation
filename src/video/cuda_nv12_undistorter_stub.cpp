#include "video/cuda_nv12_undistorter.hpp"

namespace trb::video
{

class CudaNv12Undistorter::Impl
{
};

CudaNv12Undistorter::CudaNv12Undistorter()
    : impl_(std::make_unique<Impl>())
{
}

CudaNv12Undistorter::~CudaNv12Undistorter() = default;

bool CudaNv12Undistorter::initialize(uint32_t, uint32_t, const std::vector<float> &)
{
    return false;
}

bool CudaNv12Undistorter::prepareOutput(NvBufSurface *, CudaNv12UndistorterResult *)
{
    return false;
}

bool CudaNv12Undistorter::remapNv12(NvBufSurface *, NvBufSurface *, CudaNv12UndistorterResult *)
{
    return false;
}

bool CudaNv12Undistorter::remapYuv422ToNv12(NvBufSurface *, NvBufSurface *, CudaNv12UndistorterResult *)
{
    return false;
}

void CudaNv12Undistorter::reset()
{
}

} // namespace trb::video
