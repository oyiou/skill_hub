cmake_minimum_required(VERSION 3.22)
project(high_performance_server
        VERSION 1.0
        DESCRIPTION "high_performance_server project"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 14)

SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include/custom)
if (WINDOWS)
    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include/windows)
    SET(SRC_DIRS ${SRC_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/windows)
    SET(OUTPUT_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/bin/windows)
elseif (LINUX)
    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include/linux)
    SET(SRC_DIRS ${SRC_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/linux)
    SET(OUTPUT_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux)
endif()

include_directories(${INCLUDE_DIRS})

SUB_DIRS(SOURCE_DIRS ${SRC_DIRS})
foreach(EXAMPLE ${SOURCE_DIRS})
    string(REPLACE "-" ";" Name ${EXAMPLE})
    list(GET Name 1 TARGET)
    message("TARGET: ${TARGET}")
    unset(TARGET_SOURCES)
    aux_source_directory(${SRC_DIRS}/${EXAMPLE} TARGET_SOURCES)
    add_executable(${TARGET} ${SOURCES} ${TARGET_SOURCES})
    set(TARGET_INCLUDE_DIRS ${SRC_DIRS}/${EXAMPLE})
    target_include_directories(${TARGET} PRIVATE ${TARGET_INCLUDE_DIRS})
    target_link_libraries(${TARGET} ws2_32 wsock32)
    set_target_properties(${TARGET} PROPERTIES
            CMAKE_DEBUG_POSTFIX         "_d"
            ARCHIVE_OUTPUT_DIRECTORY    "${OUTPUT_DIRS}/${TARGET}/lib"
            LIBRARY_OUTPUT_DIRECTORY    "${OUTPUT_DIRS}/${TARGET}/lib"
            RUNTIME_OUTPUT_DIRECTORY    "${OUTPUT_DIRS}/${TARGET}/bin"
            )
endforeach(EXAMPLE)