#include "../../headers/processes/atevent.h"

bool atIsKeyPressed(int keyCode) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[keyCode];
}

bool atIsKeyReleased(int keyCode) {
    return atKeyboardState[keyCode].justReleased;
}

bool atIsKeyTriggered(int keyCode) {
    return !atKeyboardState[keyCode].wasPressed && atKeyboardState[keyCode].isPressed;
}

bool atIsMouseButtonPressed(int button) {
    if (button - 1 < 0 || button - 1 >= MAX_MOUSE_BUTTONS)
        return false;

    return atMouseState[button - 1].isPressed;
}

bool atIsMouseButtonTriggered(int button) {
    if (button - 1 < 0 || button - 1 >= MAX_MOUSE_BUTTONS)
        return false;

    return !atMouseState[button - 1].wasPressed && atMouseState[button - 1].isPressed;
}

bool atIsMouseWheelScrolledUp() {
    if (atMouseState->scrollValue > 0) {
        atMouseState->scrollValue = 0;
        return true;
    } else {
        return false;
    }
}

bool atIsMouseWheelScrolledDown() {
    if (atMouseState->scrollValue < 0) {
        atMouseState->scrollValue = 0;
        return true;
    } else {
        return false;
    }
}

// event process
void _atSyncKeyboard() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i) {
        bool isCurrentlyPressed = state[i];
        atKeyboardState[i].justReleased = atKeyboardState[i].isPressed && !isCurrentlyPressed;
        atKeyboardState[i].wasPressed = atKeyboardState[i].isPressed; // Store last frame's state
        atKeyboardState[i].isPressed = isCurrentlyPressed;
    }
}

void _atSyncMouse() {
    atMouseState->scrollValue = 0;

    for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i) {
        atMouseState[i].wasPressed = atMouseState[i].isPressed;
    }
}

atErrorType _atPrepEvent(void* d) {
    ATeventData* event_data = atTypeCastPtr(ATeventData, d);
    while (SDL_PollEvent(event_data->_sdlEvent)) {
        switch (event_data->_sdlEvent->type) {
            case SDL_QUIT:
                event_data->type = QUIT_EVENT;
                event_data->quit = 1;
                break;
            case SDL_KEYDOWN:
                event_data->type = KEYDOWN_EVENT;
                event_data->data.key.keyCode = event_data->_sdlEvent->key.keysym.scancode;
                break;
            case SDL_KEYUP:
                event_data->type = KEYUP_EVENT;
                event_data->data.key.keyCode = event_data->_sdlEvent->key.keysym.scancode;
                break;
            case SDL_MOUSEMOTION:
                event_data->type = MOUSEMOVE_EVENT;
                event_data->data.mouseMotion.mouseX = event_data->_sdlEvent->motion.x;
                event_data->data.mouseMotion.mouseY = event_data->_sdlEvent->motion.y;
                event_data->data.mouseMotion.relX = event_data->_sdlEvent->motion.xrel;
                event_data->data.mouseMotion.relY = event_data->_sdlEvent->motion.yrel;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event_data->_sdlEvent->button.button <= MAX_MOUSE_BUTTONS) {
                    atMouseState[event_data->_sdlEvent->button.button - 1].isPressed = true;
                }
                event_data->type = MOUSEDOWN_EVENT;
                event_data->data.mouseButton.mouseX = event_data->_sdlEvent->button.x;
                event_data->data.mouseButton.mouseY = event_data->_sdlEvent->button.y;
                event_data->data.mouseButton.button = event_data->_sdlEvent->button.button;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event_data->_sdlEvent->button.button <= MAX_MOUSE_BUTTONS) {
                    atMouseState[event_data->_sdlEvent->button.button - 1].isPressed = false;
                }
                event_data->type = MOUSEUP_EVENT;
                event_data->data.mouseButton.mouseX = event_data->_sdlEvent->button.x;
                event_data->data.mouseButton.mouseY = event_data->_sdlEvent->button.y;
                event_data->data.mouseButton.button = event_data->_sdlEvent->button.button;
                break;
            case SDL_MOUSEWHEEL:
                atMouseState->scrollValue += event_data->_sdlEvent->wheel.y;
                event_data->type = MOUSEWHEEL_EVENT;
                event_data->data.mouseWheel.scrollDirection = event_data->_sdlEvent->wheel.y;
                break;
            default:
                event_data->type = NONE_EVENT;
                return ERR_NONE;                // no event to process
        } return ERR_NONE;                      // event processed
    }; return ERR_NONE;
}

atErrorType _atMainEvent(void* d) {
    ATeventData* event_data = atTypeCastPtr(ATeventData, d);
    return ERR_NONE;
}

atErrorType _atPostEvent(void* d) {
    _atSyncMouse(); _atSyncKeyboard();
    return ERR_NONE;
}

