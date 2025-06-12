#include "../../WebCpp/include/webcpp.h"
#include <stdio.h> // For fprintf and printf

int main() {
    webcpp_config_t config = {
        .max_memory = 64 * 1024 * 1024, // 64MB, adjust as needed
        .enable_gpu = true,
        .enable_threading = true,
        .js_engine = "v8"
    };
    if (!webcpp_init(&config)) {
        fprintf(stderr, "Error: Failed to initialize WebCpp for Phone app.\n");
        return 1;
    }

    webcpp_context_t* ctx = webcpp_create_context();
    if (!ctx) {
        fprintf(stderr, "Error: Failed to create WebCpp context for Phone app.\n");
        webcpp_shutdown();
        return 1;
    }

    // Load the Phone.html file for the application's UI
    // This uses the function we previously added to webcpp.h and webcpp.c
    if (!webcpp_load_html_file(ctx, "Phone.html")) {
        fprintf(stderr, "Error: Phone app failed to load Phone.html\n");
        webcpp_destroy_context(ctx);
        webcpp_shutdown();
        return 1;
    }
    printf("Phone app: Phone.html loaded successfully.\n");

    // Main loop or event handling would go here
    // For now, the application will initialize, load HTML, print a success message, and then exit.

    webcpp_destroy_context(ctx);
    webcpp_shutdown();
    return 0;
}