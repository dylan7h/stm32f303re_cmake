# =====================================================
# function name: 
#   @ build_executable
# Parameter:
#   @ working_dir
#   @ target_name
#   @ include_paths
#   @ library_paths
#   @ linker_script
#   @ source_lists
#   @ library_lists
#   @ compile_definitions
#   @ compile_options
#   @ link_options
# =====================================================
function(build_executable working_dir target_name include_paths library_paths linker_script source_lists library_lists compile_definitions compile_options link_options)
    # ======================================
    # [ pushback 'autoconfig.h' generation ]
    # ======================================
    pushback_autoconfig("${compile_definitions}")    

    # =====================================================
    # Parsing Global Variable
    # =====================================================
    parameter_parser("${ASM_FLAGS}")
    parameter_parser("${C_FLAGS}")
    parameter_parser("${CXX_FLAGS}")
    parameter_parser("${EXE_LINKER_FLAGS}")

    # =====================================================
    # Parsing Function Parameter
    # =====================================================
    parameter_parser("${compile_definitions}")
    parameter_parser("${compile_options}")
    parameter_parser("${link_options}")

    # =====================================================
    # Executable Target Definition
    # =====================================================
    # Executable Target
    add_executable(${target_name} ${source_lists})
    # Override RUNTIME_OUTPUT_DIRECTORY
    set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${working_dir})
    # Add Clean Rule
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${working_dir})
    # Show Executable Size Information
    add_custom_command(TARGET ${target_name} POST_BUILD
        WORKING_DIRECTORY ${working_dir}
        COMMAND ${CMAKE_SIZE} ${target_name}${CMAKE_EXECUTABLE_SUFFIX}
    )

    # =====================================================
    # Option - Generate Map File
    # =====================================================
    if(${EXT_MAP})
        # --cref        : Generate Cross Reference Table into Map file
        # --gc-sections : Garbage Collection Unused Sections
        set(link_options -Wl,-Map=${working_dir}/${target_name}.map,--cref -Wl,--gc-sections ${link_options})
    else()
        set(link_options -Wl,--gc-sections ${link_options})
    endif()

    # =====================================================
    # Compile Definitions
    # =====================================================
    target_compile_definitions(${target_name} PRIVATE 
        $<$<COMPILE_LANGUAGE:C>:${CMAKE_DEFINITIONS} ${compile_definitions}>
        $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_DEFINITIONS} ${compile_definitions}>
    )

    # =====================================================
    # Compile Options
    # =====================================================    
    target_compile_options(${target_name} PRIVATE 
        $<$<COMPILE_LANGUAGE:ASM>:${ASM_FLAGS} ${compile_options}>
        $<$<COMPILE_LANGUAGE:C>:
            -mcpu=${CPU}
            -m${INSTRUCTION_SET}
            -mfpu=${FPU}
            -mfloat-abi=${FLOAT_ABI}
            -std=${STD_C_CXX}
            ${C_FLAGS}
            ${compile_options}
        >
        $<$<COMPILE_LANGUAGE:CXX>:
            -mcpu=${CPU}
            -m${INSTRUCTION_SET}
            -mfpu=${FPU}
            -mfloat-abi=${FLOAT_ABI}
            -std=${STD_C_CXX}
            ${CXX_FLAGS}
            ${compile_options}
        >
    )

    # =====================================================
    # Compile Include Path
    # =====================================================
    target_include_directories(${target_name} PRIVATE 
        $<$<COMPILE_LANGUAGE:C>:${include_paths}>
        $<$<COMPILE_LANGUAGE:CXX>:${include_paths}>
    )

    # =====================================================
    # Link Library Path
    # =====================================================
    target_link_directories(${target_name} PRIVATE ${library_paths})

    # =====================================================
    # Link Library
    # =====================================================
    target_link_libraries(${target_name} PRIVATE ${LINK_LIBRARY} ${library_lists})

    # =====================================================
    # Link Option
    # =====================================================
    target_link_options(${target_name} PRIVATE
        -mcpu=${CPU}
        -m${INSTRUCTION_SET}
        -mfpu=${FPU}
        -mfloat-abi=${FLOAT_ABI}
        -specs=${SPEC}
        -T ${linker_script}
        ${link_options}
        ${EXE_LINKER_FLAGS}
    )
endfunction()
