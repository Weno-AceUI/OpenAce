#include "../../../WebCpp/include/webcpp.h" // Adjusted path
#include <stdio.h> // For fprintf and printf

int main() {
    webcpp_config_t config = {
        .max_memory = 128 * 1024 * 1024, // 128MB, adjust as needed for home screen
        .enable_gpu = true,
        .enable_threading = true,
        .js_engine = "v8"
    };
    if (!webcpp_init(&config)) {
        fprintf(stderr, "Error: Failed to initialize WebCpp for Home Screen.\n");
        return 1;
    }

    webcpp_context_t* ctx = webcpp_create_context();
    if (!ctx) {
        fprintf(stderr, "Error: Failed to create WebCpp context for Home Screen.\n");
        webcpp_shutdown();
        return 1;
    }

    // Load the home_screen.html file for the UI
    if (!webcpp_load_html_file(ctx, "home_screen.html")) {
        fprintf(stderr, "Error: Home Screen failed to load home_screen.html\n");
        webcpp_destroy_context(ctx);
        webcpp_shutdown();
        return 1;
    }
    printf("Home Screen: home_screen.html loaded successfully.\n");

    // Main loop or event handling for the home screen would go here

    webcpp_destroy_context(ctx);
    webcpp_shutdown();
    return 0;
}