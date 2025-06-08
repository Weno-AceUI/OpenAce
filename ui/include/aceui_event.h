#ifndef ACEUI_EVENT_H
#define ACEUI_EVENT_H

#include "aceui.h"
#include "aceui_widget.h"

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
    EVENT_FOCUS_IN,
    EVENT_FOCUS_OUT,
    EVENT_RESIZE,
    EVENT_MOVE,
    EVENT_CLOSE,
    EVENT_CUSTOM,
    EVENT_COUNT
} event_type_t;

// Mouse button flags
#define MOUSE_BUTTON_NONE    0x00
#define MOUSE_BUTTON_LEFT    0x01
#define MOUSE_BUTTON_RIGHT   0x02
#define MOUSE_BUTTON_MIDDLE  0x04
#define MOUSE_BUTTON_X1      0x08
#define MOUSE_BUTTON_X2      0x10

// Key modifiers
#define KEY_MODIFIER_NONE    0x00
#define KEY_MODIFIER_SHIFT   0x01
#define KEY_MODIFIER_CTRL    0x02
#define KEY_MODIFIER_ALT     0x04
#define KEY_MODIFIER_SUPER   0x08
#define KEY_MODIFIER_CAPS    0x10
#define KEY_MODIFIER_NUM     0x20

// Event structure
typedef struct {
    event_type_t type;           // Event type
    widget_t* target;            // Target widget
    widget_t* source;            // Source widget
    union {
        struct {
            int x;               // Mouse X position
            int y;               // Mouse Y position
            int buttons;         // Mouse button flags
            int modifiers;       // Key modifiers
        } mouse;                 // Mouse event data
        struct {
            int key;             // Key code
            int modifiers;       // Key modifiers
            bool repeat;         // Key repeat flag
        } key;                   // Keyboard event data
        struct {
            int x;               // New X position
            int y;               // New Y position
        } move;                  // Move event data
        struct {
            int width;           // New width
            int height;          // New height
        } resize;                // Resize event data
        struct {
            void* data;          // Custom event data
        } custom;                // Custom event data
    } data;                      // Event data
} event_t;

// Event handler function type
typedef void (*event_handler_t)(event_t* event, void* user_data);

// Initialize event system
bool event_init(void);

// Register event handler
bool event_register_handler(widget_t* widget, event_type_t type, event_handler_t handler, void* user_data);

// Unregister event handler
void event_unregister_handler(widget_t* widget, event_type_t type);

// Process event
void event_process(event_t* event);

// Create mouse event
event_t event_create_mouse(event_type_t type, widget_t* target, int x, int y, int buttons, int modifiers);

// Create keyboard event
event_t event_create_keyboard(event_type_t type, widget_t* target, int key, int modifiers, bool repeat);

// Create move event
event_t event_create_move(widget_t* target, int x, int y);

// Create resize event
event_t event_create_resize(widget_t* target, int width, int height);

// Create custom event
event_t event_create_custom(widget_t* target, void* data);

// Clean up event system
void event_cleanup(void);

#endif // ACEUI_EVENT_H 