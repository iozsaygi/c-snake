cmake_minimum_required(VERSION 3.30)
project(CSnake C)

set(CMAKE_C_STANDARD 11)

# Set output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# Prevent in-source builds.
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed, please create a separate 'build' directory to trigger CMake build.")
endif ()

# Download and extract SDL3.
if (WIN32)
    message(STATUS "Executing Windows specific build operations.")

    include(FetchContent)

    set(SDL3_DIR "${CMAKE_SOURCE_DIR}/dependencies/SDL")

    set(SDL_DOWNLOAD_URL "https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-devel-3.2.4-mingw.zip")
    set(SDL_EXTRACTION_DIRECTORY "${SDL3_DIR}")

    message(STATUS "Downloading and extracting SDL3...")
    FetchContent_Declare(SDL URL ${SDL_DOWNLOAD_URL} SOURCE_DIR ${SDL_EXTRACTION_DIRECTORY} DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(SDL)

    find_package(SDL3 REQUIRED PATHS ${SDL3_DIR}/cmake NO_DEFAULT_PATH)
elseif (APPLE)
    message(STATUS "Executing macOS specific build operations.")
    include(FetchContent)
    set(SDL_TARGET_REVISION 877399b2b2cf21e67554ed9046410f268ce1d1b2)
    FetchContent_Declare(SDL GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG ${SDL_TARGET_REVISION} GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(SDL)
endif ()

# Ensure SDL3 is available.
if (NOT SDL3_FOUND AND NOT APPLE)
    message(FATAL_ERROR "Couldn't find SDL3!")
endif ()

# Create the executable.
add_executable(${PROJECT_NAME} src/main.c src/renderer.c src/game.c)

# Include self header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

if (WIN32)
    message(STATUS "Binding dependencies for Windows.")

    # Add SDL3 include directories.
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS})

    # Link SDL3 library to executable.
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES})
elseif (APPLE)
    message(STATUS "Binding dependencies for macOS.")

    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
endif ()