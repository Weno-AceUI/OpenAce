#ifndef ACEUI_WIDGET_H
#define ACEUI_WIDGET_H

#include "aceui.h"

// Widget flags
#define WIDGET_FLAG_NONE        0x00000000
#define WIDGET_FLAG_VISIBLE     0x00000001
#define WIDGET_FLAG_ENABLED     0x00000002
#define WIDGET_FLAG_FOCUSABLE   0x00000004
#define WIDGET_FLAG_FOCUSED     0x00000008
#define WIDGET_FLAG_HOVERED     0x00000010
#define WIDGET_FLAG_PRESSED     0x00000020
#define WIDGET_FLAG_CHECKED     0x00000040
#define WIDGET_FLAG_DRAGGABLE   0x00000080
#define WIDGET_FLAG_DRAGGING    0x00000100
#define WIDGET_FLAG_RESIZABLE   0x00000200
#define WIDGET_FLAG_RESIZING    0x00000400

// Widget event types
typedef enum {
    EVENT_NONE,
    EVENT_MOUSE_ENTER,
    EVENT_MOUSE_LEAVE,
    EVENT_MOUSE_MOVE,
    EVENT_MOUSE_DOWN,
    EVENT_MOUSE_UP,
    EVENT_MOUSE_WHEEL,
    EVENT_KEY_DOWN,
    EVENT_KEY_UP,
    EVENT_CHAR,
    EVENT_FOCUS_GAIN,
    EVENT_FOCUS_LOSE,
    EVENT_CHECK,
    EVENT_UNCHECK,
    EVENT_DRAG_START,
    EVENT_DRAG_MOVE,
    EVENT_DRAG_END,
    EVENT_RESIZE_START,
    EVENT_RESIZE_MOVE,
    EVENT_RESIZE_END,
    EVENT_CUSTOM
} widget_event_type_t;

// Widget event structure
typedef struct {
    widget_event_type_t type;
    void* sender;
    void* data;
    bool handled;
} widget_event_t;

// Widget structure
typedef struct widget_s {
    char* id;                    // Widget identifier
    char* text;                  // Widget text
    rect_t bounds;              // Widget bounds
    color_t background_color;    // Background color
    color_t foreground_color;    // Foreground color
    color_t border_color;        // Border color
    float border_width;         // Border width
    float corner_radius;        // Corner radius
    font_t* font;               // Widget font
    uint32_t flags;             // Widget flags
    void* user_data;            // User data
    struct widget_s* parent;    // Parent widget
    struct widget_s** children; // Child widgets
    size_t child_count;         // Number of children
    size_t child_capacity;      // Child array capacity
    void (*on_event)(struct widget_s*, widget_event_t*); // Event handler
    void (*on_paint)(struct widget_s*); // Paint handler
} widget_t;

// Initialize widget system
bool widget_init(void);

// Create widget
widget_t* widget_create(const char* id, const char* text);

// Destroy widget
void widget_destroy(widget_t* widget);

// Add child widget
bool widget_add_child(widget_t* parent, widget_t* child);

// Remove child widget
bool widget_remove_child(widget_t* parent, widget_t* child);

// Set widget text
void widget_set_text(widget_t* widget, const char* text);

// Set widget bounds
void widget_set_bounds(widget_t* widget, rect_t bounds);

// Set widget colors
void widget_set_colors(widget_t* widget, color_t background, color_t foreground, color_t border);

// Set widget font
void widget_set_font(widget_t* widget, font_t* font);

// Set widget flags
void widget_set_flags(widget_t* widget, uint32_t flags);

// Clear widget flags
void widget_clear_flags(widget_t* widget, uint32_t flags);

// Check widget flags
bool widget_has_flags(widget_t* widget, uint32_t flags);

// Set widget event handler
void widget_set_event_handler(widget_t* widget, void (*handler)(widget_t*, widget_event_t*));

// Set widget paint handler
void widget_set_paint_handler(widget_t* widget, void (*handler)(widget_t*));

// Process widget event
bool widget_process_event(widget_t* widget, widget_event_t* event);

// Paint widget
void widget_paint(widget_t* widget);

// Find widget by ID
widget_t* widget_find_by_id(widget_t* root, const char* id);

// Clean up widget system
void widget_cleanup(void);

// Create tabbar widget
widget_t* widget_create_tabbar(const char* id);

// Create tab widget
widget_t* widget_create_tab(const char* id, const char* title, widget_t* content);

#endif // ACEUI_WIDGET_H 