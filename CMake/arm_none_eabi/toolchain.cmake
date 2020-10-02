# =========================================
# Set Target System Information
# =========================================
set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  ${CPU})

# =========================================
# Set Compiler
# =========================================
set(CMAKE_ASM_COMPILER      "${tools}/bin/arm-none-eabi-gcc")
set(CMAKE_C_COMPILER        "${tools}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER      "${tools}/bin/arm-none-eabi-g++")

# =========================================
# Set Archive
# =========================================
set(CMAKE_AR                "${tools}/bin/arm-none-eabi-ar")
set(CMAKE_C_COMPILER_AR     "${tools}/bin/arm-none-eabi-ar")
set(CMAKE_CXX_COMPILER_AR   "${tools}/bin/arm-none-eabi-ar")

# =========================================
# Set Linker
# =========================================
set(CMAKE_LINKER            "${tools}/bin/arm-none-eabi-ld")

# =========================================
# Set Objcopy
# =========================================
set(CMAKE_OBJCOPY           "${tools}/bin/arm-none-eabi-objcopy")

# =========================================
# Set Objdump
# =========================================
set(CMAKE_OBJDUMP           "${tools}/bin/arm-none-eabi-objdump")

# =========================================
# Set GDB
# =========================================
set(CMAKE_GDB               "${tools}/bin/arm-none-eabi-gdb")

# =========================================
# Set Toolchain Root Path & Program/Library/Include/Package Path
# =========================================
set(CMAKE_FIND_ROOT_PATH                "${tools}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE   ONLY)

# =========================================
# Set Reset Linker Option( For Reset Configuration )
# =========================================
# aprofile-validation-v2m.specs
# aprofile-validation.specs
# aprofile-ve-v2m.specs
# aprofile-ve.specs
# iq80310.specs
# linux.specs
# nano.specs
# nosys.specs
# pid.specs
# rdimon-v2m.specs
# rdimon.specs
# rdpmon.specs
# redboot.specs
set(CMAKE_EXE_LINKER_FLAGS_INIT     "-specs=nosys.specs")

# =========================================
# Set Build Option each type of build
# =========================================
set(CMAKE_C_FLAGS_RELEASE_INIT      "-O2")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT   "-O2 -DDEBUG -D_DEBUG")
set(CMAKE_C_FLAGS_DEBUG_INIT        "-g -DDEBUG -D_DEBUG")

# =========================================
# Set Execuatable File Extension
# =========================================
set(CMAKE_EXECUTABLE_SUFFIX         ".axf")
