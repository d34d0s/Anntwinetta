#pragma once

#include "../attypes.h"
#include "../athelpers.h"
#include "../backend/GL/atGLAPI.h"

typedef struct ATwindow {
    char* title;
    int dimensions[2];
    GLFWwindow* _glfwWin;
} ATwindow;

void _atDestroyWindow(ATwindow* w);
ATwindow* _atMakeWindow(int x, int y, char* t);
void _atResizeCallback(GLFWwindow* window, int w, int h);