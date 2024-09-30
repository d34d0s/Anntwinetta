#pragma once

#include "atengine.h"

ATWIN_API atErrorType atInit(void);
ATWIN_API atErrorType atRunning(void);
ATWIN_API atErrorType atExit(void);

ATWIN_API void atPollEvents(void);

ATWIN_API void atRender(void);
ATWIN_API void atDrawCall(ATdrawCallType type, int glMode);
ATWIN_API void atDrawCallSelect(ATdrawCallType type, int glMode, int shader, int vao, int n_verts);

ATWIN_API void atClearColor(float r, float g, float b, float a);

ATWIN_API int atMakeMesh(int n_verts, float* vertices);
ATWIN_API ATmeshLayout* atGetMeshLayout(int index);
ATWIN_API void atDestroyMeshLayout(ATmeshLayout* layout);

ATWIN_API int atMakeShader(const char* vertex, const char* fragment);
ATWIN_API ATshaderLayout* atGetShaderLayout(int index);
ATWIN_API void atDestroyShaderLayout(ATshaderLayout* layout);