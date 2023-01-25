cmake_minimum_required(VERSION 3.15)

project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OpenCV_DIR "/root/computer-vision/opencv4.7-install/lib/cmake/opencv4")

find_package(OpenCV 4.7.0 QUIET COMPONENTS opencv_world wechat_qrcode)
# for opencv 2.4 on ubuntu 16.04, there is no opencv_world but OpenCV_FOUND will be TRUE
if("${OpenCV_LIBS}" STREQUAL "")
    set(OpenCV_FOUND FALSE)
endif()
if(NOT OpenCV_FOUND)
    find_package(OpenCV QUIET COMPONENTS core highgui imgproc imgcodecs videoio)
endif()
if(NOT OpenCV_FOUND)
    find_package(OpenCV QUIET COMPONENTS core highgui imgproc)
endif()


if(OpenCV_FOUND)
    message(STATUS "OpenCV library: ${OpenCV_INSTALL_PATH}")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
    if(${OpenCV_VERSION_MAJOR} GREATER 3)
        set(CMAKE_CXX_STANDARD 11)
    endif()
else()
    message(FATAL_ERROR "Error! OpenCV not found!")
endif()

link_directories("/root/computer-vision/opencv4.7-install/lib")

add_executable(test
test-tencent.cpp
)

target_link_libraries(test ${OpenCV_LIBS})