add_subdirectory(visitor)

set(EngineSource ${EngineSource}
        ${CMAKE_CURRENT_SOURCE_DIR}/node.cpp
        PARENT_SCOPE)
