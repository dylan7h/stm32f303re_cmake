# =====================================================
# function name: 
#   @ extract_hex
# Parameter:
#   @ working_dir
#   @ target_name
# =====================================================
function(extract_hex working_dir target_name)
    # Extract HEX File from Execuable
    add_custom_command(TARGET ${target_name} POST_BUILD
        WORKING_DIRECTORY ${working_dir}
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${target_name}${CMAKE_EXECUTABLE_SUFFIX} ${CMAKE_PROJECT_NAME}.hex
    )
endfunction()

# =====================================================
# function name: 
#   @ extract_asm
# Parameter:
#   @ working_dir
#   @ target_name
# =====================================================
function(extract_asm working_dir target_name)
    # Extract Assemble File from Execuable
    add_custom_command(TARGET ${target_name} POST_BUILD
        WORKING_DIRECTORY ${working_dir}
        COMMAND ${CMAKE_OBJDUMP} -S --disassemble ${target_name}${CMAKE_EXECUTABLE_SUFFIX} > ${target_name}.asm
    )
endfunction()

# =====================================================
# function name: 
#   @ extract_bin
# Parameter:
#   @ working_dir
#   @ target_name
# =====================================================
function(extract_bin working_dir target_name)
    # Extract Binary File from Execuable
    add_custom_command(TARGET ${target_name} POST_BUILD
        WORKING_DIRECTORY ${working_dir}
        COMMAND ${CMAKE_OBJCOPY} -O binary -S ${target_name}${CMAKE_EXECUTABLE_SUFFIX} ${CMAKE_PROJECT_NAME}.bin
    )
endfunction()
