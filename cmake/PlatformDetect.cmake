# PlatformDetect.cmake
# Unified platform / compiler / architecture detection
#
# This module:
#   - Sets PROJ_OS_* variables (Windows / Linux / macOS)
#   - Sets PROJ_COMPILER_* variables (MSVC / Clang / GCC / AppleClang)
#   - Sets PROJ_ARCH_* variables (x86_64 / x86 / arm64 / armv7)
#   - Sets PROJ_BUILD_TYPE for single-config generators
#   - Provides helper function: proj_print_platform_summary()
#
# Usage:
#   include(PlatformDetect)
#   proj_print_platform_summary()

include_guard(GLOBAL)

# ===== 1.OS Detection =====
set(PROJ_OS_WINDOWS     OFF)
set(PROJ_OS_LINUX       OFF)
set(PROJ_OS_MACOS       OFF)

if (WIN32)
    set(PROJ_OS_WINDOWS ON)
    set(PROJ_OS_NAME "Windows")
elseif (APPLE)
    set(PROJ_OS_MACOS ON)
    set(PROJ_OS_NAME "macOS")
elseif (LINUX)
    set(PROJ_OS_LINUX ON)
    set(PROJ_OS_NAME "Linux")
else()
    set(PROJ_OS_NAME "${CMAKE_SYSTEM_NAME}")
endif()

# ===== 2.Compiler detection =====
set(PROJ_COMPILER_MSVC              OFF)
set(PROJ_COMPILER_CLANG             OFF)
set(PROJ_COMPILER_APPLE_CLANG       OFF)
set(PROJ_COMPILER_GCC               OFF)

set(PROJ_COMPILER_ID "${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(PROJ_COMPILER_MSVC ON)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(PROJ_COMPILER_CLANG ON)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(PROJ_COMPILER_APPLE_CLANG ON)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJ_COMPILER_GCC ON)
endif()

# ===== 3. Architecture Detection =====
set(_PROJ_RAW_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
if (NOT _PROJ_RAW_ARCH)
    set(_PROJ_RAW_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
endif()

string(TOLOWER "${_PROJ_RAW_ARCH}" _PROJ_ARCH_LOWER)

set(PROJ_ARCH_X86_64        OFF)
set(PROJ_ARCH_X86           OFF)
set(PROJ_ARCH_ARM64         OFF)
set(PROJ_ARCH_ARMV7         OFF)

if (_PROJ_ARCH_LOWER MATCHES "^(x86_64|amd64)")
    set(PROJ_ARCH_X86_64 ON)
    set(PROJ_ARCH_NAME "x86_64")
elseif (_PROJ_ARCH_LOWER MATCHES "^(x86|i[3-6]86)$")
    set(PROJ_ARCH_X86 ON)
    set(PROJ_ARCH_NAME "x86")
elseif (_PROJ_ARCH_LOWER MATCHES "^(arm64|aarch64)$")
    set(PROJ_ARCH_ARM64 ON)
    set(PROJ_ARCH_NAME "arm64")
elseif (_PROJ_ARCH_LOWER MATCHES "^armv7")
    set(PROJ_ARCH_ARMV7 ON)
    set(PROJ_ARCH_NAME "armv7")
else()
    set(PROJ_ARCH_NAME "${_PROJ_RAW_ARCH}")
endif()

unset(_PROJ_RAW_ARCH)
unset(_PROJ_ARCH_LOWER)

# ===== 4. Build type detection =====
# For single-config generators (Ninja/Makefile) CMAKE_BUILD_TYPE is relevant.
# For multi-config (Visual Studio, Xcode) use CMAKE_CONFIGURATION_TYPES.
if (CMAKE_CONFIGURATION_TYPES)
    set(PROJ_BUILD_TYPE "")
else()
    if (NOT CMAKE_BUILD_TYPE)
        set(PROJ_BUILD_TYPE "Debug")
    else()
        set(PROJ_BUILD_TYPE "${CMAKE_BUILD_TYPE}")
    endif()
endif()

# ===== 5. Helper Function =====
function(proj_print_platform_summary)
    message(STATUS "=== Platform Summary ===")
    message(STATUS " OS: ${PROJ_OS_NAME}")
    message(STATUS " Compiler: ${PROJ_COMPILER_ID}")
    if (DEFINED PROJ_ARCH_NAME)
        message(STATUS " Arch: ${PROJ_ARCH_NAME}")
    endif()
    if (DEFINED PROJ_BUILD_TYPE AND PROJ_BUILD_TYPE)
        message(STATUS " BuildType: ${PROJ_BUILD_TYPE}")
    else()
        message(STATUS " BuildType: multi-config generator")
    endif()
endfunction()