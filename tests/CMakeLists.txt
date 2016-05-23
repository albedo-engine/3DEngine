add_executable(tests tests.cpp)
target_link_libraries(tests engine GLEW)
set_target_properties(tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

add_custom_target(check
        COMMAND ${CMAKE_BINARY_DIR}/bin/tests/tests
        DEPENDS tests)
