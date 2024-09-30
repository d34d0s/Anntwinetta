#include "../headers/anntwinetta.h"

atErrorType atInit(void) {
    atErrorType err = _atInitEngine();
    atClearColor(120, 82, 150, 255);
    return err;
}

atErrorType atRunning(void) {
    Anntwinetta* atwin = _atGetEngine();
    return !atwin->internal.event_data.quit;
}

atErrorType atExit(void) {
    atErrorType err = _atExitEngine();
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

void atDrawCallSelect(ATdrawCallType type, int glMode, int shader, int vao, int n_verts) {
    ATrenderData* render_data = _atGetRenderData();
    if (render_data->nCalls+1 > DRAW_CALL_MAX) {
        atLogError("max draw calls reached");
        return;
    }

    ATdrawCall* dc = _atMakeDrawCall(type, glMode);
    dc->vao = vao;
    dc->shader = shader;
    dc->n_verts = n_verts;
    if (!dc) {
        atLogError("failed to create draw call");
        return;
    };

    render_data->drawCallArr[render_data->nCalls] = dc;
    render_data->nCalls++;
}


void atRender(void) {
    Anntwinetta* atwin = _atGetEngine();
    if (atRunProcess(atwin->internal.render_proc)) {
        atLogError("failed to run engine render process");
        return;
    };
}


// external event+input API
void atPollEvents(void) {
    Anntwinetta* atwin = _atGetEngine();
    if (atRunProcess(atwin->internal.event_proc)) {
        atLogError("failed to run engine event process");
        return;
    };
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
