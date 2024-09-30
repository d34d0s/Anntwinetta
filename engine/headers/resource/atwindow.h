#pragma once

#include "../attypes.h"
#include "../athelpers.h"
#include "../../vendor/SDL2/SDL.h"

typedef struct ATwindow {
    char* title;
    int dimensions[2];
    SDL_Window* _sdlWin;
    SDL_Renderer* _sdlRen;
} ATwindow;

void _atDestroyWindow(ATwindow* w);
ATwindow* _atMakeWindow(int x, int y, char* t);
