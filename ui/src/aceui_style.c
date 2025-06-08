#include "aceui_style.h"
#include <stdlib.h>
#include <string.h>

// Global state
static bool g_initialized = false;

// Initialize style system
bool style_init(void) {
    if (g_initialized) {
        return true;
    }

    // TODO: Initialize style system resources
    g_initialized = true;
    return true;
}

// Create style
style_t* style_create(const char* name) {
    if (!g_initialized || !name) {
        return NULL;
    }

    style_t* style = (style_t*)malloc(sizeof(style_t));
    if (!style) {
        return NULL;
    }

    style->name = strdup(name);
    style->properties = NULL;
    style->property_count = 0;
    style->property_capacity = 0;

    return style;
}

// Destroy style
void style_destroy(style_t* style) {
    if (!style) {
        return;
    }

    // Free properties
    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        free(prop->name);
        if (prop->type == STYLE_PROPERTY_STRING) {
            free(prop->value.string_value);
        }
    }

    free(style->properties);
    free(style->name);
    free(style);
}

// Add style property
bool style_add_property(style_t* style, const char* name, style_property_type_t type) {
    if (!style || !name) {
        return false;
    }

    // Check if property already exists
    for (size_t i = 0; i < style->property_count; i++) {
        if (strcmp(style->properties[i].name, name) == 0) {
            return false;
        }
    }

    // Resize property array if needed
    if (style->property_count >= style->property_capacity) {
        size_t new_capacity = style->property_capacity == 0 ? 8 : style->property_capacity * 2;
        style_property_t* new_properties = (style_property_t*)realloc(style->properties, 
            new_capacity * sizeof(style_property_t));
        if (!new_properties) {
            return false;
        }
        style->properties = new_properties;
        style->property_capacity = new_capacity;
    }

    // Add new property
    style_property_t* prop = &style->properties[style->property_count++];
    prop->name = strdup(name);
    prop->type = type;
    memset(&prop->value, 0, sizeof(prop->value));

    return true;
}

// Set style property color
void style_set_property_color(style_t* style, const char* name, color_t color) {
    if (!style || !name) {
        return;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0) {
            prop->type = STYLE_PROPERTY_COLOR;
            prop->value.color = color;
            return;
        }
    }
}

// Set style property float
void style_set_property_float(style_t* style, const char* name, float value) {
    if (!style || !name) {
        return;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0) {
            prop->type = STYLE_PROPERTY_FLOAT;
            prop->value.float_value = value;
            return;
        }
    }
}

// Set style property int
void style_set_property_int(style_t* style, const char* name, int value) {
    if (!style || !name) {
        return;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0) {
            prop->type = STYLE_PROPERTY_INT;
            prop->value.int_value = value;
            return;
        }
    }
}

// Set style property bool
void style_set_property_bool(style_t* style, const char* name, bool value) {
    if (!style || !name) {
        return;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0) {
            prop->type = STYLE_PROPERTY_BOOL;
            prop->value.bool_value = value;
            return;
        }
    }
}

// Set style property string
void style_set_property_string(style_t* style, const char* name, const char* value) {
    if (!style || !name || !value) {
        return;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0) {
            prop->type = STYLE_PROPERTY_STRING;
            prop->value.string_value = strdup(value);
            return;
        }
    }
}

// Set style property font
void style_set_property_font(style_t* style, const char* name, font_t* font) {
    if (!style || !name || !font) {
        return;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0) {
            prop->type = STYLE_PROPERTY_FONT;
            prop->value.font_value = font;
            return;
        }
    }
}

// Set style property image
void style_set_property_image(style_t* style, const char* name, void* image) {
    if (!style || !name || !image) {
        return;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0) {
            prop->type = STYLE_PROPERTY_IMAGE;
            prop->value.image_value = image;
            return;
        }
    }
}

// Get style property color
color_t style_get_property_color(style_t* style, const char* name) {
    if (!style || !name) {
        return (color_t){0, 0, 0, 0};
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0 && prop->type == STYLE_PROPERTY_COLOR) {
            return prop->value.color;
        }
    }

    return (color_t){0, 0, 0, 0};
}

// Get style property float
float style_get_property_float(style_t* style, const char* name) {
    if (!style || !name) {
        return 0.0f;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0 && prop->type == STYLE_PROPERTY_FLOAT) {
            return prop->value.float_value;
        }
    }

    return 0.0f;
}

// Get style property int
int style_get_property_int(style_t* style, const char* name) {
    if (!style || !name) {
        return 0;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0 && prop->type == STYLE_PROPERTY_INT) {
            return prop->value.int_value;
        }
    }

    return 0;
}

// Get style property bool
bool style_get_property_bool(style_t* style, const char* name) {
    if (!style || !name) {
        return false;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0 && prop->type == STYLE_PROPERTY_BOOL) {
            return prop->value.bool_value;
        }
    }

    return false;
}

// Get style property string
const char* style_get_property_string(style_t* style, const char* name) {
    if (!style || !name) {
        return NULL;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0 && prop->type == STYLE_PROPERTY_STRING) {
            return prop->value.string_value;
        }
    }

    return NULL;
}

// Get style property font
font_t* style_get_property_font(style_t* style, const char* name) {
    if (!style || !name) {
        return NULL;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0 && prop->type == STYLE_PROPERTY_FONT) {
            return prop->value.font_value;
        }
    }

    return NULL;
}

// Get style property image
void* style_get_property_image(style_t* style, const char* name) {
    if (!style || !name) {
        return NULL;
    }

    for (size_t i = 0; i < style->property_count; i++) {
        style_property_t* prop = &style->properties[i];
        if (strcmp(prop->name, name) == 0 && prop->type == STYLE_PROPERTY_IMAGE) {
            return prop->value.image_value;
        }
    }

    return NULL;
}

// Apply style to widget
void style_apply_to_widget(style_t* style, widget_t* widget) {
    if (!style || !widget) {
        return;
    }

    // TODO: Apply style properties to widget
    // This will be implemented when we have widget-specific styling
}

// Clean up style system
void style_cleanup(void) {
    if (!g_initialized) {
        return;
    }

    // TODO: Clean up style system resources
    g_initialized = false;
} 