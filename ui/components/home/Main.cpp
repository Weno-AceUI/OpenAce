#include "../../../WebCpp/include/webcpp.h" // Adjusted path
#include <stdio.h> // For fprintf and printf

// C++ function to be called from JavaScript to "launch" an application
// In a real OS, this would interact with a process manager or window manager.
bool launch_application_js(webcpp_context_t* ctx, const char* app_identifier) {
    if (!ctx || !app_identifier) {
        fprintf(stderr, "HomeScreen: Invalid arguments to launch_application_js.\n");
        return false;
    }
    printf("HomeScreen: Received request to launch application: %s (Actual launch mechanism TBD)\n", app_identifier);
    // TODO: Implement actual application launching logic here.
    // This might involve IPC to a system shell or process manager.
    return true; // Placeholder success
}

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

    // Register the C++ launch function to be callable from JavaScript
    webcpp_register_function(ctx, "HomeScreenAPI_launchApplication", (void*)launch_application_js);

    // Main loop or event handling for the home screen would go here
    // For the Home Screen/Launcher, this process needs to stay alive.

    webcpp_destroy_context(ctx);
    webcpp_shutdown();
    return 0;
}