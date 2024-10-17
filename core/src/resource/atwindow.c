#include "../../headers/resource/atwindow.h"

void _atResizeCallback(GLFWwindow* window, int w, int h) { glViewport(0, 0, w, h); }

ATwindow* _atMakeWindow(int x, int y, char* t) {
    ATwindow*w = (ATwindow*)malloc(sizeof(ATwindow));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    w->_glfwWin = glfwCreateWindow(x, y, t, NULL, NULL);
    if (!w->_glfwWin) {
        atLogError("failed to create GLFW window");
        return atTypeCastPtr(ATwindow, ERR_MALLOC);
    }; glfwMakeContextCurrent(w->_glfwWin);
    
    // glfwSetWindowAttrib(w->_glfwWin, GLFW_DOUBLEBUFFER, 1);
    // glfwSetWindowAttrib(w->_glfwWin, GLFW_DEPTH_BITS, 24);

    glViewport(0, 0, x, y);
    glfwSetFramebufferSizeCallback(w->_glfwWin, _atResizeCallback);

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
