#include "../../headers/resource/atwindow.h"

ATwindow* _atMakeWindow(int x, int y, char* t) {
    ATwindow*w = (ATwindow*)malloc(sizeof(ATwindow));
    
    w->_sdlWin=SDL_CreateWindow(t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    if (!w) {
        atLogError("failed to create SDL window");
        return atTypeCastPtr(ATwindow, ERR_MALLOC);
    }


    w->_sdlRen=SDL_CreateRenderer(w->_sdlWin, -1, SDL_RENDERER_ACCELERATED);
    if (!w->_sdlRen) {
        atLogError("failed to create SDL renderer");
        return atTypeCastPtr(ATwindow, ERR_MALLOC);
    }
    
    w->title=t;
    w->dimensions[0] = x;
    w->dimensions[1] = y;
    return w;
}

void _atDestroyWindow(ATwindow* w) {
    free(w->title);
    SDL_DestroyWindow(w->_sdlWin);
    SDL_DestroyRenderer(w->_sdlRen);
    free(w);
}
