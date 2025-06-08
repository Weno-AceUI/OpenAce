#ifndef ACEUI_FONT_H
#define ACEUI_FONT_H

#include "aceui.h"

// Font style flags
#define FONT_STYLE_NORMAL     0x00
#define FONT_STYLE_BOLD       0x01
#define FONT_STYLE_ITALIC     0x02
#define FONT_STYLE_UNDERLINE  0x04
#define FONT_STYLE_STRIKEOUT  0x08

// Font structure
typedef struct {
    char* name;                // Font name
    float size;                // Font size
    int style;                 // Font style flags
    void* data;                // Font data
    void* handle;              // Font handle
} font_t;

// Initialize font system
bool font_init(void);

// Load font
font_t* font_load(const char* name, float size, int style);

// Load font from file
font_t* font_load_from_file(const char* filename, float size, int style);

// Load font from memory
font_t* font_load_from_memory(const void* data, size_t size, float font_size, int style);

// Destroy font
void font_destroy(font_t* font);

// Get font metrics
void font_get_metrics(font_t* font, float* ascent, float* descent, float* line_height);

// Get text size
void font_get_text_size(font_t* font, const char* text, float* width, float* height);

// Get text bounds
void font_get_text_bounds(font_t* font, const char* text, float x, float y, float* bounds);

// Draw text
void font_draw_text(font_t* font, const char* text, float x, float y, color_t color);

// Clean up font system
void font_cleanup(void);

#endif // ACEUI_FONT_H 