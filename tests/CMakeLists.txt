enable_testing()

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

#Run through each source
foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)

    add_executable(${testName} ${testSrc})

    target_link_libraries(${testName} Engine GLEW)

    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
            COMMAND ${CMAKE_BINARY_DIR}/bin/tests/${testName} )
endforeach(testSrc)