#pragma once

#include <cstdint>
#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

// Forward declaration for Jetson Multimedia API
struct NvBufSurface;

namespace trb::video
{

/**
 * @brief Publishes left and right eye images from a side-by-side stereo frame.
 * 
 * ARCHITECTURE: Receives NV12 surface from shared decoder (VideoConverter)
 * - No independent decoder (shares with encode pipeline)
 * - Receives NV12 surface pointer, crops left/right halves, scales, converts to RGB
 * - Publishes to ROS Image topics
 * 
 * Input: NV12 NvBufSurface* (3840x1520)
 * Output: Two ROS Image topics (640x360 each)
 * 
 * Uses Jetson VIC for hardware-accelerated crop + scale.
 */
class EyeImagePublisher
{
public:
    struct Config
    {
        // Output image size
        uint32_t output_width = 640;
        uint32_t output_height = 360;
        
        // Topic names
        std::string left_topic = "data/left_eye_image";
        std::string right_topic = "data/right_eye_image";
        
        // Enable/disable publishing
        bool enabled = true;
        
        // Frame ID for ROS headers
        std::string frame_id = "camera";
    };

    EyeImagePublisher();
    ~EyeImagePublisher();

    EyeImagePublisher(const EyeImagePublisher&) = delete;
    EyeImagePublisher& operator=(const EyeImagePublisher&) = delete;

    /**
     * @brief Initialize the publisher with ROS node handle and config.
     * @param nh ROS NodeHandle for creating publishers
     * @param src_width Full frame width (e.g., 3840)
     * @param src_height Full frame height (e.g., 1520)
     * @param config Configuration options
     * @return true if initialization succeeded
     */
    bool initialize(ros::NodeHandle& nh, uint32_t src_width, uint32_t src_height, const Config& config);

    /**
     * @brief Inject the VIC mutex used to serialise NvBufSurfTransform calls
     * across pipeline stages. When set, only the actual NvBufSurfTransform
     * call is locked; the subsequent CPU NV12->RGB conversion and ROS publish
     * run outside the lock so they do not block the encode thread.
     * Pass nullptr to disable external locking.
     */
    void setVicMutex(std::mutex* vic_mutex) { vic_mutex_ = vic_mutex; }

    /**
     * @brief Process NV12 frame from shared decoder.
     * @param src_surface NvBufSurface pointer of the source NV12 surface
     * @param timestamp_us Frame timestamp in microseconds
     * 
     * This crops left/right eye regions, scales to output size,
     * converts to RGB, and publishes to ROS topics.
     */
    void processFrame(NvBufSurface* src_surface, uint64_t timestamp_us);

    /**
     * @brief Check if publisher is enabled and ready.
     */
    bool isEnabled() const { return config_.enabled && initialized_.load(); }

    /**
     * @brief Check if either eye image topic currently has subscribers.
     */
    bool hasSubscribers() const { return left_pub_.getNumSubscribers() > 0 || right_pub_.getNumSubscribers() > 0; }

    /**
     * @brief Stop the publisher.
     */
    void stop();

private:
    Config config_;
    uint32_t src_width_ = 0;
    uint32_t src_height_ = 0;
    
    ros::Publisher left_pub_;
    ros::Publisher right_pub_;
    
    // NV12 buffers for crop+scale output (2 buffers: left and right)
    std::vector<void*> nv12_surfaces_;  // NvBufSurface*
    std::vector<int> nv12_fds_;
    
    // RGB buffers for final output
    std::vector<std::vector<uint8_t>> rgb_buffers_;
    
    std::atomic<bool> initialized_{false};
    std::mutex mutex_;
    // Optional injected VIC mutex (owned externally). Used only around the
    // NvBufSurfTransform call inside cropScaleToNV12 to keep lock-hold time
    // minimal. nullptr = no external locking.
    std::mutex* vic_mutex_ = nullptr;
    
    // Statistics
    std::atomic<uint64_t> frame_count_{0};
    
    void destroyBuffers();
    bool cropScaleToNV12(NvBufSurface* src_surf, int dst_idx, bool is_right_eye);
    bool convertNV12ToRGB(NvBufSurface* surf, uint8_t* rgb_out, size_t rgb_size);
    void publishImage(ros::Publisher& pub, const uint8_t* rgb_data, uint64_t timestamp_us);
};

} // namespace trb::video
