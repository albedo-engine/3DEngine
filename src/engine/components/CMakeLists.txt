add_subdirectory(camera)
add_subdirectory(geometry)
add_subdirectory(transform)
add_subdirectory(material)
add_subdirectory(renderer)

set(EngineSource ${EngineSource}
        ${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/component-factory.cpp
        PARENT_SCOPE)
