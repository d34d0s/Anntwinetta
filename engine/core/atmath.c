#include "../headers/atmath.h"

float atToRadians(float deg) {
    return deg * _PI_/180.0;
}

// Creates a atVec2
atVec2 atNewVec2(float x, float y) {
    return (atVec2){x, y};
}

// Scales a atVec2 by a scalar value
atVec2 atScaleVec2(atVec2 v, float scale) {
    return (atVec2){v.x * scale, v.y * scale};
}

// Adds two Vec2s
atVec2 atAddVec2(atVec2 v1, atVec2 v2) {
    return (atVec2){v1.x + v2.x, v1.y + v2.y};
}

// Subtracts one atVec2 from another
atVec2 atSubVec2(atVec2 v1, atVec2 v2) {
    return (atVec2){v1.x - v2.x, v1.y - v2.y};
}

// Dot product of two Vec2s
float atDotVec2(atVec2 v1, atVec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

// Normalize a atVec2 (make it unit length)
atVec2 atNormVec2(atVec2 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y);
    return atScaleVec2(v, 1.0f / length);
}


// Creates a atVec3
atVec3 atNewVec3(float x, float y, float z) {
    return (atVec3){x, y, z};
}
// Scales a vector by a scalar value
atVec3 atScaleVec3(atVec3 v, float scale) {
    atVec3 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    result.z = v.z * scale;
    return result;
}

// Adds two vectors
atVec3 atAddVec3(atVec3 v1, atVec3 v2) {
    atVec3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

// Subtracts one vector from another
atVec3 atSubVec3(atVec3 v1, atVec3 v2) {
    atVec3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

float atDotVec3(atVec3 a, atVec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Normalize a vector (make it unit length)
atVec3 atNormVec3(atVec3 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return atScaleVec3(v, 1.0f / length);
}

// Cross product of two vectors
atVec3 atCrossVec3(atVec3 v1, atVec3 v2) {
    atVec3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}


// Creates a atVec4
atVec4 atNewVec4(float x, float y, float z, float w) {
    return (atVec4){x, y, z, w};
}

// Scales a atVec4 by a scalar value
atVec4 atScaleVec4(atVec4 v, float scale) {
    return (atVec4){v.x * scale, v.y * scale, v.z * scale, v.w * scale};
}

// Adds two Vec4s
atVec4 atAddVec4(atVec4 v1, atVec4 v2) {
    return (atVec4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

// Subtracts one atVec4 from another
atVec4 atSubVec4(atVec4 v1, atVec4 v2) {
    return (atVec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

// Dot product of two Vec4s
float atDotVec4(atVec4 v1, atVec4 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Normalize a atVec4 (make it unit length)
atVec4 atNormVec4(atVec4 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    return atScaleVec4(v, 1.0f / length);
}


atMat4 atIdentity() {
    atMat4 result = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f};
    return result;
}

atVec3 atMulMat4Vec3(atMat4 m, atVec3 v) {
    atVec3 result;
    result.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12];
    result.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13];
    result.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14];
    return result;
}

atMat4 atTransMat4(float x, float y, float z) {
    atMat4 result = atIdentity();
    result.m[12] = x;
    result.m[13] = y;
    result.m[14] = z;
    return result;
}

atMat4 atRotMat4(float x, float y, float z, float angle) {
    atMat4 result = atIdentity();
    float rad = atToRadians(angle);
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

atMat4 atScaleMat4(float x, float y, float z) {
    atMat4 result = atIdentity();
    result.m[0] = x;
    result.m[5] = y;
    result.m[10] = z;
    return result;
}

atMat4 atMulMat4(atMat4 a, atMat4 b) {
    atMat4 result = {0};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            for (int i = 0; i < 4; ++i) {
                result.m[row * 4 + col] += a.m[row * 4 + i] * b.m[i * 4 + col];
            }
        }
    }
    return result;
}

atMat4 atOrtho(float left, float right, float bottom, float top, float near, float far) {
    atMat4 result = atIdentity();
    result.m[0] = 2.0f / (right - left);
    result.m[5] = 2.0f / (top - bottom);
    result.m[10] = -2.0f / (far - near);
    result.m[12] = -(right + left) / (right - left);
    result.m[13] = -(top + bottom) / (top - bottom);
    result.m[14] = -(far + near) / (far - near);
    return result;
}

atMat4 atPerspective(float fov, float aspect, float near, float far) {
    float tan_half_fov = tanf(fov / 2.0f);
    atMat4 result = {0};
    result.m[0] = 1.0f / (aspect * tan_half_fov);
    result.m[5] = 1.0f / tan_half_fov;
    result.m[10] = -(far + near) / (far - near);
    result.m[11] = -1.0f;
    result.m[14] = -(2.0f * far * near) / (far - near);
    return result;
}

atMat4 atLookAt(atVec3 eye, atVec3 center, atVec3 up) {
    atVec3 f = atNormVec3(atSubVec3(center, eye));
    atVec3 s = atNormVec3(atCrossVec3(f, up));
    atVec3 u = atCrossVec3(s, f);

    atMat4 result = atIdentity();
    result.m[0] = s.x;
    result.m[4] = s.y;
    result.m[8] = s.z;
    result.m[1] = u.x;
    result.m[5] = u.y;
    result.m[9] = u.z;
    result.m[2] = -f.x;
    result.m[6] = -f.y;
    result.m[10] = -f.z;
    result.m[12] = -atDotVec3(s, eye);
    result.m[13] = -atDotVec3(u, eye);
    result.m[14] = atDotVec3(f, eye);
    return result;
}
