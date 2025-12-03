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
        ${PROJ_INCLUDE_DIR}
)

# ===== platform =====