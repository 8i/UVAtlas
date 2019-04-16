cmake_minimum_required (VERSION 3.13.1)

project(UVAtlas)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory(UVAtlas)
