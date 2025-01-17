cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(game VERSION 1.0)

option(ENABLE_CLANG_TIDY "Enable clang-tidy for static analysis" OFF)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_PROGRAM clang-tidy)
    if(CLANG_TIDY_PROGRAM)
        message(STATUS "Using clang-tidy: ${CLANG_TIDY_PROGRAM}")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_PROGRAM};-header-filter=.*")
        set(USE_PCH OFF)
    else()
        message(WARNING "clang-tidy not found, ignoring ENABLE_CLANG_TIDY option.")
    endif()
else()
    set(USE_PCH ON)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(RAYLIB_PATH "C:/raylib")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin") # macOS
    set(RAYLIB_PATH "$ENV{RAYLIB_PATH}")
else()
    message(FATAL_ERROR "Add your raylib path: ${CMAKE_SYSTEM_NAME}")
endif()

set(LIB_PCH_PATH "${CMAKE_SOURCE_DIR}/library/common")
set(LIB_PCH_HEADER "${LIB_PCH_PATH}/LIB_PCH.hpp")
set(SOURCE_PATH "${CMAKE_SOURCE_DIR}/example")
set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/library")

include_directories(
    "${RAYLIB_PATH}"
    "${LIB_PCH_PATH}"
)

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_PATH}/*.cpp")

add_library(kodelib STATIC library/source/kodelib.cpp)
target_include_directories(kodelib PUBLIC "${LIBRARY_PATH}/include")
target_compile_options(kodelib PRIVATE -Werror -Wextra)

add_executable(game "${SOURCE_FILES}")
target_link_libraries(game PRIVATE kodelib)

set_target_properties(game PROPERTIES UNITY_BUILD ON)
set_target_properties(kodelib PROPERTIES UNITY_BUILD ON)

message(STATUS "Detected operating system: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Current build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -march=native -flto -fomit-frame-pointer -funroll-loops")

target_include_directories(game PRIVATE
    "${RAYLIB_PATH}/include"
    "${LIBRARY_PATH}/include"
)

target_compile_options(game PRIVATE -Werror -Wextra)

if (USE_PCH)
    target_precompile_headers(kodelib PRIVATE "${LIB_PCH_HEADER}")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(game PRIVATE
        "${RAYLIB_PATH}/libraylib.a"
        "-lopengl32"
        "-lgdi32"
        "-lwinmm"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin") # macOS
    target_link_libraries(game PRIVATE
        "${RAYLIB_PATH}/libraylib.a"
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
    )
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
