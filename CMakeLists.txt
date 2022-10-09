# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("MicroFlakeX")

add_subdirectory ("MicroGenerics")

add_subdirectory ("MicroGhost")

set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/build)

