# =========================================
# link object files to an executable
# =========================================
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

# =========================================
# Set Reset Linker Option( For Reset Configuration )
# =========================================
set(CMAKE_EXE_LINKER_FLAGS_INIT             "-specs=nosys.specs")

# =========================================
# Set Build Option each type of build
# - Debug
# - RelWithDebInfo
# - Release
# =========================================
# Language ASM
set(CMAKE_ASM_FLAGS_DEBUG_INIT              "-x assembler-with-cpp")
set(CMAKE_ASM_FLAGS_RELWITHDEBINFO_INIT     "-x assembler-with-cpp")
set(CMAKE_ASM_FLAGS_RELEASE_INIT            "-x assembler-with-cpp")
# Language C
set(CMAKE_C_FLAGS_DEBUG_INIT                "-g -gdwarf-2")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT       "-O2 -g -gdwarf-2")
set(CMAKE_C_FLAGS_RELEASE_INIT              "-O2")
# Language C++
set(CMAKE_CXX_FLAGS_DEBUG_INIT              "-g -gdwarf-2")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT     "-O2 -g -gdwarf-2")
set(CMAKE_CXX_FLAGS_RELEASE_INIT            "-O2")

# =========================================
# Set Execuatable File Extension
# =========================================
set(CMAKE_EXECUTABLE_SUFFIX                 .axf)
