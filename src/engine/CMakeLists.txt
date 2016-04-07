add_subdirectory(scene)
add_subdirectory(components)

add_library(Engine SHARED
	engine.cpp
)

target_link_libraries(Engine Scene)
target_link_libraries(Engine Components)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
