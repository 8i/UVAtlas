cmake_minimum_required(VERSION 3.13.1)

project(UVAtlas)

#These compiler settings are set for all targets that are added for included in this file.
if (WIN32)

    ### KV: Disabling windows compilation through cmake since we are not worrying about supporting this for now

    message(FATAL_ERROR "Windows currently no supported for this library")
    ##Configure compile flags to match VS sln
    #set(CXX_COMMON_FLAGS "/MP /fp:fast /sdl /permissive- /Zc:__cplusplus")
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_COMMON_FLAGS}")
    #set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CXX_COMMON_FLAGS}")
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_COMMON_FLAGS}")
    #
    ##    UVAtlas is too slow in debug so use optimization flags to speed up
    #string(REPLACE "/Od" "/O2" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    #string(REPLACE "/Ob0" "" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    #string(REPLACE "/RTC1" "" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    #string(REPLACE "/Od" "/O2" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    #string(REPLACE "/Ob0" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    #string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
endif ()

set(UVATLAS_SRC
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

add_library(${PROJECT_NAME} STATIC ${UVATLAS_SRC})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/isochart
    ${CMAKE_CURRENT_LIST_DIR}/geodesics
    )

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<PLATFORM_ID:Linux>:__LINUX__>
    UNICODE
    _UNICODE
    )

set_target_properties(UVAtlas PROPERTIES
    COMPILE_PDB_NAME "UVAtlas"
    COMPILE_PDB_NAME_DEBUG "UVAtlas${CMAKE_DEBUG_POSTFIX}"
    POSITION_INDEPENDENT_CODE ON
    )
