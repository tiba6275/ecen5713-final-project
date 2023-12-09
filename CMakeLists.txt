cmake_minimum_required(VERSION 2.8)
project(DetectChange)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-video-1.0)
include_directories(${GSTREAMER_INCLUDE_DIRS})
link_directories(${GSTREAMER_LIBRARY_DIRS})

add_executable(DetectChange DetectChange.cpp)

target_link_libraries(DetectChange ${OpenCV_LIBS} ${GSTREAMER_LIBRARIES} pthread)

