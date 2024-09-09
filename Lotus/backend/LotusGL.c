#include "headers/LotusGL.h"

void _lotusInitGLFW(void) {
    if (!glfwInit()) {
        printf("Error Initializing GLFW\n");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool _lotusGLWindowOpen(GLFWwindow* window) {
    if (!glfwWindowShouldClose(window)) { return 1; } return 0;
}

void _lotusResizeCallback(GLFWwindow* window, int w, int h) { glViewport(0, 0, w, h); }
GLFWwindow* _lotusMakeWindowGL(unsigned int w, unsigned int h, const char* t) {
    GLFWwindow* window = glfwCreateWindow(w, h, t, NULL, NULL);
    if (!window) {
        _lotusLogError("Error Creatig GLFW Window");
        return NULL;
    } glfwMakeContextCurrent(window); glfwSetFramebufferSizeCallback(window, _lotusResizeCallback);
    if (glewInit() != GLEW_OK) {
        _lotusLogError("Error Initializing GLEW");
        return NULL;
    } glViewport(0, 0, w, h); glEnable(GL_DEPTH_TEST);
    return window;
}

void _lotusMakeVBO(unsigned int* vbo, float* vertices, unsigned short nvertices) {
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*nvertices, vertices, GL_STATIC_DRAW);
}

void _lotusMakeVAO(unsigned int* vao, unsigned int* vbo) {
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
}

void _lotusConfigureVAO(unsigned int* vao) {
    glBindVertexArray(*vao);
    // configure VAO position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void _lotusMakeEBO();

