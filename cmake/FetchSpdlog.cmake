# FetchSpdlog.cmake
include_guard(GLOBAL)
include(FetchContent)

function(proj_fetch_spdlog)
    if (TARGET spdlog::spdlog_header_only)
        return()
    endif()

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git 
        GIT_TAG     v1.14.1
    )

    FetchContent_MakeAvailable(spdlog)
endfunction()