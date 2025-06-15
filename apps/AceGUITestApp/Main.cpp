#include "../../WebCpp/include/webcpp.h"
#include <stdio.h>

int main() {
    webcpp_config_t config = {
        .max_memory = 128 * 1024 * 1024,
        .enable_gpu = true,
        .enable_threading = true,
        .js_engine = "v8"
    };

    if (!webcpp_init(&config)) {
        fprintf(stderr, "AceGUITestApp: Failed to initialize WebCpp.\n");
        return 1;
    }

    webcpp_context_t* ctx = webcpp_create_context();
    if (!ctx) {
        fprintf(stderr, "AceGUITestApp: Failed to create WebCpp context.\n");
        webcpp_shutdown();
        return 1;
    }

    // Load the AceGUITestApp.html file
    if (!webcpp_load_html_file(ctx, "AceGUITestApp.html")) {
        fprintf(stderr, "AceGUITestApp: Failed to load AceGUITestApp.html\n");
        webcpp_destroy_context(ctx);
        webcpp_shutdown();
        return 1;
    }
    printf("AceGUITestApp: AceGUITestApp.html loaded successfully.\n");

    // For a test app, we might not need to register any specific C++ functions.
    // The app primarily tests the JS framework.
    // The main process would typically enter an event loop here or wait for shutdown.

    // webcpp_destroy_context(ctx); // In a real app, context is destroyed on app close
    // webcpp_shutdown();          // Shutdown is typically system-wide
    return 0; // For now, let it exit after loading. A real app would loop.
}