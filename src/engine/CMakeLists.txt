project(engine VERSION 0.1 LANGUAGES CXX)

set(EngineSource engine.cpp)

add_subdirectory(components)
add_subdirectory(rendering)
add_subdirectory(scene)
add_subdirectory(shaders)

add_library(engine SHARED
	${EngineSource}
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/shaders/formatted/)