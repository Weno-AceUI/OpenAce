#ifndef ACEUI_GRAPHICS_H
#define ACEUI_GRAPHICS_H

#include "aceui.h"

// Graphics context structure
typedef struct {
    void* handle;
    int32_t width;
    int32_t height;
    bool double_buffered;
} graphics_context_t;

// Initialize graphics system
bool graphics_init(void);

// Create graphics context
graphics_context_t* graphics_create_context(int32_t width, int32_t height, bool double_buffered);

// Destroy graphics context
void graphics_destroy_context(graphics_context_t* context);

// Set current graphics context
void graphics_set_context(graphics_context_t* context);

// Clear graphics context
void graphics_clear(color_t color);

// Draw rectangle
void graphics_draw_rect(rect_t rect, color_t color);

// Fill rectangle
void graphics_fill_rect(rect_t rect, color_t color);

// Draw line
void graphics_draw_line(point_t start, point_t end, color_t color);

// Draw text
void graphics_draw_text(const char* text, point_t position, color_t color);

// Draw image
void graphics_draw_image(void* image, rect_t src_rect, rect_t dst_rect);

// Set clip rectangle
void graphics_set_clip(rect_t rect);

// Clear clip rectangle
void graphics_clear_clip(void);

// Present graphics
void graphics_present(void);

// Clean up graphics system
void graphics_cleanup(void);

#endif // ACEUI_GRAPHICS_H 