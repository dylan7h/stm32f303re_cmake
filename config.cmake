# ======================================
# [ Configuration Information ]
#   - 01. working_dir
#   - 02. target_name
#   - 03. linker_script
#   - 04. include_path
#   - 05. library_path
#   - 06. source_lists
#   - 07. library_lists
#   - 08. compile_definitions
#   - 08. compile_option
#   - 09. link_option
# ======================================

# ======================================
#   - 01. working_dir
# ======================================
set(working_dir         "${BUILD_OUTPUT_DIR}")

# ======================================
#   - 02. target_name
# ======================================
set(target_name         "${CMAKE_PROJECT_NAME}")

# ======================================
#   - 03. linker_script
# ======================================
set(linker_script       "${CMAKE_SOURCE_DIR}/startup/GNU/STM32F303RETx_FLASH.ld")

# ======================================
#   - 04. include_path
# ======================================
list(APPEND include_path "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F3xx/Include")
list(APPEND include_path "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Core/Include")

# ======================================
#   - 05. library_path
# ======================================
list(APPEND library_path "")

# ======================================
#   - 06. source_lists
# ======================================
# GNU Style startup
list(APPEND source_lists "startup/GNU/startup_stm32f303xe.s")
# stm32 startup
list(APPEND source_lists "startup/system_stm32f3xx.c")
# Source
list(APPEND source_lists "Source/main.c")

# ======================================
#   - 07. library_lists
# ======================================
list(APPEND library_lists "")

# ======================================
#   - 08. compile_definitions
# ======================================
if(${ENABLE_HAL})
    list(APPEND compile_definitions "USE_HAL_DRIVER")
endif()

list(APPEND compile_definitions "SIGNATURE=\"Hello World!\"")
list(APPEND compile_definitions "AUTO_CONFIG_VER=6.672")
list(APPEND compile_definitions "CHEAT=\"Show Me The Money!\"")

# ======================================
#   - 09. compile_option
# ======================================
list(APPEND compile_option "")

# ======================================
#   - 10. link_option
# ======================================
list(APPEND link_option "")
