#pragma once

#include "../../atmath.h"
#include "../../attypes.h"
#include "../../athelpers.h"

#ifdef _ATWIN_WEB_
    #include "../../../../vendor/GLES3/gl32.h"
    #include "../../../../vendor/SDL2/SDL_opengles.h"
#else
    #include "../../../../vendor/GL/glew.h"
#endif

#include "../../../../vendor/GLFW/glfw3.h"

typedef enum ATuniformType {
    UNIFORM_NONE=0,
    UNIFORM_VEC2,
    UNIFORM_VEC3,
    UNIFORM_VEC4,
    UNIFORM_MAT4,
    UNIFORM_TYPES
} ATuniformType;

typedef struct ATGLcontext {
    b8 init;
} ATGLcontext;

ATGLcontext* atglCreateContext(GLFWwindow* w);
ATerrorType atglDestroyContext(ATGLcontext* ctx);

int atglMakeVBO(int n_verts, int attrs, float* vertices);
int atglMakeVAO(int vbo, int n_verts, int attrs);

int atglMakeShader(const char* vertexShader, const char* fragmentShader);
int atglGetUniformLocation(int program, const char* name);
void atglSetUniformValue(ATuniformType type, int program, int location, void* value);

