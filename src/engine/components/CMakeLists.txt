add_subdirectory(camera)
add_subdirectory(geometry)
add_subdirectory(light)
add_subdirectory(material)
add_subdirectory(renderer)
add_subdirectory(transform)

set(EngineSource ${EngineSource}
        ${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
        PARENT_SCOPE)
