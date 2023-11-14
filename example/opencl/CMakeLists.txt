#do not compile. for development in IDE only.
cmake_minimum_required(VERSION 3.20)
project(rc4gpu_opencl C)

set(CMAKE_C_STANDARD 99)

include_directories(../../OpenclHelpers)

file(GLOB OPENCL
        *
        ../../OpenclHelpers/*
)
add_library(rc4gpu_opencl ${OPENCL})
set_target_properties(rc4gpu_opencl PROPERTIES LINKER_LANGUAGE C)

