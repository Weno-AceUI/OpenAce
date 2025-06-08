#ifndef ACEUI_STYLE_H
#define ACEUI_STYLE_H

#include "aceui.h"
#include "aceui_widget.h"

// Style property types
typedef enum {
    STYLE_PROPERTY_NONE,
    STYLE_PROPERTY_COLOR,
    STYLE_PROPERTY_FLOAT,
    STYLE_PROPERTY_INT,
    STYLE_PROPERTY_BOOL,
    STYLE_PROPERTY_STRING,
    STYLE_PROPERTY_FONT,
    STYLE_PROPERTY_IMAGE,
    STYLE_PROPERTY_COUNT
} style_property_type_t;

// Style property structure
typedef struct {
    char* name;                    // Property name
    style_property_type_t type;    // Property type
    union {
        color_t color;             // Color value
        float float_value;         // Float value
        int int_value;             // Integer value
        bool bool_value;           // Boolean value
        char* string_value;        // String value
        font_t* font_value;        // Font value
        void* image_value;         // Image value
    } value;                       // Property value
} style_property_t;

// Style structure
typedef struct {
    char* name;                    // Style name
    style_property_t* properties;  // Style properties
    size_t property_count;         // Number of properties
    size_t property_capacity;      // Property array capacity
} style_t;

// Initialize style system
bool style_init(void);

// Create style
style_t* style_create(const char* name);

// Destroy style
void style_destroy(style_t* style);

// Add style property
bool style_add_property(style_t* style, const char* name, style_property_type_t type);

// Set style property color
void style_set_property_color(style_t* style, const char* name, color_t color);

// Set style property float
void style_set_property_float(style_t* style, const char* name, float value);

// Set style property int
void style_set_property_int(style_t* style, const char* name, int value);

// Set style property bool
void style_set_property_bool(style_t* style, const char* name, bool value);

// Set style property string
void style_set_property_string(style_t* style, const char* name, const char* value);

// Set style property font
void style_set_property_font(style_t* style, const char* name, font_t* font);

// Set style property image
void style_set_property_image(style_t* style, const char* name, void* image);

// Get style property color
color_t style_get_property_color(style_t* style, const char* name);

// Get style property float
float style_get_property_float(style_t* style, const char* name);

// Get style property int
int style_get_property_int(style_t* style, const char* name);

// Get style property bool
bool style_get_property_bool(style_t* style, const char* name);

// Get style property string
const char* style_get_property_string(style_t* style, const char* name);

// Get style property font
font_t* style_get_property_font(style_t* style, const char* name);

// Get style property image
void* style_get_property_image(style_t* style, const char* name);

// Apply style to widget
void style_apply_to_widget(style_t* style, widget_t* widget);

// Clean up style system
void style_cleanup(void);

#endif // ACEUI_STYLE_H 