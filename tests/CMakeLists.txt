cmake_minimum_required(VERSION 3.10)
project(OpenAceTests)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/kernel
    ${CMAKE_SOURCE_DIR}/kernel/services
    ${CMAKE_SOURCE_DIR}/kernel/drivers
)

# Add test executable
add_executable(test_devmgr
    unit/test_devmgr.c
    unit/test_framework.h
    ${CMAKE_SOURCE_DIR}/kernel/services/devmgr.c
    ${CMAKE_SOURCE_DIR}/kernel/drivers/driver.c
    ${CMAKE_SOURCE_DIR}/kernel/core/memory.c
)

# Link against required libraries
target_link_libraries(test_devmgr
    # Add any required libraries here
)

# Add test to CTest
add_test(NAME test_devmgr COMMAND test_devmgr) 