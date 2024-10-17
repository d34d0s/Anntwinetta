#pragma once

#include "../attypes.h"
#include "../athelpers.h"

#include "../resource/atwindow.h"
#include "../backend/GL/atGLAPI.h"


#define DRAW_CALL_MAX 1024

typedef enum ATdrawCallType {
    DRAW_CLEAR          =0x0000,
    DRAW_MESH           =0x0001,
    DRAW_TYPES
} ATdrawCallType;

typedef enum ATdrawMode {
    POINT_MODE         =0x0000, // GL EQUIVALENT
    LINE_MODE          =0x0001, // GL EQUIVALENT
    TRIANGLE_MODE      =0x0004, // GL EQUIVALENT
    DRAW_MODES
} ATdrawMode;

typedef struct ATdrawCall {
    int vao;
    int type;
    int glMode;
    int shader;
    int n_verts;
} ATdrawCall;

typedef struct ATrenderData {
    int glMode;
    int passes;
    int nCalls;
    ATwindow* windowPtr;
    float clearColor[4];
    ATdrawCall** drawCallArr;
} ATrenderData;
ATrenderData* _atGetRenderData(void);

void _atDestroyDrawCall(ATdrawCall* dc);
ATdrawCall* _atMakeDrawCall(ATdrawCallType type, int glMode);

ATerrorType _atPrepRender(void*);
ATerrorType _atMainRender(void*);
ATerrorType _atPostRender(void*);
