cmake_minimum_required(VERSION 3.22)
project(src VERSION 1.0 DESCRIPTION "src project" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)

SUB_DIRS(SUB_SRC_DIRS ${CPP_SRC_DIR})
foreach(SUB_SRC ${SUB_SRC_DIRS})
    add_subdirectory(${SUB_SRC})
endforeach(SUB_SRC)
