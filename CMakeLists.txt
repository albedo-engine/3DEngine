cmake_minimum_required(VERSION 3.0)
project(Engine)

# Options
option(BUILD_SAMPLES "Build sample programs" OFF)

# C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/samples)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/samples)

# Subdirectories
add_subdirectory(src)

if (BUILD_SAMPLES)
	add_subdirectory(samples)
endif (BUILD_SAMPLES)
