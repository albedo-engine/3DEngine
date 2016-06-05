cmake_minimum_required(VERSION 3.0)
project(Engine)

# C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin/samples)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin/samples)
set(CMAKE_DOC_OUTPUT_DIRECTORY      ${CMAKE_BINARY_DIR}/doc)

# Add the engine and samples directories
add_subdirectory(src)
add_subdirectory(samples)

# Add the test suite subdirectory
add_subdirectory(tests)

# Add the doc subdirectory
add_subdirectory(doc)
