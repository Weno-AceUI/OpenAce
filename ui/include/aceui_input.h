#ifndef ACEUI_INPUT_H
#define ACEUI_INPUT_H

#include "aceui.h"
#include "aceui_widget.h"
#include "aceui_event.h"

// Mouse button flags
#define MOUSE_BUTTON_NONE  0x00000000
#define MOUSE_BUTTON_LEFT  0x00000001
#define MOUSE_BUTTON_RIGHT 0x00000002
#define MOUSE_BUTTON_MIDDLE 0x00000004

// Key codes
typedef enum {
    KEY_NONE,
    KEY_ESCAPE,
    KEY_ENTER,
    KEY_TAB,
    KEY_BACKSPACE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK,
    KEY_NUM_LOCK,
    KEY_PRINT_SCREEN,
    KEY_PAUSE,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_LEFT_CONTROL,
    KEY_LEFT_SHIFT,
    KEY_LEFT_ALT,
    KEY_LEFT_SUPER,
    KEY_RIGHT_CONTROL,
    KEY_RIGHT_SHIFT,
    KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER,
    KEY_MENU,
    KEY_COUNT
} key_code_t;

// Key modifier flags
#define KEY_MODIFIER_NONE  0x00000000
#define KEY_MODIFIER_SHIFT 0x00000001
#define KEY_MODIFIER_CTRL  0x00000002
#define KEY_MODIFIER_ALT   0x00000004
#define KEY_MODIFIER_SUPER 0x00000008

// Initialize input system
bool input_init(void);

// Process input events
void input_process(void);

// Get mouse position
void input_get_mouse_position(int* x, int* y);

// Get mouse button state
bool input_is_mouse_button_down(int button);

// Get key state
bool input_is_key_down(key_code_t key);

// Get key modifiers
int input_get_key_modifiers(void);

// Set mouse position
void input_set_mouse_position(int x, int y);

// Set mouse button state
void input_set_mouse_button(int button, bool down);

// Set key state
void input_set_key(key_code_t key, bool down);

// Set key modifiers
void input_set_key_modifiers(int modifiers);

// Show cursor
void input_show_cursor(void);

// Hide cursor
void input_hide_cursor(void);

// Clean up input system
void input_cleanup(void);

#endif // ACEUI_INPUT_H 