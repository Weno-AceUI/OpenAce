#ifndef ACEUI_IMAGE_H
#define ACEUI_IMAGE_H

#include "aceui.h"

// Image format
typedef enum {
    IMAGE_FORMAT_NONE,
    IMAGE_FORMAT_RGBA,
    IMAGE_FORMAT_RGB,
    IMAGE_FORMAT_GRAY,
    IMAGE_FORMAT_COUNT
} image_format_t;

// Image structure
typedef struct {
    int width;                  // Image width
    int height;                 // Image height
    image_format_t format;      // Image format
    void* data;                 // Image data
    void* handle;               // Image handle
} image_t;

// Initialize image system
bool image_init(void);

// Load image
image_t* image_load(const char* filename);

// Load image from memory
image_t* image_load_from_memory(const void* data, size_t size);

// Create image
image_t* image_create(int width, int height, image_format_t format);

// Destroy image
void image_destroy(image_t* image);

// Get image size
void image_get_size(image_t* image, int* width, int* height);

// Get image format
image_format_t image_get_format(image_t* image);

// Get image data
void* image_get_data(image_t* image);

// Set image data
bool image_set_data(image_t* image, const void* data);

// Draw image
void image_draw(image_t* image, float x, float y, float width, float height);

// Draw image with color
void image_draw_color(image_t* image, float x, float y, float width, float height, color_t color);

// Draw image with rotation
void image_draw_rotated(image_t* image, float x, float y, float width, float height, float rotation);

// Draw image with rotation and color
void image_draw_rotated_color(image_t* image, float x, float y, float width, float height, float rotation, color_t color);

// Clean up image system
void image_cleanup(void);

#endif // ACEUI_IMAGE_H 