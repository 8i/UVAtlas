cmake_minimum_required (VERSION 3.13.1)

project(UVAtlas)

set(CMAKE_DEBUG_POSTFIX d)

add_definitions(-D_UNICODE -DUNICODE)

#These compiler settings are set for all targets that are added for included in this file.
if (WIN32)
    #Configure compile flags to match VS sln
    set(CXX_COMMON_FLAGS "/MP /fp:fast /sdl /permissive- /Zc:__cplusplus")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_COMMON_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CXX_COMMON_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_COMMON_FLAGS}")

    #    UVAtlas is too slow in debug so use optimization flags to speed up
    string(REPLACE "/Od" "/O2" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    string(REPLACE "/Ob0" "" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    string(REPLACE "/RTC1" "" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    string(REPLACE "/Od" "/O2" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/Ob0" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
elseif(UNIX)
    set(CXX_COMMON_FLAGS "-std=c++11 -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG ${CXX_COMMON_FLAGS}" CACHE STRING "Debug options" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG ${CXX_COMMON_FLAGS}" CACHE STRING "Release options" FORCE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g" CACHE STRING "Relwithdebinfo options" FORCE)
    set(CMAKE_C_FLAGS_DEBUG "-g -D_DEBUG" CACHE STRING "Debug options" FORCE)
    set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "Release options" FORCE)
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} -g" CACHE STRING "Relwithdebinfo" FORCE)

    add_definitions(-D__LINUX__)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/inc)
include_directories(${CMAKE_CURRENT_LIST_DIR}/geodesics)
include_directories(${CMAKE_CURRENT_LIST_DIR}/isochart)

set (UVATLAS_SRC
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/ApproximateOneToAll.cpp
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/ExactOneToAll.cpp
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/mathutils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/barycentricparam.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/basemeshinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/graphcut.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/imtcomputation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochart.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochartengine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochartmesh.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochartutil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isomap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/lscmparam.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/mergecharts.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/meshapplyisomap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/meshoptimizeboundaries.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/meshoptimizestretch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/meshpartitionchart.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/packingcharts.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/progressivemesh.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/UVAtlas.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/UVAtlasRepacker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/vertiter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/Vis_Maxflow.cpp
    )
	
set (UVATLAS_HDR
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/ApproximateOneToAll.h
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/datatypes.h
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/ExactOneToAll.h
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/mathutils.h
    ${CMAKE_CURRENT_LIST_DIR}/geodesics/minheap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/inc/UVAtlas.h
    ${CMAKE_CURRENT_LIST_DIR}/inc/JntLinuxTypes.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/basemeshinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/callbackschemer.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/graphcut.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochart.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochartconfig.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochartengine.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochartmesh.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isochartutil.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/isomap.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/progressivemesh.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/sparsematrix.hpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/SymmetricMatrix.hpp
    ${CMAKE_CURRENT_LIST_DIR}/isochart/UVAtlasRepacker.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/vertiter.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/Vis_Maxflow.h
    ${CMAKE_CURRENT_LIST_DIR}/isochart/meshcommon.inl
    ${CMAKE_CURRENT_LIST_DIR}/maxheap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/pch.h
    )

add_library(UVAtlas STATIC ${UVATLAS_SRC} ${UVATLAS_HDR})

set_target_properties(UVAtlas PROPERTIES
                      COMPILE_PDB_NAME "UVAtlas"
                      COMPILE_PDB_NAME_DEBUG "UVAtlas${CMAKE_DEBUG_POSTFIX}"
                      )
