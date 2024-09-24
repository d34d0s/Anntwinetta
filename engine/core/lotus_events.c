#include "../include/lotus_events.h"

void lotus_update_keyboard_state() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i) {
        bool isCurrentlyPressed = state[i];
        lotus_keyboard_state[i].justReleased = lotus_keyboard_state[i].isPressed && !isCurrentlyPressed;
        lotus_keyboard_state[i].wasPressed = lotus_keyboard_state[i].isPressed; // Store last frame's state
        lotus_keyboard_state[i].isPressed = isCurrentlyPressed;
    }
}

bool lotus_is_key_pressed(int keyCode) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[keyCode];
}

bool lotus_is_key_released(int keyCode) {
    return lotus_keyboard_state[keyCode].justReleased;
}

bool lotus_is_key_triggered(int keyCode) {
    return !lotus_keyboard_state[keyCode].wasPressed && lotus_keyboard_state[keyCode].isPressed;
}

void lotus_update_mouse_button_state() {
    lotus_mouse_state->scrollValue = 0;

    for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i) {
        lotus_mouse_state[i].wasPressed = lotus_mouse_state[i].isPressed;
    }
}

bool lotus_is_mouse_button_pressed(int button) {
    if (button - 1 < 0 || button - 1 >= MAX_MOUSE_BUTTONS)
        return false;

    return lotus_mouse_state[button - 1].isPressed;
}

bool lotus_is_mouse_button_triggered(int button) {
    if (button - 1 < 0 || button - 1 >= MAX_MOUSE_BUTTONS)
        return false;

    return !lotus_mouse_state[button - 1].wasPressed && lotus_mouse_state[button - 1].isPressed;
}

bool lotus_is_mouse_wheel_scrolled_up() {
    if (lotus_mouse_state->scrollValue > 0) {
        lotus_mouse_state->scrollValue = 0;
        return true;
    } else {
        return false;
    }
}

bool lotus_is_mouse_wheel_scrolled_down() {
    if (lotus_mouse_state->scrollValue < 0) {
        lotus_mouse_state->scrollValue = 0;
        return true;
    } else {
        return false;
    }
}

lotus_event_t *lotus_make_event_structure() {
    lotus_event_t *event = (lotus_event_t *)malloc(sizeof(lotus_event_t));
    if (!event) { _lotus_log_error("failed to create engine event structure"); return NULL; }
    return event;
}
