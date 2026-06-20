#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <atomic>

#include "sensor_msgs/msg/image.hpp"
#include "rclcpp/rclcpp.hpp"

// Forward declaration for Jetson Multimedia API
struct NvBufSurface;

namespace trb::video
{

class CudaEyeImageProcessor;

/**
 * @brief Publishes left and right eye images from a side-by-side stereo frame.
 * 
 * ARCHITECTURE: Receives NV12 surface from the encode pipeline
 * - No independent decoder (shares with encode pipeline)
 * - Uses CUDA to crop left/right halves, scale, and convert to RGB
 * - Publishes to ROS Image topics
 * 
 * Input: NV12 NvBufSurface* (3840x1520)
 * Output: Two ROS Image topics (640x360 each)
 * 
 * Uses pinned host RGB buffers for the final ROS Image copy.
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
    bool initialize(rclcpp::Node & nh, uint32_t src_width, uint32_t src_height, const Config& config);

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
    bool hasSubscribers() const { return left_pub_->get_subscription_count() > 0 || right_pub_->get_subscription_count() > 0; }

    /**
     * @brief Stop the publisher.
     */
    void stop();

private:
    Config config_;
    uint32_t src_width_ = 0;
    uint32_t src_height_ = 0;
    
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr left_pub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr right_pub_;
    
    // RGB buffers for final output
    std::vector<uint8_t*> rgb_buffers_;
    size_t rgb_buffer_size_ = 0;
    std::unique_ptr<CudaEyeImageProcessor> cuda_processor_;
    
    std::atomic<bool> initialized_{false};
    
    // Statistics
    std::atomic<uint64_t> frame_count_{0};
    
    void destroyBuffers();
    void publishImage(rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr& pub, const uint8_t* rgb_data, uint64_t timestamp_us);
};

} // namespace trb::video
