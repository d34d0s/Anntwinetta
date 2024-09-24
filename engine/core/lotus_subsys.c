#include "../include/lotus_subsys.h"

void lotus_render_fallback(void* v){}
void lotus_events_fallback(void* v){}

bool lotus_render_main(void* dc) {
    if (!dc) return 1;
    lotus_draw_call* _dc = (lotus_draw_call*) dc;
    lotus_render_subsys* _rsys = (lotus_render_subsys*) _dc->rsys;
    
    glClearColor(
        _dc->rsys->state.ccolor.x,
        _dc->rsys->state.ccolor.y,
        _dc->rsys->state.ccolor.z,
        1.0
    ); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _rsys->state.drawing = 1;
    _rsys->state.mode = _dc->mode;

    SDL_GL_SwapWindow(_rsys->window->_sdl_win);
    return 0;
}

bool lotus_init_render_subsys(int mode, lm_vec3 ccolor, lotus_render_subsys* rsys) {
    rsys->state.mode = mode;
    rsys->state.drawing = 0;
    rsys->state.ccolor = ccolor;
    rsys->_proc = lotus_new_proc((void*)0, lotus_render_main, lotus_default_fallback);
    return 0;
}

bool lotus_events_main(void* v) {
    lotus_event_t* _event  = (lotus_event_t*) v;
    while (SDL_PollEvent(&_event->event)) {
        switch (_event->event.type) {
            case SDL_QUIT:
                _event->type = lotus_quit_event;
                break;
            case SDL_KEYDOWN:
                _event->type = lotus_key_down_event;
                _event->data.key.keyCode = _event->event.key.keysym.scancode;
                break;
            case SDL_KEYUP:
                _event->type = lotus_key_up_event;
                _event->data.key.keyCode = _event->event.key.keysym.scancode;
                break;
            case SDL_MOUSEMOTION:
                _event->type = lotus_mouse_motion_event;
                _event->data.mouseMotion.mouseX = _event->event.motion.x;
                _event->data.mouseMotion.mouseY = _event->event.motion.y;
                _event->data.mouseMotion.relX = _event->event.motion.xrel;
                _event->data.mouseMotion.relY = _event->event.motion.yrel;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (_event->event.button.button <= MAX_MOUSE_BUTTONS) {
                    lotus_mouse_state[_event->event.button.button - 1].isPressed = true;
                }
                _event->type = lotus_mouse_button_down_event;
                _event->data.mouseButton.mouseX = _event->event.button.x;
                _event->data.mouseButton.mouseY = _event->event.button.y;
                _event->data.mouseButton.button = _event->event.button.button;
                break;
            case SDL_MOUSEBUTTONUP:
                if (_event->event.button.button <= MAX_MOUSE_BUTTONS) {
                    lotus_mouse_state[_event->event.button.button - 1].isPressed = false;
                }
                _event->type = lotus_mouse_button_up_event;
                _event->data.mouseButton.mouseX = _event->event.button.x;
                _event->data.mouseButton.mouseY = _event->event.button.y;
                _event->data.mouseButton.button = _event->event.button.button;
                break;
            case SDL_MOUSEWHEEL:
                lotus_mouse_state->scrollValue += _event->event.wheel.y;
                _event->type = lotus_mouse_wheel_event;
                _event->data.mouseWheel.scrollDirection = _event->event.wheel.y;
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                _event->type = lotus_controller_button_down_event;
                _event->data.controller.controllerButton = _event->event.cbutton.button;
                break;
            case SDL_CONTROLLERBUTTONUP:
                _event->type = lotus_controller_button_up_event;
                _event->data.controller.controllerButton = _event->event.cbutton.button;
                break;
            default:
                _event->type = lotus_none_event;
                return false; // No relevant event to process
        } return true;  // Event processed
    } return false;     // Event not processed
}
