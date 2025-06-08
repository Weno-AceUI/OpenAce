#include "aceui_window.h"
#include <stdlib.h>
#include <string.h>

// Global state
static bool g_initialized = false;
static window_t* g_focused_window = NULL;
static window_t** g_windows = NULL;
static size_t g_window_count = 0;
static size_t g_window_capacity = 0;

bool window_init(void) {
    if (g_initialized) {
        return true;
    }

    // TODO: Initialize window system
    // - Set up window cache
    // - Initialize platform-specific window system
    // - Set up event queue

    g_initialized = true;
    return true;
}

window_t* window_create(const char* title, rect_t bounds, uint32_t flags) {
    if (!g_initialized || !title) {
        return NULL;
    }

    window_t* window = (window_t*)malloc(sizeof(window_t));
    if (!window) {
        return NULL;
    }

    // Initialize window structure
    window->title = strdup(title);
    window->bounds = bounds;
    window->state = WINDOW_STATE_NORMAL;
    window->flags = flags;
    window->handle = NULL;
    window->root_widget = NULL;
    window->focused_widget = NULL;
    window->hovered_widget = NULL;
    window->user_data = NULL;

    // TODO: Create platform-specific window
    // - Create window handle
    // - Set up window properties
    // - Initialize graphics context

    // Add window to list
    if (g_window_count >= g_window_capacity) {
        size_t new_capacity = g_window_capacity == 0 ? 4 : g_window_capacity * 2;
        window_t** new_windows = (window_t**)realloc(g_windows, new_capacity * sizeof(window_t*));
        if (!new_windows) {
            free(window->title);
            free(window);
            return NULL;
        }
        g_windows = new_windows;
        g_window_capacity = new_capacity;
    }
    g_windows[g_window_count++] = window;

    return window;
}

void window_destroy(window_t* window) {
    if (!window) {
        return;
    }

    // Remove window from list
    for (size_t i = 0; i < g_window_count; i++) {
        if (g_windows[i] == window) {
            memmove(&g_windows[i], &g_windows[i + 1],
                    (g_window_count - i - 1) * sizeof(window_t*));
            g_window_count--;
            break;
        }
    }

    // TODO: Destroy platform-specific window
    // - Destroy window handle
    // - Clean up graphics context

    // Destroy root widget
    if (window->root_widget) {
        widget_destroy(window->root_widget);
    }

    free(window->title);
    free(window);
}

void window_set_title(window_t* window, const char* title) {
    if (!window || !title) {
        return;
    }

    free(window->title);
    window->title = strdup(title);

    // TODO: Update platform-specific window title
}

void window_set_bounds(window_t* window, rect_t bounds) {
    if (!window) {
        return;
    }

    window->bounds = bounds;

    // TODO: Update platform-specific window bounds
}

void window_set_state(window_t* window, window_state_t state) {
    if (!window) {
        return;
    }

    window->state = state;

    // TODO: Update platform-specific window state
}

void window_set_flags(window_t* window, uint32_t flags) {
    if (!window) {
        return;
    }

    window->flags |= flags;

    // TODO: Update platform-specific window flags
}

void window_clear_flags(window_t* window, uint32_t flags) {
    if (!window) {
        return;
    }

    window->flags &= ~flags;

    // TODO: Update platform-specific window flags
}

bool window_has_flags(window_t* window, uint32_t flags) {
    return window && (window->flags & flags) == flags;
}

void window_set_root_widget(window_t* window, widget_t* widget) {
    if (!window) {
        return;
    }

    if (window->root_widget) {
        widget_destroy(window->root_widget);
    }

    window->root_widget = widget;
}

void window_process_events(window_t* window) {
    if (!window) {
        return;
    }

    // TODO: Process platform-specific window events
    // - Handle window events
    // - Update window state
    // - Process input events
}

void window_paint(window_t* window) {
    if (!window || !window_has_flags(window, WINDOW_FLAG_VISIBLE)) {
        return;
    }

    // TODO: Paint platform-specific window
    // - Clear window
    // - Paint root widget
    // - Present window
}

void window_show(window_t* window) {
    if (!window) {
        return;
    }

    window_set_flags(window, WINDOW_FLAG_VISIBLE);

    // TODO: Show platform-specific window
}

void window_hide(window_t* window) {
    if (!window) {
        return;
    }

    window_clear_flags(window, WINDOW_FLAG_VISIBLE);

    // TODO: Hide platform-specific window
}

void window_focus(window_t* window) {
    if (!window) {
        return;
    }

    g_focused_window = window;

    // TODO: Focus platform-specific window
}

void window_minimize(window_t* window) {
    if (!window) {
        return;
    }

    window_set_state(window, WINDOW_STATE_MINIMIZED);

    // TODO: Minimize platform-specific window
}

void window_maximize(window_t* window) {
    if (!window) {
        return;
    }

    window_set_state(window, WINDOW_STATE_MAXIMIZED);

    // TODO: Maximize platform-specific window
}

void window_restore(window_t* window) {
    if (!window) {
        return;
    }

    window_set_state(window, WINDOW_STATE_NORMAL);

    // TODO: Restore platform-specific window
}

void window_close(window_t* window) {
    if (!window) {
        return;
    }

    // TODO: Close platform-specific window

    window_destroy(window);
}

window_t* window_get_by_handle(void* handle) {
    if (!handle) {
        return NULL;
    }

    for (size_t i = 0; i < g_window_count; i++) {
        if (g_windows[i]->handle == handle) {
            return g_windows[i];
        }
    }

    return NULL;
}

window_t* window_get_focused(void) {
    return g_focused_window;
}

void window_cleanup(void) {
    if (!g_initialized) {
        return;
    }

    // Destroy all windows
    for (size_t i = 0; i < g_window_count; i++) {
        window_destroy(g_windows[i]);
    }

    free(g_windows);
    g_windows = NULL;
    g_window_count = 0;
    g_window_capacity = 0;
    g_focused_window = NULL;

    // TODO: Clean up platform-specific window system

 