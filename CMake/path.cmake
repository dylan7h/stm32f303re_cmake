# Toolchain Configuration
set(CMAKE_TOOLCHAIN_FILE                "${CMAKE_CURRENT_LIST_DIR}/${COMPILER}/toolchain.cmake")

# Override rules  each type of build
set(CMAKE_USER_MAKE_RULES_OVERRIDE      "${CMAKE_CURRENT_LIST_DIR}/${COMPILER}/rules_override.cmake")

# Build Option Configuration & Include Rule of Autoconfig.h 
include("${CMAKE_CURRENT_LIST_DIR}/${COMPILER}/options.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/autoconfig/autoconfig.cmake")

# Include Build Fuction
include("${CMAKE_CURRENT_LIST_DIR}/${COMPILER}/library.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/${COMPILER}/executable.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/${COMPILER}/extract.cmake")

# Set Build Ouput Path
set(BUILD_OUTPUT_DIR    "${CMAKE_SOURCE_DIR}/build/DebugRel")
