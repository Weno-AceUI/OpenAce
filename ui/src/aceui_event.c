#include "aceui_event.h"
#include <stdlib.h>
#include <string.h>

// Global state
static bool g_initialized = false;

// Event handler structure
typedef struct {
    event_handler_t handler;      // Event handler function
    void* user_data;             // User data for handler
} event_handler_info_t;

// Event handler table
typedef struct {
    event_handler_info_t* handlers;  // Array of handlers
    size_t count;                    // Number of handlers
    size_t capacity;                 // Handler array capacity
} event_handler_table_t;

// Initialize event system
bool event_init(void) {
    if (g_initialized) {
        return true;
    }

    // TODO: Initialize event system resources
    g_initialized = true;
    return true;
}

// Register event handler
bool event_register_handler(widget_t* widget, event_type_t type, event_handler_t handler, void* user_data) {
    if (!g_initialized || !widget || !handler || type >= EVENT_COUNT) {
        return false;
    }

    // Get or create handler table for widget
    event_handler_table_t* table = (event_handler_table_t*)widget->event_handlers;
    if (!table) {
        table = (event_handler_table_t*)malloc(sizeof(event_handler_table_t));
        if (!table) {
            return false;
        }
        table->handlers = NULL;
        table->count = 0;
        table->capacity = 0;
        widget->event_handlers = table;
    }

    // Resize handler array if needed
    if (table->count >= table->capacity) {
        size_t new_capacity = table->capacity == 0 ? 8 : table->capacity * 2;
        event_handler_info_t* new_handlers = (event_handler_info_t*)realloc(table->handlers,
            new_capacity * sizeof(event_handler_info_t));
        if (!new_handlers) {
            return false;
        }
        table->handlers = new_handlers;
        table->capacity = new_capacity;
    }

    // Add handler
    event_handler_info_t* info = &table->handlers[table->count++];
    info->handler = handler;
    info->user_data = user_data;

    return true;
}

// Unregister event handler
void event_unregister_handler(widget_t* widget, event_type_t type) {
    if (!g_initialized || !widget) {
        return;
    }

    event_handler_table_t* table = (event_handler_table_t*)widget->event_handlers;
    if (!table) {
        return;
    }

    // Find and remove handler
    for (size_t i = 0; i < table->count; i++) {
        if (table->handlers[i].handler) {
            table->handlers[i].handler = NULL;
            table->handlers[i].user_data = NULL;
            break;
        }
    }
}

// Process event
void event_process(event_t* event) {
    if (!g_initialized || !event || !event->target) {
        return;
    }

    // Get handler table
    event_handler_table_t* table = (event_handler_table_t*)event->target->event_handlers;
    if (!table) {
        return;
    }

    // Call handlers
    for (size_t i = 0; i < table->count; i++) {
        event_handler_info_t* info = &table->handlers[i];
        if (info->handler) {
            info->handler(event, info->user_data);
        }
    }
}

// Create mouse event
event_t event_create_mouse(event_type_t type, widget_t* target, int x, int y, int buttons, int modifiers) {
    event_t event;
    memset(&event, 0, sizeof(event));
    event.type = type;
    event.target = target;
    event.source = target;
    event.data.mouse.x = x;
    event.data.mouse.y = y;
    event.data.mouse.buttons = buttons;
    event.data.mouse.modifiers = modifiers;
    return event;
}

// Create keyboard event
event_t event_create_keyboard(event_type_t type, widget_t* target, int key, int modifiers, bool repeat) {
    event_t event;
    memset(&event, 0, sizeof(event));
    event.type = type;
    event.target = target;
    event.source = target;
    event.data.key.key = key;
    event.data.key.modifiers = modifiers;
    event.data.key.repeat = repeat;
    return event;
}

// Create move event
event_t event_create_move(widget_t* target, int x, int y) {
    event_t event;
    memset(&event, 0, sizeof(event));
    event.type = EVENT_MOVE;
    event.target = target;
    event.source = target;
    event.data.move.x = x;
    event.data.move.y = y;
    return event;
}

// Create resize event
event_t event_create_resize(widget_t* target, int width, int height) {
    event_t event;
    memset(&event, 0, sizeof(event));
    event.type = EVENT_RESIZE;
    event.target = target;
    event.source = target;
    event.data.resize.width = width;
    event.data.resize.height = height;
    return event;
}

// Create custom event
event_t event_create_custom(widget_t* target, void* data) {
    event_t event;
    memset(&event, 0, sizeof(event));
    event.type = EVENT_CUSTOM;
    event.target = target;
    event.source = target;
    event.data.custom.data = data;
    return event;
}

// Clean up event system
void event_cleanup(void) {
    if (!g_initialized) {
        return;
    }

    // TODO: Clean up event system resources
    g_initialized = false;
} 