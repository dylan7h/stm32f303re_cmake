# ==========================================
# [ select compiler spec : -spec=<name> ]
# [x] linux.specs
# [O] nano.specs   - to use custom standard library
# [O] nosys.specs  - to use standard library
# [O] rdimon.specs - to use semihosting printf
# ==========================================
set(SPEC        nano.specs)
if(${SPEC} STREQUAL "nano.specs")
    # standard c library such as <stdio.h>, <stdlib.h> abs <string.h> ... 
    list(APPEND LINK_LIBRARY "c")
    # standard c math library such as <math.h>, <complex.h> and <fenv.h> ...
    list(APPEND LINK_LIBRARY "m")
    list(APPEND LINK_LIBRARY "nosys")
elseif(${SPEC} STREQUAL "nosys.specs")
    list(APPEND LINK_LIBRARY        "gcc")
    list(APPEND EXE_LINKER_FLAGS    "-nostartfiles")
    list(APPEND EXE_LINKER_FLAGS    "-nostdlib")
    list(APPEND EXE_LINKER_FLAGS    "-nodefaultlibs")
    list(APPEND EXE_LINKER_FLAGS    "-static")
elseif(${SPEC} STREQUAL "rdimon.specs")
    list(APPEND LINK_LIBRARY        "c")
    list(APPEND LINK_LIBRARY        "rdimon")
else()
    message(FATAL_ERROR "Specifications not supported")
endif()

# ==========================================
# [ Set Global Definitions : <compiler> -D<definitions> ]
# ==========================================
if(${CMAKE_BUILD_TYPE} MATCHES Debug OR ${CMAKE_BUILD_TYPE} MATCHES RelWithDebInfo)
    list(APPEND CMAKE_DEFINITIONS _DEBUG)
    list(APPEND CMAKE_DEFINITIONS DEBUG)
endif()

list(APPEND CMAKE_DEFINITIONS ${TARGET_BOARD}) 

# ==========================================
# [ Set Global ASM FLAGS ]
# ==========================================
list(APPEND ASM_FLAGS "-Wall")
list(APPEND ASM_FLAGS "-fdata-sections")
list(APPEND ASM_FLAGS "-ffunction-sections")

# ==========================================
# [ Set Global C FLAGS ]
# ==========================================
list(APPEND C_FLAGS "-Wall")
list(APPEND C_FLAGS "-fdata-sections")
list(APPEND C_FLAGS "-ffunction-sections")

# ==========================================
# [ Set Global CXX FLAGS ]
# ==========================================
list(APPEND CXX_FLAGS "-Wall")
list(APPEND CXX_FLAGS "-fdata-sections")
list(APPEND CXX_FLAGS "-ffunction-sections")

# ==========================================
# [ Set Global Linker FLAGS ]
# ==========================================
list(APPEND EXE_LINKER_FLAGS )
