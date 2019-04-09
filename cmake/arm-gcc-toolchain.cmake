# CMake toolchain file for arm-none-eabi-gcc
#
# Original source:         https://github.com/vpetrigo/arm-cmake-toolchains/blob/master/arm-gcc-toolchain.cmake
#                      and https://github.com/vpetrigo/arm-cmake-toolchains/blob/master/clang-arm-gcc-toolchain.cmake
# Some code was taken from https://github.com/nnarain/cmake-avr-template/blob/master/cmake/avr-gcc.toolchain.cmake

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(TOOLCHAIN_TARGET arm-none-eabi)

find_program(TOOLCHAIN_GCC ${TOOLCHAIN_TARGET}-gcc)
if(NOT TOOLCHAIN_GCC)
  message(FATAL_ERROR "${TOOLCHAIN_TARGET}-gcc could not be found")
endif()
get_filename_component(TOOLCHAIN_GCC "${TOOLCHAIN_GCC}" REALPATH)
get_filename_component(TOOLCHAIN_ROOT "${TOOLCHAIN_GCC}" DIRECTORY)

set(TOOL_PREFIX "${TOOLCHAIN_ROOT}/${TOOLCHAIN_TARGET}-")
set(CMAKE_C_COMPILER   "${TOOL_PREFIX}gcc"     CACHE PATH "gcc"     FORCE)
set(CMAKE_CXX_COMPILER "${TOOL_PREFIX}g++"     CACHE PATH "g++"     FORCE)
set(CMAKE_AR           "${TOOL_PREFIX}ar"      CACHE PATH "ar"      FORCE)
set(CMAKE_LINKER       "${TOOL_PREFIX}ld"      CACHE PATH "linker"  FORCE)
set(CMAKE_NM           "${TOOL_PREFIX}nm"      CACHE PATH "nm"      FORCE)
set(CMAKE_OBJCOPY      "${TOOL_PREFIX}objcopy" CACHE PATH "objcopy" FORCE)
set(CMAKE_OBJDUMP      "${TOOL_PREFIX}objdump" CACHE PATH "objdump" FORCE)
set(CMAKE_STRIP        "${TOOL_PREFIX}strip"   CACHE PATH "strip"   FORCE)
set(CMAKE_RANLIB       "${TOOL_PREFIX}ranlib"  CACHE PATH "ranlib"  FORCE)
set(CMAKE_SIZE         "${TOOL_PREFIX}size"    CACHE PATH "size"    FORCE)
unset(TOOL_PREFIX)

# without this option ARM GCC is unable to pass CMake's compilation test check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_SYSROOT "${TOOLCHAIN_ROOT}/../${TOOLCHAIN_TARGET}")
set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
