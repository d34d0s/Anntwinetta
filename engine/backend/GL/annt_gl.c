#include "../include/annt_gl.h"

char at_create_window_gl(at_window_gl* w, at_vec2_i size, char* title) {
    w->is_open=0; w->size=size; w->title=title;

    w->_sdl_win=SDL_CreateWindow(w->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w->size.x, w->size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!w->_sdl_win) {
        _at_log_fatal("Failed To Create Window And GL Context | %s", SDL_GetError());
        free(w->title);
        free(w);
        return 1;
    } 
    
    w->_sdl_ren=SDL_CreateRenderer(w->_sdl_win, -1, SDL_RENDERER_ACCELERATED);
    
    w->_gl_ctx=SDL_GL_CreateContext(w->_sdl_win);
    if (!w->_gl_ctx) {
        _at_log_fatal("Failed To Create OpenGL Context | %s", SDL_GetError()); return 1;
    } return 0;
}

char at_enable_vsync_gl(void) {
    if (SDL_GL_SetSwapInterval(1) < 0) {
        _at_log_error("Failed To Enable VSYNC | %s", SDL_GetError()); return 1;
    } return 0;
}

void at_destroy_window_gl(at_window_gl* w) {
    SDL_GL_DeleteContext(&w->_gl_ctx);
    SDL_DestroyRenderer(w->_sdl_ren);
    SDL_DestroyWindow(w->_sdl_win);
    free(w->title);
    free(w);
}

char at_is_error_gl(void) {
    GLenum err=glGetError();
    if (err != GL_NO_ERROR) {
        _at_log_error("OpenGL Error | %u", glGetString(err)); return 1;
    } return 0;
}

char at_init_gl(at_window_gl* w) {
    // use OpenGL 4.3 core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // enable double buffering with a 24bit Z buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if (at_is_error_gl()) {
        _at_log_fatal("Failed To Initialize OpenGL"); return 1;
    }
    
    _at_log_init("OpenGL Vendor:   %s", glGetString(GL_VENDOR));
    _at_log_init("OpenGL Version:  %s", glGetString(GL_VERSION));
    _at_log_init("OpenGL Renderer: %s", glGetString(GL_RENDERER));
    _at_log_init("GLSL Version:    %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    return 0;
}
