#ifndef ACEUI_H
#define ACEUI_H

#include <stdint.h>
#include <stdbool.h>

// Window flags
#define WINDOW_FLAG_NONE        0x00000000
#define WINDOW_FLAG_RESIZABLE   0x00000001
#define WINDOW_FLAG_MINIMIZABLE 0x00000002
#define WINDOW_FLAG_MAXIMIZABLE 0x00000004
#define WINDOW_FLAG_CLOSABLE    0x00000008
#define WINDOW_FLAG_MODAL       0x00000010
#define WINDOW_FLAG_TOPMOST     0x00000020
#define WINDOW_FLAG_FULLSCREEN  0x00000040

// Widget types
typedef enum {
    WIDGET_WINDOW,
    WIDGET_BUTTON,
    WIDGET_LABEL,
    WIDGET_TEXTBOX,
    WIDGET_CHECKBOX,
    WIDGET_RADIOBUTTON,
    WIDGET_COMBOBOX,
    WIDGET_LISTBOX,
    WIDGET_PROGRESSBAR,
    WIDGET_SCROLLBAR,
    WIDGET_SLIDER,
    WIDGET_TABCONTROL,
    WIDGET_TREEVIEW,
    WIDGET_MENU,
    WIDGET_TOOLBAR,
    WIDGET_STATUSBAR,
    WIDGET_TABBAR,
    WIDGET_TAB
} widget_type_t;

// Color structure
typedef struct {
    uint8_t r, g, b, a;
} color_t;

// Rectangle structure
typedef struct {
    int32_t x, y;
    int32_t width, height;
} rect_t;

// Point structure
typedef struct {
    int32_t x, y;
} point_t;

// Size structure
typedef struct {
    int32_t width, height;
} size_t;

// Event types
typedef enum {
    EVENT_NONE,
    EVENT_MOUSE_MOVE,
    EVENT_MOUSE_DOWN,
    EVENT_MOUSE_UP,
    EVENT_MOUSE_WHEEL,
    EVENT_KEY_DOWN,
    EVENT_KEY_UP,
    EVENT_CHAR,
    EVENT_FOCUS,
    EVENT_BLUR,
    EVENT_RESIZE,
    EVENT_MOVE,
    EVENT_CLOSE,
    EVENT_CUSTOM
} event_type_t;

// Event structure
typedef struct {
    event_type_t type;
    union {
        struct {
            point_t position;
            uint32_t buttons;
            int32_t wheel_delta;
        } mouse;
        struct {
            uint32_t key_code;
            uint32_t modifiers;
        } keyboard;
        struct {
            size_t size;
        } resize;
        struct {
            point_t position;
        } move;
        struct {
            void* data;
        } custom;
    } data;
} event_t;

// Widget structure
typedef struct widget_s {
    widget_type_t type;
    rect_t bounds;
    bool visible;
    bool enabled;
    bool focused;
    char* text;
    color_t background;
    color_t foreground;
    struct widget_s* parent;
    struct widget_s* first_child;
    struct widget_s* last_child;
    struct widget_s* next_sibling;
    struct widget_s* prev_sibling;
    void (*on_event)(struct widget_s* widget, event_t* event);
    void* user_data;
} widget_t;

// Window structure
typedef struct {
    widget_t base;
    uint32_t flags;
    char* title;
    bool minimized;
    bool maximized;
    bool fullscreen;
    rect_t normal_bounds;
} window_t;

// Initialize AceUI framework
void aceui_init(void);

// Create a new window
window_t* aceui_create_window(const char* title, rect_t bounds, uint32_t flags);

// Create a new widget
widget_t* aceui_create_widget(widget_type_t type, rect_t bounds);

// Add a widget to a parent
void aceui_add_widget(widget_t* parent, widget_t* child);

// Remove a widget from its parent
void aceui_remove_widget(widget_t* widget);

// Set widget text
void aceui_set_text(widget_t* widget, const char* text);

// Set widget colors
void aceui_set_colors(widget_t* widget, color_t background, color_t foreground);

// Set widget position
void aceui_set_position(widget_t* widget, int32_t x, int32_t y);

// Set widget size
void aceui_set_size(widget_t* widget, int32_t width, int32_t height);

// Set widget bounds
void aceui_set_bounds(widget_t* widget, rect_t bounds);

// Show widget
void aceui_show(widget_t* widget);

// Hide widget
void aceui_hide(widget_t* widget);

// Enable widget
void aceui_enable(widget_t* widget);

// Disable widget
void aceui_disable(widget_t* widget);

// Focus widget
void aceui_focus(widget_t* widget);

// Process events
void aceui_process_events(void);

// Render UI
void aceui_render(void);

// Clean up AceUI framework
void aceui_cleanup(void);

// Optionally, define TabBar/Tab structures here if needed for your C backend

#endif // ACEUI_H 