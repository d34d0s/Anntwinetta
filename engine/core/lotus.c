#include <stdio.h>

#include "lotus.h"
#include "version.h"

char* lotus_get_ver(void) { return LOTUS.ver; }

void lotus_init(void) {
    sprintf(LOTUS.ver, "%d.%d.%d-%s", LOTUS_VERSION_MAJOR, LOTUS_VERSION_MINOR, LOTUS_VERSION_YEAR, LOTUS_VERSION_PHASE);
    
    _lotusLogInit("Lotus %s", LOTUS.ver);
    _lotusLogInfo("Platform:        %s", SDL_GetPlatform());
    _lotusLogInfo("CPU Count:       %d", SDL_GetCPUCount());
    _lotusLogInfo("System RAM:      %d MB", SDL_GetSystemRAM());
    
    if (SDL_Init(SDL_INIT_VIDEO)) {
        _lotusLogFatal("Failed To Initialize SDL2 | %s", SDL_GetError());
    }

    #ifdef _LOTUS_GL_
        char win_title[100];
        sprintf(win_title, "Lotus Engine | %s", LOTUS.ver);
        lotus_create_window_gl(&LOTUS.window, (lm_vec2_i){800, 600}, win_title);
        lotus_init_gl(&LOTUS.window);
    #endif
}

void lotus_exit(void) {
    _lotusLogExit("Lotus %s", LOTUS.ver);
}