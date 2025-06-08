#include "aceui_widget.h"
#include <stdlib.h>
#include <string.h>

// Global state
static bool g_initialized = false;
static widget_t* g_focused_widget = NULL;
static widget_t* g_hovered_widget = NULL;

// Default widget colors
static const color_t DEFAULT_BACKGROUND_COLOR = {0.95f, 0.95f, 0.95f, 1.0f};
static const color_t DEFAULT_FOREGROUND_COLOR = {0.0f, 0.0f, 0.0f, 1.0f};
static const color_t DEFAULT_BORDER_COLOR = {0.8f, 0.8f, 0.8f, 1.0f};

// Default widget properties
static const float DEFAULT_BORDER_WIDTH = 1.0f;
static const float DEFAULT_CORNER_RADIUS = 4.0f;

bool widget_init(void) {
    if (g_initialized) {
        return true;
    }

    // TODO: Initialize widget system
    // - Set up widget cache
    // - Initialize default styles
    // - Set up event queue

    g_initialized = true;
    return true;
}

widget_t* widget_create(const char* id, const char* text) {
    if (!g_initialized || !id) {
        return NULL;
    }

    widget_t* widget = (widget_t*)malloc(sizeof(widget_t));
    if (!widget) {
        return NULL;
    }

    // Initialize widget structure
    widget->id = strdup(id);
    widget->text = text ? strdup(text) : NULL;
    widget->bounds = (rect_t){0, 0, 0, 0};
    widget->background_color = DEFAULT_BACKGROUND_COLOR;
    widget->foreground_color = DEFAULT_FOREGROUND_COLOR;
    widget->border_color = DEFAULT_BORDER_COLOR;
    widget->border_width = DEFAULT_BORDER_WIDTH;
    widget->corner_radius = DEFAULT_CORNER_RADIUS;
    widget->font = NULL;
    widget->flags = WIDGET_FLAG_VISIBLE | WIDGET_FLAG_ENABLED;
    widget->user_data = NULL;
    widget->parent = NULL;
    widget->children = NULL;
    widget->child_count = 0;
    widget->child_capacity = 0;
    widget->on_event = NULL;
    widget->on_paint = NULL;

    return widget;
}

void widget_destroy(widget_t* widget) {
    if (!widget) {
        return;
    }

    // Destroy all children
    for (size_t i = 0; i < widget->child_count; i++) {
        widget_destroy(widget->children[i]);
    }

    // Free widget resources
    free(widget->children);
    free(widget->text);
    free(widget->id);
    free(widget);
}

bool widget_add_child(widget_t* parent, widget_t* child) {
    if (!parent || !child || child->parent) {
        return false;
    }

    // Resize children array if needed
    if (parent->child_count >= parent->child_capacity) {
        size_t new_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        widget_t** new_children = (widget_t**)realloc(parent->children, new_capacity * sizeof(widget_t*));
        if (!new_children) {
            return false;
        }
        parent->children = new_children;
        parent->child_capacity = new_capacity;
    }

    // Add child to parent
    parent->children[parent->child_count++] = child;
    child->parent = parent;

    return true;
}

bool widget_remove_child(widget_t* parent, widget_t* child) {
    if (!parent || !child || child->parent != parent) {
        return false;
    }

    // Find child index
    size_t index = 0;
    while (index < parent->child_count && parent->children[index] != child) {
        index++;
    }

    if (index == parent->child_count) {
        return false;
    }

    // Remove child from parent
    child->parent = NULL;
    memmove(&parent->children[index], &parent->children[index + 1],
            (parent->child_count - index - 1) * sizeof(widget_t*));
    parent->child_count--;

    return true;
}

void widget_set_text(widget_t* widget, const char* text) {
    if (!widget) {
        return;
    }

    free(widget->text);
    widget->text = text ? strdup(text) : NULL;
}

void widget_set_bounds(widget_t* widget, rect_t bounds) {
    if (!widget) {
        return;
    }

    widget->bounds = bounds;
}

void widget_set_colors(widget_t* widget, color_t background, color_t foreground, color_t border) {
    if (!widget) {
        return;
    }

    widget->background_color = background;
    widget->foreground_color = foreground;
    widget->border_color = border;
}

void widget_set_font(widget_t* widget, font_t* font) {
    if (!widget) {
        return;
    }

    widget->font = font;
}

void widget_set_flags(widget_t* widget, uint32_t flags) {
    if (!widget) {
        return;
    }

    widget->flags |= flags;
}

void widget_clear_flags(widget_t* widget, uint32_t flags) {
    if (!widget) {
        return;
    }

    widget->flags &= ~flags;
}

bool widget_has_flags(widget_t* widget, uint32_t flags) {
    return widget && (widget->flags & flags) == flags;
}

void widget_set_event_handler(widget_t* widget, void (*handler)(widget_t*, widget_event_t*)) {
    if (!widget) {
        return;
    }

    widget->on_event = handler;
}

void widget_set_paint_handler(widget_t* widget, void (*handler)(widget_t*)) {
    if (!widget) {
        return;
    }

    widget->on_paint = handler;
}

bool widget_process_event(widget_t* widget, widget_event_t* event) {
    if (!widget || !event) {
        return false;
    }

    // Process event in children first (bottom-up)
    for (size_t i = widget->child_count; i > 0; i--) {
        widget_t* child = widget->children[i - 1];
        if (widget_has_flags(child, WIDGET_FLAG_VISIBLE | WIDGET_FLAG_ENABLED)) {
            if (widget_process_event(child, event)) {
                return true;
            }
        }
    }

    // Process event in widget
    if (widget->on_event) {
        widget->on_event(widget, event);
        if (event->handled) {
            return true;
        }
    }

    return false;
}

void widget_paint(widget_t* widget) {
    if (!widget || !widget_has_flags(widget, WIDGET_FLAG_VISIBLE)) {
        return;
    }

    // Paint widget
    if (widget->on_paint) {
        widget->on_paint(widget);
    }

    // Paint children
    for (size_t i = 0; i < widget->child_count; i++) {
        widget_paint(widget->children[i]);
    }
}

widget_t* widget_find_by_id(widget_t* root, const char* id) {
    if (!root || !id) {
        return NULL;
    }

    // Check root widget
    if (strcmp(root->id, id) == 0) {
        return root;
    }

    // Check children
    for (size_t i = 0; i < root->child_count; i++) {
        widget_t* found = widget_find_by_id(root->children[i], id);
        if (found) {
            return found;
        }
    }

    return NULL;
}

void widget_cleanup(void) {
    if (!g_initialized) {
        return;
    }

    // TODO: Clean up widget system
    // - Clear widget cache
    // - Clean up event queue
    // - Free default styles

    g_initialized = false;
} 