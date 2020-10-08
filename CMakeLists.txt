cmake_minimum_required(VERSION 3.0)
project(pvz-randomEventWall)


set(CMAKE_CXX_FLAGS "/std:c++latest /utf-8 ${CMAKE_CXX_FLAGS}")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFESTUAC:level='requireAdministrator'")
#configure_file(
#    "${PROJECT_SOURCE_DIR}/randomEventWall/include/config.h.in"
#    "${pvz-randomEventWall_BINARY_DIR}/randomEventWall/config.h"
#)
 
aux_source_directory(${PROJECT_SOURCE_DIR}/randomEventWall/ DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/randomEventWall/include DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/randomEventWall/components DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/randomEventWall/components/include DIR_SRCS)
include_directories(DIR_SRCS)

aux_source_directory(${PROJECT_SOURCE_DIR}/pvzclass/pvzclass DIR_LIB_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/pvzclass/pvzclass/Classes DIR_LIB_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/pvzclass/pvzclass/Enums DIR_LIB_SRCS)
include_directories(DIR_LIB_SRCS)


#list(REMOVE_ITEM DIR_LIB_SRCS "pvzclass\pvzclass\pvzclass.cpp" "pvzclass\pvzclass\pvzclass.h")
add_library (libpvzclass STATIC ${DIR_LIB_SRCS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(pvz-randomEventWall ${DIR_SRCS}) 


target_link_libraries(pvz-randomEventWall libpvzclass)

