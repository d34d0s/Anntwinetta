#pragma once

#include "../../headers/atmath.h"
#include "../../headers/attypes.h"
#include "../../headers/athelpers.h"

#include "../../vendor/SDL2/SDL.h"

#include "../../vendor/GL/glew.h"   // TODO: REMOVE THIS ON RELEASE
#ifdef _ATWIN_WINDOWS_
    #include "../../vendor/GL/glew.h"
#endif

typedef struct ATGLcontext {
    b8 init;
    SDL_GLContext* GL;
} ATGLcontext;

ATGLcontext* atglCreateContext(SDL_Window* w);
atErrorType atglDestroyContext(ATGLcontext* ctx);

int atglMakeVBO(int n_verts, int attrs, float* vertices);
int atglMakeVAO(int vbo, int n_verts, int attrs);

int atglMakeShader(const char* vertexShader, const char* fragmentShader);
