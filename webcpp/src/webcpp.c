#include "../include/webcpp.h"
#include "../include/webcpp_gpu.h"
#include "../include/webcpp_threading.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // For directory listing
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

// Basic Base64 encoding (simplified, no line breaks)
static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char* webcpp_base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    *output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = (char*)malloc(*output_length + 1); // +1 for null terminator
    if (encoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 0 * 6) & 0x3F];
    }

    // Pad with '='
    size_t mod_table[] = {0, 2, 1};
    for (size_t i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    encoded_data[*output_length] = '\0';
    return encoded_data;
}

// Basic Base64 decoding
static unsigned char* webcpp_base64_decode(const char *data, size_t input_length, size_t *output_length) {
    if (input_length % 4 != 0) return NULL; // Invalid Base64 input

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    unsigned char *decoded_data = (unsigned char*)malloc(*output_length);
    if (decoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : strchr(base64_chars, data[i++]) - base64_chars;
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : strchr(base64_chars, data[i++]) - base64_chars;
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : strchr(base64_chars, data[i++]) - base64_chars;
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : strchr(base64_chars, data[i++]) - base64_chars;

        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
    return decoded_data;
}

bool webcpp_save_image_from_data_url(webcpp_context_t* context, const char* full_file_path, const char* base64_data_url) {
    if (!context || !full_file_path || !base64_data_url) return false;

    const char* base64_marker = ";base64,";
    const char* base64_content_start = strstr(base64_data_url, base64_marker);

    if (!base64_content_start) {
        fprintf(stderr, "WebCpp Error: Invalid data URL format. Missing ';base64,'.\n");
        return false;
    }
    base64_content_start += strlen(base64_marker); // Move pointer past the marker

    size_t decoded_length;
    unsigned char* image_bytes = webcpp_base64_decode(base64_content_start, strlen(base64_content_start), &decoded_length);

    if (!image_bytes) {
        fprintf(stderr, "WebCpp Error: Failed to decode Base64 image data for %s.\n", full_file_path);
        return false;
    }

    FILE* outfile = fopen(full_file_path, "wb");
    if (!outfile) {
        fprintf(stderr, "WebCpp Error: Could not open file %s for writing.\n", full_file_path);
        free(image_bytes);
        return false;
    }

    size_t written = fwrite(image_bytes, 1, decoded_length, outfile);
    fclose(outfile);
    free(image_bytes);

    if (written != decoded_length) {
        fprintf(stderr, "WebCpp Error: Failed to write all image bytes to %s.\n", full_file_path);
        return false;
    }
    return true;
}

bool webcpp_list_directory_items(webcpp_context_t* context, const char* directory_path, char** result_json) {
    if (!context || !directory_path || !result_json) return false;

    DIR *dir;
    struct dirent *entry;
    char buffer[2048]; // Buffer for constructing JSON string
    strcpy(buffer, "[");
    bool first_item = true;

    if ((dir = opendir(directory_path)) == NULL) {
        perror("opendir() error");
        *result_json = strdup("[]"); // Return empty JSON array on error
        return false;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Skip . and ..
        }

        if (!first_item) {
            strcat(buffer, ",");
        }
        first_item = false;

        char item_path[1024];
        snprintf(item_path, sizeof(item_path), "%s/%s", directory_path, entry->d_name);

        // Basic escaping for JSON string values (name and path)
        // A robust solution would handle all special characters.
        char escaped_name[256];
        char escaped_path[1024];
        // Simple escape: just an example, not comprehensive
        strncpy(escaped_name, entry->d_name, sizeof(escaped_name)-1); escaped_name[sizeof(escaped_name)-1] = '\0';
        strncpy(escaped_path, item_path, sizeof(escaped_path)-1); escaped_path[sizeof(escaped_path)-1] = '\0';
        // TODO: Implement proper JSON string escaping for name and path

        char item_json[1500];
        snprintf(item_json, sizeof(item_json),
                 "{\"name\":\"%s\",\"type\":\"%s\",\"path\":\"%s\"}",
                 escaped_name,
                 (entry->d_type == DT_DIR) ? "dir" : "file",
                 escaped_path);
        strcat(buffer, item_json);
    }
    closedir(dir);
    strcat(buffer, "]");

    *result_json = strdup(buffer);
    if (!*result_json) return false; // strdup failed

    return true;
}

bool webcpp_get_image_data_url(webcpp_context_t* context, const char* image_path, char** data_url_string) {
    if (!context || !image_path || !data_url_string) return false;

    FILE* image_file = fopen(image_path, "rb");
    if (!image_file) {
        fprintf(stderr, "WebCpp Error: Could not open image file %s\n", image_path);
        return false;
    }

    fseek(image_file, 0, SEEK_END);
    long file_size = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    unsigned char* image_data = (unsigned char*)malloc(file_size);
    if (!image_data) {
        fprintf(stderr, "WebCpp Error: Could not allocate memory for image data.\n");
        fclose(image_file);
        return false;
    }

    if (fread(image_data, 1, file_size, image_file) != (size_t)file_size) {
        fprintf(stderr, "WebCpp Error: Could not read image file %s\n", image_path);
        fclose(image_file);
        free(image_data);
        return false;
    }
    fclose(image_file);

    size_t base64_len;
    char* base64_data = webcpp_base64_encode(image_data, file_size, &base64_len);
    free(image_data);

    if (!base64_data) {
        fprintf(stderr, "WebCpp Error: Base64 encoding failed for %s\n", image_path);
        return false;
    }

    // Determine MIME type (very basic, based on extension)
    const char* mime_type = "image/jpeg"; // Default
    const char* ext = strrchr(image_path, '.');
    if (ext) {
        if (strcmp(ext, ".png") == 0) mime_type = "image/png";
        else if (strcmp(ext, ".gif") == 0) mime_type = "image/gif";
        // Add more types as needed
    }

    // Format: "data:[<mime_type>];base64,<data>"
    size_t data_url_len = strlen("data:") + strlen(mime_type) + strlen(";base64,") + base64_len + 1;
    *data_url_string = (char*)malloc(data_url_len);
    if (!*data_url_string) {
        fprintf(stderr, "WebCpp Error: Could not allocate memory for data URL string.\n");
        free(base64_data);
        return false;
    }

    sprintf(*data_url_string, "data:%s;base64,%s", mime_type, base64_data);
    free(base64_data);

    return true;
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