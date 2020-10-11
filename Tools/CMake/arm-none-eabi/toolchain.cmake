if(WIN32)
    set(FILE_EXT ".exe")
endif()

# =========================================
# Set Target System Information
# =========================================
set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  ${CPU})

# =========================================
# Set Compiler
# =========================================
set(CMAKE_ASM_COMPILER      "${tools}/bin/arm-none-eabi-gcc${FILE_EXT}")
set(CMAKE_C_COMPILER        "${tools}/bin/arm-none-eabi-gcc${FILE_EXT}")
set(CMAKE_CXX_COMPILER      "${tools}/bin/arm-none-eabi-g++${FILE_EXT}")

# =========================================
# Set Archive
# =========================================
set(CMAKE_AR                "${tools}/bin/arm-none-eabi-ar${FILE_EXT}")
set(CMAKE_C_COMPILER_AR     "${tools}/bin/arm-none-eabi-ar${FILE_EXT}")
set(CMAKE_CXX_COMPILER_AR   "${tools}/bin/arm-none-eabi-ar${FILE_EXT}")

# =========================================
# Set Linker
# =========================================
set(CMAKE_LINKER            "${tools}/bin/arm-none-eabi-gcc${FILE_EXT}")

# =========================================
# Set Objcopy
# =========================================
set(CMAKE_OBJCOPY           "${tools}/bin/arm-none-eabi-objcopy${FILE_EXT}")

# =========================================
# Set Objdump
# =========================================
set(CMAKE_OBJDUMP           "${tools}/bin/arm-none-eabi-objdump${FILE_EXT}")

# =========================================
# Set Objdump
# =========================================
set(CMAKE_SIZE              "${tools}/bin/arm-none-eabi-size${FILE_EXT}")

# =========================================
# Set GDB
# =========================================
set(CMAKE_GDB               "${tools}/bin/arm-none-eabi-gdb${FILE_EXT}")

# =========================================
# Set Toolchain Root Path & Program/Library/Include/Package Path
# =========================================
set(CMAKE_FIND_ROOT_PATH                "${tools}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE   ONLY)
