#include "../include/anntwinetta.h"
#include "../include/annt_events.h"

char* at_get_ver(void) { return ANNT.ver; }

void at_init(void) {
    sprintf(ANNT.ver, "%d.%d.%d-%s", ANNT_VERSION_MAJOR, ANNT_VERSION_MINOR, ANNT_VERSION_YEAR, ANNT_VERSION_PHASE);
    
    _at_log_init("~Annwinetta~ | %s", ANNT.ver);
    _at_log_info("Platform:        %s", SDL_GetPlatform());
    _at_log_info("CPU Count:       %d", SDL_GetCPUCount());
    _at_log_info("System RAM:      %d MB", SDL_GetSystemRAM());
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        _at_log_fatal("Failed To Initialize SDL2 | %s", SDL_GetError());
    }

    #ifdef _ANNT_GL_
        char win_title[100];
        sprintf(win_title, "~Annwinetta~ | %s", ANNT.ver);
        at_create_window_gl(&ANNT.window, (at_vec2_i){800, 600}, win_title);
        at_init_gl(&ANNT.window);
        glClearColor(0.4, 0.3, 0.7, 1.0);

        at_init_render_subsys(
            DRAW_TRIANGLES,
            (at_vec3){0.3, 0.5, 0.8},
            &ANNT.subsys.render_subsys
        ); ANNT.subsys.render_subsys.window = &ANNT.window;
    #endif
    
    ANNT.event = at_make_event_structure();
    ANNT.engine_state._win_quit = 0;
}

void at_set_win_main(at_proc_main_ptr main) {
    #ifdef _ANNT_WINDOWS_
        ANNT._proc_main = at_new_proc((void*)0, (at_proc_main_ptr)main, _at_fallback);
        if (!ANNT._proc_main) {
            _at_log_error("unable to create main procedure!");
        }
    #endif
}

void at_main(void) {
    #ifdef _ANNT_WINDOWS_
        while (!ANNT.engine_state._win_quit) {
            if (ANNT._proc_main->main(ANNT._proc_main->data)) ANNT.engine_state._win_quit = 1;
        }; ANNT._proc_main->fallback(ANNT._proc_main->data);
    #endif
}

void at_events(void) {
    if (at_events_main(ANNT.event)) {
        at_events_fallback((void*)0);
    }
}

void at_update(void) {
    at_update_keyboard_state();
    at_update_mouse_button_state();
    if (ANNT.event->type == at_quit_event) at_exit();
}

void at_render(at_draw_call dc) {
    dc.rsys = &ANNT.subsys.render_subsys;
    if (ANNT.subsys.render_subsys._proc->main(&dc)) {
        ANNT.subsys.render_subsys._proc->fallback(&dc);
    }
}

void at_exit(void) {
    // free event structure
    ANNT.engine_state._win_quit = 1;
    _at_log_exit("Lotus %s", ANNT.ver);
    #ifdef _ANNT_GL_
        at_destroy_window_gl(&ANNT.window);
    #endif
}


void _at_fallback(void* v) {
    _at_log_error("(O_O) main procedure fallback!");
}

