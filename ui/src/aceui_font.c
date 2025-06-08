#include "aceui_font.h"
#include <stdlib.h>
#include <string.h>

// Global state
static bool g_initialized = false;

// Initialize font system
bool font_init(void) {
    if (g_initialized) {
        return true;
    }

    // TODO: Initialize font system resources
    g_initialized = true;
    return true;
}

// Load font
font_t* font_load(const char* name, float size, int style) {
    if (!g_initialized || !name) {
        return NULL;
    }

    font_t* font = (font_t*)malloc(sizeof(font_t));
    if (!font) {
        return NULL;
    }

    font->name = strdup(name);
    font->size = size;
    font->style = style;
    font->data = NULL;
    font->handle = NULL;

    // TODO: Load font from system
    return font;
}

// Load font from file
font_t* font_load_from_file(const char* filename, float size, int style) {
    if (!g_initialized || !filename) {
        return NULL;
    }

    font_t* font = (font_t*)malloc(sizeof(font_t));
    if (!font) {
        return NULL;
    }

    font->name = strdup(filename);
    font->size = size;
    font->style = style;
    font->data = NULL;
    font->handle = NULL;

    // TODO: Load font from file
    return font;
}

// Load font from memory
font_t* font_load_from_memory(const void* data, size_t size, float font_size, int style) {
    if (!g_initialized || !data || size == 0) {
        return NULL;
    }

    font_t* font = (font_t*)malloc(sizeof(font_t));
    if (!font) {
        return NULL;
    }

    font->name = NULL;
    font->size = font_size;
    font->style = style;
    font->data = malloc(size);
    if (!font->data) {
        free(font);
        return NULL;
    }
    memcpy(font->data, data, size);
    font->handle = NULL;

    // TODO: Load font from memory
    return font;
}

// Destroy font
void font_destroy(font_t* font) {
    if (!font) {
        return;
    }

    // TODO: Free font resources
    free(font->name);
    free(font->data);
    free(font);
}

// Get font metrics
void font_get_metrics(font_t* font, float* ascent, float* descent, float* line_height) {
    if (!font || !ascent || !descent || !line_height) {
        return;
    }

    // TODO: Get font metrics
    *ascent = font->size * 0.8f;
    *descent = font->size * 0.2f;
    *line_height = font->size;
}

// Get text size
void font_get_text_size(font_t* font, const char* text, float* width, float* height) {
    if (!font || !text || !width || !height) {
        return;
    }

    // TODO: Get text size
    *width = strlen(text) * font->size * 0.6f;
    *height = font->size;
}

// Get text bounds
void font_get_text_bounds(font_t* font, const char* text, float x, float y, float* bounds) {
    if (!font || !text || !bounds) {
        return;
    }

    // TODO: Get text bounds
    float width, height;
    font_get_text_size(font, text, &width, &height);
    bounds[0] = x;
    bounds[1] = y;
    bounds[2] = x + width;
    bounds[3] = y + height;
}

// Draw text
void font_draw_text(font_t* font, const char* text, float x, float y, color_t color) {
    if (!font || !text) {
        return;
    }

    // TODO: Draw text
}

// Clean up font system
void font_cleanup(void) {
    if (!g_initialized) {
        return;
    }

    // TODO: Clean up font system resources
    g_initialized = false;
} 