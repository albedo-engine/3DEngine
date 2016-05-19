project(engine VERSION 0.1 LANGUAGES CXX)

set(EngineSource engine.cpp)

add_subdirectory(scene)
add_subdirectory(components)
add_subdirectory(components/geometry)

add_library(Engine SHARED
	${EngineSource}
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
