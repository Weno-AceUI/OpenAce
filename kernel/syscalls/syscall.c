#include "syscall.h"
#include "drivers/console.h" // Hypothetical console driver

uint64_t syscall_handler(uint64_t syscall_number, uint64_t arg1, uint64_t arg2, uint64_t arg3) {
    switch (syscall_number) {
        case SYSCALL_WRITE:
            console_write((const char *)arg1, (size_t)arg2);
            return 0;
        case SYSCALL_EXIT:
            // In real kernel: clean up and terminate the process
            return 0;
        default:
            return (uint64_t)-1; // Invalid syscall
    }
}
