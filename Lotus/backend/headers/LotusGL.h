#ifndef LOTUSGL_H
#define LOTUSGL_H

#include "../../core/vendor/GL/glew.h"
#include "../../core/vendor/GL/glfw3.h"
#include "../../core/headers/lotus_types.h"

void _lotusInitGLFW(void);
bool _lotusGLWindowOpen(GLFWwindow* window);
GLFWwindow* _lotusMakeWindowGL(unsigned int w, unsigned int h, const char* t);

void _lotusMakeVAO(unsigned int* vao, unsigned int* vbo);
void _lotusMakeVBO(unsigned int* vbo, unsigned short vsize, unsigned short nverts, float* vertices);
void _lotusConfigureVAO(unsigned int* vao, unsigned short vsize, unsigned char vColor, unsigned char vTexture);

#endif