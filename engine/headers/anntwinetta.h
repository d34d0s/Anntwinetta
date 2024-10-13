#pragma once

#include "atengine.h"

ATWIN_API atErrorType atInit(void);
ATWIN_API atErrorType atRunning(void);
ATWIN_API atErrorType atExit(void);

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

ATWIN_API atErrorType atMakeUniform(ATuniformType type, int shaderIndex, const char* name, void* value);
ATWIN_API ATuniformLayout* atGetUniformLayout(int shaderIndex, const char* name);
ATWIN_API void atSetUniform(ATuniformType type, int shaderIndex, const char* name);

// external Camera API
ATWIN_API ATmat4* atGetProjMatrix(void);
ATWIN_API ATmat4* atGetViewMatrix(void);
