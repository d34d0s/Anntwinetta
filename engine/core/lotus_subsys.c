#include "../include/lotus_subsys.h"

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
}

