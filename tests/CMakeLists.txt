file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(src ${TEST_SRCS})
    get_filename_component(testName test_${src} NAME_WE)

    add_executable(${testName} ${src})

    target_link_libraries(${testName} engine GLEW)

    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

    set(TEST_LIST ${TEST_LIST} ${testName})
endforeach(src)

add_custom_target(check
        COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS ${TEST_LIST})