#include "../include/lotus.h"

char* lotus_get_ver(void) { return LOTUS.ver; }

void lotus_init(void) {
    sprintf(LOTUS.ver, "%d.%d.%d-%s", LOTUS_VERSION_MAJOR, LOTUS_VERSION_MINOR, LOTUS_VERSION_YEAR, LOTUS_VERSION_PHASE);
    
    _lotus_log_init("Lotus %s", LOTUS.ver);
    _lotus_log_info("Platform:        %s", SDL_GetPlatform());
    _lotus_log_info("CPU Count:       %d", SDL_GetCPUCount());
    _lotus_log_info("System RAM:      %d MB", SDL_GetSystemRAM());
    
    if (SDL_Init(SDL_INIT_VIDEO)) {
        _lotus_log_fatal("Failed To Initialize SDL2 | %s", SDL_GetError());
    }

    #ifdef _LOTUS_GL_
        char win_title[100];
        sprintf(win_title, "Lotus Engine | %s", LOTUS.ver);
        lotus_create_window_gl(&LOTUS.window, (lm_vec2_i){800, 600}, win_title);
        lotus_init_gl(&LOTUS.window);
        glClearColor(0.4, 0.3, 0.7, 1.0);

        lotus_init_render_subsys(
            DRAW_TRIANGLES,
            (lm_vec3){0.3, 0.5, 0.8},
            &LOTUS.subsys.render_subsys
        ); LOTUS.subsys.render_subsys.window = &LOTUS.window;
    #endif

}

void lotus_exit(void) {
    _lotus_log_exit("Lotus %s", LOTUS.ver);
    #ifdef _LOTUS_GL_
        lotus_destroy_window_gl(&LOTUS.window);
    #endif
}

void lotus_render(lotus_draw_call dc) {
    dc.rsys = &LOTUS.subsys.render_subsys;
    if (LOTUS.subsys.render_subsys._proc->main(&dc)) {
        LOTUS.subsys.render_subsys._proc->fallback(&dc);
    }
}
