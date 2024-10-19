#pragma once

#include "atengine.h"

// external engine api
ATWIN_API ATerrorType atInit(void);
ATWIN_API ATerrorType atRunning(void);
ATWIN_API ATerrorType atClockTick(void);

ATWIN_API ATerrorType atExit(void);
ATWIN_API void atProcEvents(void);
ATWIN_API void atProcRender(void);
ATWIN_API void atProcCamera(void);

// external rendering api
ATWIN_API void atDrawModel(int modelID);
ATWIN_API void atDrawCall(ATdrawCallType type);
ATWIN_API void atClearColor(float r, float g, float b, float a);
ATWIN_API void atDrawSelect(ATdrawCallType type, ATmeshLayout* meshLayout, ATshaderLayout* shaderLayout);

// external resource api

// meshes
ATWIN_API int atMakeMesh(int n_verts, float* vertices);
ATWIN_API ATmeshLayout* atGetMeshLayout(int index);
ATWIN_API void atDestroyMeshLayout(ATmeshLayout* layout);

// shaders
ATWIN_API int atMakeShader(const char* vertex, const char* fragment);
ATWIN_API ATshaderLayout* atGetShaderLayout(int index);
ATWIN_API void atDestroyShaderLayout(ATshaderLayout* layout);

// uniforms
ATWIN_API void atDestroyUniformLayout(ATuniformLayout* layout);
ATWIN_API ATuniformLayout* atGetUniformLayout(int shaderIndex, const char* name);
ATWIN_API void atSendUniform(ATuniformType type, int shaderIndex, const char* name);
ATWIN_API ATerrorType atSetUniform(ATuniformType type, int shaderIndex, const char* name, void* value);
ATWIN_API ATerrorType atMakeUniform(ATuniformType type, int shaderIndex, const char* name, void* value);

// materials
ATWIN_API ATmaterialLayout* atGetMaterialLayout(int index);
ATWIN_API void atDestroyMateralLayout(ATmaterialLayout* layout);
ATWIN_API int atMakeMaterial(const char* vertex, const char* fragment);

ATWIN_API ATshaderLayout* atGetMaterialShaderLayout(int index);
ATWIN_API ATuniformLayout* atGetMaterialUniformLayout(int index, const char* name);
ATWIN_API void atSendMaterialUniform(int index, ATuniformType type, const char* name);
ATWIN_API ATerrorType atSetMaterialUniform(int index, ATuniformType type, const char* name, void* value);
ATWIN_API ATerrorType atMakeMaterialUniform(int index, ATuniformType type, const char* name, void* value);

// models
ATWIN_API ATmodelLayout* atGetModelLayout(int index);
ATWIN_API int atMakeModel(int n_verts, float* vertices);
ATWIN_API void atDestroyModelLayout(ATmodelLayout* layout);

ATWIN_API ATmeshLayout* atGetModelMeshLayout(int index);
ATWIN_API ATmaterialLayout* atGetModelMaterialLayout(int index);

ATWIN_API ATerrorType atSetModelMaterial(int modelID, int materialID);
ATWIN_API ATerrorType atRemModelMaterial(int modelID, int materialID);

// external event API
ATWIN_API bool atIsKeyPressed(ATkeyboardKey key);
ATWIN_API bool atIsKeyTriggered(ATkeyboardKey key);
ATWIN_API bool atIsKeyReleased(ATkeyboardKey key);
ATWIN_API bool atIsMouseButtonPressed(ATmouseButton button);
ATWIN_API bool atIsMouseButtonTriggered(ATmouseButton button);
ATWIN_API bool atIsMouseButtonReleased(ATmouseButton button);

// external Camera API
ATWIN_API void atCamUp(void);
ATWIN_API void atCamIn(void);
ATWIN_API void atCamOut(void);
ATWIN_API void atCamLeft(void);
ATWIN_API void atCamDown(void);
ATWIN_API void atCamRight(void);
ATWIN_API ATmat4* atGetCamProj(void);
ATWIN_API ATmat4* atGetCamView(void);
ATWIN_API ATvec3* atGetCamLocation(void);
ATWIN_API void atSetCamMode(ATcamMode mode);
