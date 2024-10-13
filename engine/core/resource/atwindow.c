#include "../../headers/resource/atwindow.h"

ATwindow* _atMakeWindow(int x, int y, char* t) {
    ATwindow*w = (ATwindow*)malloc(sizeof(ATwindow));
    
    w->_glfwWin = glfwCreateWindow(x, y, t, NULL, NULL);
    if (!w->_glfwWin) {
        atLogError("failed to create GLFW window");
        return atTypeCastPtr(ATwindow, ERR_MALLOC);
    }

    w->title=t;
    w->dimensions[0] = x;
    w->dimensions[1] = y;
    return w;
}

void _atDestroyWindow(ATwindow* w) {
    free(w->title);
    glfwDestroyWindow(w->_glfwWin);
    free(w);
}
