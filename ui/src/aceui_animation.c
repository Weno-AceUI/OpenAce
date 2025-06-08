#include "aceui_animation.h"
#include <stdlib.h>
#include <math.h>

// Global state
static bool g_initialized = false;

// Easing functions
static float ease_linear(float t) {
    return t;
}

static float ease_quad_in(float t) {
    return t * t;
}

static float ease_quad_out(float t) {
    return t * (2.0f - t);
}

static float ease_quad_in_out(float t) {
    return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
}

static float ease_cubic_in(float t) {
    return t * t * t;
}

static float ease_cubic_out(float t) {
    float f = t - 1.0f;
    return f * f * f + 1.0f;
}

static float ease_cubic_in_out(float t) {
    return t < 0.5f ? 4.0f * t * t * t : (t - 1.0f) * (2.0f * t - 2.0f) * (2.0f * t - 2.0f) + 1.0f;
}

static float ease_elastic_in(float t) {
    float c4 = (2.0f * M_PI) / 3.0f;
    return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : -powf(2.0f, 10.0f * t - 10.0f) * sinf((t * 10.0f - 10.75f) * c4);
}

static float ease_elastic_out(float t) {
    float c4 = (2.0f * M_PI) / 3.0f;
    return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : powf(2.0f, -10.0f * t) * sinf((t * 10.0f - 0.75f) * c4) + 1.0f;
}

static float ease_elastic_in_out(float t) {
    float c5 = (2.0f * M_PI) / 4.5f;
    return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : t < 0.5f ? -(powf(2.0f, 20.0f * t - 10.0f) * sinf((20.0f * t - 11.125f) * c5)) / 2.0f : (powf(2.0f, -20.0f * t + 10.0f) * sinf((20.0f * t - 11.125f) * c5)) / 2.0f + 1.0f;
}

static float ease_bounce_in(float t) {
    return 1.0f - ease_bounce_out(1.0f - t);
}

static float ease_bounce_out(float t) {
    const float n1 = 7.5625f;
    const float d1 = 2.75f;
    if (t < 1.0f / d1) {
        return n1 * t * t;
    } else if (t < 2.0f / d1) {
        return n1 * (t -= 1.5f / d1) * t + 0.75f;
    } else if (t < 2.5f / d1) {
        return n1 * (t -= 2.25f / d1) * t + 0.9375f;
    } else {
        return n1 * (t -= 2.625f / d1) * t + 0.984375f;
    }
}

static float ease_bounce_in_out(float t) {
    return t < 0.5f ? (1.0f - ease_bounce_out(1.0f - 2.0f * t)) / 2.0f : (1.0f + ease_bounce_out(2.0f * t - 1.0f)) / 2.0f;
}

// Easing function table
static float (*easing_functions[EASING_COUNT])(float) = {
    ease_linear,
    ease_quad_in,
    ease_quad_out,
    ease_quad_in_out,
    ease_cubic_in,
    ease_cubic_out,
    ease_cubic_in_out,
    ease_elastic_in,
    ease_elastic_out,
    ease_elastic_in_out,
    ease_bounce_in,
    ease_bounce_out,
    ease_bounce_in_out
};

// Initialize animation system
bool animation_init(void) {
    if (g_initialized) {
        return true;
    }

    // TODO: Initialize animation system resources
    g_initialized = true;
    return true;
}

// Create animation
animation_t* animation_create(widget_t* widget, animation_property_t property) {
    if (!g_initialized || !widget) {
        return NULL;
    }

    animation_t* animation = (animation_t*)malloc(sizeof(animation_t));
    if (!animation) {
        return NULL;
    }

    animation->widget = widget;
    animation->property = property;
    animation->easing = EASING_LINEAR;
    animation->duration = 1.0f;
    animation->delay = 0.0f;
    animation->start_value = 0.0f;
    animation->end_value = 1.0f;
    animation->current_time = 0.0f;
    animation->is_running = false;
    animation->is_looping = false;
    animation->on_complete = NULL;
    animation->user_data = NULL;

    return animation;
}

// Destroy animation
void animation_destroy(animation_t* animation) {
    if (!animation) {
        return;
    }

    free(animation);
}

// Set animation properties
void animation_set_easing(animation_t* animation, easing_function_t easing) {
    if (!animation || easing >= EASING_COUNT) {
        return;
    }
    animation->easing = easing;
}

void animation_set_duration(animation_t* animation, float duration) {
    if (!animation || duration < 0.0f) {
        return;
    }
    animation->duration = duration;
}

void animation_set_delay(animation_t* animation, float delay) {
    if (!animation || delay < 0.0f) {
        return;
    }
    animation->delay = delay;
}

void animation_set_values(animation_t* animation, float start_value, float end_value) {
    if (!animation) {
        return;
    }
    animation->start_value = start_value;
    animation->end_value = end_value;
}

void animation_set_looping(animation_t* animation, bool is_looping) {
    if (!animation) {
        return;
    }
    animation->is_looping = is_looping;
}

void animation_set_callback(animation_t* animation, void (*on_complete)(void*), void* user_data) {
    if (!animation) {
        return;
    }
    animation->on_complete = on_complete;
    animation->user_data = user_data;
}

// Start animation
void animation_start(animation_t* animation) {
    if (!animation) {
        return;
    }
    animation->current_time = 0.0f;
    animation->is_running = true;
}

// Stop animation
void animation_stop(animation_t* animation) {
    if (!animation) {
        return;
    }
    animation->is_running = false;
}

// Pause animation
void animation_pause(animation_t* animation) {
    if (!animation) {
        return;
    }
    animation->is_running = false;
}

// Resume animation
void animation_resume(animation_t* animation) {
    if (!animation) {
        return;
    }
    animation->is_running = true;
}

// Update animation
void animation_update(animation_t* animation, float delta_time) {
    if (!animation || !animation->is_running) {
        return;
    }

    // Handle delay
    if (animation->delay > 0.0f) {
        animation->delay -= delta_time;
        return;
    }

    // Update time
    animation->current_time += delta_time;
    float progress = animation->current_time / animation->duration;

    // Check if animation is complete
    if (progress >= 1.0f) {
        if (animation->is_looping) {
            animation->current_time = 0.0f;
            progress = 0.0f;
        } else {
            animation->is_running = false;
            progress = 1.0f;
            if (animation->on_complete) {
                animation->on_complete(animation->user_data);
            }
        }
    }

    // Apply easing
    float eased_progress = easing_functions[animation->easing](progress);

    // Calculate current value
    float current_value = animation->start_value + (animation->end_value - animation->start_value) * eased_progress;

    // Apply to widget
    switch (animation->property) {
        case ANIMATION_PROPERTY_POSITION:
            // TODO: Update widget position
            break;
        case ANIMATION_PROPERTY_SIZE:
            // TODO: Update widget size
            break;
        case ANIMATION_PROPERTY_COLOR:
            // TODO: Update widget color
            break;
        case ANIMATION_PROPERTY_ALPHA:
            // TODO: Update widget alpha
            break;
        case ANIMATION_PROPERTY_ROTATION:
            // TODO: Update widget rotation
            break;
        case ANIMATION_PROPERTY_SCALE:
            // TODO: Update widget scale
            break;
        default:
            break;
    }
}

// Get animation progress
float animation_get_progress(animation_t* animation) {
    if (!animation) {
        return 0.0f;
    }
    return animation->current_time / animation->duration;
}

// Get animation is running
bool animation_is_running(animation_t* animation) {
    if (!animation) {
        return false;
    }
    return animation->is_running;
}

// Clean up animation system
void animation_cleanup(void) {
    if (!g_initialized) {
        return;
    }

    // TODO: Clean up animation system resources
    g_initialized = false;
} 