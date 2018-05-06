add_subdirectory(triangle)
add_subdirectory(camera-fps)

add_custom_target(samples
        DEPENDS ${SAMPLE_LIST})

# Copies the asset folder in the build folder
add_custom_command(TARGET samples POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/samples/asset
        ${CMAKE_BINARY_DIR}/bin/samples/asset/)