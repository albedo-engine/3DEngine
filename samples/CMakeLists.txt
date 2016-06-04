add_subdirectory(triangle)
add_subdirectory(camera-fps)

add_custom_target(samples
        DEPENDS ${SAMPLE_LIST})