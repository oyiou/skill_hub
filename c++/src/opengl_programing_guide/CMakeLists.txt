cmake_minimum_required(VERSION 3.22)
project(opengl_programing_guide VERSION 1.0 DESCRIPTION "opengl_programing_guide project" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)

include_directories(${INCLUDE_DIRS})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/lib SOURCES)
link_directories(${LINK_DIRS})
link_libraries(OpenGL32 glad glfw)

OBJCT_TEMPLATE(${CMAKE_CURRENT_SOURCE_DIR})
