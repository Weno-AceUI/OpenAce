cmake_minimum_required(VERSION 3.20)
project(OpenAce)

add_subdirectory(WebCpp) # Build the WebCpp library

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Enable cross-compilation for kernel
option(BUILD_KERNEL "Build the kernel" OFF)
if(BUILD_KERNEL)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/x86_64-elf-toolchain.cmake)
    add_subdirectory(kernel)
endif()

# Native compilation for user-space applications
option(BUILD_APPS "Build user-space applications" ON)
if(BUILD_APPS)
    # Ensure we're using native compiler for apps
    if(CMAKE_CROSSCOMPILING)
        message(FATAL_ERROR "Cross-compilation detected but BUILD_APPS is ON. Please set BUILD_KERNEL=OFF for native compilation.")
    endif()
    
    # Set C++ standard for all targets
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
    add_subdirectory(ui)
    add_subdirectory(base)
endif()

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Add tests directory
add_subdirectory(tests)