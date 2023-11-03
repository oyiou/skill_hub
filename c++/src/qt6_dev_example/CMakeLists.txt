cmake_minimum_required(VERSION 3.22)
project(Qt6_dev_example VERSION 1.0 DESCRIPTION "Qt6_dev_example project" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

include(${CPP_CMAKE_DIR}/qt6/qt6.cmake)

OBJCT_TEMPLATE(${CMAKE_CURRENT_SOURCE_DIR})
