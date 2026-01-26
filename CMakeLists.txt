cmake_minimum_required(VERSION 3.0.2)
project(teleoperation_robot_bridge)

## Compile as C++17 (needed for ported ROS2 code)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  std_msgs
  sensor_msgs
  geometry_msgs
)

find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG QUIET)
find_package(OpenSSL REQUIRED)

set(GRPC_FOUND_CONFIG FALSE)
if(gRPC_FOUND)
  set(GRPC_FOUND_CONFIG TRUE)
endif()

if(NOT GRPC_FOUND_CONFIG)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GRPC REQUIRED grpc++ grpc)
endif()

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp roslib std_msgs sensor_msgs geometry_msgs
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(JETSON_MMAPI_DIR "/usr/src/jetson_multimedia_api")
set(JETSON_MMAPI_COMMON_DIR "${JETSON_MMAPI_DIR}/samples/common/classes")
if(EXISTS "${JETSON_MMAPI_DIR}/include/NvJpegDecoder.h")
  include_directories(
    ${JETSON_MMAPI_DIR}/include
    ${JETSON_MMAPI_DIR}/include/libjpeg-8b
  )
endif()

# gRPC / Protobuf generated sources
file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
if(NOT PROTO_FILES)
  message(WARNING "No .proto files found in ${CMAKE_CURRENT_SOURCE_DIR}/proto")
endif()

if(TARGET gRPC::grpc_cpp_plugin)
  set(gRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
else()
  find_program(gRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
  if(NOT gRPC_CPP_PLUGIN_EXECUTABLE)
    message(FATAL_ERROR "grpc_cpp_plugin not found. Ensure gRPC is installed and grpc_cpp_plugin is in PATH.")
  endif()
endif()

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
if(GRPC_FOUND_CONFIG)
  target_link_libraries(${PROJECT_NAME}_grpc_proto
    ${Protobuf_LIBRARIES}
    gRPC::grpc++
  )
else()
  target_link_libraries(${PROJECT_NAME}_grpc_proto
    ${Protobuf_LIBRARIES}
    ${GRPC_LIBRARIES}
  )
  target_include_directories(${PROJECT_NAME}_grpc_proto PUBLIC
    ${GRPC_INCLUDE_DIRS}
  )
endif()
target_include_directories(${PROJECT_NAME}_grpc_proto PUBLIC
  "${PROTO_GENS_DIR}"
)

## Declare a C++ executable
add_executable(${PROJECT_NAME}
  src/main_node.cpp
  src/signaling_client.cpp
  src/video/video_stream_manager.cpp
  src/video/video_v4l2_capturer.cpp
  src/video/video_decoder.cpp
  src/video/video_converter.cpp
  src/video/video_encoder.cpp
  src/video/video_recorder.cpp
  src/udp/udp_manager.cpp
  src/udp/pose_udp_receiver.cpp
  src/udp/udp_packet.cpp
  src/udp/udp_video_sender.cpp
  src/udp/fec_executor.cpp
  src/udp/gf256.cpp
)

if(EXISTS "${JETSON_MMAPI_COMMON_DIR}/NvJpegDecoder.cpp")
  target_sources(${PROJECT_NAME} PRIVATE
    ${JETSON_MMAPI_COMMON_DIR}/NvJpegDecoder.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvBufSurface.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvBuffer.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvElement.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvElementProfiler.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvLogging.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvV4l2Element.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvV4l2ElementPlane.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvVideoEncoder.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvVideoDecoder.cpp
    ${JETSON_MMAPI_COMMON_DIR}/NvUtils.cpp
  )
endif()

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}_grpc_proto
  OpenSSL::SSL
  OpenSSL::Crypto
)

set(JETSON_LIB_PATHS
  /usr/lib/aarch64-linux-gnu
  /usr/lib/aarch64-linux-gnu/tegra
  /usr/lib
)
find_library(NVV4L2_LIB nvv4l2 PATHS ${JETSON_LIB_PATHS})
find_library(NVBUF_SURFACE_LIB nvbufsurface PATHS ${JETSON_LIB_PATHS})
find_library(NVBUF_TRANSFORM_LIB nvbufsurftransform PATHS ${JETSON_LIB_PATHS})
find_library(NVJPEG_LIB nvjpeg PATHS ${JETSON_LIB_PATHS})
find_library(V4L2_LIB v4l2 PATHS ${JETSON_LIB_PATHS})

if(NVV4L2_LIB)
  target_link_libraries(${PROJECT_NAME} ${NVV4L2_LIB})
endif()
if(NVBUF_SURFACE_LIB)
  target_link_libraries(${PROJECT_NAME} ${NVBUF_SURFACE_LIB})
endif()
if(NVBUF_TRANSFORM_LIB)
  target_link_libraries(${PROJECT_NAME} ${NVBUF_TRANSFORM_LIB})
endif()
if(NVJPEG_LIB)
  target_link_libraries(${PROJECT_NAME} ${NVJPEG_LIB})
endif()
if(V4L2_LIB)
  target_link_libraries(${PROJECT_NAME} ${V4L2_LIB})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROTO_GENS_DIR}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/teleoperation_robot_bridge.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/teleoperation_robot_bridge_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.hpp"
)

install(DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_teleoperation_robot_bridge.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
