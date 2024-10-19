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

void atDrawModel(int modelID) {
    ATmodelData* model_data = _atGetModelData();
    ATrenderData* render_data = _atGetRenderData();
    ATmaterialData* material_data = _atGetMaterialData();
    
    if (render_data->nCalls+1 > DRAW_CALL_MAX) {
        atLogError("max draw calls reached");
        return;
    }
    
    atDrawSelect(
        DRAW_MODEL,
        atGetModelMeshLayout(modelID),
        atGetShaderLayout(material_data->shader[model_data->material[modelID]])
    );
}

void atDrawCall(ATdrawCallType type) {
    ATrenderData* render_data = _atGetRenderData();
    if (render_data->nCalls+1 > DRAW_CALL_MAX) {
        atLogError("max draw calls reached");
        return;
    }

    ATdrawCall* dc = _atMakeDrawCall(type);
    if (!dc) {
        atLogError("failed to create draw call");
        return;
    };

    render_data->drawCallArr[render_data->nCalls] = dc;
    render_data->nCalls++;
}

void atDrawSelect(ATdrawCallType type, ATmeshLayout* meshLayout, ATshaderLayout* shaderLayout) {
    ATrenderData* render_data = _atGetRenderData();
    if (render_data->nCalls+1 > DRAW_CALL_MAX) {
        atLogError("max draw calls reached");
        return;
    }

    ATdrawCall* dc = _atMakeDrawCall(type);
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

// uniform
void atDestroyUniformLayout(ATuniformLayout* layout) {
    _atDestroyUniformLayout(layout);
}

ATerrorType atMakeUniform(ATuniformType type, int index, const char* name, void* value) {
    ATshaderData* shader_data = _atGetShaderData();
    return _atMakeUniform(shader_data, index, type, name, value);
}

ATerrorType atSetUniform(ATuniformType type, int index, const char* name, void* value) {
    ATshaderData* shader_data = _atGetShaderData();
    return _atSetUniform(shader_data, index, type, name, value);
}

void atSendUniform(ATuniformType type, int index, const char* name) {
    ATshaderData* shader_data = _atGetShaderData();
    ATuniformLayout* uniform = atGetUniformLayout(index, name);
    atglSetUniformValue(type, shader_data->program[index], uniform->location, uniform->value);
    _atDestroyUniformLayout(uniform);
}

ATuniformLayout* atGetUniformLayout(int index, const char* name) {
    ATshaderData* shader_data = _atGetShaderData();
    return _atGetUniformLayout(shader_data, index, name);
}

// model
void atDestroyModelLayout(ATmodelLayout* layout) {
    _atDestroyModelLayout(layout);
}

int atMakeModel(int n_verts, float* vertices) {
    ATmeshData* mesh_data = _atGetMeshData();
    ATmodelData* model_data = _atGetModelData();
    return _atSetModelData(model_data, mesh_data, n_verts, vertices);
}

ATmodelLayout* atGetModelLayout(int index) {
    ATmodelData* model_data = _atGetModelData();
    return _atGetModelLayout(model_data, index);
}

ATmeshLayout* atGetModelMeshLayout(int index) {
    ATmeshData* mesh_data = _atGetMeshData();
    ATmodelData* model_data = _atGetModelData();
    return _atGetMeshLayout(mesh_data, model_data->mesh[index]);
}

ATerrorType atSetModelMaterial(int modelID, int materialID) {
    ATmodelData* model_data = _atGetModelData();
    ATmaterialData* material_data = _atGetMaterialData();
    
    if (materialID < 0 || materialID >= material_data->count) {
        return ERR_MATERIAL;
    }
    
    return _atSetModelMaterial(model_data, modelID, materialID);
}

ATerrorType atRemModelMaterial(int modelID, int materialID) {
    ATmodelData* model_data = _atGetModelData();
    ATmaterialData* material_data = _atGetMaterialData();
    
    if (materialID < 0 || materialID >= material_data->count) {
        return ERR_MATERIAL;
    }
    
    return _atSetModelMaterial(model_data, modelID, materialID);
}

ATmaterialLayout* atGetModelMaterialLayout(int index) {
    ATmodelData* model_data = _atGetModelData();
    ATmaterialData* material_data = _atGetMaterialData();
    return _atGetMaterialLayout(material_data, model_data->material[index]);
}

// material
int atMakeMaterial(const char* vertex, const char* fragment) {
    ATshaderData* shaderData = _atGetShaderData();
    ATmaterialData* materialData = _atGetMaterialData();
    return _atSetMaterialData(materialData, shaderData, vertex, fragment);
}

void atDestroyMateralLayout(ATmaterialLayout* layout) {
    _atDestroyMaterialLayout(layout);
}

ATmaterialLayout* atGetMaterialLayout(int index) {
    ATmaterialData* materialData = _atGetMaterialData();
    return _atGetMaterialLayout(materialData, index);
}


ATshaderLayout* atGetMaterialShaderLayout(int index) {
    ATshaderData* shaderData = _atGetShaderData();
    ATmaterialData* materialData = _atGetMaterialData();
    return _atGetShaderLayout(shaderData, materialData->shader[index]);
}

ATuniformLayout* atGetMaterialUniformLayout(int index, const char* name) {
    ATshaderData* shaderData = _atGetShaderData();
    ATmaterialData* materialData = _atGetMaterialData();
    return _atGetUniformLayout(shaderData, materialData->shader[index], name);
}

ATerrorType atMakeMaterialUniform(int index, ATuniformType type, const char* name, void* value) {
    ATmaterialData* materialData = _atGetMaterialData();
    return atMakeUniform(type, materialData->shader[index], name, value);
}

ATerrorType atSetMaterialUniform(int index, ATuniformType type, const char* name, void* value) {
    ATmaterialData* materialData = _atGetMaterialData();
    return atSetUniform(type, materialData->shader[index], name, value);
}

void atSendMaterialUniform(int index, ATuniformType type, const char* name) {
    ATmaterialData* materialData = _atGetMaterialData();
    atSendUniform(type, materialData->shader[index], name);
}

