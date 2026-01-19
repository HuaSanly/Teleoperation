cmake_minimum_required(VERSION 3.8)
project(teleop_robot_bridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# gRPC / Protobuf (for signaling_client.hpp)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Helper to find the grpc_cpp_plugin
if(TARGET gRPC::grpc_cpp_plugin)
  set(gRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
else()
  find_program(gRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
  if(NOT gRPC_CPP_PLUGIN_EXECUTABLE)
    message(FATAL_ERROR "grpc_cpp_plugin not found. Ensure gRPC is installed and grpc_cpp_plugin is in PATH or gRPC CMake targets are available.")
  endif()
endif()

# Collect .proto files
file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
if(NOT PROTO_FILES)
  message(WARNING "No .proto files found in ${CMAKE_CURRENT_SOURCE_DIR}/proto")
endif()

# Generate sources
set(PROTO_GENS_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_GENS_DIR})

set(PROTO_SRCS "")
set(PROTO_HDRS "")

foreach(PROTO_FILE ${PROTO_FILES})
  get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
  set(PROTO_SRC "${PROTO_GENS_DIR}/${PROTO_NAME}.pb.cc")
  set(PROTO_HDR "${PROTO_GENS_DIR}/${PROTO_NAME}.pb.h")
  set(GRPC_SRC "${PROTO_GENS_DIR}/${PROTO_NAME}.grpc.pb.cc")
  set(GRPC_HDR "${PROTO_GENS_DIR}/${PROTO_NAME}.grpc.pb.h")

  add_custom_command(
    OUTPUT "${PROTO_SRC}" "${PROTO_HDR}" "${GRPC_SRC}" "${GRPC_HDR}"
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS --grpc_out="${PROTO_GENS_DIR}"
      --cpp_out="${PROTO_GENS_DIR}"
      --plugin=protoc-gen-grpc=${gRPC_CPP_PLUGIN_EXECUTABLE}
      -I "${CMAKE_CURRENT_SOURCE_DIR}/proto"
      "${PROTO_FILE}"
    DEPENDS "${PROTO_FILE}"
  )

  list(APPEND PROTO_SRCS ${PROTO_SRC} ${GRPC_SRC})
  list(APPEND PROTO_HDRS ${PROTO_HDR} ${GRPC_HDR})
endforeach()

add_library(${PROJECT_NAME}_grpc_proto ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(${PROJECT_NAME}_grpc_proto
  ${Protobuf_LIBRARIES}
  gRPC::grpc++
)
target_include_directories(${PROJECT_NAME}_grpc_proto PUBLIC
  "${PROTO_GENS_DIR}"
)

add_library(video_v4l2_capturer
  src/video/video_v4l2_capturer.cpp
)

target_include_directories(video_v4l2_capturer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(video_v4l2_capturer
  v4l2
  Threads::Threads
)

list(APPEND EXTRA_LIBS video_v4l2_capturer)

add_library(video_converter
  src/video/video_converter.cpp
)

ament_target_dependencies(video_converter
  rclcpp
)

# Jetson Multimedia API (MJPEG hardware decode + NV12 NVMM)
set(JETSON_MM_API_PATH "/usr/src/jetson_multimedia_api")
set(JETSON_COMMON_DIR "${JETSON_MM_API_PATH}/samples/common")

if(EXISTS "${JETSON_MM_API_PATH}")
  message(STATUS "Found Jetson Multimedia API at ${JETSON_MM_API_PATH}")

  # Jetson Multimedia API sources are third-party; keep our code strict, but
  # silence known noisy warnings from upstream headers/samples.
  target_compile_options(video_converter PRIVATE
    -Wno-pedantic
    -Wno-missing-field-initializers
    -Wno-unused-parameter
  )

  target_compile_definitions(video_converter PUBLIC TRB_HAS_JETSON_MM_API=1)

  if(NOT CUDA_FOUND)
    if(POLICY CMP0146)
      cmake_policy(SET CMP0146 OLD)
    endif()
    find_package(CUDA)
  endif()

  if(CUDA_FOUND)
    target_include_directories(video_converter PUBLIC ${CUDA_INCLUDE_DIRS})
    target_link_libraries(video_converter cuda)
  elseif(EXISTS "/usr/local/cuda/include")
    target_include_directories(video_converter PUBLIC "/usr/local/cuda/include")
    target_link_libraries(video_converter cuda)
  else()
    message(WARNING "CUDA headers not found; Jetson MJPEG decode may fail to compile (missing cuda.h).")
  endif()

  target_include_directories(video_converter PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${JETSON_MM_API_PATH}/include/libjpeg-8b
    ${JETSON_MM_API_PATH}/include
    ${JETSON_COMMON_DIR}/classes
  )

  link_directories(
    "/usr/lib/aarch64-linux-gnu/nvidia"
    "/usr/lib/aarch64-linux-gnu/tegra"
  )

  target_sources(video_converter PRIVATE
    "${JETSON_COMMON_DIR}/classes/NvJpegDecoder.cpp"
    "${JETSON_COMMON_DIR}/classes/NvBufSurface.cpp"
    "${JETSON_COMMON_DIR}/classes/NvBuffer.cpp"
    "${JETSON_COMMON_DIR}/classes/NvElement.cpp"
    "${JETSON_COMMON_DIR}/classes/NvLogging.cpp"
    "${JETSON_COMMON_DIR}/classes/NvElementProfiler.cpp"
    "${JETSON_COMMON_DIR}/classes/NvUtils.cpp"
    "${JETSON_COMMON_DIR}/classes/NvV4l2Element.cpp"
    "${JETSON_COMMON_DIR}/classes/NvV4l2ElementPlane.cpp"
  )

  target_link_libraries(video_converter
    Threads::Threads
    v4l2
    nvv4l2
    nvbufsurface
    nvbufsurftransform
    nvmm_jpeg
  )

  # Video Encoder (H.264 hardware encode)
  add_library(video_encoder
    src/video/video_encoder.cpp
  )

  # video_encoder now uses TeleopLogger, which depends on rclcpp.
  ament_target_dependencies(video_encoder
    rclcpp
  )

  target_compile_options(video_encoder PRIVATE
    -Wno-pedantic
    -Wno-missing-field-initializers
    -Wno-unused-parameter
  )

  target_compile_definitions(video_encoder PUBLIC TRB_HAS_JETSON_MM_API=1)

  if(CUDA_FOUND)
    target_include_directories(video_encoder PUBLIC ${CUDA_INCLUDE_DIRS})
    target_link_libraries(video_encoder cuda)
  elseif(EXISTS "/usr/local/cuda/include")
    target_include_directories(video_encoder PUBLIC "/usr/local/cuda/include")
    target_link_libraries(video_encoder cuda)
  endif()

  target_include_directories(video_encoder PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${JETSON_MM_API_PATH}/include/libjpeg-8b
    ${JETSON_MM_API_PATH}/include
    ${JETSON_COMMON_DIR}/classes
  )

  target_sources(video_encoder PRIVATE
    "${JETSON_COMMON_DIR}/classes/NvVideoEncoder.cpp"
    "${JETSON_COMMON_DIR}/classes/NvBufSurface.cpp"
    "${JETSON_COMMON_DIR}/classes/NvBuffer.cpp"
    "${JETSON_COMMON_DIR}/classes/NvElement.cpp"
    "${JETSON_COMMON_DIR}/classes/NvLogging.cpp"
    "${JETSON_COMMON_DIR}/classes/NvElementProfiler.cpp"
    "${JETSON_COMMON_DIR}/classes/NvUtils.cpp"
    "${JETSON_COMMON_DIR}/classes/NvV4l2Element.cpp"
    "${JETSON_COMMON_DIR}/classes/NvV4l2ElementPlane.cpp"
  )

  target_link_libraries(video_encoder
    Threads::Threads
    v4l2
    nvv4l2
    nvbufsurface
    nvbufsurftransform
  )
else()
  message(WARNING "Jetson Multimedia API not found at ${JETSON_MM_API_PATH}. video_converter will be built in stub mode.")
endif()



list(APPEND EXTRA_LIBS video_converter video_encoder)

add_executable(${PROJECT_NAME}
  src/main_node.cpp
  src/signaling_client.cpp
  src/utils/teleop_logger.cpp
  src/video/video_recorder.cpp
  src/video/video_stream_manager.cpp
  src/udp/udp_socket.cpp
  src/udp/udp_packet.cpp
  src/udp/gf256.cpp
  src/udp/pose_udp_receiver.cpp
  src/udp/udp_stream_manager.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  "${PROTO_GENS_DIR}"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  rclpy
  std_msgs
  sensor_msgs
  geometry_msgs
)

target_link_libraries(${PROJECT_NAME}
  ${PROJECT_NAME}_grpc_proto
  v4l2
  Threads::Threads
  OpenSSL::SSL
  OpenSSL::Crypto
  ${EXTRA_LIBS}
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

# Scoped header install: install under include/${PROJECT_NAME}
install(FILES
  include/main_node.hpp
  include/signaling_client.hpp
  DESTINATION include/${PROJECT_NAME}
)

install(DIRECTORY include/video
  DESTINATION include/${PROJECT_NAME}
)


install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()