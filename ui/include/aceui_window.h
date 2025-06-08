#ifndef ACEUI_WINDOW_H
#define ACEUI_WINDOW_H

#include "aceui.h"
#include "aceui_widget.h"

// Window flags
#define WINDOW_FLAG_NONE          0x00000000
#define WINDOW_FLAG_VISIBLE       0x00000001
#define WINDOW_FLAG_RESIZABLE     0x00000002
#define WINDOW_FLAG_MINIMIZABLE   0x00000004
#define WINDOW_FLAG_MAXIMIZABLE   0x00000008
#define WINDOW_FLAG_CLOSABLE      0x00000010
#define WINDOW_FLAG_FULLSCREEN    0x00000020
#define WINDOW_FLAG_BORDERLESS    0x00000040
#define WINDOW_FLAG_ALWAYS_ON_TOP 0x00000080
#define WINDOW_FLAG_MODAL         0x00000100
#define WINDOW_FLAG_TOOLTIP       0x00000200
#define WINDOW_FLAG_POPUP         0x00000400

// Window state
typedef enum {
    WINDOW_STATE_NORMAL,
    WINDOW_STATE_MINIMIZED,
    WINDOW_STATE_MAXIMIZED,
    WINDOW_STATE_FULLSCREEN
} window_state_t;

// Window structure
typedef struct {
    char* title;                // Window title
    rect_t bounds;             // Window bounds
    window_state_t state;      // Window state
    uint32_t flags;            // Window flags
    void* handle;              // Platform-specific window handle
    widget_t* root_widget;     // Root widget
    widget_t* focused_widget;  // Currently focused widget
    widget_t* hovered_widget;  // Currently hovered widget
    void* user_data;           // User data
} window_t;

// Initialize window system
bool window_init(void);

// Create window
window_t* window_create(const char* title, rect_t bounds, uint32_t flags);

// Destroy window
void window_destroy(window_t* window);

// Set window title
void window_set_title(window_t* window, const char* title);

// Set window bounds
void window_set_bounds(window_t* window, rect_t bounds);

// Set window state
void window_set_state(window_t* window, window_state_t state);

// Set window flags
void window_set_flags(window_t* window, uint32_t flags);

// Clear window flags
void window_clear_flags(window_t* window, uint32_t flags);

// Check window flags
bool window_has_flags(window_t* window, uint32_t flags);

// Set window root widget
void window_set_root_widget(window_t* window, widget_t* widget);

// Process window events
void window_process_events(window_t* window);

// Paint window
void window_paint(window_t* window);

// Show window
void window_show(window_t* window);

// Hide window
void window_hide(window_t* window);

// Focus window
void window_focus(window_t* window);

// Minimize window
void window_minimize(window_t* window);

// Maximize window
void window_maximize(window_t* window);

// Restore window
void window_restore(window_t* window);

// Close window
void window_close(window_t* window);

// Get window by handle
window_t* window_get_by_handle(void* handle);

// Get focused window
window_t* window_get_focused(void);

// Clean up window system
void window_cleanup(void);

#endif // ACEUI_WINDOW_H 