#ifndef ATMATHH
#define ATMATHH

#include "attypes.h"

#define _PI_ 3.14159265358979323846

typedef struct atVec2 {
    float x, y;
} atVec2;

typedef struct atVec2I {
    b32 x, y;
} atVec2I;

typedef struct atVec2B {
    b8 x, y;
} atVec2B;

typedef struct atVec3 {
    float x, y, z;
} atVec3;

typedef struct atVec3I {
    b32 x, y, z;
} atVec3I;

typedef struct atVec3B {
    b8 x, y, z;
} atVec3B;

typedef struct atVec4 {
    float x, y, z, w;
} atVec4;

typedef struct atVec4I {
    b32 x, y, z, w;
} atVec4I;

typedef struct atVec4B {
    b8 x, y, z, w;
} atVec4B;

typedef struct atMat4{
    float m[16];
} atMat4;

ATWIN_API float atToRadians(float deg);

ATWIN_API atVec2 atNewVec2(float x, float y);
ATWIN_API atVec2 atScaleVec2(atVec2 v, float scale);
ATWIN_API atVec2 atAddVec2(atVec2 v1, atVec2 v2);
ATWIN_API atVec2 atSubVec2(atVec2 v1, atVec2 v2);
ATWIN_API float atDotVec2(atVec2 v1, atVec2 v2);
ATWIN_API atVec2 atNormVec2(atVec2 v);

ATWIN_API atVec3 atNewVec3(float x, float y, float z);
ATWIN_API atVec3 atScaleVec3(atVec3 v, float scale);
ATWIN_API atVec3 atAddVec3(atVec3 v1, atVec3 v2);
ATWIN_API atVec3 atSubVec3(atVec3 v1, atVec3 v2);
ATWIN_API float atDotVec3(atVec3 a, atVec3 b);
ATWIN_API atVec3 atNormVec3(atVec3 v);
ATWIN_API atVec3 atCrossVec3(atVec3 v1, atVec3 v2);

ATWIN_API atVec4 atNewVec4(float x, float y, float z, float w);
ATWIN_API atVec4 atScaleVec4(atVec4 v, float scale);
ATWIN_API atVec4 atAddVec4(atVec4 v1, atVec4 v2);
ATWIN_API atVec4 atSubVec4(atVec4 v1, atVec4 v2);
ATWIN_API float atDotVec4(atVec4 v1, atVec4 v2);
ATWIN_API atVec4 atNormVec4(atVec4 v);

ATWIN_API atMat4 atIdentity();
ATWIN_API atMat4 atMulMat4(atMat4 a, atMat4 b);
ATWIN_API atVec3 atMulMat4Vec3(atMat4 m, atVec3 v);
ATWIN_API atMat4 atTransMat4(float x, float y, float z);
ATWIN_API atMat4 atScaleMat4(float x, float y, float z);
ATWIN_API atMat4 atLookAt(atVec3 eye, atVec3 center, atVec3 up);
ATWIN_API atMat4 atRotMat4(float x, float y, float z, float angle);
ATWIN_API atMat4 atPerspective(float fov, float aspect, float near, float far);
ATWIN_API atMat4 atOrtho(float left, float right, float bottom, float top, float near, float far);

#endif