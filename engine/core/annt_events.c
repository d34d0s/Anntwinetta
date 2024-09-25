#include "../include/annt_events.h"

void at_update_keyboard_state() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i) {
        bool isCurrentlyPressed = state[i];
        at_keyboard_state[i].justReleased = at_keyboard_state[i].isPressed && !isCurrentlyPressed;
        at_keyboard_state[i].wasPressed = at_keyboard_state[i].isPressed; // Store last frame's state
        at_keyboard_state[i].isPressed = isCurrentlyPressed;
    }
}

bool at_is_key_pressed(int keyCode) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[keyCode];
}

bool at_is_key_released(int keyCode) {
    return at_keyboard_state[keyCode].justReleased;
}

bool at_is_key_triggered(int keyCode) {
    return !at_keyboard_state[keyCode].wasPressed && at_keyboard_state[keyCode].isPressed;
}

void at_update_mouse_button_state() {
    at_mouse_state->scrollValue = 0;

    for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i) {
        at_mouse_state[i].wasPressed = at_mouse_state[i].isPressed;
    }
}

bool at_is_mouse_button_pressed(int button) {
    if (button - 1 < 0 || button - 1 >= MAX_MOUSE_BUTTONS)
        return false;

    return at_mouse_state[button - 1].isPressed;
}

bool at_is_mouse_button_triggered(int button) {
    if (button - 1 < 0 || button - 1 >= MAX_MOUSE_BUTTONS)
        return false;

    return !at_mouse_state[button - 1].wasPressed && at_mouse_state[button - 1].isPressed;
}

bool at_is_mouse_wheel_scrolled_up() {
    if (at_mouse_state->scrollValue > 0) {
        at_mouse_state->scrollValue = 0;
        return true;
    } else {
        return false;
    }
}

bool at_is_mouse_wheel_scrolled_down() {
    if (at_mouse_state->scrollValue < 0) {
        at_mouse_state->scrollValue = 0;
        return true;
    } else {
        return false;
    }
}

at_event_t *at_make_event_structure() {
    at_event_t *event = (at_event_t *)malloc(sizeof(at_event_t));
    if (!event) { _at_log_error("failed to create engine event structure"); return NULL; }
    return event;
}
