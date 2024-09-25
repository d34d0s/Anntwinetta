#ifndef ANNT_GL_H
#define ANNT_GL_H

#include "../../include/annt_math.h"
#include "../../include/annt_types.h"
#include "../../vendor/SDL2/SDL_opengl.h"

typedef struct at_window_gl {
    char* title;
    char is_open;
    at_vec2_i size;
    SDL_Window* _sdl_win;
    SDL_Renderer* _sdl_ren;
    SDL_GLContext* _gl_ctx;
} at_window_gl;

char at_is_error_gl(void);
char at_enable_vsync_gl(void);
char at_init_gl(at_window_gl* w);
void at_destroy_window_gl(at_window_gl* w);
char at_create_window_gl(at_window_gl* w, at_vec2_i size, char* title);

#endif