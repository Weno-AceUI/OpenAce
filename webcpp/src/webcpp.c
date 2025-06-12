#include "../include/webcpp.h"
#include "../include/webcpp_gpu.h"
#include "../include/webcpp_threading.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static bool g_initialized = false;
static webcpp_config_t g_config;

bool webcpp_init(const webcpp_config_t* config) {
    if (g_initialized) return false;
    
    // Copy configuration
    memcpy(&g_config, config, sizeof(webcpp_config_t));
    
    // Initialize JavaScript engine
    // TODO: Initialize selected JS engine (V8, JavaScriptCore, etc.)
    
    // Initialize subsystems
    if (g_config.enable_gpu && !gpu_init()) {
        return false;
    }
    
    if (g_config.enable_threading && !threading_init()) {
        if (g_config.enable_gpu) gpu_cleanup();
        return false;
    }
    
    g_initialized = true;
    return true;
}

webcpp_context_t* webcpp_create_context(void) {
    if (!g_initialized) return NULL;
    
    webcpp_context_t* context = (webcpp_context_t*)malloc(sizeof(webcpp_context_t));
    if (!context) return NULL;
    
    // TODO: Create JavaScript context
    // This will involve:
    // 1. Creating JS engine context
    // 2. Setting up DOM environment
    // 3. Initializing renderer
    
    context->js_context = NULL;    // Will be set by JS engine
    context->dom_context = NULL;   // Will be set by DOM implementation
    context->render_context = NULL; // Will be set by renderer
    context->context_id = 0;       // Will be set by context manager
    
    return context;
}

bool webcpp_eval_js(webcpp_context_t* context, const char* js_code) {
    if (!context || !js_code) return false;
    
    // TODO: Execute JavaScript code
    // This will involve:
    // 1. Parsing JS code
    // 2. Executing in JS context
    // 3. Handling errors
    
    return true;
}

bool webcpp_load_js_file(webcpp_context_t* context, const char* file_path) {
    if (!context || !file_path) return false;
    
    // TODO: Load and execute JS file
    // This will involve:
    // 1. Reading file
    // 2. Parsing JS code
    // 3. Executing in context
    
    return true;
}

bool webcpp_register_function(webcpp_context_t* context, const char* name, void* function_ptr) {
    if (!context || !name || !function_ptr) return false;
    
    // TODO: Register C++ function
    // This will involve:
    // 1. Creating JS function wrapper
    // 2. Registering with JS engine
    // 3. Setting up type conversion
    
    return true;
}

static char* webcpp_read_entire_file(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        // In a real library, you might have a WebCpp-specific error logging mechanism
        fprintf(stderr, "WebCpp Error: Could not open file %s\n", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "WebCpp Error: Could not allocate memory to read file %s\n", file_path);
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, length, file) != (size_t)length) {
        fprintf(stderr, "WebCpp Error: Could not read entire file %s\n", file_path);
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

// Helper function to escape HTML content for safe embedding in a JS string literal
// This is a very basic escaper and would need to be more robust for production.
static char* webcpp_escape_html_for_js_injection(const char* html_content) {
    if (!html_content) return NULL;
    
    size_t original_len = strlen(html_content);
    // Estimate new size. Worst case: every char needs escaping (e.g., \n -> \\n, ' -> \')
    // A more robust solution would calculate exact length or use dynamic resizing.
    size_t new_len_estimate = original_len * 2 + 1; 
    char* escaped_str = (char*)malloc(new_len_estimate);
    if (!escaped_str) return NULL;

    char* p_out = escaped_str;
    const char* p_in = html_content;
    while (*p_in) {
        switch (*p_in) {
            case '\'': *(p_out++) = '\\'; *(p_out++) = '\''; break;
            case '"':  *(p_out++) = '\\'; *(p_out++) = '"';  break; // If using double quotes in JS
            case '\\': *(p_out++) = '\\'; *(p_out++) = '\\'; break;
            case '\n': *(p_out++) = '\\'; *(p_out++) = 'n';  break;
            case '\r': *(p_out++) = '\\'; *(p_out++) = 'r';  break;
            // Add more escapes as needed (e.g., for backticks if using template literals)
            default:   *(p_out++) = *p_in; break;
        }
        if (p_out >= escaped_str + new_len_estimate - 2) { // -2 for potential two-char escape + null terminator
            // Buffer too small, realloc or handle error
            // For simplicity, we'll assume initial estimate is enough here.
            // In a real scenario, this needs robust handling.
            fprintf(stderr, "WebCpp Warning: Escaped string buffer might be too small for HTML content.\n");
            // To prevent buffer overflow, we stop here. A real implementation might realloc.
            *p_out = '\0'; // Null-terminate what we have
            // Potentially free(escaped_str) and return NULL if this is considered a fatal error.
            // For now, we'll proceed with the potentially truncated (but safe) string.
            break; 
        }
        p_in++;
    }
    *p_out = '\0';
    return escaped_str;
}

bool webcpp_load_html_file(webcpp_context_t* context, const char* file_path) {
    if (!context || !file_path) {
        return false; // Invalid arguments
    }

    char* html_content = webcpp_read_entire_file(file_path);
    if (!html_content) {
        return false; // Failed to read file
    }

    char* escaped_html = webcpp_escape_html_for_js_injection(html_content);
    free(html_content); // Free original content

    if (!escaped_html) {
        fprintf(stderr, "WebCpp Error: Failed to escape HTML content for JS injection.\n");
        return false;
    }

    // Construct the JavaScript command to replace the document's content.
    // Using document.documentElement.innerHTML is a common way.
    // Max command length: "document.documentElement.innerHTML = '';" + content + safety margin
    size_t js_command_len = strlen("document.documentElement.innerHTML = '';") + strlen(escaped_html) + 50;
    char* js_command = (char*)malloc(js_command_len);
    
    if (!js_command) {
        fprintf(stderr, "WebCpp Error: Failed to allocate memory for JS command.\n");
        free(escaped_html);
        return false;
    }

    sprintf(js_command, "document.documentElement.innerHTML = '%s';", escaped_html);
    
    free(escaped_html); // Free escaped content

    bool success = webcpp_eval_js(context, js_command);
    free(js_command); // Free the JS command string

    if (!success) {
        fprintf(stderr, "WebCpp Error: webcpp_eval_js failed to load HTML content from %s.\n", file_path);
    }
    return success;
}

bool webcpp_call_js_function(webcpp_context_t* context, const char* function_name, const char* args_json, char** result_json) {
    if (!context || !function_name) return false;
    
    // TODO: Call JS function
    // This will involve:
    // 1. Parsing arguments
    // 2. Calling function
    // 3. Converting result
    
    return true;
}

void* webcpp_get_element(webcpp_context_t* context, const char* selector) {
    if (!context || !selector) return NULL;
    
    // TODO: Get DOM element
    // This will involve:
    // 1. Parsing selector
    // 2. Finding element
    // 3. Creating wrapper
    
    return NULL;
}

bool webcpp_set_property(webcpp_context_t* context, void* element, const char* property, const char* value) {
    if (!context || !element || !property) return false;
    
    // TODO: Set element property
    // This will involve:
    // 1. Validating property
    // 2. Setting value
    // 3. Updating DOM
    
    return true;
}

bool webcpp_get_property(webcpp_context_t* context, void* element, const char* property, char** value) {
    if (!context || !element || !property || !value) return false;
    
    // TODO: Get element property
    // This will involve:
    // 1. Validating property
    // 2. Getting value
    // 3. Converting to string
    
    return true;
}

void webcpp_destroy_context(webcpp_context_t* context) {
    if (!context) return;
    
    // TODO: Cleanup context
    // This will involve:
    // 1. Destroying JS context
    // 2. Cleaning up DOM
    // 3. Releasing renderer
    
    free(context);
}

void webcpp_shutdown(void) {
    if (!g_initialized) return;
    
    if (g_config.enable_gpu) gpu_cleanup();
    if (g_config.enable_threading) threading_cleanup();
    
    // TODO: Shutdown JS engine
    
    g_initialized = false;
} 