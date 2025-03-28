function(copy_resources PATH)
    file (GLOB_RECURSE resources ${PATH}/*.*)
    foreach(resource ${resources})
        get_filename_component(filename ${resource} NAME)
        get_filename_component(dir_with_prefix ${resource} DIRECTORY)
        get_filename_component(dirname ${dir_with_prefix} NAME)
        string(REGEX REPLACE "^${PATH}" "" dir ${dir_with_prefix})

        set (output "")

        while(NOT ${dirname} STREQUAL resources)
            get_filename_component(path_component "${dir}" NAME)
            set (output "${path_component}/${output}")
            get_filename_component(dir "${dir}" DIRECTORY)
            get_filename_component(dirname "${dir}" NAME)
        endwhile()

        set(output "${CMAKE_CURRENT_BINARY_DIR}/resources/${output}/${filename}")

        add_custom_command(
                COMMENT Moving updated resource-file '${filename}'
                OUTPUT ${output}
                DEPENDS ${resource}
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${resource}
                ${output}
        )
        add_custom_target(${filename} ALL DEPENDS ${resource} ${output})

    endforeach()
endfunction()
