# ======================================
# [ Set toolchain root path  ]
# ======================================
set(tools               "/usr/local/gcc-arm-none-eabi-9-2020-q2-update")

# ======================================
# [ Select Compiler ]
# - arm_none_eabi
# - armcompiler4
# - armcompiler6
# - clang
# ======================================
set(COMPILER            "arm_none_eabi")

# ======================================
# [ Select Architecure ]
# - arm_none_eabi
# <compiler> -mcpu
# ======================================
set(CPU                 "cortex-m4")

# ======================================
# [ Select CPU ]
# - arm_none_eabi
# <compiler> -mcpu
# ======================================
set(CPU                 "cortex-m4")

# ======================================
# [ Select FPU ]
# <compiler> -mfpu
# ======================================
set(FPU                 "fpv4-sp-d16")

# ======================================
# [ Select build type ]
# - Debug
# - RelWithDebInfo
# - Release
# ======================================
set(CMAKE_BUILD_TYPE    Debug)

# ======================================
# [ Select Target Board ]
# ======================================
set(TARGET_BOARD        "STM32F303xE")

# ======================================
# [ Enable CMSIS ]
# ======================================
set(ENABLE_CMSIS        ON)

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
