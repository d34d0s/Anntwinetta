#include "lotus.h"

void lotusInit(void) {
    _lotusInitGLFW();

    sprintf(LOTUS.version, "Lotus %d.%d.%d+%d",
    LOTUS_VERSION_MAJOR,
    LOTUS_VERSION_MINOR,
    LOTUS_VERSION_YEAR,
    LOTUS_VERSION_PATCH );
    
    LOTUS.camera = NULL;
    LOTUS.clock = _lotusMakeClock();
    LOTUS.window = _lotusMakeWindowGL(800, 600, LOTUS.version);
    _lotusInitRenderer(&LOTUS.renderer, LOTUS.window);
    _LOTUS_INIT_ECS();
    _lotusLogInit("%s\n",LOTUS.version);
}
void lotusExit(void) { glfwSetWindowShouldClose(LOTUS.window, 1); }
void lotusCleanup(void) { glfwDestroyWindow(LOTUS.window); glfwTerminate(); }

// External Engine API
void lotusInitCamera(unsigned int mode) {
    LOTUS.camera = _lotusMakeCamera(
        LOTUS.window,
        (LMvec3){0.0f, 0.0f, 1.0f},
        (LMvec3){0.0f, 1.0f, 0.0f},
        45.0f,
        0.1f, 
        1000.0f,
        mode
    );
}

float lotusGetDeltaTime(void) { return LOTUS.clock.delta; }
void lotusCamMovUp(void) { _lotusCamMovUp(LOTUS.clock.delta); }
void lotusCamMovIn(void) { _lotusCamMovIn(LOTUS.clock.delta); }
void lotusCamMovOut(void) { _lotusCamMovOut(LOTUS.clock.delta); }
void lotusCamMovLeft(void) { _lotusCamMovLeft(LOTUS.clock.delta); }
void lotusCamMovDown(void) { _lotusCamMovDown(LOTUS.clock.delta); }
void lotusCamMovRight(void) { _lotusCamMovRight(LOTUS.clock.delta); }

// External Event/Input API
void lotusPollEvents(void) { _lotusClockTick(&LOTUS.clock); _lotusPollEvents(LOTUS.window); }
bool lotusRunning(void) { return _lotusGLWindowOpen(LOTUS.window); }
unsigned char lotusIsKeyPressed(LotusKeyboardKey key) { return _lotusIsKeyPressed(key); }
unsigned char lotusIsKeyTriggered(LotusKeyboardKey key) { return _lotusIsKeyTriggered(key); }
unsigned char lotusIsKeyReleased(LotusKeyboardKey key) { return _lotusIsKeyReleased(key); }
unsigned char lotusIsMouseButtonPressed(LotusMouseButton button) { return _lotusIsMouseButtonPressed(button); }
unsigned char lotusIsMouseButtonTriggered(LotusMouseButton button) { return _lotusIsMouseButtonTriggered(button); }
unsigned char lotusIsMouseButtonReleased(LotusMouseButton button) { return _lotusIsMouseButtonReleased(button); }

// External Rendering API
void lotusPreProcess (void) {
    if (LOTUS.camera != NULL) _lotusUpdateCam(LOTUS.window);
    _lotusPreProcessing(&LOTUS.renderer);
}
void lotusPosProcess(void) { _lotusPostProcessing(&LOTUS.renderer); }
void lotusProcess(void) {
    for (int call = 0; call < LOTUS.renderer.ncalls; call++) {
        LotusDrawCall* dc = &LOTUS.renderer.calls[call];
        if (dc->texture != NULL) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, dc->texture->glid);
        } if (dc->material != NULL) {
            glUseProgram(dc->material->shader.program);
            for (int i = 0; i < dc->nuniforms; i++) { _lotusSendUniform(&dc->material->shader, i); }
            lotusReleaseMaterial(dc->material);
        }
        glBindVertexArray(dc->vao);
        glDrawArrays(GL_TRIANGLES, 0, dc->nverts);
        glBindVertexArray(0);
    }
}

