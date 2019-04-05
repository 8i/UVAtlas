cmake_minimum_required (VERSION 3.13.1)

project(UVAtlas)

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/inc)
include_directories(${CMAKE_CURRENT_LIST_DIR}/geodesics)
include_directories(${CMAKE_CURRENT_LIST_DIR}/isochart)

if (UNIX)
add_definitions(-D__LINUX__)
include_directories(${CMAKE_CURRENT_LIST_DIR}/linux)
endif()

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
#include(${CMAKE_USER_MAKE_RULES_OVERRIDE}) 
add_library(UVAtlas STATIC ${UVATLAS_SRC} ${UVATLAS_HDR})
