cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE cmake/arm-gcc-toolchain.cmake)
project(AlitaElectricSkates)
enable_language(ASM)

set(StdPeriph_PATH "${CMAKE_SOURCE_DIR}/libs/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0" CACHE PATH "path to the Standard Peripheral Library" FORCE)

function(add_flags FLAGS_VAR)
  string(JOIN " " JOINED_FLAGS ${ARGN})
  set("${FLAGS_VAR}" "${${FLAGS_VAR}} ${JOINED_FLAGS}" PARENT_SCOPE)
endfunction()

# CPU-specific compiler flags
set(CPU_COMPILER_FLAGS
  -mcpu=cortex-m4 -mlittle-endian -mthumb -mthumb-interwork
  -mfloat-abi=hard -mfpu=fpv4-sp-d16
  --specs=nosys.specs
)
add_flags(CMAKE_C_FLAGS ${CPU_COMPILER_FLAGS})
add_flags(CMAKE_CXX_FLAGS ${CPU_COMPILER_FLAGS})
add_flags(CMAKE_ASM_FLAGS ${CPU_COMPILER_FLAGS})
# add linker script for the target MCU
# In the nutshell, linker scripts control where (in the physical memory):
# 1. RAM, stack and flash memory begin
# 2. different sections (code, data etc) of the compiled program should be located
add_flags(CMAKE_EXE_LINKER_FLAGS "-T${StdPeriph_PATH}/Project/STM32F4xx_StdPeriph_Templates/TrueSTUDIO/STM32F40_41xxx/STM32F417IG_FLASH.ld")

# ARM GCC can generate only .elf executables...
set(ELF_EXE ${CMAKE_PROJECT_NAME}.elf)
# ...but they need to be converted into .hex files to be flashed on the MCU
set(HEX_EXE ${CMAKE_PROJECT_NAME}.hex)

set(PROJECT_SOURCE_FILES main.c Clock.c Timer.c LED.c Button.c ErrorProvider.c Indep_WD.c ModuleUnitTests.c)
list(TRANSFORM PROJECT_SOURCE_FILES PREPEND "src/")

set(StdPeriph_Driver_MODULES gpio rcc flash syscfg tim iwdg)
list(TRANSFORM StdPeriph_Driver_MODULES PREPEND "${StdPeriph_PATH}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_")
list(TRANSFORM StdPeriph_Driver_MODULES APPEND ".c")

add_executable(${ELF_EXE}
  ${PROJECT_SOURCE_FILES}
  ${StdPeriph_Driver_MODULES}

  "${StdPeriph_PATH}/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c"
  # system clock configuration
  "${StdPeriph_PATH}/Project/STM32F4xx_StdPeriph_Templates/system_stm32f4xx.c"
  # actual entry point of the program, executed when the controller is reset or started
  "${StdPeriph_PATH}/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f40_41xxx.s"
)

target_include_directories(${ELF_EXE} PUBLIC
  "src"
  "${StdPeriph_PATH}/Libraries/CMSIS/Include"
  "${StdPeriph_PATH}/Libraries/CMSIS/Device/ST/STM32F4xx/Include"
  "${StdPeriph_PATH}/Libraries/STM32F4xx_StdPeriph_Driver/inc"
  "${StdPeriph_PATH}/Project/STM32F4xx_StdPeriph_Templates"
)

target_compile_options(${ELF_EXE} PRIVATE -Wall)
target_compile_definitions(${ELF_EXE} PUBLIC
  # enables peripheral drivers, an abstraction layer over actual hardware and
  # peripheral registers (which is basically most of the SPL)
  USE_STDPERIPH_DRIVER
  # family of the target MCU
  STM32F40_41xxx
)

add_custom_command(TARGET ${ELF_EXE} POST_BUILD
  COMMAND "${CMAKE_OBJCOPY}" ARGS -O ihex ${ELF_EXE} ${HEX_EXE}
)

add_custom_target(flash
  COMMAND st-flash --format ihex write ${HEX_EXE}
  DEPENDS ${ELF_EXE}
)
