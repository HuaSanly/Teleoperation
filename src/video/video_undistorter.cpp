#include "video/video_undistorter.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cctype>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <yaml-cpp/yaml.h>

#include "nvbufsurface.h"
#include "video/cuda_nv12_undistorter.hpp"
#include "video/nvbuf_mutex.hpp"

#include <vpi/Image.h>
#include <vpi/Status.h>
#include <vpi/Stream.h>
#include <vpi/Types.h>
#include <vpi/WarpMap.h>
#include <vpi/algo/Remap.h>

#ifndef TRB_HAS_CUDA_UNDISTORTER
#define TRB_HAS_CUDA_UNDISTORTER 0
#endif

namespace trb::video
{

    namespace
    {
        enum class Backend
        {
            kVpiCuda,
            kCuda,
            kIdentity,
        };

        struct CalibrationSelection
        {
            YAML::Node node;
            std::string profile;
            std::string session;
            double baseline_mm = 0.0;
            double alpha = 0.0;
            cv::Size calibration_size;
            cv::Size runtime_size;
            cv::Size stream_size;
        };

        struct MapBuildResult
        {
            std::vector<float> full_map_xy;
            CalibrationSelection calibration;
        };

        bool checkVpi(VPIStatus s, const char *what)
        {
            if (s == VPI_SUCCESS)
            {
                return true;
            }
            char buf[VPI_MAX_STATUS_MESSAGE_LENGTH];
            vpiGetLastStatusMessage(buf, sizeof(buf));
            RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] %s failed: %d (%s)", what, static_cast<int>(s), buf);
            return false;
        }

        std::string normalizeBackend(std::string value)
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            });
            std::replace(value.begin(), value.end(), '-', '_');
            return value;
        }

        Backend parseBackend(const std::string &value)
        {
            const std::string backend = normalizeBackend(value.empty() ? "vpi_cuda" : value);
            if (backend == "cuda")
            {
                return Backend::kCuda;
            }
            if (backend == "identity" || backend == "disabled" || backend == "none")
            {
                return Backend::kIdentity;
            }
            return Backend::kVpiCuda;
        }

        const char *backendToString(Backend backend)
        {
            switch (backend)
            {
            case Backend::kCuda:
                return "cuda";
            case Backend::kIdentity:
                return "identity";
            case Backend::kVpiCuda:
            default:
                return "vpi_cuda";
            }
        }

        bool readSize(const YAML::Node &node, const char *key, cv::Size &out)
        {
            if (!node[key])
            {
                return false;
            }
            const auto values = node[key].as<std::vector<int>>();
            if (values.size() != 2)
            {
                return false;
            }
            out = cv::Size(values[0], values[1]);
            return out.width > 0 && out.height > 0;
        }

        std::string sizeString(const cv::Size &size)
        {
            std::ostringstream oss;
            oss << size.width << "x" << size.height;
            return oss.str();
        }

        std::string availableProfilesString(const YAML::Node &list)
        {
            std::ostringstream oss;
            if (!list || !list.IsSequence())
            {
                return "";
            }
            for (std::size_t i = 0; i < list.size(); ++i)
            {
                const YAML::Node item = list[i];
                cv::Size stream_size;
                const std::string profile = item["profile"] ? item["profile"].as<std::string>() : "";
                const std::string session = item["session"] ? item["session"].as<std::string>() : "";
                if (i > 0)
                {
                    oss << ", ";
                }
                oss << "{profile=" << (profile.empty() ? "<empty>" : profile)
                    << " session=" << (session.empty() ? "<empty>" : session);
                if (readSize(item, "stream_image_size", stream_size))
                {
                    oss << " stream=" << sizeString(stream_size);
                }
                oss << "}";
            }
            return oss.str();
        }

        bool selectCalibration(const YAML::Node &root,
                               const VideoUndistorter::Config &cfg,
                               CalibrationSelection &selection)
        {
            const cv::Size stream_size(static_cast<int>(cfg.width), static_cast<int>(cfg.height));
            const cv::Size runtime_eye(static_cast<int>(cfg.width / 2u), static_cast<int>(cfg.height));

            YAML::Node selected;
            if (root["stereo_calibrations"])
            {
                const YAML::Node list = root["stereo_calibrations"];
                if (!list.IsSequence())
                {
                    RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"),
                                 "[UNDISTORT] stereo_calibrations must be a list");
                    return false;
                }

                for (const YAML::Node item : list)
                {
                    cv::Size item_stream;
                    const bool have_stream = readSize(item, "stream_image_size", item_stream);
                    const std::string profile = item["profile"] ? item["profile"].as<std::string>() : "";
                    const std::string session = item["session"] ? item["session"].as<std::string>() : "";
                    const bool profile_match = !cfg.profile.empty() &&
                                               (cfg.profile == profile || cfg.profile == session);
                    const bool size_match = cfg.profile.empty() && have_stream && item_stream == stream_size;
                    if (profile_match || size_match)
                    {
                        selected = item;
                        break;
                    }
                }

                if (!selected)
                {
                    RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"),
                                 "[UNDISTORT] no calibration profile matched stream=%s selector='%s'. Available: %s",
                                 sizeString(stream_size).c_str(),
                                 cfg.profile.c_str(),
                                 availableProfilesString(list).c_str());
                    return false;
                }
            }
            else
            {
                selected = root;
            }

            if (!selected["left"] || !selected["right"])
            {
                RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"),
                             "[UNDISTORT] selected calibration missing left/right sections");
                return false;
            }

            selection = CalibrationSelection{};
            selection.node = selected;
            selection.profile = selected["profile"] ? selected["profile"].as<std::string>() : "";
            selection.session = selected["session"] ? selected["session"].as<std::string>() : "";
            selection.baseline_mm = selected["baseline_mm"] ? selected["baseline_mm"].as<double>() : 0.0;
            selection.alpha = selected["alpha"] ? selected["alpha"].as<double>() : 0.0;
            selection.calibration_size = runtime_eye;
            selection.runtime_size = runtime_eye;
            selection.stream_size = stream_size;

            (void)readSize(selected, "calibration_image_size", selection.calibration_size);
            cv::Size yaml_runtime;
            if (readSize(selected, "runtime_image_size", yaml_runtime) && yaml_runtime != runtime_eye)
            {
                RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                            "[UNDISTORT] runtime_image_size=%s differs from pipeline single-eye size=%s; using pipeline size",
                            sizeString(yaml_runtime).c_str(),
                            sizeString(runtime_eye).c_str());
            }
            cv::Size yaml_stream;
            if (readSize(selected, "stream_image_size", yaml_stream) && yaml_stream != stream_size)
            {
                RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                            "[UNDISTORT] stream_image_size=%s differs from pipeline size=%s; using pipeline size",
                            sizeString(yaml_stream).c_str(),
                            sizeString(stream_size).c_str());
            }

            return true;
        }

        bool loadMatrixFromYaml(const YAML::Node &eye, const char *key,
                                int rows, int cols, cv::Mat &out, bool required)
        {
            if (!eye[key])
            {
                if (required)
                {
                    RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] calibration missing required field '%s'", key);
                    return false;
                }
                return false;
            }
            const auto values = eye[key].as<std::vector<double>>();
            const int expected = rows * cols;
            if (static_cast<int>(values.size()) != expected)
            {
                RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] '%s' expects %d floats, got %zu", key, expected, values.size());
                return false;
            }
            out.create(rows, cols, CV_64F);
            std::memcpy(out.ptr<double>(), values.data(), expected * sizeof(double));
            return true;
        }

        bool loadDistortion(const YAML::Node &eye, cv::Mat &out)
        {
            if (!eye["D"])
            {
                RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] calibration missing 'D'");
                return false;
            }
            const auto values = eye["D"].as<std::vector<double>>();
            if (values.size() < 4)
            {
                RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] 'D' too short: %zu (need >= 4)", values.size());
                return false;
            }
            out = cv::Mat(1, static_cast<int>(values.size()), CV_64F);
            std::memcpy(out.ptr<double>(), values.data(), values.size() * sizeof(double));
            return true;
        }

        bool buildEyeMap(const YAML::Node &eye_node,
                         const cv::Size &calib_size,
                         const cv::Size &runtime_size,
                         double alpha,
                         cv::Mat &map_xy_out)
        {
            cv::Mat K_calib, D, R, P;
            if (!loadMatrixFromYaml(eye_node, "K", 3, 3, K_calib, true))
            {
                return false;
            }
            if (!loadDistortion(eye_node, D))
            {
                return false;
            }
            if (!loadMatrixFromYaml(eye_node, "R", 3, 3, R, false))
            {
                R = cv::Mat::eye(3, 3, CV_64F);
            }

            const double sx = static_cast<double>(runtime_size.width) /
                              static_cast<double>(calib_size.width);
            const double sy = static_cast<double>(runtime_size.height) /
                              static_cast<double>(calib_size.height);
            cv::Mat K_run = K_calib.clone();
            K_run.at<double>(0, 0) *= sx;
            K_run.at<double>(0, 2) *= sx;
            K_run.at<double>(1, 1) *= sy;
            K_run.at<double>(1, 2) *= sy;

            const bool have_P = loadMatrixFromYaml(eye_node, "P", 3, 4, P, false);
            cv::Mat new_K;
            if (have_P)
            {
                new_K = P.clone();
                new_K.at<double>(0, 0) *= sx;
                new_K.at<double>(0, 2) *= sx;
                new_K.at<double>(0, 3) *= sx;
                new_K.at<double>(1, 1) *= sy;
                new_K.at<double>(1, 2) *= sy;
                new_K.at<double>(1, 3) *= sy;
            }
            else
            {
                new_K = cv::getOptimalNewCameraMatrix(
                    K_run, D, runtime_size, alpha, runtime_size, nullptr, false);
            }

            cv::Mat map1, map2;
            cv::initUndistortRectifyMap(K_run, D, R, new_K, runtime_size,
                                        CV_32FC2, map1, map2);
            map_xy_out = map1;
            return true;
        }

        bool buildFullMap(const CalibrationSelection &selection,
                          const VideoUndistorter::Config &cfg,
                          MapBuildResult &result)
        {
            const cv::Size runtime_eye(static_cast<int>(cfg.width / 2u),
                                       static_cast<int>(cfg.height));
            cv::Mat map_left, map_right;
            if (!buildEyeMap(selection.node["left"], selection.calibration_size, runtime_eye, selection.alpha, map_left))
            {
                return false;
            }
            if (!buildEyeMap(selection.node["right"], selection.calibration_size, runtime_eye, selection.alpha, map_right))
            {
                return false;
            }

            const int width = static_cast<int>(cfg.width);
            const int height = static_cast<int>(cfg.height);
            const int single_w = runtime_eye.width;
            const int single_h = runtime_eye.height;
            const float clamp_x_max = static_cast<float>(single_w - 1);
            const float clamp_y_max = static_cast<float>(single_h - 1);
            result.full_map_xy.assign(static_cast<size_t>(width) * height * 2u, 0.0f);
            result.calibration = selection;

            for (int y = 0; y < height; ++y)
            {
                const int y_src = std::min(y, single_h - 1);
                for (int x = 0; x < width; ++x)
                {
                    cv::Vec2f src;
                    if (x < single_w)
                    {
                        src = map_left.at<cv::Vec2f>(y_src, x);
                        src[0] = std::clamp(src[0], 0.0f, clamp_x_max);
                        src[1] = std::clamp(src[1], 0.0f, clamp_y_max);
                    }
                    else
                    {
                        const int x_local = std::min(x - single_w, single_w - 1);
                        src = map_right.at<cv::Vec2f>(y_src, x_local);
                        src[0] = std::clamp(src[0], 0.0f, clamp_x_max);
                        src[1] = std::clamp(src[1], 0.0f, clamp_y_max);
                        src[0] += static_cast<float>(single_w);
                    }

                    const size_t index = (static_cast<size_t>(y) * width + x) * 2u;
                    result.full_map_xy[index] = src[0];
                    result.full_map_xy[index + 1] = src[1];
                }
            }
            return true;
        }

        bool loadCalibrationMap(const std::string &yaml_path,
                                const VideoUndistorter::Config &cfg,
                                MapBuildResult &result)
        {
            YAML::Node root;
            try
            {
                root = YAML::LoadFile(yaml_path);
            }
            catch (const std::exception &e)
            {
                RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] failed to load '%s': %s", yaml_path.c_str(), e.what());
                return false;
            }

            CalibrationSelection selection;
            if (!selectCalibration(root, cfg, selection))
            {
                return false;
            }
            return buildFullMap(selection, cfg, result);
        }

        void buildIdentityMap(const VideoUndistorter::Config &cfg, MapBuildResult &result)
        {
            result = MapBuildResult{};
            result.calibration.runtime_size = cv::Size(static_cast<int>(cfg.width / 2u), static_cast<int>(cfg.height));
            result.calibration.stream_size = cv::Size(static_cast<int>(cfg.width), static_cast<int>(cfg.height));
            result.full_map_xy.assign(static_cast<size_t>(cfg.width) * cfg.height * 2u, 0.0f);
            for (uint32_t y = 0; y < cfg.height; ++y)
            {
                for (uint32_t x = 0; x < cfg.width; ++x)
                {
                    const size_t index = (static_cast<size_t>(y) * cfg.width + x) * 2u;
                    result.full_map_xy[index] = static_cast<float>(x);
                    result.full_map_xy[index + 1] = static_cast<float>(y);
                }
            }
        }

        void logCudaFailureOnce(const CudaNv12UndistorterResult &result,
                                int src_fd,
                                uint32_t width,
                                uint32_t height,
                                const char *mode)
        {
            static std::atomic<uint64_t> failure_count{0};
            const uint64_t count = failure_count.fetch_add(1, std::memory_order_relaxed) + 1;
            if (count <= 5 || (count % 300 == 0))
            {
                RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                            "[UNDISTORT] CUDA %s failed stage=%s err=%d src_fd=%d w=%u h=%u src_color=%u dst_color=%u src_planes=%u dst_planes=%u src_frame_type=%u dst_frame_type=%u failures=%lu",
                            mode,
                            result.error_stage,
                            result.error_code,
                            src_fd,
                            width,
                            height,
                            result.src_color_format,
                            result.dst_color_format,
                            result.src_plane_count,
                            result.dst_plane_count,
                            result.src_frame_type,
                            result.dst_frame_type,
                            static_cast<unsigned long>(count));
            }
        }

    } // namespace

    struct VideoUndistorter::Impl
    {
        Config cfg;
        Backend backend{Backend::kVpiCuda};
        bool fused_enabled{false};
        std::string backend_name{"vpi_cuda"};
        MapBuildResult map_result;

        std::vector<void *> surfaces;
        std::vector<int> dmabuf_fds;
        std::mutex pool_mutex;
        std::queue<size_t> free_indices;
        std::unordered_map<int, size_t> fd_to_index;

        VPIStream stream{nullptr};
        VPIPayload remap_payload{nullptr};
        VPIWarpMap warp_map{};
        bool warp_allocated{false};
        std::unordered_map<int, VPIImage> input_image_cache;
        std::unordered_map<int, VPIImage> output_image_cache;

        std::unique_ptr<CudaNv12Undistorter> cuda_backend;

        std::atomic<uint64_t> processed_frames{0};
        std::atomic<uint64_t> pool_drops{0};
        std::atomic<uint64_t> failed_frames{0};
        std::atomic<uint64_t> fallback_frames{0};
        std::atomic<int64_t> remap_us_total{0};
        std::atomic<int64_t> map_us_total{0};
        std::atomic<int64_t> kernel_us_total{0};
        std::atomic<int64_t> sync_us_total{0};

        ~Impl()
        {
            teardown();
        }

        void teardown()
        {
            if (cuda_backend)
            {
                cuda_backend->reset();
                cuda_backend.reset();
            }

            for (auto &kv : input_image_cache)
            {
                if (kv.second)
                {
                    vpiImageDestroy(kv.second);
                }
            }
            input_image_cache.clear();

            for (auto &kv : output_image_cache)
            {
                if (kv.second)
                {
                    vpiImageDestroy(kv.second);
                }
            }
            output_image_cache.clear();

            if (remap_payload)
            {
                vpiPayloadDestroy(remap_payload);
                remap_payload = nullptr;
            }
            if (stream)
            {
                vpiStreamDestroy(stream);
                stream = nullptr;
            }
            if (warp_allocated)
            {
                vpiWarpMapFreeData(&warp_map);
                warp_allocated = false;
            }

            {
                std::lock_guard<std::mutex> lk(pool_mutex);
                while (!free_indices.empty())
                {
                    free_indices.pop();
                }
                fd_to_index.clear();
            }
            for (void *s : surfaces)
            {
                if (s)
                {
                    NvBufSurfaceDestroy(reinterpret_cast<NvBufSurface *>(s));
                }
            }
            surfaces.clear();
            dmabuf_fds.clear();
        }

        bool createOutputPool()
        {
            NvBufSurfaceCreateParams p;
            std::memset(&p, 0, sizeof(p));
            p.gpuId = 0;
            p.width = cfg.width;
            p.height = cfg.height;
            p.layout = (cfg.output_surface_layout == 1) ? NVBUF_LAYOUT_BLOCK_LINEAR
                                                       : NVBUF_LAYOUT_PITCH;
            p.colorFormat = NVBUF_COLOR_FORMAT_NV12;
            p.memType = NVBUF_MEM_SURFACE_ARRAY;
            p.isContiguous = true;

            surfaces.assign(cfg.buffer_pool_size, nullptr);
            dmabuf_fds.assign(cfg.buffer_pool_size, -1);
            {
                std::lock_guard<std::mutex> lk(pool_mutex);
                while (!free_indices.empty())
                {
                    free_indices.pop();
                }
                fd_to_index.clear();
            }
            for (uint32_t i = 0; i < cfg.buffer_pool_size; ++i)
            {
                NvBufSurface *surf = nullptr;
                if (NvBufSurfaceCreate(&surf, 1, &p) != 0)
                {
                    RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] NvBufSurfaceCreate failed at i=%u", i);
                    return false;
                }
                surf->numFilled = 1;
                surfaces[i] = surf;
                dmabuf_fds[i] = surf->surfaceList[0].bufferDesc;
                std::lock_guard<std::mutex> lk(pool_mutex);
                free_indices.push(i);
                fd_to_index.emplace(dmabuf_fds[i], i);
            }
            return true;
        }

        bool buildVpiWarpMap()
        {
            std::memset(&warp_map, 0, sizeof(warp_map));
            warp_map.grid.numHorizRegions = 1;
            warp_map.grid.numVertRegions = 1;
            warp_map.grid.horizInterval[0] = 1;
            warp_map.grid.vertInterval[0] = 1;
            warp_map.grid.regionWidth[0] = static_cast<int16_t>(cfg.width);
            warp_map.grid.regionHeight[0] = static_cast<int16_t>(cfg.height);

            if (!checkVpi(vpiWarpMapAllocData(&warp_map), "vpiWarpMapAllocData"))
            {
                return false;
            }
            warp_allocated = true;

            const int nx = warp_map.numHorizPoints;
            const int ny = warp_map.numVertPoints;
            const int width = static_cast<int>(cfg.width);
            const int height = static_cast<int>(cfg.height);
            for (int y = 0; y < ny; ++y)
            {
                auto *row = reinterpret_cast<VPIKeypointF32 *>(
                    reinterpret_cast<uint8_t *>(warp_map.keypoints) +
                    static_cast<ptrdiff_t>(y) * warp_map.pitchBytes);
                const int y_src = std::min(y, height - 1);
                for (int x = 0; x < nx; ++x)
                {
                    const int x_src = std::min(x, width - 1);
                    const size_t index = (static_cast<size_t>(y_src) * width + x_src) * 2u;
                    row[x].x = map_result.full_map_xy[index];
                    row[x].y = map_result.full_map_xy[index + 1];
                }
            }
            return true;
        }

        bool createVpiResources()
        {
            if (!buildVpiWarpMap())
            {
                return false;
            }
            if (!checkVpi(vpiStreamCreate(VPI_BACKEND_CUDA, &stream),
                          "vpiStreamCreate(CUDA)"))
            {
                return false;
            }
            if (!checkVpi(vpiCreateRemap(VPI_BACKEND_CUDA, &warp_map, &remap_payload),
                          "vpiCreateRemap"))
            {
                return false;
            }
            return true;
        }

        bool createCudaResources()
        {
#if TRB_HAS_CUDA_UNDISTORTER
            if (cfg.output_surface_layout != 0)
            {
                RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                            "[UNDISTORT] CUDA backend supports pitch-linear NV12 output only; current output layout is block-linear");
                return false;
            }
            cuda_backend = std::make_unique<CudaNv12Undistorter>();
            if (!cuda_backend->initialize(cfg.width, cfg.height, map_result.full_map_xy))
            {
                RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                            "[UNDISTORT] CUDA backend map initialization failed");
                cuda_backend.reset();
                return false;
            }
            for (void *surface : surfaces)
            {
                auto *dst = reinterpret_cast<NvBufSurface *>(surface);
                if (!dst)
                {
                    return false;
                }
                dst->numFilled = 1;
                CudaNv12UndistorterResult result;
                if (!cuda_backend->prepareOutput(dst, &result))
                {
                    logCudaFailureOnce(result, dst->surfaceList[0].bufferDesc, cfg.width, cfg.height, "prepare");
                    cuda_backend.reset();
                    return false;
                }
            }
            return true;
#else
            RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                        "[UNDISTORT] CUDA backend requested but CUDA undistorter was not built");
            return false;
#endif
        }

        VPIImage getOrWrapImage(int fd, std::unordered_map<int, VPIImage> &cache)
        {
            auto it = cache.find(fd);
            if (it != cache.end())
            {
                return it->second;
            }
            VPIImageData data;
            std::memset(&data, 0, sizeof(data));
            data.bufferType = VPI_IMAGE_BUFFER_NVBUFFER;
            data.buffer.fd = fd;

            VPIImage img = nullptr;
            const VPIStatus s = vpiImageCreateWrapper(
                &data, nullptr, VPI_BACKEND_CUDA, &img);
            if (s != VPI_SUCCESS || !img)
            {
                checkVpi(s, "vpiImageCreateWrapper(NVBUFFER)");
                return nullptr;
            }
            cache.emplace(fd, img);
            return img;
        }

        bool acquireOutput(size_t &out_idx, int &out_fd)
        {
            std::lock_guard<std::mutex> lk(pool_mutex);
            if (free_indices.empty())
            {
                pool_drops.fetch_add(1, std::memory_order_relaxed);
                return false;
            }
            out_idx = free_indices.front();
            free_indices.pop();
            out_fd = dmabuf_fds[out_idx];
            return true;
        }

        void releaseOutputIndex(size_t out_idx)
        {
            std::lock_guard<std::mutex> lk(pool_mutex);
            free_indices.push(out_idx);
        }

        bool processVpi(int nv12_fd_in, size_t out_idx, int out_fd)
        {
            (void)out_idx;
            const auto t0 = std::chrono::steady_clock::now();
            VPIImage in_img = getOrWrapImage(nv12_fd_in, input_image_cache);
            VPIImage out_img = getOrWrapImage(out_fd, output_image_cache);
            if (!in_img || !out_img)
            {
                failed_frames.fetch_add(1, std::memory_order_relaxed);
                return false;
            }

            const VPIStatus s_submit = vpiSubmitRemap(
                stream, VPI_BACKEND_CUDA, remap_payload,
                in_img, out_img, VPI_INTERP_LINEAR, VPI_BORDER_ZERO, 0);
            if (s_submit != VPI_SUCCESS)
            {
                checkVpi(s_submit, "vpiSubmitRemap");
                failed_frames.fetch_add(1, std::memory_order_relaxed);
                return false;
            }

            const auto sync_start = std::chrono::steady_clock::now();
            const VPIStatus s_sync = vpiStreamSync(stream);
            const auto t1 = std::chrono::steady_clock::now();
            if (s_sync != VPI_SUCCESS)
            {
                checkVpi(s_sync, "vpiStreamSync");
                failed_frames.fetch_add(1, std::memory_order_relaxed);
                return false;
            }

            const int64_t total_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
            const int64_t sync_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - sync_start).count();
            remap_us_total.fetch_add(total_us, std::memory_order_relaxed);
            kernel_us_total.fetch_add(std::max<int64_t>(0, total_us - sync_us), std::memory_order_relaxed);
            sync_us_total.fetch_add(sync_us, std::memory_order_relaxed);
            processed_frames.fetch_add(1, std::memory_order_relaxed);
            return true;
        }

        bool surfaceFromFd(int fd, NvBufSurface *&surface)
        {
            std::lock_guard<std::mutex> lk(getNvBufMutex());
            return NvBufSurfaceFromFd(fd, reinterpret_cast<void **>(&surface)) == 0 && surface;
        }

        void noteCudaFailure(bool count_failure)
        {
            if (count_failure)
            {
                failed_frames.fetch_add(1, std::memory_order_relaxed);
            }
        }

        bool processCuda(int fd_in, size_t out_idx, int out_fd, bool src_yuv422, bool count_failure)
        {
            if (!cuda_backend)
            {
                noteCudaFailure(count_failure);
                return false;
            }
            NvBufSurface *src = nullptr;
            if (!surfaceFromFd(fd_in, src))
            {
                noteCudaFailure(count_failure);
                return false;
            }
            NvBufSurface *dst = reinterpret_cast<NvBufSurface *>(surfaces[out_idx]);
            if (!dst)
            {
                noteCudaFailure(count_failure);
                return false;
            }
            src->numFilled = 1;
            dst->numFilled = 1;

            const auto t0 = std::chrono::steady_clock::now();
            CudaNv12UndistorterResult result;
            const bool ok = src_yuv422
                ? cuda_backend->remapYuv422ToNv12(src, dst, &result)
                : cuda_backend->remapNv12(src, dst, &result);
            const auto t1 = std::chrono::steady_clock::now();
            if (!ok)
            {
                logCudaFailureOnce(result, fd_in, cfg.width, cfg.height, src_yuv422 ? "yuv422->nv12" : "nv12");
                noteCudaFailure(count_failure);
                return false;
            }

            remap_us_total.fetch_add(
                std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count(),
                std::memory_order_relaxed);
            map_us_total.fetch_add(result.map_us, std::memory_order_relaxed);
            kernel_us_total.fetch_add(result.kernel_us, std::memory_order_relaxed);
            sync_us_total.fetch_add(result.sync_us, std::memory_order_relaxed);
            processed_frames.fetch_add(1, std::memory_order_relaxed);
            (void)out_fd;
            return true;
        }

        bool processIdentity(int fd_in, size_t out_idx, int out_fd)
        {
            return processVpi(fd_in, out_idx, out_fd);
        }
    };

    VideoUndistorter::VideoUndistorter() : impl_(new Impl()) {}
    VideoUndistorter::~VideoUndistorter() = default;

    bool VideoUndistorter::initialize(const Config &config)
    {
        impl_->teardown();
        impl_->cfg = config;
        impl_->backend = parseBackend(config.backend);
        impl_->backend_name = backendToString(impl_->backend);
        impl_->fused_enabled = config.fused && impl_->backend == Backend::kCuda;

        if (config.width == 0 || config.height == 0 || (config.width & 1u) != 0)
        {
            RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"),
                         "[UNDISTORT] invalid SBS dimensions %ux%u", config.width, config.height);
            return false;
        }

        bool map_ok = false;
        if (impl_->backend == Backend::kIdentity)
        {
            buildIdentityMap(config, impl_->map_result);
            map_ok = true;
        }
        else if (config.calibration_file.empty())
        {
            RCLCPP_ERROR(rclcpp::get_logger("teleop_robot_bridge.video"), "[UNDISTORT] empty calibration_file");
            map_ok = false;
        }
        else
        {
            map_ok = loadCalibrationMap(config.calibration_file, config, impl_->map_result);
        }

        if (!map_ok)
        {
            if (config.require_calibration)
            {
                return false;
            }
            RCLCPP_WARN(rclcpp::get_logger("teleop_robot_bridge.video"),
                        "[UNDISTORT] calibration unavailable; falling back to identity backend");
            impl_->backend = Backend::kIdentity;
            impl_->backend_name = backendToString(impl_->backend);
            impl_->fused_enabled = false;
            buildIdentityMap(config, impl_->map_result);
        }

        if (!impl_->createOutputPool())
        {
            return false;
        }

        if (impl_->backend == Backend::kCuda)
        {
            if (!impl_->createCudaResources())
            {
                return false;
            }
        }
        else
        {
            if (!impl_->createVpiResources())
            {
                return false;
            }
        }

        const auto &cal = impl_->map_result.calibration;
        RCLCPP_INFO(rclcpp::get_logger("teleop_robot_bridge.video"),
                    "[UNDISTORT] initialized: %ux%u eye=%s pool=%u backend=%s fused=%d profile=%s session=%s baseline=%.3fmm alpha=%.3f calib=%s",
                    config.width,
                    config.height,
                    sizeString(cal.runtime_size).c_str(),
                    config.buffer_pool_size,
                    impl_->backend_name.c_str(),
                    impl_->fused_enabled ? 1 : 0,
                    cal.profile.empty() ? "<direct>" : cal.profile.c_str(),
                    cal.session.empty() ? "<none>" : cal.session.c_str(),
                    cal.baseline_mm,
                    cal.alpha,
                    config.calibration_file.c_str());
        return true;
    }

    bool VideoUndistorter::process(int nv12_fd_in, int &nv12_fd_out)
    {
        nv12_fd_out = -1;
        if (nv12_fd_in < 0)
        {
            return false;
        }

        if (impl_->backend == Backend::kVpiCuda && (!impl_->stream || !impl_->remap_payload))
        {
            return false;
        }

        size_t out_idx = 0;
        int out_fd = -1;
        if (!impl_->acquireOutput(out_idx, out_fd))
        {
            return false;
        }

        bool ok = false;
        if (impl_->backend == Backend::kCuda)
        {
            ok = impl_->processCuda(nv12_fd_in, out_idx, out_fd, false, true);
        }
        else
        {
            ok = impl_->processVpi(nv12_fd_in, out_idx, out_fd);
        }

        if (!ok)
        {
            impl_->releaseOutputIndex(out_idx);
            return false;
        }

        nv12_fd_out = out_fd;
        return true;
    }

    bool VideoUndistorter::processYuv422(int yuv422_fd_in, int &nv12_fd_out)
    {
        nv12_fd_out = -1;
        if (yuv422_fd_in < 0 || !supportsFusedYuv422())
        {
            return false;
        }

        size_t out_idx = 0;
        int out_fd = -1;
        if (!impl_->acquireOutput(out_idx, out_fd))
        {
            return false;
        }

        const bool ok = impl_->processCuda(yuv422_fd_in, out_idx, out_fd, true, false);
        if (!ok)
        {
            impl_->releaseOutputIndex(out_idx);
            return false;
        }

        nv12_fd_out = out_fd;
        return true;
    }

    bool VideoUndistorter::supportsFusedYuv422() const
    {
        return impl_ && impl_->fused_enabled && impl_->backend == Backend::kCuda;
    }

    const std::string &VideoUndistorter::backendName() const
    {
        return impl_->backend_name;
    }

    void VideoUndistorter::noteFusedFallback()
    {
        if (impl_)
        {
            impl_->fallback_frames.fetch_add(1, std::memory_order_relaxed);
        }
    }

    void VideoUndistorter::releaseFd(int dmabuf_fd)
    {
        std::lock_guard<std::mutex> lk(impl_->pool_mutex);
        auto it = impl_->fd_to_index.find(dmabuf_fd);
        if (it != impl_->fd_to_index.end())
        {
            impl_->free_indices.push(it->second);
        }
    }

    VideoUndistorter::StatsSnapshot VideoUndistorter::consumeStats()
    {
        StatsSnapshot s;
        s.processed_frames = impl_->processed_frames.exchange(0, std::memory_order_relaxed);
        s.pool_drops = impl_->pool_drops.exchange(0, std::memory_order_relaxed);
        s.failed_frames = impl_->failed_frames.exchange(0, std::memory_order_relaxed);
        s.fallback_frames = impl_->fallback_frames.exchange(0, std::memory_order_relaxed);
        s.remap_us_total = impl_->remap_us_total.exchange(0, std::memory_order_relaxed);
        s.map_us_total = impl_->map_us_total.exchange(0, std::memory_order_relaxed);
        s.kernel_us_total = impl_->kernel_us_total.exchange(0, std::memory_order_relaxed);
        s.sync_us_total = impl_->sync_us_total.exchange(0, std::memory_order_relaxed);
        s.backend = impl_->backend_name;
        return s;
    }

} // namespace trb::video
