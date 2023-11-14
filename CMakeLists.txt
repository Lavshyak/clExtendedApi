cmake_minimum_required(VERSION 3.26)
project(clExtendedApiProj)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(CL_HPP_TARGET_OPENCL_VERSION=220)
add_compile_definitions(CL_HPP_ENABLE_EXCEPTIONS)

#OpenclSDK
#include(libs/OpenCL-SDK-v2023.04.17-Win-x64/share/cmake/OpenCL/OpenCLConfig.cmake)
include_directories(headers)

file(GLOB SRC
        src/*
        headers/*
)

add_library(clExtendedApi SHARED ${SRC})

#OpenclSDK
target_link_libraries(clExtendedApi OpenCL::OpenCL)