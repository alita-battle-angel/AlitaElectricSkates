cmake_minimum_required(VERSION 3.13)
# convert relative paths to absolute when using target_sources
cmake_policy(SET CMP0076 NEW)

set(CMAKE_TOOLCHAIN_FILE cmake/arm-gcc-toolchain.cmake)
project(AlitaElectricSkates)
enable_language(ASM)

set(StdPeriph_PATH "${CMAKE_SOURCE_DIR}/libs/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0" CACHE PATH "path to the Standard Peripheral Library" FORCE)

function(add_flags FLAGS_VAR)
  string(JOIN " " JOINED_FLAGS ${ARGN})
  set("${FLAGS_VAR}" "${${FLAGS_VAR}} ${JOINED_FLAGS}" PARENT_SCOPE)
endfunction()

set(COMPILER_FLAGS
  # CPU-specific
  -mcpu=cortex-m4 -mlittle-endian -mthumb -mthumb-interwork
  -mfloat-abi=hard -mfpu=fpv4-sp-d16
  --specs=nosys.specs
)
add_flags(CMAKE_C_FLAGS ${COMPILER_FLAGS})
add_flags(CMAKE_CXX_FLAGS ${COMPILER_FLAGS})
add_flags(CMAKE_ASM_FLAGS ${COMPILER_FLAGS})
# add linker script for the target MCU
# In the nutshell, linker scripts control where (in the physical memory):
# 1. RAM, stack and flash memory begin
# 2. different sections (code, data etc) of the compiled program should be located
add_flags(CMAKE_EXE_LINKER_FLAGS "-T${StdPeriph_PATH}/Project/STM32F4xx_StdPeriph_Templates/TrueSTUDIO/STM32F40_41xxx/STM32F417IG_FLASH.ld")

set(MAIN_EXE ${CMAKE_PROJECT_NAME}.elf)

set(StdPeriph_Driver_MODULES gpio rcc flash syscfg tim iwdg adc)
list(TRANSFORM StdPeriph_Driver_MODULES PREPEND "${StdPeriph_PATH}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_")
list(TRANSFORM StdPeriph_Driver_MODULES APPEND ".c")

add_executable(${MAIN_EXE}
  # actual entry point of the program, executed when the controller is reset or started
  "${StdPeriph_PATH}/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f40_41xxx.s"
  ${StdPeriph_Driver_MODULES}
  "${StdPeriph_PATH}/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c"
  # system clock configuration
  "${StdPeriph_PATH}/Project/STM32F4xx_StdPeriph_Templates/system_stm32f4xx.c"
)
add_subdirectory(src)

target_include_directories(${MAIN_EXE} PUBLIC
  "src"
  "${StdPeriph_PATH}/Libraries/CMSIS/Include"
  "${StdPeriph_PATH}/Libraries/CMSIS/Device/ST/STM32F4xx/Include"
  "${StdPeriph_PATH}/Libraries/STM32F4xx_StdPeriph_Driver/inc"
  "${StdPeriph_PATH}/Project/STM32F4xx_StdPeriph_Templates"
)

target_compile_options(${MAIN_EXE} PRIVATE -Wall)
target_compile_definitions(${MAIN_EXE} PUBLIC
  # enables peripheral drivers, an abstraction layer over actual hardware and
  # peripheral registers (which is basically most of the SPL)
  USE_STDPERIPH_DRIVER
  # family of the target MCU
  STM32F40_41xxx
)

add_custom_target(flash
  COMMAND openocd -f "${CMAKE_SOURCE_DIR}/openocd.cfg" -c "program ${MAIN_EXE} verify reset exit"
  DEPENDS ${MAIN_EXE}
)

add_custom_target(monitor
  COMMAND openocd -f "${CMAKE_SOURCE_DIR}/openocd.cfg" -c "tpiu config internal /dev/stdout uart off 168000000" | itmdump
  DEPENDS ${MAIN_EXE}
)
