#ifndef ACEUI_ANIMATION_H
#define ACEUI_ANIMATION_H

#include "aceui.h"
#include "aceui_widget.h"

// Animation easing functions
typedef enum {
    EASING_LINEAR,
    EASING_QUAD_IN,
    EASING_QUAD_OUT,
    EASING_QUAD_IN_OUT,
    EASING_CUBIC_IN,
    EASING_CUBIC_OUT,
    EASING_CUBIC_IN_OUT,
    EASING_ELASTIC_IN,
    EASING_ELASTIC_OUT,
    EASING_ELASTIC_IN_OUT,
    EASING_BOUNCE_IN,
    EASING_BOUNCE_OUT,
    EASING_BOUNCE_IN_OUT,
    EASING_COUNT
} easing_function_t;

// Animation property types
typedef enum {
    ANIMATION_PROPERTY_NONE,
    ANIMATION_PROPERTY_POSITION,
    ANIMATION_PROPERTY_SIZE,
    ANIMATION_PROPERTY_COLOR,
    ANIMATION_PROPERTY_ALPHA,
    ANIMATION_PROPERTY_ROTATION,
    ANIMATION_PROPERTY_SCALE,
    ANIMATION_PROPERTY_COUNT
} animation_property_t;

// Animation structure
typedef struct {
    widget_t* widget;              // Target widget
    animation_property_t property; // Property to animate
    easing_function_t easing;      // Easing function
    float duration;                // Animation duration in seconds
    float delay;                   // Delay before starting in seconds
    float start_value;             // Start value
    float end_value;               // End value
    float current_time;            // Current animation time
    bool is_running;               // Whether animation is running
    bool is_looping;               // Whether animation should loop
    void (*on_complete)(void*);    // Callback when animation completes
    void* user_data;               // User data for callback
} animation_t;

// Initialize animation system
bool animation_init(void);

// Create animation
animation_t* animation_create(widget_t* widget, animation_property_t property);

// Destroy animation
void animation_destroy(animation_t* animation);

// Set animation properties
void animation_set_easing(animation_t* animation, easing_function_t easing);
void animation_set_duration(animation_t* animation, float duration);
void animation_set_delay(animation_t* animation, float delay);
void animation_set_values(animation_t* animation, float start_value, float end_value);
void animation_set_looping(animation_t* animation, bool is_looping);
void animation_set_callback(animation_t* animation, void (*on_complete)(void*), void* user_data);

// Start animation
void animation_start(animation_t* animation);

// Stop animation
void animation_stop(animation_t* animation);

// Pause animation
void animation_pause(animation_t* animation);

// Resume animation
void animation_resume(animation_t* animation);

// Update animation
void animation_update(animation_t* animation, float delta_time);

// Get animation progress
float animation_get_progress(animation_t* animation);

// Get animation is running
bool animation_is_running(animation_t* animation);

// Clean up animation system
void animation_cleanup(void);

#endif // ACEUI_ANIMATION_H 