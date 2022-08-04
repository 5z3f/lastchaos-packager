cmake_minimum_required(VERSION 3.22)

project(packager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")

add_subdirectory(extern/zstd)

add_executable(packager
    src/main.cpp
    src/file.hpp
)

target_link_libraries(packager PRIVATE zstd)
target_include_directories(packager PRIVATE src/)
target_include_directories(packager PRIVATE extern/json/ extern/xxhash/)
