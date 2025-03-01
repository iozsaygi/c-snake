cmake_minimum_required(VERSION 3.30)
project(CSnake C)

set(CMAKE_C_STANDARD 11)

# Set output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# Do not allow in-source builds.
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed, please create a separate 'build' directory to trigger CMake build.")
endif ()

# Download and extract SDL library.
if (WIN32)
    message(STATUS "Executing Windows specific build operations.")

    include(FetchContent)

    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/dependencies/SDL/cmake")

    # Set the download URL for SDL library.
    set(SDL_DOWNLOAD_URL "https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-devel-3.2.4-mingw.zip")

    # Set the extract directory for downloaded SDL library.
    set(SDL_EXTRACTION_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/SDL")

    # Download and extract SDL library.
    message(STATUS "Trying to download and extract SDL library.")
    include(FetchContent)
    FetchContent_Declare(SDL URL ${SDL_DOWNLOAD_URL} SOURCE_DIR ${SDL_EXTRACTION_DIRECTORY} DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(SDL)

    find_package(SDL2 REQUIRED)
endif ()

# Specific to 'MinGW', enable all warnings and treat them as errors.
# This is totally optional.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND MINGW)
    message(STATUS "Executing 'MinGW' specific operations.")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(${PROJECT_NAME} main.c)
