cmake_minimum_required(VERSION 3.0)
project(pvz-randomEventWall)

set (pvz-randomEventWall_VERSION_MAJOR 0)
set (pvz-randomEventWall_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "/std:c++latest ${CMAKE_CXX_FLAGS}")
configure_file(
    "${PROJECT_SOURCE_DIR}/randomEventWall/include/config.h.in"
    "${pvz-randomEventWall_BINARY_DIR}/randomEventWall/config.h"
)
 
aux_source_directory(./randomEventWall DIR_SRCS)
aux_source_directory(./randomEventWall/include DIR_SRCS)
aux_source_directory(./randomEventWall/components DIR_SRCS)
aux_source_directory(./randomEventWall/components/include DIR_SRCS)
include_directories(DIR_SRCS)

aux_source_directory(./pvzclass/pvzclass DIR_LIB_SRCS)
aux_source_directory(./pvzclass/pvzclass/Classes DIR_LIB_SRCS)
aux_source_directory(./pvzclass/pvzclass/Enums DIR_LIB_SRCS)
include_directories(DIR_LIB_SRCS)


#list(REMOVE_ITEM DIR_LIB_SRCS "pvzclass\pvzclass\pvzclass.cpp" "pvzclass\pvzclass\pvzclass.h")
add_library (libpvzclass STATIC ${DIR_LIB_SRCS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(pvz-randomEventWall ${DIR_SRCS}) 
target_link_libraries(pvz-randomEventWall libpvzclass)

