# CMakeList.txt: MicroGhost的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set(OBJECT_CXX_V 17)
set(OBJECT_NAME "MicroGhost")
set(OBJECT_INCLUDE_DIR "MicroGenerics")
set(OBJECT_LINK_LIBRARY "")

if (CMAKE_CL_64)
set(CMAKE_DEBUG_POSTFIX "_x64_d")
set(CMAKE_RELEASE_POSTFIX "_x64_r")
else()
set(CMAKE_DEBUG_POSTFIX "_x86_d")
set(CMAKE_RELEASE_POSTFIX "_x86_r")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_SOURCE_DIR}/out/library)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_SOURCE_DIR}/out/library)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_SOURCE_DIR}/out/library)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_SOURCE_DIR}/out/library)

link_directories(
    ${PROJECT_SOURCE_DIR}/out/library
) 

foreach(iter ${OBJECT_INCLUDE_DIR})
    include_directories("${PROJECT_SOURCE_DIR}/${iter}/include")
    message(STATUS "INCLUDE_DIR ==> ${PROJECT_SOURCE_DIR}/${iter}/include")
endforeach()

include_directories(
    "source"
    "include/${OBJECT_NAME}"
)

foreach(iter ${OBJECT_LINK_LIBRARY})
    link_libraries(${iter})
    message(STATUS "LINK_LIBRARIES ==> ${iter}")
endforeach()

file(GLOB_RECURSE MICRO_OBJECT_SRC
    "source/*.h"
    "source/*.cpp"
    "include/${OBJECT_NAME}/*.h"
    "include/${OBJECT_NAME}/*.cpp"
)

add_library(${OBJECT_NAME} SHARED ${MICRO_OBJECT_SRC})
add_library(${OBJECT_NAME}_s STATIC ${MICRO_OBJECT_SRC})

target_precompile_headers(${OBJECT_NAME} PUBLIC
    "source/pch.h"
)

target_precompile_headers(${OBJECT_NAME}_s PUBLIC
    "source/pch.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${OBJECT_NAME} PROPERTY CXX_STANDARD ${OBJECT_CXX_V})
    set_property(TARGET ${OBJECT_NAME}_s PROPERTY CXX_STANDARD ${OBJECT_CXX_V})
endif()

# TODO: 如有需要，请添加测试并安装目标。
