# =====================================================
# function name: 
#   @ build_library
# Parameter:
#   @ working_dir
#   @ target_name
#   @ include_paths
#   @ source_lists
#   @ compile_definitions
#   @ compile_options
# =====================================================
function(build_library working_dir target_name include_paths source_lists compile_definitions compile_options)
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

    # =====================================================
    # Parsing Function Parameter
    # =====================================================
    parameter_parser("${compile_definitions}")
    parameter_parser("${compile_options}")

    # =====================================================
    # library Target Definition
    # =====================================================
    # library Target
    add_library(${target_name} ${source_lists})
    # Override ARCHIVE/LIBRARY_OUTPUT_DIRECTORY
    set_target_properties(${target_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${working_dir})
    set_target_properties(${target_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${working_dir})
    # Add Clean Rule
    set_target_properties(${target_name} PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${working_dir})

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
endfunction()
