#ifndef ATMATHH
#define ATMATHH

#include "attypes.h"

#define _PI_ 3.14159265358979323846

typedef struct ATvec2 {
    float x, y;
} ATvec2;

typedef struct ATvec2i {
    b32 x, y;
} ATvec2i;

typedef struct ATvec2b {
    b8 x, y;
} ATvec2b;

typedef struct ATvec3 {
    float x, y, z;
} ATvec3;

typedef struct ATvec3i {
    b32 x, y, z;
} ATvec3i;

typedef struct ATvec3b {
    b8 x, y, z;
} ATvec3b;

typedef struct ATvec4 {
    float x, y, z, w;
} ATvec4;

typedef struct ATvec4i {
    b32 x, y, z, w;
} ATvec4i;

typedef struct ATvec4b {
    b8 x, y, z, w;
} ATvec4b;

typedef struct ATmat4{
    float m[16];
} ATmat4;

ATWIN_API float atToRadians(float deg);

ATWIN_API ATvec2 atNewVec2(float x, float y);
ATWIN_API ATvec2 atScaleVec2(ATvec2 v, float scale);
ATWIN_API ATvec2 atAddVec2(ATvec2 v1, ATvec2 v2);
ATWIN_API ATvec2 atSubVec2(ATvec2 v1, ATvec2 v2);
ATWIN_API float atDotVec2(ATvec2 v1, ATvec2 v2);
ATWIN_API ATvec2 atNormVec2(ATvec2 v);

ATWIN_API ATvec3 atNewVec3(float x, float y, float z);
ATWIN_API ATvec3 atScaleVec3(ATvec3 v, float scale);
ATWIN_API ATvec3 atAddVec3(ATvec3 v1, ATvec3 v2);
ATWIN_API ATvec3 atSubVec3(ATvec3 v1, ATvec3 v2);
ATWIN_API float atDotVec3(ATvec3 a, ATvec3 b);
ATWIN_API ATvec3 atNormVec3(ATvec3 v);
ATWIN_API ATvec3 atCrossVec3(ATvec3 v1, ATvec3 v2);

ATWIN_API ATvec4 atNewVec4(float x, float y, float z, float w);
ATWIN_API ATvec4 atScaleVec4(ATvec4 v, float scale);
ATWIN_API ATvec4 atAddVec4(ATvec4 v1, ATvec4 v2);
ATWIN_API ATvec4 atSubVec4(ATvec4 v1, ATvec4 v2);
ATWIN_API float atDotVec4(ATvec4 v1, ATvec4 v2);
ATWIN_API ATvec4 atNormVec4(ATvec4 v);

ATWIN_API ATmat4 atIdentity();
ATWIN_API ATmat4 atMulMat4(ATmat4 a, ATmat4 b);
ATWIN_API ATvec3 atMulMat4Vec3(ATmat4 m, ATvec3 v);
ATWIN_API ATmat4 atTransMat4(float x, float y, float z);
ATWIN_API ATmat4 atScaleMat4(float x, float y, float z);
ATWIN_API ATmat4 atLookAt(ATvec3 eye, ATvec3 center, ATvec3 up);
ATWIN_API ATmat4 atRotMat4(float x, float y, float z, float angle);
ATWIN_API ATmat4 atPerspective(float fov, float aspect, float near, float far);
ATWIN_API ATmat4 atOrtho(float left, float right, float bottom, float top, float near, float far);

#endif