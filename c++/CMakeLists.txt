cmake_minimum_required(VERSION 3.22)
project(c++ VERSION 1.0 DESCRIPTION "c++ project" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)

set(CPP_DIR    ${CMAKE_CURRENT_SOURCE_DIR})
SET(CPP_SRC_DIR            ${CPP_DIR}/src)
SET(CPP_LIB_DIR            ${CPP_DIR}/lib)
SET(CPP_RES_DIR            ${CPP_DIR}/res)
SET(CPP_BIN_DIR            ${CPP_DIR}/bin)
set(CPP_CMAKE_DIR          ${CPP_DIR}/cmake)
set(CPP_INCLUDE_DIR        ${CPP_DIR}/include)
set(CPP_CMAKE_COMMON_DIR   ${CPP_CMAKE_DIR}/common)

include_directories(${CPP_INCLUDE_DIR})

file(GLOB CPP_CMAKE_FILES "${CPP_CMAKE_COMMON_DIR}/*.cmake")
foreach(SUB_CMAKE ${CPP_CMAKE_FILES})
    include(${SUB_CMAKE})
endforeach(SUB_CMAKE)

EXISTS_FILE_SUB_PATHS(SUB_PROJ_DIRS ${CPP_LIB_DIR} CMakeLists.txt)
foreach(SUB_PROJ ${SUB_PROJ_DIRS})
    add_subdirectory(${SUB_PROJ})
endforeach(SUB_PROJ)

aux_source_directory(${CPP_LIB_DIR}/oyiou SOURCES)

add_subdirectory(src)
