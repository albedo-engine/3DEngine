project(engine VERSION 0.1 LANGUAGES CXX)

set(EngineSource engine.cpp)

add_subdirectory(components)
add_subdirectory(rendering)
add_subdirectory(data)
add_subdirectory(lib)
add_subdirectory(scene)

add_library(engine SHARED ${EngineSource})

target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR}/include/shaders/formatted/)
