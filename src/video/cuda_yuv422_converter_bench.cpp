#include "video/cuda_yuv422_converter.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "nvbufsurface.h"
#include "nvbufsurftransform.h"

namespace
{

struct Options
{
    uint32_t width = 3840;
    uint32_t height = 1520;
    int iterations = 200;
    int warmup = 20;
    NvBufSurfaceLayout src_layout = NVBUF_LAYOUT_PITCH;
    NvBufSurfaceLayout dst_layout = NVBUF_LAYOUT_PITCH;
};

struct TimingStats
{
    double avg_us = 0.0;
    int64_t min_us = 0;
    int64_t p50_us = 0;
    int64_t p90_us = 0;
    int64_t p99_us = 0;
    int64_t max_us = 0;
};

uint8_t yValue(uint32_t x, uint32_t y)
{
    return static_cast<uint8_t>((x * 3u + y * 5u) & 0xffu);
}

uint8_t uValue(uint32_t x, uint32_t y)
{
    return static_cast<uint8_t>((64u + x * 7u + y * 3u) & 0xffu);
}

uint8_t vValue(uint32_t x, uint32_t y)
{
    return static_cast<uint8_t>((192u + x * 5u + y * 11u) & 0xffu);
}

void printUsage(const char *argv0)
{
    std::cerr << "Usage: " << argv0
              << " [--width W] [--height H] [--iterations N] [--warmup N]"
              << " [--src-layout pitch|block] [--dst-layout pitch|block]\n";
}

const char *layoutName(NvBufSurfaceLayout layout)
{
    return layout == NVBUF_LAYOUT_BLOCK_LINEAR ? "block" : "pitch";
}

bool parseLayout(const std::string &value, NvBufSurfaceLayout &layout)
{
    if (value == "pitch")
    {
        layout = NVBUF_LAYOUT_PITCH;
        return true;
    }
    if (value == "block")
    {
        layout = NVBUF_LAYOUT_BLOCK_LINEAR;
        return true;
    }
    return false;
}

bool parseArgs(int argc, char **argv, Options &options)
{
    for (int i = 1; i < argc; ++i)
    {
        const std::string arg = argv[i];
        auto requireValue = [&](uint32_t &value) {
            if (++i >= argc)
            {
                return false;
            }
            value = static_cast<uint32_t>(std::stoul(argv[i]));
            return true;
        };
        auto requireInt = [&](int &value) {
            if (++i >= argc)
            {
                return false;
            }
            value = std::stoi(argv[i]);
            return true;
        };

        if (arg == "--width")
        {
            if (!requireValue(options.width))
            {
                return false;
            }
        }
        else if (arg == "--height")
        {
            if (!requireValue(options.height))
            {
                return false;
            }
        }
        else if (arg == "--iterations")
        {
            if (!requireInt(options.iterations))
            {
                return false;
            }
        }
        else if (arg == "--warmup")
        {
            if (!requireInt(options.warmup))
            {
                return false;
            }
        }
        else if (arg == "--src-layout")
        {
            if (++i >= argc || !parseLayout(argv[i], options.src_layout))
            {
                return false;
            }
        }
        else if (arg == "--dst-layout")
        {
            if (++i >= argc || !parseLayout(argv[i], options.dst_layout))
            {
                return false;
            }
        }
        else if (arg == "--help" || arg == "-h")
        {
            printUsage(argv[0]);
            return false;
        }
        else
        {
            std::cerr << "Unknown argument: " << arg << '\n';
            return false;
        }
    }

    return options.width > 0 && options.height > 0 && (options.height % 2u) == 0u &&
           options.iterations > 0 && options.warmup >= 0;
}

NvBufSurface *createSurface(uint32_t width,
                            uint32_t height,
                            NvBufSurfaceColorFormat format,
                            NvBufSurfaceLayout layout)
{
    NvBufSurfaceCreateParams params;
    std::memset(&params, 0, sizeof(params));
    params.gpuId = 0;
    params.width = width;
    params.height = height;
    params.layout = layout;
    params.colorFormat = format;
    params.memType = NVBUF_MEM_SURFACE_ARRAY;
    params.isContiguous = true;

    NvBufSurface *surface = nullptr;
    if (NvBufSurfaceCreate(&surface, 1, &params) != 0)
    {
        return nullptr;
    }
    surface->numFilled = 1;
    return surface;
}

bool fillYuv422Surface(NvBufSurface *surface)
{
    if (!surface || surface->numFilled == 0)
    {
        return false;
    }

    auto &sp = surface->surfaceList[0];
    auto &pp = sp.planeParams;
    if (pp.num_planes < 3)
    {
        std::cerr << "YUV422 surface has " << pp.num_planes << " plane(s), expected 3\n";
        return false;
    }

    if (sp.layout != NVBUF_LAYOUT_PITCH)
    {
        for (uint32_t plane = 0; plane < 3; ++plane)
        {
            if (NvBufSurfaceMemSet(surface, 0, static_cast<int>(plane),
                                   plane == 0 ? 0x40 : 0x80) != 0)
            {
                std::cerr << "NvBufSurfaceMemSet failed for block-linear source plane "
                          << plane << '\n';
                return false;
            }
        }
        return true;
    }

    for (uint32_t plane = 0; plane < 3; ++plane)
    {
        if (NvBufSurfaceMap(surface, 0, static_cast<int>(plane), NVBUF_MAP_READ_WRITE) != 0)
        {
            std::cerr << "NvBufSurfaceMap failed for source plane " << plane << '\n';
            return false;
        }
        (void)NvBufSurfaceSyncForCpu(surface, 0, static_cast<int>(plane));

        auto *base = static_cast<uint8_t *>(sp.mappedAddr.addr[plane]);
        const uint32_t width = pp.width[plane] * std::max<uint32_t>(1, pp.bytesPerPix[plane]);
        const uint32_t height = pp.height[plane];
        const uint32_t pitch = pp.pitch[plane];
        for (uint32_t y = 0; y < height; ++y)
        {
            auto *row = base + y * pitch;
            for (uint32_t x = 0; x < width; ++x)
            {
                if (plane == 0)
                {
                    row[x] = yValue(x, y);
                }
                else if (plane == 1)
                {
                    row[x] = uValue(x, y);
                }
                else
                {
                    row[x] = vValue(x, y);
                }
            }
        }

        (void)NvBufSurfaceSyncForDevice(surface, 0, static_cast<int>(plane));
        if (NvBufSurfaceUnMap(surface, 0, static_cast<int>(plane)) != 0)
        {
            std::cerr << "NvBufSurfaceUnMap failed for source plane " << plane << '\n';
            return false;
        }
    }

    return true;
}

bool validateNv12Surface(NvBufSurface *surface)
{
    if (!surface || surface->numFilled == 0)
    {
        return false;
    }

    auto &sp = surface->surfaceList[0];
    auto &pp = sp.planeParams;
    if (pp.num_planes < 2)
    {
        std::cerr << "NV12 surface has " << pp.num_planes << " plane(s), expected 2\n";
        return false;
    }

    for (uint32_t plane = 0; plane < 2; ++plane)
    {
        if (NvBufSurfaceMap(surface, 0, static_cast<int>(plane), NVBUF_MAP_READ) != 0)
        {
            std::cerr << "NvBufSurfaceMap failed for output plane " << plane << '\n';
            return false;
        }
        (void)NvBufSurfaceSyncForCpu(surface, 0, static_cast<int>(plane));
    }

    const auto *y_base = static_cast<const uint8_t *>(sp.mappedAddr.addr[0]);
    const auto *uv_base = static_cast<const uint8_t *>(sp.mappedAddr.addr[1]);

    const uint32_t sample_x = std::min<uint32_t>(128, pp.width[0] - 1);
    const uint32_t sample_y = std::min<uint32_t>(64, pp.height[0] - 1);
    const uint8_t actual_y = y_base[sample_y * pp.pitch[0] + sample_x];
    const uint8_t expected_y = yValue(sample_x, sample_y);
    bool ok = actual_y == expected_y;
    if (!ok)
    {
        std::cerr << "Y mismatch: expected=" << static_cast<int>(expected_y)
                  << " actual=" << static_cast<int>(actual_y) << '\n';
    }

    const uint32_t chroma_x = std::min<uint32_t>(64, pp.width[1] - 1);
    const uint32_t chroma_y = std::min<uint32_t>(32, pp.height[1] - 1);
    const uint8_t actual_u = uv_base[chroma_y * pp.pitch[1] + chroma_x * 2u];
    const uint8_t actual_v = uv_base[chroma_y * pp.pitch[1] + chroma_x * 2u + 1u];
    const uint32_t src_y0 = chroma_y * 2u;
    const uint32_t src_y1 = src_y0 + 1u;
    const uint8_t expected_u = static_cast<uint8_t>(
        (static_cast<unsigned>(uValue(chroma_x, src_y0)) +
         static_cast<unsigned>(uValue(chroma_x, src_y1)) + 1u) >> 1);
    const uint8_t expected_v = static_cast<uint8_t>(
        (static_cast<unsigned>(vValue(chroma_x, src_y0)) +
         static_cast<unsigned>(vValue(chroma_x, src_y1)) + 1u) >> 1);
    if (actual_u != expected_u || actual_v != expected_v)
    {
        std::cerr << "UV mismatch: expected=(" << static_cast<int>(expected_u)
                  << ',' << static_cast<int>(expected_v) << ") actual=("
                  << static_cast<int>(actual_u) << ',' << static_cast<int>(actual_v) << ")\n";
        ok = false;
    }

    for (uint32_t plane = 0; plane < 2; ++plane)
    {
        (void)NvBufSurfaceUnMap(surface, 0, static_cast<int>(plane));
    }

    return ok;
}

TimingStats summarize(std::vector<int64_t> samples)
{
    std::sort(samples.begin(), samples.end());
    TimingStats stats;
    stats.min_us = samples.front();
    stats.max_us = samples.back();
    stats.p50_us = samples[samples.size() / 2];
    stats.p90_us = samples[std::min(samples.size() - 1, samples.size() * 90 / 100)];
    stats.p99_us = samples[std::min(samples.size() - 1, samples.size() * 99 / 100)];
    stats.avg_us = static_cast<double>(std::accumulate(samples.begin(), samples.end(), int64_t{0})) /
                   static_cast<double>(samples.size());
    return stats;
}

void printStats(const char *name, const TimingStats &stats)
{
    std::cout << name
              << " avg=" << stats.avg_us / 1000.0 << "ms"
              << " min=" << stats.min_us / 1000.0 << "ms"
              << " p50=" << stats.p50_us / 1000.0 << "ms"
              << " p90=" << stats.p90_us / 1000.0 << "ms"
              << " p99=" << stats.p99_us / 1000.0 << "ms"
              << " max=" << stats.max_us / 1000.0 << "ms\n";
}

template <typename Fn>
bool runTimed(const char *name, int warmup, int iterations, Fn &&fn, TimingStats &stats)
{
    for (int i = 0; i < warmup; ++i)
    {
        if (!fn())
        {
            std::cerr << name << " failed during warmup " << i << '\n';
            return false;
        }
    }

    std::vector<int64_t> samples;
    samples.reserve(static_cast<size_t>(iterations));
    for (int i = 0; i < iterations; ++i)
    {
        const auto start = std::chrono::steady_clock::now();
        if (!fn())
        {
            std::cerr << name << " failed during iteration " << i << '\n';
            return false;
        }
        const auto end = std::chrono::steady_clock::now();
        samples.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
    }

    stats = summarize(std::move(samples));
    return true;
}

} // namespace

int main(int argc, char **argv)
{
    Options options;
    if (!parseArgs(argc, argv, options))
    {
        printUsage(argv[0]);
        return 2;
    }

    NvBufSurface *src = createSurface(options.width, options.height,
                                      NVBUF_COLOR_FORMAT_YUV422, options.src_layout);
    NvBufSurface *dst_cuda = createSurface(options.width, options.height,
                                           NVBUF_COLOR_FORMAT_NV12, options.dst_layout);
    NvBufSurface *dst_vic = createSurface(options.width, options.height,
                                          NVBUF_COLOR_FORMAT_NV12, options.dst_layout);
    if (!src || !dst_cuda || !dst_vic)
    {
        std::cerr << "Failed to create NvBufSurface objects\n";
        if (src)
        {
            NvBufSurfaceDestroy(src);
        }
        if (dst_cuda)
        {
            NvBufSurfaceDestroy(dst_cuda);
        }
        if (dst_vic)
        {
            NvBufSurfaceDestroy(dst_vic);
        }
        return 1;
    }

    std::cout << "surface src planes=" << src->surfaceList[0].planeParams.num_planes
              << " dst planes=" << dst_cuda->surfaceList[0].planeParams.num_planes
              << " size=" << options.width << 'x' << options.height
              << " src_layout=" << layoutName(options.src_layout)
              << " dst_layout=" << layoutName(options.dst_layout)
              << " iterations=" << options.iterations
              << " warmup=" << options.warmup << '\n';

    if (!fillYuv422Surface(src))
    {
        std::cerr << "Failed to fill source surface\n";
        NvBufSurfaceDestroy(src);
        NvBufSurfaceDestroy(dst_cuda);
        NvBufSurfaceDestroy(dst_vic);
        return 1;
    }

    NvBufSurfTransformParams transform_params;
    std::memset(&transform_params, 0, sizeof(transform_params));
    transform_params.transform_flag = NVBUFSURF_TRANSFORM_FILTER;
    transform_params.transform_filter = NvBufSurfTransformInter_Nearest;

    TimingStats vic_stats;
    const bool vic_ok = runTimed(
        "NvBufSurfTransform", options.warmup, options.iterations,
        [&] {
            return NvBufSurfTransform(src, dst_vic, &transform_params) == 0;
        },
        vic_stats);
    if (vic_ok)
    {
        printStats("NvBufSurfTransform", vic_stats);
    }

    bool cuda_ran = false;
    bool cuda_ok = false;
    trb::video::CudaYuv422ConverterResult cuda_result;
    TimingStats cuda_stats;
    if (options.src_layout == NVBUF_LAYOUT_PITCH && options.dst_layout == NVBUF_LAYOUT_PITCH)
    {
        trb::video::CudaYuv422Converter cuda_converter;
        cuda_ran = true;
        if (!cuda_converter.prepareOutput(dst_cuda, &cuda_result))
        {
            std::cerr << "CUDA converter prepare failed stage=" << cuda_result.error_stage
                      << " err=" << cuda_result.error_code << '\n';
        }
        else
        {
            cuda_ok = runTimed(
                "CUDA converter", options.warmup, options.iterations,
                [&] {
                    return cuda_converter.convert(src, dst_cuda, &cuda_result);
                },
                cuda_stats);
        }
    }
    else
    {
        std::cout << "CUDA converter skipped: prototype supports pitch->pitch only\n";
    }
    if (cuda_ran && !cuda_ok)
    {
        std::cerr << "CUDA converter failed stage=" << cuda_result.error_stage
                  << " err=" << cuda_result.error_code
                  << " src_color=" << cuda_result.src_color_format
                  << " dst_color=" << cuda_result.dst_color_format
                  << " src_planes=" << cuda_result.src_plane_count
                  << " dst_planes=" << cuda_result.dst_plane_count
                  << " src_frame_type=" << cuda_result.src_frame_type
                  << " dst_frame_type=" << cuda_result.dst_frame_type << '\n';
    }
    else if (cuda_ran)
    {
        printStats("CUDA converter", cuda_stats);
        if (!validateNv12Surface(dst_cuda))
        {
            std::cerr << "CUDA converter output validation failed\n";
            NvBufSurfaceDestroy(src);
            NvBufSurfaceDestroy(dst_cuda);
            NvBufSurfaceDestroy(dst_vic);
            return 1;
        }
        std::cout << "CUDA converter validation=ok\n";
    }

    NvBufSurfaceDestroy(src);
    NvBufSurfaceDestroy(dst_cuda);
    NvBufSurfaceDestroy(dst_vic);
    return (vic_ok && (!cuda_ran || cuda_ok)) ? 0 : 1;
}
