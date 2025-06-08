#include "aceui_layout.h"
#include <stdlib.h>
#include <string.h>

// Global state
static bool g_initialized = false;

// Default layout properties
static const float DEFAULT_SPACING = 4.0f;
static const float DEFAULT_PADDING = 4.0f;
static const float DEFAULT_MIN_WIDTH = 0.0f;
static const float DEFAULT_MIN_HEIGHT = 0.0f;
static const float DEFAULT_MAX_WIDTH = 0.0f;
static const float DEFAULT_MAX_HEIGHT = 0.0f;
static const float DEFAULT_ASPECT_RATIO = 0.0f;

bool layout_init(void) {
    if (g_initialized) {
        return true;
    }

    // TODO: Initialize layout system
    // - Set up layout cache
    // - Initialize layout algorithms
    // - Set up layout event queue

    g_initialized = true;
    return true;
}

layout_t* layout_create(widget_t* widget) {
    if (!g_initialized || !widget) {
        return NULL;
    }

    layout_t* layout = (layout_t*)malloc(sizeof(layout_t));
    if (!layout) {
        return NULL;
    }

    // Initialize layout structure
    layout->widget = widget;
    layout->flags = LAYOUT_FLAG_NONE;
    layout->direction = LAYOUT_DIRECTION_HORIZONTAL;
    layout->alignment = LAYOUT_ALIGNMENT_START;
    layout->spacing = DEFAULT_SPACING;
    layout->padding = DEFAULT_PADDING;
    layout->min_width = DEFAULT_MIN_WIDTH;
    layout->min_height = DEFAULT_MIN_HEIGHT;
    layout->max_width = DEFAULT_MAX_WIDTH;
    layout->max_height = DEFAULT_MAX_HEIGHT;
    layout->aspect_ratio = DEFAULT_ASPECT_RATIO;

    return layout;
}

void layout_destroy(layout_t* layout) {
    if (!layout) {
        return;
    }

    free(layout);
}

void layout_set_flags(layout_t* layout, uint32_t flags) {
    if (!layout) {
        return;
    }

    layout->flags = flags;
}

void layout_set_direction(layout_t* layout, layout_direction_t direction) {
    if (!layout) {
        return;
    }

    layout->direction = direction;
}

void layout_set_alignment(layout_t* layout, layout_alignment_t alignment) {
    if (!layout) {
        return;
    }

    layout->alignment = alignment;
}

void layout_set_spacing(layout_t* layout, float spacing) {
    if (!layout) {
        return;
    }

    layout->spacing = spacing;
}

void layout_set_padding(layout_t* layout, float padding) {
    if (!layout) {
        return;
    }

    layout->padding = padding;
}

void layout_set_min_size(layout_t* layout, float width, float height) {
    if (!layout) {
        return;
    }

    layout->min_width = width;
    layout->min_height = height;
}

void layout_set_max_size(layout_t* layout, float width, float height) {
    if (!layout) {
        return;
    }

    layout->max_width = width;
    layout->max_height = height;
}

void layout_set_aspect_ratio(layout_t* layout, float aspect_ratio) {
    if (!layout) {
        return;
    }

    layout->aspect_ratio = aspect_ratio;
}

void layout_calculate(layout_t* layout) {
    if (!layout || !layout->widget) {
        return;
    }

    // Get widget bounds
    rect_t bounds = layout->widget->bounds;
    float width = bounds.width;
    float height = bounds.height;

    // Apply minimum size constraints
    if (layout->min_width > 0 && width < layout->min_width) {
        width = layout->min_width;
    }
    if (layout->min_height > 0 && height < layout->min_height) {
        height = layout->min_height;
    }

    // Apply maximum size constraints
    if (layout->max_width > 0 && width > layout->max_width) {
        width = layout->max_width;
    }
    if (layout->max_height > 0 && height > layout->max_height) {
        height = layout->max_height;
    }

    // Apply aspect ratio constraint
    if (layout->aspect_ratio > 0) {
        float current_ratio = width / height;
        if (current_ratio > layout->aspect_ratio) {
            width = height * layout->aspect_ratio;
        } else {
            height = width / layout->aspect_ratio;
        }
    }

    // Calculate available space for children
    float available_width = width - 2 * layout->padding;
    float available_height = height - 2 * layout->padding;

    // Calculate child sizes and positions
    if (layout->widget->child_count > 0) {
        if (layout->direction == LAYOUT_DIRECTION_HORIZONTAL) {
            // Calculate total spacing
            float total_spacing = layout->spacing * (layout->widget->child_count - 1);

            // Calculate child width
            float child_width = 0;
            if (layout->flags & LAYOUT_FLAG_FILL_WIDTH) {
                child_width = (available_width - total_spacing) / layout->widget->child_count;
            }

            // Position children
            float x = bounds.x + layout->padding;
            float y = bounds.y + layout->padding;

            for (size_t i = 0; i < layout->widget->child_count; i++) {
                widget_t* child = layout->widget->children[i];
                rect_t child_bounds = child->bounds;

                // Set child width
                if (layout->flags & LAYOUT_FLAG_FILL_WIDTH) {
                    child_bounds.width = child_width;
                }

                // Set child height
                if (layout->flags & LAYOUT_FLAG_FILL_HEIGHT) {
                    child_bounds.height = available_height;
                }

                // Align child vertically
                if (layout->flags & LAYOUT_FLAG_ALIGN_TOP) {
                    child_bounds.y = y;
                } else if (layout->flags & LAYOUT_FLAG_ALIGN_BOTTOM) {
                    child_bounds.y = y + available_height - child_bounds.height;
                } else if (layout->flags & LAYOUT_FLAG_ALIGN_MIDDLE) {
                    child_bounds.y = y + (available_height - child_bounds.height) / 2;
                }

                // Set child position
                child_bounds.x = x;
                widget_set_bounds(child, child_bounds);

                // Update x position for next child
                x += child_bounds.width + layout->spacing;
            }
        } else {
            // Calculate total spacing
            float total_spacing = layout->spacing * (layout->widget->child_count - 1);

            // Calculate child height
            float child_height = 0;
            if (layout->flags & LAYOUT_FLAG_FILL_HEIGHT) {
                child_height = (available_height - total_spacing) / layout->widget->child_count;
            }

            // Position children
            float x = bounds.x + layout->padding;
            float y = bounds.y + layout->padding;

            for (size_t i = 0; i < layout->widget->child_count; i++) {
                widget_t* child = layout->widget->children[i];
                rect_t child_bounds = child->bounds;

                // Set child width
                if (layout->flags & LAYOUT_FLAG_FILL_WIDTH) {
                    child_bounds.width = available_width;
                }

                // Set child height
                if (layout->flags & LAYOUT_FLAG_FILL_HEIGHT) {
                    child_bounds.height = child_height;
                }

                // Align child horizontally
                if (layout->flags & LAYOUT_FLAG_ALIGN_LEFT) {
                    child_bounds.x = x;
                } else if (layout->flags & LAYOUT_FLAG_ALIGN_RIGHT) {
                    child_bounds.x = x + available_width - child_bounds.width;
                } else if (layout->flags & LAYOUT_FLAG_ALIGN_CENTER) {
                    child_bounds.x = x + (available_width - child_bounds.width) / 2;
                }

                // Set child position
                child_bounds.y = y;
                widget_set_bounds(child, child_bounds);

                // Update y position for next child
                y += child_bounds.height + layout->spacing;
            }
        }
    }
}

void layout_cleanup(void) {
    if (!g_initialized) {
        return;
    }

    // TODO: Clean up layout system
    // - Clear layout cache
    // - Clean up layout algorithms
    // - Clean up layout event queue

    g_initialized = false;
} 