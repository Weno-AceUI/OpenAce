#include "aceui.h"
#include "memory.h"
#include <string.h>

// Global state
static window_t* active_window = NULL;
static window_t* focused_window = NULL;
static widget_t* focused_widget = NULL;
static bool initialized = false;

// Initialize AceUI framework
void aceui_init(void) {
    if (initialized) return;

    // Initialize graphics system
    // TODO: Initialize graphics system

    // Initialize input system
    // TODO: Initialize input system

    // Initialize font system
    // TODO: Initialize font system

    initialized = true;
}

// Create a new window
window_t* aceui_create_window(const char* title, rect_t bounds, uint32_t flags) {
    window_t* window = (window_t*)memory_alloc(sizeof(window_t));
    if (!window) return NULL;

    // Initialize base widget
    window->base.type = WIDGET_WINDOW;
    window->base.bounds = bounds;
    window->base.visible = true;
    window->base.enabled = true;
    window->base.focused = false;
    window->base.text = NULL;
    window->base.background = (color_t){255, 255, 255, 255};
    window->base.foreground = (color_t){0, 0, 0, 255};
    window->base.parent = NULL;
    window->base.first_child = NULL;
    window->base.last_child = NULL;
    window->base.next_sibling = NULL;
    window->base.prev_sibling = NULL;
    window->base.on_event = NULL;
    window->base.user_data = NULL;

    // Initialize window-specific fields
    window->flags = flags;
    window->title = strdup(title);
    window->minimized = false;
    window->maximized = false;
    window->fullscreen = false;
    window->normal_bounds = bounds;

    // Add window to window list
    if (!active_window) {
        active_window = window;
    }

    return window;
}

// Create a new widget
widget_t* aceui_create_widget(widget_type_t type, rect_t bounds) {
    widget_t* widget = (widget_t*)memory_alloc(sizeof(widget_t));
    if (!widget) return NULL;

    // Initialize widget
    widget->type = type;
    widget->bounds = bounds;
    widget->visible = true;
    widget->enabled = true;
    widget->focused = false;
    widget->text = NULL;
    widget->background = (color_t){255, 255, 255, 255};
    widget->foreground = (color_t){0, 0, 0, 255};
    widget->parent = NULL;
    widget->first_child = NULL;
    widget->last_child = NULL;
    widget->next_sibling = NULL;
    widget->prev_sibling = NULL;
    widget->on_event = NULL;
    widget->user_data = NULL;

    return widget;
}

// Add a widget to a parent
void aceui_add_widget(widget_t* parent, widget_t* child) {
    if (!parent || !child) return;

    // Remove child from its current parent
    if (child->parent) {
        aceui_remove_widget(child);
    }

    // Add child to parent
    child->parent = parent;
    child->next_sibling = NULL;
    child->prev_sibling = parent->last_child;

    if (parent->last_child) {
        parent->last_child->next_sibling = child;
    } else {
        parent->first_child = child;
    }

    parent->last_child = child;
}

// Remove a widget from its parent
void aceui_remove_widget(widget_t* widget) {
    if (!widget || !widget->parent) return;

    // Update parent's child pointers
    if (widget->prev_sibling) {
        widget->prev_sibling->next_sibling = widget->next_sibling;
    } else {
        widget->parent->first_child = widget->next_sibling;
    }

    if (widget->next_sibling) {
        widget->next_sibling->prev_sibling = widget->prev_sibling;
    } else {
        widget->parent->last_child = widget->prev_sibling;
    }

    widget->parent = NULL;
    widget->next_sibling = NULL;
    widget->prev_sibling = NULL;
}

// Set widget text
void aceui_set_text(widget_t* widget, const char* text) {
    if (!widget) return;

    if (widget->text) {
        memory_free(widget->text);
    }

    widget->text = text ? strdup(text) : NULL;
}

// Set widget colors
void aceui_set_colors(widget_t* widget, color_t background, color_t foreground) {
    if (!widget) return;

    widget->background = background;
    widget->foreground = foreground;
}

// Set widget position
void aceui_set_position(widget_t* widget, int32_t x, int32_t y) {
    if (!widget) return;

    widget->bounds.x = x;
    widget->bounds.y = y;
}

// Set widget size
void aceui_set_size(widget_t* widget, int32_t width, int32_t height) {
    if (!widget) return;

    widget->bounds.width = width;
    widget->bounds.height = height;
}

// Set widget bounds
void aceui_set_bounds(widget_t* widget, rect_t bounds) {
    if (!widget) return;

    widget->bounds = bounds;
}

// Show widget
void aceui_show(widget_t* widget) {
    if (!widget) return;

    widget->visible = true;
}

// Hide widget
void aceui_hide(widget_t* widget) {
    if (!widget) return;

    widget->visible = false;
}

// Enable widget
void aceui_enable(widget_t* widget) {
    if (!widget) return;

    widget->enabled = true;
}

// Disable widget
void aceui_disable(widget_t* widget) {
    if (!widget) return;

    widget->enabled = false;
}

// Focus widget
void aceui_focus(widget_t* widget) {
    if (!widget) return;

    // Unfocus current widget
    if (focused_widget) {
        focused_widget->focused = false;
        if (focused_widget->on_event) {
            event_t event = {EVENT_BLUR};
            focused_widget->on_event(focused_widget, &event);
        }
    }

    // Focus new widget
    focused_widget = widget;
    widget->focused = true;
    if (widget->on_event) {
        event_t event = {EVENT_FOCUS};
        widget->on_event(widget, &event);
    }

    // Update focused window
    if (widget->type == WIDGET_WINDOW) {
        focused_window = (window_t*)widget;
    } else if (widget->parent) {
        widget_t* parent = widget->parent;
        while (parent && parent->type != WIDGET_WINDOW) {
            parent = parent->parent;
        }
        if (parent) {
            focused_window = (window_t*)parent;
        }
    }
}

// Process events
void aceui_process_events(void) {
    // TODO: Process input events
    // TODO: Handle window management events
    // TODO: Handle widget events
}

// Render UI
void aceui_render(void) {
    // TODO: Render windows and widgets
    // TODO: Handle window composition
    // TODO: Apply visual effects
}

// Clean up AceUI framework
void aceui_cleanup(void) {
    if (!initialized) return;

    // TODO: Clean up graphics system
    // TODO: Clean up input system
    // TODO: Clean up font system

    initialized = false;
} 