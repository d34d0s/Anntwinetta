#ifndef LOTUSMATH_H
#define LOTUSMATH_H

#include <math.h>
#include "lotus_types.h"

#define LM_PI       3.14159265358979323846   // pi

typedef struct LMvec2 {
    float x, y;
} LMvec2;

typedef struct LMvec2_i {
    int x, y;
} LMvec2_i;

typedef struct LMvec3 {
    float x, y, z;
} LMvec3;

typedef struct LMvec3_i {
    int x, y, z;
} LMvec3_i;

typedef struct LMvec4 {
    float x, y, z, w;
} LMvec4;

typedef struct LMmat4{
    float m[16];
} LMmat4;

LOTUS_API float lmRadians(float deg);

LOTUS_API LMvec2 lmVec2(float x, float y);
LOTUS_API LMvec2 lmScaleVec2(LMvec2 v, float scale);
LOTUS_API LMvec2 lmAddVec2(LMvec2 v1, LMvec2 v2);
LOTUS_API LMvec2 lmSubVec2(LMvec2 v1, LMvec2 v2);
LOTUS_API float lmDotVec2(LMvec2 v1, LMvec2 v2);
LOTUS_API LMvec2 lmNormVec2(LMvec2 v);

LOTUS_API LMvec3 lmVec3(float x, float y, float z);
LOTUS_API LMvec3 lmScaleVec3(LMvec3 v, float scale);
LOTUS_API LMvec3 lmAddVec3(LMvec3 v1, LMvec3 v2);
LOTUS_API LMvec3 lmSubVec3(LMvec3 v1, LMvec3 v2);
LOTUS_API float lmDotVec3(LMvec3 a, LMvec3 b);
LOTUS_API LMvec3 lmNormVec3(LMvec3 v);
LOTUS_API LMvec3 lmCrossVec3(LMvec3 v1, LMvec3 v2);

LOTUS_API LMvec4 lmVec4(float x, float y, float z, float w);
LOTUS_API LMvec4 lmScaleVec4(LMvec4 v, float scale);
LOTUS_API LMvec4 lmAddVec4(LMvec4 v1, LMvec4 v2);
LOTUS_API LMvec4 lmSubVec4(LMvec4 v1, LMvec4 v2);
LOTUS_API float lmDotVec4(LMvec4 v1, LMvec4 v2);
LOTUS_API LMvec4 lmNormVec4(LMvec4 v);

LOTUS_API LMmat4 lmIdentity();
LOTUS_API LMmat4 lmMulMat4(LMmat4 a, LMmat4 b);
LOTUS_API LMvec3 lmMulMat4Vec3(LMmat4 m, LMvec3 v);
LOTUS_API LMmat4 lmTransMat4(float x, float y, float z);
LOTUS_API LMmat4 lmScaleMat4(float x, float y, float z);
LOTUS_API LMmat4 lmLookAt(LMvec3 eye, LMvec3 center, LMvec3 up);
LOTUS_API LMmat4 lmRotMat4(float x, float y, float z, float angle);
LOTUS_API LMmat4 lmPerspective(float fov, float aspect, float near, float far);
LOTUS_API LMmat4 lmOrtho(float left, float right, float bottom, float top, float near, float far);

#endif