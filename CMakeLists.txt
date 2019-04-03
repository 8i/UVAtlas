cmake_minimum_required (VERSION 3.13.1)

set(CMAKE_DEBUG_POSTFIX -debug)

if(MSVC)
    add_subdirectory(UVAtlas)
endif()
