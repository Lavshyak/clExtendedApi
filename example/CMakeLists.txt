cmake_minimum_required(VERSION 3.26)
project(exampleProj)

set(CMAKE_CXX_STANDARD 17)

include(../libs/OpenCL-SDK-v2023.04.17-Win-x64/share/cmake/OpenCL/OpenCLConfig.cmake)

#clExtendedApi
include(../CMakeLists.txt)

include_directories(exampleExe ../headers)

file(GLOB SRC
    src/*
)

add_executable(exampleExe ${SRC})

target_link_libraries(exampleExe clExtendedApi)

add_custom_command(
        TARGET exampleExe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/opencl
        ${CMAKE_CURRENT_BINARY_DIR}/opencl)