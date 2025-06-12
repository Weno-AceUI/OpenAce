#include "../../../WebCpp/include/webcpp.h" // Adjusted path
#include <stdio.h> // For fprintf and printf

int main() {
    webcpp_config_t config = {
        .max_memory = 64 * 1024 * 1024, // 64MB, adjust as needed
        .enable_gpu = true,
        .enable_threading = true,
        .js_engine = "v8"
    };
    if (!webcpp_init(&config)) {
        fprintf(stderr, "Error: Failed to initialize WebCpp for Lock Screen.\n");
        return 1;
    }

    webcpp_context_t* ctx = webcpp_create_context();
    if (!ctx) {
        fprintf(stderr, "Error: Failed to create WebCpp context for Lock Screen.\n");
        webcpp_shutdown();
        return 1;
    }

    // Load the lock_screen.html file for the UI
    if (!webcpp_load_html_file(ctx, "lock_screen.html")) {
        fprintf(stderr, "Error: Lock Screen failed to load lock_screen.html\n");
        webcpp_destroy_context(ctx);
        webcpp_shutdown();
        return 1;
    }
    printf("Lock Screen: lock_screen.html loaded successfully.\n");

    // Main loop or event handling for the lock screen would go here

    webcpp_destroy_context(ctx);
    webcpp_shutdown();
    return 0;
}