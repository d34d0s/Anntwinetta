#include "../../headers/processes/atevent.h"

void _atDestroyEventData(ATeventData* d) {
    d->quit = -1;
    d->windowPtr = NULL;
    free(d);
}

ATerrorType _atInitEventData(ATeventData* d, ATwindow* w) {
    if (!d || !w) {
        return ERR_TYPE;
    }

    d->quit = 0;
    d->windowPtr = w->_glfwWin;

    memset(d->inputState.current_keys, 0, sizeof(d->inputState.current_keys));
    if (!d->inputState.current_keys) {
        atLogError("failed to allocate current_keys input state");
        return ERR_MALLOC;
    }

    memset(d->inputState.previous_keys, 0, sizeof(d->inputState.previous_keys));
    if (!d->inputState.previous_keys) {
        atLogError("failed to allocate previous_keys input state");
        return ERR_MALLOC;
    }

    memset(d->inputState.current_mouse_buttons, 0, sizeof(d->inputState.current_mouse_buttons));
    if (!d->inputState.current_mouse_buttons) {
        atLogError("failed to allocate current_mouse_buttons input state");
        return ERR_MALLOC;
    }

    memset(d->inputState.previous_mouse_buttons, 0, sizeof(d->inputState.previous_mouse_buttons));
    if (!d->inputState.previous_mouse_buttons) {
        atLogError("failed to allocate previous_mouse_buttons input state");
        return ERR_MALLOC;
    }

    return ERR_NONE;
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

