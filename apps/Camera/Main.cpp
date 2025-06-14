#include "../../WebCpp/include/webcpp.h"
#include <stdio.h> // For fprintf and printf
#include <stdlib.h> // For free()

// Wrapper for webcpp_save_image_from_data_url to be called from JS
// JS will pass (full_file_path, base64_data_url), C++ returns true/false.
bool save_photo_js(webcpp_context_t* ctx, const char* full_file_path, const char* base64_data_url) {
    if (!ctx || !full_file_path || !base64_data_url) {
        fprintf(stderr, "CameraApp: Invalid arguments to save_photo_js.\n");
        return false;
    }
    return webcpp_save_image_from_data_url(ctx, full_file_path, base64_data_url);
}

int main() {
    webcpp_config_t config = {
        .max_memory = 128 * 1024 * 1024, // 128MB, adjust as needed for camera
        .enable_gpu = true,
        .enable_threading = true,
        .js_engine = "v8"
    };
    if (!webcpp_init(&config)) {
        fprintf(stderr, "Error: Failed to initialize WebCpp for Camera app.\n");
        return 1;
    }

    webcpp_context_t* ctx = webcpp_create_context();
    if (!ctx) {
        fprintf(stderr, "Error: Failed to create WebCpp context for Camera app.\n");
        webcpp_shutdown();
        return 1;
    }

    if (!webcpp_load_html_file(ctx, "Camera.html")) {
        fprintf(stderr, "Error: Camera app failed to load Camera.html\n");
        webcpp_destroy_context(ctx);
        webcpp_shutdown();
        return 1;
    }
    printf("Camera app: Camera.html loaded successfully.\n");

    webcpp_register_function(ctx, "CameraAPI_savePhoto", (void*)save_photo_js);

    // Main loop or event handling would go here

    webcpp_destroy_context(ctx);
    webcpp_shutdown();
    return 0;
}