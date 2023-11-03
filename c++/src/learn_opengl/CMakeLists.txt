cmake_minimum_required(VERSION 3.22)
project(learn_opengl VERSION 1.0 DESCRIPTION "learn_opengl project" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)

link_libraries(OpenGL32 glad glfw
#        soil2
        glm)

aux_source_directory(${CPP_LIB_DIR}/oyiou PROJ_SOURCES)

OBJCT_TEMPLATE(${CMAKE_CURRENT_SOURCE_DIR})
