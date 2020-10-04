# =====================================================
# function name: 
#   @ begin_autoconfig
# Parameter:
#   @ N/A
# =====================================================
function(begin_autoconfig)
    # =====================================================
    # Begin Flag set to ON
    # =====================================================
    set(BEGIN_AUTO_CONFIG ON CACHE INTERNAL "begin gen autoconfig" FORCE)

    # =====================================================
    # Reset 'AUTO_CONFIG_LISTS'
    # =====================================================
    set(AUTO_CONFIG_LISTS "" CACHE INTERNAL "reset variable" FORCE)
endfunction()

# =====================================================
# function name: 
#   @ pushback_autoconfig
# Parameter:
#   @ definition_lists
# =====================================================
function(pushback_autoconfig definition_lists)
    # =====================================================
    # definition_lists push back to AUTO_CONFIG_LISTS
    # =====================================================
    set(AUTO_CONFIG_LISTS "${AUTO_CONFIG_LISTS};${definition_lists}" CACHE INTERNAL "pushback value" FORCE)
endfunction()

# =====================================================
# function name: 
#   @ end_autoconfig
# Parameter:
#   @ base_directory
# =====================================================
function(end_autoconfig base_directory)
    # =====================================================
    # Check Begin Flag
    # =====================================================
    if(${BEGIN_AUTO_CONFIG})
        # =====================================================
        # Begin Flag set to OFF
        # =====================================================
        set(BEGIN_AUTO_CONFIG OFF CACHE INTERNAL "end gen autoconfig" FORCE)

        # =====================================================
        # Check Invalidation of AUTO_CONFIG_LISTS 
        # =====================================================
        if(NOT "${AUTO_CONFIG_LISTS}" STREQUAL "${PREV_AUTO_CONFIG_LISTS}")
            # =====================================================
            # Get Current Date 
            # =====================================================
            string(TIMESTAMP AUTOCONFIG_GENERATED_DATE "%Y-%m-%d")

            # =====================================================
            # Read & Config Doxy Template
            # =====================================================
            file(READ "${CMAKE_HOME_DIRECTORY}/Tools/CMake/autoconfig/doxy/header.txt" HEADER_DOXY)
            string(REPLACE "[file-name]" "autoconfig.h" HEADER_DOXY ${HEADER_DOXY})
            string(REPLACE "[date]" "${AUTOCONFIG_GENERATED_DATE}" HEADER_DOXY ${HEADER_DOXY})

            # =====================================================
            # Write Modified Doxy Template
            # =====================================================
            file(WRITE  "${base_directory}/autoconfig.h" ${HEADER_DOXY})
            file(APPEND "${base_directory}/autoconfig.h" "#ifndef __AUTO_CONFIG_H__\n")
            file(APPEND "${base_directory}/autoconfig.h" "#define __AUTO_CONFIG_H__\n\n")

            # =====================================================
            # Write Definitions
            # =====================================================
            foreach(it ${AUTO_CONFIG_LISTS})
                # =====================================================
                # Replace Delimiter = to ;
                # =====================================================
                string(REGEX REPLACE "()=()" ";" item ${it})

                # =====================================================
                # Get Argument Length
                # =====================================================
                list(LENGTH item ARG_COUNT)
                if(${ARG_COUNT} MATCHES 1)
                    # =====================================================
                    # if Argument Count 1EA
                    # =====================================================
                    list(GET item 0 ARG_DEFINITION)

                    file(APPEND "${base_directory}/autoconfig.h" "#ifndef ${ARG_DEFINITION}\n")
                    file(APPEND "${base_directory}/autoconfig.h" "#define ${ARG_DEFINITION}\n")
                    file(APPEND "${base_directory}/autoconfig.h" "#endif /* ${ARG_DEFINITION} */\n\n")
                else()
                    # =====================================================
                    # if Argument Count 2EA
                    # =====================================================
                    list(GET item 0 ARG_DEFINITION)
                    list(GET item 1 ARG_VALUE)

                    file(APPEND "${base_directory}/autoconfig.h" "#ifndef ${ARG_DEFINITION}\n")
                    file(APPEND "${base_directory}/autoconfig.h" "#define ${ARG_DEFINITION} ${ARG_VALUE}\n")
                    file(APPEND "${base_directory}/autoconfig.h" "#endif /* ${ARG_DEFINITION} */\n\n")
                endif()
            endforeach()
            
            # =====================================================
            # Write End of file
            # =====================================================
            file(APPEND "${base_directory}/autoconfig.h" "#endif /* __AUTO_CONFIG_H__ */\n")
            
            # =====================================================
            # Upate 'PREV_AUTO_CONFIG_LISTS'
            # =====================================================
            set(PREV_AUTO_CONFIG_LISTS ${AUTO_CONFIG_LISTS} CACHE INTERNAL "Update Prev" FORCE)
        endif()
    endif()
endfunction()
