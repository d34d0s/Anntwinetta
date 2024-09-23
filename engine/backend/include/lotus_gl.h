#ifndef LOTUSGL_H
#define LOTUSGL_H

#include "../../include/lotus_math.h"
#include "../../include/lotus_types.h"
#include "../../vendor/SDL2/SDL_opengl.h"

typedef struct lotus_window_gl {
    char* title;
    char is_open;
    lm_vec2_i size;
    SDL_Window* _sdl_win;
    SDL_Renderer* _sdl_ren;
    SDL_GLContext* _gl_ctx;
} lotus_window_gl;

char lotus_is_error_gl(void);
char lotus_enable_vsync_gl(void);
char lotus_init_gl(lotus_window_gl* w);
void lotus_destroy_window_gl(lotus_window_gl* w);
char lotus_create_window_gl(lotus_window_gl* w, lm_vec2_i size, char* title);

#endif