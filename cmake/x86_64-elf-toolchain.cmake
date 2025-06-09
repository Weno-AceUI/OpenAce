set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the cross compilers
set(CMAKE_C_COMPILER x86_64-elf-gcc)
set(CMAKE_CXX_COMPILER x86_64-elf-g++)

# Set compiler flags
set(CMAKE_C_FLAGS "-nostdlib -nostartfiles -ffreestanding -mno-red-zone -mcmodel=kernel")
set(CMAKE_CXX_FLAGS "-nostdlib -nostartfiles -ffreestanding -mno-red-zone -mcmodel=kernel")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles -ffreestanding")

# Disable compiler checks
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set the root path
set(CMAKE_FIND_ROOT_PATH /opt/local/x86_64-elf)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY) 