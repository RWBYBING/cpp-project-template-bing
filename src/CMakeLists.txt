# Responsibilities:
#   1. Define all primary library targets:
#   2. Setup include dir
#   3. Establish dependencies between these lib

set(PROJ_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJ_INCLUDE_DIR "${PROJ_SRC_DIR}/include")

# ===== infra =====
add_library(infra)

target_sources(infra
    PRIVATE 
        infra/logger.cpp
)

target_include_directories(infra
    PUBLIC 
        ${PROJ_INCLUDE_DIR}/infra
)

# spdlog
proj_fetch_spdlog()
target_link_libraries(infra 
    PUBLIC 
        spdlog::spdlog_header_only
)


# ===== platform =====
add_library(platform)

target_sources(platform
    PRIVATE 
        platform/temp.cpp
)

target_include_directories(platform
    PUBLIC 
        ${PROJ_INCLUDE_DIR}/platform
)

# ===== domain =====
add_library(domain)

target_sources(domain
    PRIVATE 
        domain/temp.cpp
)

target_include_directories(domain
    PUBLIC 
        ${PROJ_INCLUDE_DIR}/domain
)

target_link_libraries(domain
    PUBLIC 
        infra 
        platform
)

# ===== public api =====
add_library(api)

target_sources(api 
    PRIVATE 
        api/log.cpp
        api/test.cpp 
)

target_include_directories(api 
    PUBLIC 
        ${PROJ_INCLUDE_DIR}/api
)

target_link_libraries(api 
    PUBLIC 
        domain
        infra 
)

