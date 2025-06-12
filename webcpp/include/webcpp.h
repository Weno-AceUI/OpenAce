#ifndef WEBCPP_H
#define WEBCPP_H

#include <stdint.h>
#include <stdbool.h>

// WebCpp Runtime Configuration
typedef struct {
    uint32_t max_memory;      // Maximum memory allocation
    bool enable_gpu;          // Enable GPU acceleration
    bool enable_threading;    // Enable threading support
    const char* js_engine;    // JavaScript engine to use (e.g., "v8", "javascriptcore")
} webcpp_config_t;

// WebCpp Context
typedef struct {
    void* js_context;         // JavaScript context
    void* dom_context;        // DOM context
    void* render_context;     // Rendering context
    uint32_t context_id;      // Unique context ID
} webcpp_context_t;

// Initialize WebCpp runtime
bool webcpp_init(const webcpp_config_t* config);

// Load HTML file and set it as the main document content
bool webcpp_load_html_file(webcpp_context_t* context, const char* file_path);


// Create new WebCpp context
webcpp_context_t* webcpp_create_context(void);

// Load and execute JavaScript code
bool webcpp_eval_js(webcpp_context_t* context, const char* js_code);

// Load and execute JavaScript file
bool webcpp_load_js_file(webcpp_context_t* context, const char* file_path);

// Register C++ function to be called from JavaScript
bool webcpp_register_function(webcpp_context_t* context, const char* name, void* function_ptr);

// Call JavaScript function from C++
bool webcpp_call_js_function(webcpp_context_t* context, const char* function_name, const char* args_json, char** result_json);

// Get DOM element
void* webcpp_get_element(webcpp_context_t* context, const char* selector);

// Set DOM element property
bool webcpp_set_property(webcpp_context_t* context, void* element, const char* property, const char* value);

// Get DOM element property
bool webcpp_get_property(webcpp_context_t* context, void* element, const char* property, char** value);

// Cleanup WebCpp context
void webcpp_destroy_context(webcpp_context_t* context);

// Shutdown WebCpp runtime
void webcpp_shutdown(void);

#endif // WEBCPP_H 