#include "../headers/atGLAPI.h"

ATGLcontext* atglCreateContext(SDL_Window* w) {
    ATGLcontext* ctx = (ATGLcontext*)malloc(sizeof(ATGLcontext));
    
    if (!ctx) {
        atLogError("failed to allocate OpenGL context");
        return atTypeCastPtr(ATGLcontext, ERR_MALLOC);
    }
    
    ctx->GL = SDL_GL_CreateContext(w);
    SDL_GL_MakeCurrent(w, ctx->GL);
    
    if (!ctx) {
        atLogError("failed to create OpenGL context");
        free(ctx);
        return atTypeCastPtr(ATGLcontext, ERR_INIT);
    }; ctx->init = 1;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // enable double buffering with a 24bit Z buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    #ifdef _ATWIN_WINDOWS_
        if (glewInit() != ERR_NONE) {
            atLogError("failed to initialize GLEW");
            free(ctx);
            return atTypeCastPtr(ATGLcontext, ERR_INIT);
        }
    #endif

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // atwin doesnt use gl stencils, so disable the tests
    glDisable(GL_STENCIL_TEST);
    
    atLogInit("OpenGL Vendor:   %s", glGetString(GL_VENDOR));
    atLogInit("OpenGL Version:  %s", glGetString(GL_VERSION));
    atLogInit("OpenGL Renderer: %s", glGetString(GL_RENDERER));
    atLogInit("GLSL Version:    %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    return ctx;
}

atErrorType atglDestroyContext(ATGLcontext* ctx) {
    if (!ctx) { return ERR_TYPE; }
    SDL_GL_DeleteContext(ctx->GL);
    free(ctx);
    return ERR_NONE;
}

int atglMakeVBO(int n_verts, int attrs, float* vertices) {
    int vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (n_verts*attrs)*sizeof(float), vertices, GL_STATIC_DRAW);
    return vbo;
}

int atglMakeVAO(int vbo, int n_verts, int attrs) {
    int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    return vao;
}

int atglMakeShader(const char* vertexShader, const char* fragmentShader) {
    int linked = 0;
    int compiled = 0;
 
    int vShader = glCreateShader(GL_VERTEX_SHADER);
    int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vShader, 1, &vertexShader, NULL);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) { atLogError("failed to compile shader"); return ERR_SHADER; }
    
    glShaderSource(fShader, 1, &fragmentShader, NULL);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) { atLogError("failed to compile shader"); return ERR_SHADER; }

    int program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) { atLogError("failed to link shader"); return ERR_SHADER; }

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}

int atglGetUniformLocation(int program, const char* name) {
    return glGetUniformLocation(program, name);
}

void atglSetUniformValue(ATuniformType type, int program, int location, void* value) {
    switch (type) {
        case UNIFORM_NONE: break;
        case UNIFORM_VEC2: glUniform2fv(location, 1, value); break;
        case UNIFORM_VEC3: glUniform3fv(location, 1, value); break;
        case UNIFORM_VEC4: glUniform4fv(location, 1, value); break;
        case UNIFORM_MAT4: glUniformMatrix4fv(location, 1, 0, value); break;
        default: break;
    }
}
