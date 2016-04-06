cmake_minimum_required(VERSION 2.8)
project(Engine)

# Options
option(BUILD_SAMPLES "Build sample programs" OFF)

# Library output directory
set (
	CMAKE_LIBRARY_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR}
)

# Subdirectories
add_subdirectory(src)

if (BUILD_SAMPLES)
	add_subdirectory(samples)
endif (BUILD_SAMPLES)
