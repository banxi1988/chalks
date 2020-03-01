cmake_minimum_required(VERSION 3.16.0)
project(cpp-chalks VERSION 0.1.0)
# 设置 所有 target 默认的 cxx 版本 11,14,17 或 20
set(CMAKE_CXX_STANDARD 11)
add_library(chalks INTERFACE)
target_include_directories(chalks INTERFACE include/)
target_sources(chalks INTERFACE include/chalks/chalks.hpp)
#  头文件
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include
)

add_subdirectory(demo)
