# Teleoperation ROS2 -> ROS1 迁移改动清单

> 目标平台：Ubuntu 20 + ROS1 + Jetson Orin
> 当前实现：ROS2 (rclcpp/ament) + Jetson MM API + gRPC

## A. 构建与包结构（优先）
1. 将 build system 从 ament_cmake 迁移为 catkin。
2. 更新 package.xml 为 ROS1 依赖（roscpp、std_msgs、sensor_msgs、geometry_msgs）。
3. 处理 Protobuf/gRPC 的 CMake 查找与生成规则（确保 Ubuntu20 可编译）。
4. 安装目标依赖清单（OpenSSL、gRPC、Protobuf、V4L2、Threads）。

## B. ROS API 迁移（核心）
5. 将 rclcpp::Node 迁移为 ros::NodeHandle（含成员结构调整）。
6. 将 rclcpp::Publisher/Timer/Logger/QoS 替换为 ROS1 API（ros::Publisher/ros::Timer/ROS_* 日志）。
7. 将 rclcpp::Time / rclcpp::Clock 用 ROS1 的 ros::Time / ros::WallTime 替代。
8. 将参数系统从 declare_parameter/get_parameter_or 改为 ros::param / nh.param。
9. 修正节点入口与 spin 方式（rclcpp::spin -> ros::spin）。

## C. 参数与 Launch（必做）
10. 将 ROS2 参数 YAML 改为 ROS1 rosparam 结构（移除 ros__parameters）。
11. 将 ROS2 launch.py 改为 ROS1 .launch XML（使用 rosparam + node）。
12. 核对参数命名空间（/teleop_robot_bridge 或私有参数 ~）。

## D. 功能级迁移注意点（不涉及硬件）
13. gRPC 信令客户端：确认 ROS1 下线程/回调生命周期管理一致。
14. UDP 传输模块：保持逻辑不变，仅改 ROS API 与日志输出。
15. Pose UDP 接收：改 ROS API 发布者与时间戳类型。
16. 日志文件模块：替换 rclcpp::Logger 为 ROS1 日志接口。

## E. 与硬件打交道的部分（暂不需要实现）
17. V4L2 采集模块（VideoV4L2Capturer）适配 Orin 的设备节点与像素格式。
18. Jetson Multimedia API 相关编解码（VideoConverter/VideoEncoder）
    - 库路径、头文件、链接库在 Orin/Ubuntu20 上校验
    - NVENC/NvBufSurface/NvJPEG 版本差异处理
19. CUDA 依赖路径与版本兼容性确认
20. 录像/写盘性能与路径权限在 Orin 上验证

---
备注：E 部分标记为“暂不需要实现”，可以先保证 ROS1 版本编译通过与网络链路可用，再逐步替换硬件相关模块。
