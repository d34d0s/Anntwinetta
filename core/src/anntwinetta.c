#include "../headers/anntwinetta.h"

ATerrorType atInit(void) {
    ATerrorType err = _atInitEngine();
    atClearColor(120, 82, 150, 255);
    return err;
}

ATerrorType atRunning(void) {
    Anntwinetta* atwin = _atGetEngine();
    return !atwin->internal.event_data.quit;
}

ATerrorType atClockTick(void) {
    ATclock* clock = _atGetClock();
    _atClockTick(clock);
}

ATerrorType atExit(void) {
    ATerrorType err = _atExitEngine();
    return err;
}


// external rendering API
void atClearColor(float r, float g, float b, float a) {
    ATrenderData* render_data = _atGetRenderData();
    render_data->clearColor[0]=r/255.0;
    render_data->clearColor[1]=g/255.0;
    render_data->clearColor[2]=b/255.0;
    render_data->clearColor[3]=a/255.0;
}

void atDrawCall(ATdrawCallType type, int glMode) {
    ATrenderData* render_data = _atGetRenderData();
    if (render_data->nCalls+1 > DRAW_CALL_MAX) {
        atLogError("max draw calls reached");
        return;
    }

    ATdrawCall* dc = _atMakeDrawCall(type, glMode);
    if (!dc) {
        atLogError("failed to create draw call");
        return;
    };

    render_data->drawCallArr[render_data->nCalls] = dc;
    render_data->nCalls++;
}

void atDrawCallSelect(ATdrawCallType type, int glMode, ATmeshLayout* meshLayout, ATshaderLayout* shaderLayout) {
    ATrenderData* render_data = _atGetRenderData();
    if (render_data->nCalls+1 > DRAW_CALL_MAX) {
        atLogError("max draw calls reached");
        return;
    }

    ATdrawCall* dc = _atMakeDrawCall(type, glMode);
    dc->vao = *meshLayout->vao;
    dc->shader = *shaderLayout->program;
    dc->n_verts = *meshLayout->n_verts;
    if (!dc) {
        atLogError("failed to create draw call");
        return;
    };

    render_data->drawCallArr[render_data->nCalls] = dc;
    render_data->nCalls++;
}

void atProcRender(void) {
    Anntwinetta* atwin = _atGetEngine();
    if (atRunProcess(atwin->internal.render_proc)) {
        atLogError("failed to run engine render process");
        return;
    };
}


// external event+input API
bool atIsKeyPressed(ATkeyboardKey key) {
    ATeventData* event = _atGetEventData();
    return _atIsKeyPressed(event, key);
}

bool atIsKeyTriggered(ATkeyboardKey key) {
    ATeventData* event = _atGetEventData();
    return _atIsKeyTriggered(event, key);
}

bool atIsKeyReleased(ATkeyboardKey key) {
    ATeventData* event = _atGetEventData();
    return _atIsKeyReleased(event, key);
}

bool atIsMouseButtonPressed(ATmouseButton button) {
    ATeventData* event = _atGetEventData();
    return _atIsMouseButtonPressed(event, button);
}

bool atIsMouseButtonTriggered(ATmouseButton button) {
    ATeventData* event = _atGetEventData();
    return _atIsMouseButtonTriggered(event, button);
}

bool atIsMouseButtonReleased(ATmouseButton button) {
    ATeventData* event = _atGetEventData();
    return _atIsMouseButtonReleased(event, button);
}


void atProcEvents(void) {
    Anntwinetta* atwin = _atGetEngine();
    if (atRunProcess(atwin->internal.event_proc)) {
        atLogError("failed to run engine event process");
        return;
    };
}


// external camera API
ATmat4* atGetCamProj(void) {
    ATcameraData* cam = _atGetCameraData();
    return &cam->camState.proj;
}

ATmat4* atGetCamView(void) {
    ATcameraData* cam = _atGetCameraData();
    return &cam->camState.view;
}

ATvec3* atGetCamLocation(void) {
    ATcameraData* cam = _atGetCameraData();
    return &cam->camState.location;
}

void atSetCamMode(ATcamMode mode) {
    ATcameraData* cam = _atGetCameraData();
    _atSetCamMode(cam, mode);
}

void atCamUp(void) {
    ATcameraData* cam = _atGetCameraData();
    _atCamMovUp(cam, _atGetDeltaTime());
}

void atCamIn(void) {
    ATcameraData* cam = _atGetCameraData();
    _atCamMovIn(cam, _atGetDeltaTime());
}

void atCamOut(void) {
    ATcameraData* cam = _atGetCameraData();
    _atCamMovOut(cam, _atGetDeltaTime());
}

void atCamLeft(void) {
    ATcameraData* cam = _atGetCameraData();
    _atCamMovLeft(cam, _atGetDeltaTime());
}

void atCamDown(void) {
    ATcameraData* cam = _atGetCameraData();
    _atCamMovDown(cam, _atGetDeltaTime());
}

void atCamRight(void) {
    ATcameraData* cam = _atGetCameraData();
    _atCamMovRight(cam, _atGetDeltaTime());
}

void atProcCamera(void) {
    Anntwinetta* atwin = _atGetEngine();
    if (atRunProcess(atwin->internal.camera_proc)) {
        atLogError("failed to run engine camera process");
        return;
    }
}


// external resource API

// mesh
int atMakeMesh(int n_verts, float* vertices) {
    ATmeshData* mesh_data = _atGetMeshData();
    return _atSetMeshData(mesh_data, n_verts, vertices);
}

ATmeshLayout* atGetMeshLayout(int index) {
    ATmeshData* mesh_data = _atGetMeshData();
    return _atGetMeshLayout(mesh_data, index);
}

void atDestroyMeshLayout(ATmeshLayout* layout) {
    _atDestroyMeshLayout(layout);
}

// shader
int atMakeShader(const char* vertex, const char* fragment) {
    ATshaderData* shader_data = _atGetShaderData();
    return _atSetShaderData(shader_data, vertex, fragment);
}

ATshaderLayout* atGetShaderLayout(int index) {
    ATshaderData* shader_data = _atGetShaderData();
    return _atGetShaderLayout(shader_data, index);
}

void atDestroyShaderLayout(ATshaderLayout* layout) {
    _atDestroyShaderLayout(layout);
}

ATerrorType atMakeUniform(ATuniformType type, int shaderIndex, const char* name, void* value) {
    ATshaderData* shader_data = _atGetShaderData();
    return _atSetShaderUniform(shader_data, shaderIndex, type, name, value);
}

ATuniformLayout* atGetUniformLayout(int shaderIndex, const char* name) {
    ATshaderData* shader_data = _atGetShaderData();
    return _atGetShaderUniform(shader_data, shaderIndex, name);
}

void atSetUniform(ATuniformType type, int shaderIndex, const char* name) {
    ATshaderLayout* shader = atGetShaderLayout(shaderIndex);
    ATuniformLayout* uniform = atGetUniformLayout(shaderIndex, name);
    glUseProgram(*shader->program);
    atglSetUniformValue(UNIFORM_MAT4, *shader->program, uniform->location, uniform->value);
}
