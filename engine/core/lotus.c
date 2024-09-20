#include <stdio.h>

#include "lotus.h"
#include "version.h"

char* lotus_get_ver(void) { return LOTUS.ver; }

void lotus_init(void) {
    sprintf(LOTUS.ver, "%d.%d.%d-%s", LOTUS_VERSION_MAJOR, LOTUS_VERSION_MINOR, LOTUS_VERSION_YEAR, LOTUS_VERSION_PHASE);

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "[ ERROR ] | Failed To Initialize SDL2 | %s\n", SDL_GetError()); return;
    }

    printf("[ INIT ] | Lotus %s\n", LOTUS.ver);
}

void lotus_exit(void) {
    printf("[ EXIT ] | Lotus Engine Exit!\n");
}