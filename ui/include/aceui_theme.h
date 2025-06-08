#ifndef ACEUI_THEME_H
#define ACEUI_THEME_H

#include "aceui.h"

// Theme color roles
typedef enum {
    THEME_COLOR_WINDOW_BACKGROUND,
    THEME_COLOR_WINDOW_FOREGROUND,
    THEME_COLOR_WINDOW_BORDER,
    THEME_COLOR_WIDGET_BACKGROUND,
    THEME_COLOR_WIDGET_FOREGROUND,
    THEME_COLOR_WIDGET_BORDER,
    THEME_COLOR_WIDGET_HOVER_BACKGROUND,
    THEME_COLOR_WIDGET_HOVER_FOREGROUND,
    THEME_COLOR_WIDGET_HOVER_BORDER,
    THEME_COLOR_WIDGET_PRESSED_BACKGROUND,
    THEME_COLOR_WIDGET_PRESSED_FOREGROUND,
    THEME_COLOR_WIDGET_PRESSED_BORDER,
    THEME_COLOR_WIDGET_FOCUSED_BACKGROUND,
    THEME_COLOR_WIDGET_FOCUSED_FOREGROUND,
    THEME_COLOR_WIDGET_FOCUSED_BORDER,
    THEME_COLOR_WIDGET_DISABLED_BACKGROUND,
    THEME_COLOR_WIDGET_DISABLED_FOREGROUND,
    THEME_COLOR_WIDGET_DISABLED_BORDER,
    THEME_COLOR_TEXT,
    THEME_COLOR_TEXT_DISABLED,
    THEME_COLOR_TEXT_SELECTED,
    THEME_COLOR_TEXT_SELECTED_BACKGROUND,
    THEME_COLOR_LINK,
    THEME_COLOR_LINK_HOVER,
    THEME_COLOR_LINK_PRESSED,
    THEME_COLOR_SCROLLBAR_BACKGROUND,
    THEME_COLOR_SCROLLBAR_THUMB,
    THEME_COLOR_SCROLLBAR_THUMB_HOVER,
    THEME_COLOR_SCROLLBAR_THUMB_PRESSED,
    THEME_COLOR_MENU_BACKGROUND,
    THEME_COLOR_MENU_FOREGROUND,
    THEME_COLOR_MENU_BORDER,
    THEME_COLOR_MENU_SELECTED_BACKGROUND,
    THEME_COLOR_MENU_SELECTED_FOREGROUND,
    THEME_COLOR_MENU_DISABLED_FOREGROUND,
    THEME_COLOR_TOOLTIP_BACKGROUND,
    THEME_COLOR_TOOLTIP_FOREGROUND,
    THEME_COLOR_TOOLTIP_BORDER,
    THEME_COLOR_COUNT
} theme_color_role_t;

// Theme dimension roles
typedef enum {
    THEME_DIM_WINDOW_BORDER_WIDTH,
    THEME_DIM_WINDOW_CORNER_RADIUS,
    THEME_DIM_WIDGET_BORDER_WIDTH,
    THEME_DIM_WIDGET_CORNER_RADIUS,
    THEME_DIM_WIDGET_PADDING,
    THEME_DIM_WIDGET_SPACING,
    THEME_DIM_MENU_PADDING,
    THEME_DIM_MENU_SPACING,
    THEME_DIM_TOOLTIP_PADDING,
    THEME_DIM_TOOLTIP_BORDER_WIDTH,
    THEME_DIM_TOOLTIP_CORNER_RADIUS,
    THEME_DIM_SCROLLBAR_WIDTH,
    THEME_DIM_SCROLLBAR_THUMB_MIN_SIZE,
    THEME_DIM_COUNT
} theme_dimension_role_t;

// Theme font roles
typedef enum {
    THEME_FONT_WINDOW_TITLE,
    THEME_FONT_WIDGET,
    THEME_FONT_MENU,
    THEME_FONT_TOOLTIP,
    THEME_FONT_COUNT
} theme_font_role_t;

// Theme structure
typedef struct {
    char* name;                    // Theme name
    color_t colors[THEME_COLOR_COUNT]; // Theme colors
    float dimensions[THEME_DIM_COUNT]; // Theme dimensions
    font_t* fonts[THEME_FONT_COUNT];  // Theme fonts
} theme_t;

// Initialize theme system
bool theme_init(void);

// Create theme
theme_t* theme_create(const char* name);

// Load theme from file
theme_t* theme_load(const char* filename);

// Save theme to file
bool theme_save(theme_t* theme, const char* filename);

// Set theme color
void theme_set_color(theme_t* theme, theme_color_role_t role, color_t color);

// Get theme color
color_t theme_get_color(theme_t* theme, theme_color_role_t role);

// Set theme dimension
void theme_set_dimension(theme_t* theme, theme_dimension_role_t role, float value);

// Get theme dimension
float theme_get_dimension(theme_t* theme, theme_dimension_role_t role);

// Set theme font
void theme_set_font(theme_t* theme, theme_font_role_t role, font_t* font);

// Get theme font
font_t* theme_get_font(theme_t* theme, theme_font_role_t role);

// Apply theme to window
void theme_apply_to_window(theme_t* theme, window_t* window);

// Apply theme to widget
void theme_apply_to_widget(theme_t* theme, widget_t* widget);

// Destroy theme
void theme_destroy(theme_t* theme);

// Clean up theme system
void theme_cleanup(void);

#endif // ACEUI_THEME_H 