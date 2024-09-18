#include "../../headers/core/LotusInput.h"

void _lotusInitEvents(void) {
    memset(lotusInputState.current_keys, 0, sizeof(lotusInputState.current_keys));
    memset(lotusInputState.previous_keys, 0, sizeof(lotusInputState.previous_keys));
    memset(lotusInputState.current_mouse_buttons, 0, sizeof(lotusInputState.current_mouse_buttons));
    memset(lotusInputState.previous_mouse_buttons, 0, sizeof(lotusInputState.previous_mouse_buttons));
}

void _lotusPollEvents(GLFWwindow* window) {
    glfwPollEvents();
    memcpy(
        lotusInputState.previous_keys,
        lotusInputState.current_keys,
        sizeof(lotusInputState.current_keys)
    ); memcpy(
        lotusInputState.previous_mouse_buttons,
        lotusInputState.current_mouse_buttons,
        sizeof(lotusInputState.current_mouse_buttons)
    );

    for (int i = 0; i < MAX_KEYS; i++) {
        lotusInputState.current_keys[i] = glfwGetKey(window, i);
    } for (int j = 0; j < MAX_MOUSE_BUTTONS; j++) {
        lotusInputState.current_mouse_buttons[j] = glfwGetMouseButton(window, j);
    }
}

unsigned char _lotusIsKeyPressed(LotusKeyboardKey key) {
    return lotusInputState.current_keys[key] == GLFW_PRESS;
}

unsigned char _lotusIsKeyTriggered(LotusKeyboardKey key) {
    return lotusInputState.current_keys[key] == GLFW_PRESS &&
    lotusInputState.previous_keys[key] == GLFW_RELEASE;
}

unsigned char _lotusIsKeyReleased(LotusKeyboardKey key) {
    return lotusInputState.current_keys[key] == GLFW_RELEASE &&
    lotusInputState.previous_keys[key] == GLFW_PRESS;
}

unsigned char _lotusIsMouseButtonPressed(LotusMouseButton button) {
    return lotusInputState.current_mouse_buttons[button] == GLFW_PRESS;
}

unsigned char _lotusIsMouseButtonTriggered(LotusMouseButton button) {
    return lotusInputState.current_mouse_buttons[button] == GLFW_PRESS &&
    lotusInputState.previous_mouse_buttons[button] == GLFW_RELEASE;
}

unsigned char _lotusIsMouseButtonReleased(LotusMouseButton button) {
    return lotusInputState.current_mouse_buttons[button] == GLFW_RELEASE &&
    lotusInputState.previous_mouse_buttons[button] == GLFW_PRESS;
}

// ENGINE CLOCK
LotusClock _lotusMakeClock(void) {
    LotusClock c = {
        .delta=0.0f,
        .current=glfwGetTime(),
        .previous=0.0f
    }; return c;
}

void _lotusClockTick(LotusClock* clock) {
    clock->current = glfwGetTime();
    clock->delta = clock->current - clock->previous;
    clock->previous = clock->current;
}


