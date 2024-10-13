#pragma once

#include "atengine.h"

ATWIN_API ATerrorType atInit(void);
ATWIN_API ATerrorType atRunning(void);
ATWIN_API ATerrorType atClockTick(void);
ATWIN_API ATerrorType atExit(void);

ATWIN_API void atProcEvents(void);
ATWIN_API void atProcRender(void);
ATWIN_API void atProcCamera(void);

ATWIN_API void atDrawCall(ATdrawCallType type, int glMode);
ATWIN_API void atClearColor(float r, float g, float b, float a);
ATWIN_API void atDrawCallSelect(ATdrawCallType type, int glMode, ATmeshLayout* meshLayout, ATshaderLayout* shaderLayout);

// external resource api
ATWIN_API int atMakeMesh(int n_verts, float* vertices);
ATWIN_API ATmeshLayout* atGetMeshLayout(int index);
ATWIN_API void atDestroyMeshLayout(ATmeshLayout* layout);

ATWIN_API int atMakeShader(const char* vertex, const char* fragment);
ATWIN_API ATshaderLayout* atGetShaderLayout(int index);
ATWIN_API void atDestroyShaderLayout(ATshaderLayout* layout);

ATWIN_API ATerrorType atMakeUniform(ATuniformType type, int shaderIndex, const char* name, void* value);
ATWIN_API ATuniformLayout* atGetUniformLayout(int shaderIndex, const char* name);
ATWIN_API void atSetUniform(ATuniformType type, int shaderIndex, const char* name);

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
