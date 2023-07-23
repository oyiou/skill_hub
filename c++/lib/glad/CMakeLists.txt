cmake_minimum_required (VERSION 3.8)

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h)

add_library(glad
	src/glad.c

	${HEADER_FILES}
)

target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)