#pragma once

#include "../attypes.h"
#include "../athelpers.h"
#include "../../vendor/SDL2/SDL.h"
#include "../../backend/headers/atGLAPI.h"

typedef struct ATwindow {
    char* title;
    int dimensions[2];
    GLFWwindow* _glfwWin;
} ATwindow;

void _atDestroyWindow(ATwindow* w);
ATwindow* _atMakeWindow(int x, int y, char* t);
