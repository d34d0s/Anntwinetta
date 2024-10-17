#include "../../headers/processes/atevent.h"

void _atInitEventData(ATeventData* event) {
    memset(event->inputState.current_keys, 0, sizeof(event->inputState.current_keys));
    memset(event->inputState.previous_keys, 0, sizeof(event->inputState.previous_keys));
    memset(event->inputState.current_mouse_buttons, 0, sizeof(event->inputState.current_mouse_buttons));
    memset(event->inputState.previous_mouse_buttons, 0, sizeof(event->inputState.previous_mouse_buttons));
}

ATerrorType _atPrepEvent(void* d) {
    ATeventData* event = atTypeCastPtr(ATeventData, d);
    GLFWwindow* window = atTypeCastPtr(GLFWwindow, event->windowPtr);
    if (glfwWindowShouldClose(window)) {
        event->quit = 1;
        return ERR_NONE;
    }
    return ERR_NONE;
}

ATerrorType _atMainEvent(void* d) {
    glfwPollEvents();
    
    ATeventData* event = atTypeCastPtr(ATeventData, d);
    GLFWwindow* window = atTypeCastPtr(GLFWwindow, event->windowPtr);
    
    memcpy(
        event->inputState.previous_keys,
        event->inputState.current_keys,
        sizeof(event->inputState.current_keys)
    ); memcpy(
        event->inputState.previous_mouse_buttons,
        event->inputState.current_mouse_buttons,
        sizeof(event->inputState.current_mouse_buttons)
    );

    for (int i = 0; i < MAX_KEYS; i++) {
        event->inputState.current_keys[i] = glfwGetKey(window, i);
    } for (int j = 0; j < MAX_MOUSE_BUTTONS; j++) {
        event->inputState.current_mouse_buttons[j] = glfwGetMouseButton(window, j);
    }

    return ERR_NONE;
}

ATerrorType _atPostEvent(void* d) {
    return ERR_NONE;
}

unsigned char _atIsKeyPressed(ATeventData* event, ATkeyboardKey key) {
    return event->inputState.current_keys[key] == GLFW_PRESS;
}

unsigned char _atIsKeyTriggered(ATeventData* event, ATkeyboardKey key) {
    return event->inputState.current_keys[key] == GLFW_PRESS &&
    event->inputState.previous_keys[key] == GLFW_RELEASE;
}

unsigned char _atIsKeyReleased(ATeventData* event, ATkeyboardKey key) {
    return event->inputState.current_keys[key] == GLFW_RELEASE &&
    event->inputState.previous_keys[key] == GLFW_PRESS;
}

unsigned char _atIsMouseButtonPressed(ATeventData* event, ATmouseButton button) {
    return event->inputState.current_mouse_buttons[button] == GLFW_PRESS;
}

unsigned char _atIsMouseButtonTriggered(ATeventData* event, ATmouseButton button) {
    return event->inputState.current_mouse_buttons[button] == GLFW_PRESS &&
    event->inputState.previous_mouse_buttons[button] == GLFW_RELEASE;
}

unsigned char _atIsMouseButtonReleased(ATeventData* event, ATmouseButton button) {
    return event->inputState.current_mouse_buttons[button] == GLFW_RELEASE &&
    event->inputState.previous_mouse_buttons[button] == GLFW_PRESS;
}

