add_subdirectory(nodes)

file(GLOB_RECURSE FILES *.vs *.fs)

separate_arguments(FILES)

foreach (file ${FILES})

    get_filename_component(name ${file} NAME_WE)
    get_filename_component(extension ${file} EXT)

    string(REGEX REPLACE "\\." "" ext_no_dot ${extension})


    set(outfile formatted/${name}_${ext_no_dot}.h)


    file(STRINGS ${file} lines)
    unset(source)
    foreach (line ${lines})
        set(source "${source}    \"${line}\\n\"\n")
    endforeach()

    string(TOUPPER ${name} name_caps)
    string(TOUPPER ${ext_no_dot} ext_no_dot_caps)
    file(
            WRITE ${outfile}
            "#include <GL/gl.h>\n"
            "static const GLchar *shader_source_${name}_${ext_no_dot}[] = {\n"
            "${source}"
            "};\n"
    )

    set(EngineSource ${EngineSource}
            ${CMAKE_CURRENT_SOURCE_DIR}/${outfile}
            PARENT_SCOPE)

endforeach()

set(EngineSource ${EngineSource}
        ${CMAKE_CURRENT_SOURCE_DIR}/shader-generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/type-dec.cpp
        PARENT_SCOPE)