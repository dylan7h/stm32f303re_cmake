# ======================================
# [ Set toolchain root path  ]
# ======================================
# tool chain path
# set(tools               "/usr")
# set(tools               "/usr/local/gcc-arm-none-eabi-9-2020-q2-update")
set(tools               "C:/Program Files (x86)/GNU Arm Embedded Toolchain/9 2020-q2-update")

# ======================================
# [ Select Compiler ]
# - arm_none_eabi
# - armcompiler4
# - armcompiler6
# - clang
# ======================================
set(COMPILER            "arm-none-eabi")
# set(COMPILER            "clang")
# set(GCC_TOOL_CHAIN      "/usr/local/gcc-arm-none-eabi-9-2020-q2-update")

# ======================================
# [ Select CPU ]
# - arm_none_eabi
# <compiler> -mcpu
# ======================================
set(CPU                 "cortex-m4")

# ======================================
# [ Select Instruction Set ]
# <compiler> -m[INSTRUCTION_SET]
# ======================================
set(INSTRUCTION_SET     "thumb")

# ======================================
# [ Select FPU ]
# <compiler> -mfpu
# ======================================
set(FPU                 "fpv4-sp-d16")

# ======================================
# [ Select Float ABI ]
# <compiler> -mfloat-abi
# ======================================
set(FLOAT_ABI           "hard")

# ======================================
# [ Select build type ]
# - Debug
# - RelWithDebInfo
# - Release
# ======================================
set(CMAKE_BUILD_TYPE    Debug)

# ======================================
# [ Select C/C++ Standard ]
# - C   : c80 / c99 /  c11
# - C++ : c++11 / c++14 / c++17
# ======================================
set(STD_C_CXX           c99)

# ======================================
# [ Select Target Board ]
# ======================================
set(TARGET_BOARD        "STM32F303xE")

# ======================================
# [ Enable HAL ]
# ======================================
set(ENABLE_HAL          OFF)

# ======================================
# [ Extract Map file ]
# ======================================
set(EXT_MAP             ON)

# ======================================
# [ Extract Assemble file ]
# ======================================
set(EXT_ASM             ON)

# ======================================
# [ Extract Binbary file ]
# ======================================
set(EXT_BIN             ON)

# ======================================
# [ Extract HEX file ]
# ======================================
set(EXT_HEX             ON)

# ======================================
# [ Parameter Check Macro ]
# ======================================
macro(parameter_parser param)
    if(param)
        string(REGEX REPLACE "\"|;" " " param    ${param})
    endif()
endmacro()