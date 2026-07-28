# Teleop Robot Bridge 使用说明

本文档面向使用者，说明如何运行 teleop_robot_bridge 节点并验证视频/遥测链路。

## 运行前准备

- 已配置 ROS 1 运行环境。
- Jetson 设备已安装 Jetson Multimedia API。
- 相机可通过 V4L2 设备访问（默认 /dev/video2）。

## 编译

在工作空间根目录执行：

```bash
cd /home/nvidia/ROS/tele_ws
catkin_make --pkg teleop_robot_bridge
```

## 配置

主配置文件：

- config/params.yaml

常用配置项：

- video.profile：分辨率与帧率
- video.device：V4L2 设备路径
- video.encoder：码率与 I/IDR 间隔
- video.eye_image：是否启用眼图与输出尺寸
- udp.server_udp_ip / udp.server_udp_port：远端地址

## 运行

启动 ROS core（如未启动）：

```bash
roscore
```

启动节点：

```bash
cd /home/nvidia/ROS/tele_ws/src/teleop_robot_bridge
./bringup.sh
```

## 验证

检查节点与话题：

```bash
rostopic list
```

若启用眼图，验证话题与频率：

```bash
rostopic hz /data/left_eye_image
rostopic hz /data/right_eye_image
```

## 说明

- UDP 视频使用 H.264 发送，可选 FEC。
- UDP 头部 KeyframeFlag 依据 IDR 判定。
- 修改 params.yaml 后需重启节点。

## 常见问题

- 视频无法启动：检查相机设备路径与权限。
- 延迟逐渐升高：检查网络质量与接收端缓冲策略。
- 退出缓慢：确认设备未被其他进程占用。
