# ======================================
# [ Specify minimum CMake version ]
# ======================================
cmake_minimum_required(VERSION 3.15)

# ======================================
# [ Include setting & config path ]
# ======================================
include("setting.cmake")
include("Tools/CMake/path.cmake")

# ======================================
# [ Project Definition ]
# ======================================
project(
    "stm32f303re"
    VERSION         1.0.0.0
    DESCRIPTION     "stm32f303re cmake project"
    HOMEPAGE_URL    "https://github.com/dylan7h"
    LANGUAGES       ASM C CXX
)

# ======================================
# [ Begin 'autoconfig.h' generation ]
# ======================================
begin_autoconfig()

# ======================================
# [ pushback 'autoconfig.h' generation ]
# ======================================
pushback_autoconfig("${CMAKE_DEFINITIONS}")

# ======================================
# [ Export Compile Commands ]
# ======================================
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

# ======================================
# [ Enable Make tool Message ]
# ======================================
set(CMAKE_VERBOSE_MAKEFILE  OFF)

# ======================================
# [ Reset Global Link Option ]
# >> Because "-specs=" option
# ======================================
set(CMAKE_EXE_LINKER_FLAGS  "")

# ======================================
# [ Include Configuration Information ]
#   - 01. working_dir
#   - 02. target_name
#   - 03. linker_script
#   - 04. include_path
#   - 05. library_path
#   - 06. source_lists
#   - 07. library_lists
#   - 08. compile_option
#   - 09. link_option
# ======================================
include("Src/config.cmake")

# =====================================================
# Build Executable(target.axf | target.elf)
# =====================================================
build_executable(
    "${working_dir}" "${target_name}" 
    "${include_path}" "${library_path}" 
    "${linker_script}" "${source_lists}" "${library_lists}" 
    "${compile_definitions}" "${compile_option}" "${link_option}"
)

# =====================================================
# Extract Assemble From Executable
# =====================================================
if(${EXT_ASM})
    extract_asm("${working_dir}" "${target_name}")
endif()

# =====================================================
# Extract Binary From Executable
# =====================================================
if(${EXT_BIN})
    extract_bin("${working_dir}" "${target_name}")
endif()

# =====================================================
# Extract HEX From Executable
# =====================================================
if(${EXT_HEX})
    extract_hex("${working_dir}" "${target_name}")
endif()

# ======================================
# [ End 'autoconfig.h' generation ]
# ======================================
end_autoconfig("${CMAKE_HOME_DIRECTORY}/Src/Include")
