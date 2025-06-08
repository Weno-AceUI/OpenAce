#ifndef ACEUI_LAYOUT_H
#define ACEUI_LAYOUT_H

#include "aceui.h"
#include "aceui_widget.h"

// Layout flags
#define LAYOUT_FLAG_NONE          0x00000000
#define LAYOUT_FLAG_FILL_WIDTH    0x00000001
#define LAYOUT_FLAG_FILL_HEIGHT   0x00000002
#define LAYOUT_FLAG_EXPAND_WIDTH  0x00000004
#define LAYOUT_FLAG_EXPAND_HEIGHT 0x00000008
#define LAYOUT_FLAG_ALIGN_LEFT    0x00000010
#define LAYOUT_FLAG_ALIGN_RIGHT   0x00000020
#define LAYOUT_FLAG_ALIGN_TOP     0x00000040
#define LAYOUT_FLAG_ALIGN_BOTTOM  0x00000080
#define LAYOUT_FLAG_ALIGN_CENTER  0x00000100
#define LAYOUT_FLAG_ALIGN_MIDDLE  0x00000200

// Layout direction
typedef enum {
    LAYOUT_DIRECTION_HORIZONTAL,
    LAYOUT_DIRECTION_VERTICAL
} layout_direction_t;

// Layout alignment
typedef enum {
    LAYOUT_ALIGNMENT_START,
    LAYOUT_ALIGNMENT_CENTER,
    LAYOUT_ALIGNMENT_END,
    LAYOUT_ALIGNMENT_SPACE_BETWEEN,
    LAYOUT_ALIGNMENT_SPACE_AROUND,
    LAYOUT_ALIGNMENT_SPACE_EVENLY
} layout_alignment_t;

// Layout structure
typedef struct {
    widget_t* widget;           // Widget to layout
    uint32_t flags;            // Layout flags
    layout_direction_t direction; // Layout direction
    layout_alignment_t alignment; // Layout alignment
    float spacing;             // Spacing between items
    float padding;             // Padding around items
    float min_width;           // Minimum width
    float min_height;          // Minimum height
    float max_width;           // Maximum width
    float max_height;          // Maximum height
    float aspect_ratio;        // Aspect ratio (width / height)
} layout_t;

// Initialize layout system
bool layout_init(void);

// Create layout
layout_t* layout_create(widget_t* widget);

// Destroy layout
void layout_destroy(layout_t* layout);

// Set layout flags
void layout_set_flags(layout_t* layout, uint32_t flags);

// Set layout direction
void layout_set_direction(layout_t* layout, layout_direction_t direction);

// Set layout alignment
void layout_set_alignment(layout_t* layout, layout_alignment_t alignment);

// Set layout spacing
void layout_set_spacing(layout_t* layout, float spacing);

// Set layout padding
void layout_set_padding(layout_t* layout, float padding);

// Set layout minimum size
void layout_set_min_size(layout_t* layout, float width, float height);

// Set layout maximum size
void layout_set_max_size(layout_t* layout, float width, float height);

// Set layout aspect ratio
void layout_set_aspect_ratio(layout_t* layout, float aspect_ratio);

// Calculate layout
void layout_calculate(layout_t* layout);

// Clean up layout system
void layout_cleanup(void);

#endif // ACEUI_LAYOUT_H 