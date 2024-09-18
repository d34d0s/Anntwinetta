#include "../../headers/core/Lotusmath.h"

float lmRadians(float deg) { return deg * LM_PI/180.0; }

// Creates a LMvec2
LMvec2 lmVec2(float x, float y) {
    return (LMvec2){x, y};
}

// Scales a LMvec2 by a scalar value
LMvec2 lmScaleVec2(LMvec2 v, float scale) {
    return (LMvec2){v.x * scale, v.y * scale};
}

// Adds two Vec2s
LMvec2 lmAddVec2(LMvec2 v1, LMvec2 v2) {
    return (LMvec2){v1.x + v2.x, v1.y + v2.y};
}

// Subtracts one LMvec2 from another
LMvec2 lmSubVec2(LMvec2 v1, LMvec2 v2) {
    return (LMvec2){v1.x - v2.x, v1.y - v2.y};
}

// Dot product of two Vec2s
float lmDotVec2(LMvec2 v1, LMvec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

// Normalize a LMvec2 (make it unit length)
LMvec2 lmNormVec2(LMvec2 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y);
    return lmScaleVec2(v, 1.0f / length);
}


// Creates a LMvec3
LMvec3 lmVec3(float x, float y, float z) {
    return (LMvec3){x, y, z};
}
// Scales a vector by a scalar value
LMvec3 lmScaleVec3(LMvec3 v, float scale) {
    LMvec3 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    result.z = v.z * scale;
    return result;
}

// Adds two vectors
LMvec3 lmAddVec3(LMvec3 v1, LMvec3 v2) {
    LMvec3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

// Subtracts one vector from another
LMvec3 lmSubVec3(LMvec3 v1, LMvec3 v2) {
    LMvec3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

float lmDotVec3(LMvec3 a, LMvec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Normalize a vector (make it unit length)
LMvec3 lmNormVec3(LMvec3 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return lmScaleVec3(v, 1.0f / length);
}

// Cross product of two vectors
LMvec3 lmCrossVec3(LMvec3 v1, LMvec3 v2) {
    LMvec3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}


// Creates a LMvec4
LMvec4 lmVec4(float x, float y, float z, float w) {
    return (LMvec4){x, y, z, w};
}

// Scales a LMvec4 by a scalar value
LMvec4 lmScaleVec4(LMvec4 v, float scale) {
    return (LMvec4){v.x * scale, v.y * scale, v.z * scale, v.w * scale};
}

// Adds two Vec4s
LMvec4 lmAddVec4(LMvec4 v1, LMvec4 v2) {
    return (LMvec4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

// Subtracts one LMvec4 from another
LMvec4 lmSubVec4(LMvec4 v1, LMvec4 v2) {
    return (LMvec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

// Dot product of two Vec4s
float lmDotVec4(LMvec4 v1, LMvec4 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Normalize a LMvec4 (make it unit length)
LMvec4 lmNormVec4(LMvec4 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    return lmScaleVec4(v, 1.0f / length);
}


LMmat4 lmIdentity() {
    LMmat4 result = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f};
    return result;
}

LMvec3 lmMulMat4Vec3(LMmat4 m, LMvec3 v) {
    LMvec3 result;
    result.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12];
    result.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13];
    result.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14];
    return result;
}

LMmat4 lmTransMat4(float x, float y, float z) {
    LMmat4 result = lmIdentity();
    result.m[12] = x;
    result.m[13] = y;
    result.m[14] = z;
    return result;
}

LMmat4 lmRotMat4(float x, float y, float z, float angle) {
    LMmat4 result = lmIdentity();
    float rad = lmRadians(angle);
    float cos_theta = cosf(rad);
    float sin_theta = sinf(rad);

    float axis_len = sqrtf(x * x + y * y + z * z);
    if (axis_len > 0.0f) {
        x /= axis_len;
        y /= axis_len;
        z /= axis_len;
    }

    result.m[0] = cos_theta + (1 - cos_theta) * x * x;
    result.m[1] = (1 - cos_theta) * x * y + sin_theta * z;
    result.m[2] = (1 - cos_theta) * x * z - sin_theta * y;

    result.m[4] = (1 - cos_theta) * y * x - sin_theta * z;
    result.m[5] = cos_theta + (1 - cos_theta) * y * y;
    result.m[6] = (1 - cos_theta) * y * z + sin_theta * x;

    result.m[8] = (1 - cos_theta) * z * x + sin_theta * y;
    result.m[9] = (1 - cos_theta) * z * y - sin_theta * x;
    result.m[10] = cos_theta + (1 - cos_theta) * z * z;

    return result;
}

LMmat4 lmScaleMat4(float x, float y, float z) {
    LMmat4 result = lmIdentity();
    result.m[0] = x;
    result.m[5] = y;
    result.m[10] = z;
    return result;
}

LMmat4 lmMulMat4(LMmat4 a, LMmat4 b) {
    LMmat4 result = {0};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            for (int i = 0; i < 4; ++i) {
                result.m[row * 4 + col] += a.m[row * 4 + i] * b.m[i * 4 + col];
            }
        }
    }
    return result;
}

LMmat4 lmOrtho(float left, float right, float bottom, float top, float near, float far) {
    LMmat4 result = lmIdentity();
    result.m[0] = 2.0f / (right - left);
    result.m[5] = 2.0f / (top - bottom);
    result.m[10] = -2.0f / (far - near);
    result.m[12] = -(right + left) / (right - left);
    result.m[13] = -(top + bottom) / (top - bottom);
    result.m[14] = -(far + near) / (far - near);
    return result;
}

LMmat4 lmPerspective(float fov, float aspect, float near, float far) {
    float tan_half_fov = tanf(fov / 2.0f);
    LMmat4 result = {0};
    result.m[0] = 1.0f / (aspect * tan_half_fov);
    result.m[5] = 1.0f / tan_half_fov;
    result.m[10] = -(far + near) / (far - near);
    result.m[11] = -1.0f;
    result.m[14] = -(2.0f * far * near) / (far - near);
    return result;
}

LMmat4 lmLookAt(LMvec3 eye, LMvec3 center, LMvec3 up) {
    LMvec3 f = lmNormVec3(lmSubVec3(center, eye));
    LMvec3 s = lmNormVec3(lmCrossVec3(f, up));
    LMvec3 u = lmCrossVec3(s, f);

    LMmat4 result = lmIdentity();
    result.m[0] = s.x;
    result.m[4] = s.y;
    result.m[8] = s.z;
    result.m[1] = u.x;
    result.m[5] = u.y;
    result.m[9] = u.z;
    result.m[2] = -f.x;
    result.m[6] = -f.y;
    result.m[10] = -f.z;
    result.m[12] = -lmDotVec3(s, eye);
    result.m[13] = -lmDotVec3(u, eye);
    result.m[14] = lmDotVec3(f, eye);
    return result;
}
