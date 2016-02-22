include_directories(include)

set (
    CMAKE_LIBRARY_OUTPUT_DIRECTORY
		${CMAKE_SOURCE_DIR}
)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(src)
