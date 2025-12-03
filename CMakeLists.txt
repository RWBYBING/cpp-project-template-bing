# Responsibilities:
#   1. Set CMake minimum version
#   2. Define the project and global language / standard
#   3. Define the global options
#   4. Setup CMake Module Path
#   5. Add subdirectories

cmake_minimum_required(VERSION 3.18)

project(cptb
    VERSION 0.1.0
    LANGUAGES C CXX
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ===== C++ Standard =====
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===== Options =====
option(PROJ_BUILD_APPS "Build application targets in apps/" ON)
option(PROJ_BUILD_TESTS "Build test cases in tests/" OFF)
option(PROJ_BUILD_EXAMPLES "Build examples in examples/" OFF)
option(PROJ_ENABLE_WARNINGS "Enable recommended compiler warnings" ON)

# ===== CMake modules =====
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (PROJ_ENABLE_WARNINGS)
    include(ConfigWarnings OPTIONAL)
endif()

# ===== Print Info =====
include(PlatformDetect)
proj_print_platform_summary()

# ===== Subdirectories =====
add_subdirectory(src)

if (PROJ_BUILD_APPS)
    add_subdirectory(apps)
endif()

if (PROJ_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (PROJ_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()




