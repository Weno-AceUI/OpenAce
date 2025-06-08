cmake_minimum_required(VERSION 4.0)
project(OpenAce)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Set up cross-compilation
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_C_COMPILER x86_64-elf-gcc)
set(CMAKE_CXX_COMPILER x86_64-elf-g++)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -fPIE -m64 -march=x86-64 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -fPIE -m64 -march=x86-64 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -z nodefaultlib -z noexecstack -no-pie -T ${CMAKE_SOURCE_DIR}/kernel/boot/linker.ld")

# Include directories
include_directories(
    kernel/include
    kernel/core
    kernel/drivers
    kernel/services
    kernel/boot
    kernel/arch
    kernel/syscalls
)

# Source files
set(KERNEL_SOURCES
    kernel/core/init.c
    kernel/core/memory.c
    kernel/core/process.c
    kernel/core/device.c
    kernel/core/config.c
    kernel/core/power.c
    kernel/core/time.c
    kernel/core/devicetree.c
    kernel/core/ipc.c
    kernel/core/security.c
    kernel/core/log.c
    kernel/core/net.c
    kernel/core/fs.c
    kernel/core/scheduler.c
    kernel/drivers/driver.c
    kernel/services/devmgr.c
    kernel/boot/boot.s
    kernel/arch/x86_64/arch.c
    kernel/syscalls/syscalls.c
)

# Build kernel
add_executable(kernel.bin ${KERNEL_SOURCES})

# Build initrd
add_custom_command(
    OUTPUT initrd.img
    COMMAND ${CMAKE_SOURCE_DIR}/tools/mkinitrd.sh
    DEPENDS kernel.bin
)

# Build WebCpp app
add_executable(WebCppApp base/frameworks/WebCpp/WebCppApp.cpp)

target_link_libraries(WebCppApp
    /Users/dylando/libs/ultralight/libUltralightCore.a
    /Users/dylando/libs/ultralight/libUltralight.a
)

# Copy files to build directory
add_custom_command(
    TARGET kernel.bin
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/kernel.bin
        ${CMAKE_BINARY_DIR}/initrd.img
        ${CMAKE_BINARY_DIR}/
)

add_subdirectory(tests)