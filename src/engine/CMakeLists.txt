add_subdirectory(scene)

add_library(Engine SHARED
	engine.cpp
)

target_link_libraries(Engine Scene)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
