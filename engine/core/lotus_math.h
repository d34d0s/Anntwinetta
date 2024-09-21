#ifndef LOTUSMATH_H
#define LOTUSMATH_H

#include <math.h>
#include "lotus_types.h"

#define LM_PI       3.14159265358979323846   // pi

typedef struct lm_vec2 {
    float x, y;
} lm_vec2;

typedef struct lm_vec2_i {
    b32 x, y;
} lm_vec2_i;

typedef struct lm_vec2_b {
    b8 x, y;
} lm_vec2_b;

typedef struct lm_vec3 {
    float x, y, z;
} lm_vec3;

typedef struct lm_vec3_i {
    b32 x, y, z;
} lm_vec3_i;

typedef struct lm_vec3_b {
    b8 x, y, z;
} lm_vec3_b;

typedef struct lm_vec4 {
    float x, y, z, w;
} lm_vec4;

typedef struct lm_vec4_i {
    b32 x, y, z, w;
} lm_vec4_i;

typedef struct lm_vec4_b {
    b8 x, y, z, w;
} lm_vec4_b;

typedef struct lm_mat4{
    float m[16];
} lm_mat4;

LOTUS_API float lm_radians(float deg);

LOTUS_API lm_vec2 lm_new_vec2(float x, float y);
LOTUS_API lm_vec2 lm_scale_vec2(lm_vec2 v, float scale);
LOTUS_API lm_vec2 lm_add_vec2(lm_vec2 v1, lm_vec2 v2);
LOTUS_API lm_vec2 lm_sub_vec2(lm_vec2 v1, lm_vec2 v2);
LOTUS_API float lm_dot_vec2(lm_vec2 v1, lm_vec2 v2);
LOTUS_API lm_vec2 lm_norm_vec2(lm_vec2 v);

LOTUS_API lm_vec3 lm_new_vec3(float x, float y, float z);
LOTUS_API lm_vec3 lm_scale_vec3(lm_vec3 v, float scale);
LOTUS_API lm_vec3 lm_add_vec3(lm_vec3 v1, lm_vec3 v2);
LOTUS_API lm_vec3 lm_sub_vec3(lm_vec3 v1, lm_vec3 v2);
LOTUS_API float lm_dot_vec3(lm_vec3 a, lm_vec3 b);
LOTUS_API lm_vec3 lm_norm_vec3(lm_vec3 v);
LOTUS_API lm_vec3 lm_cross_vec3(lm_vec3 v1, lm_vec3 v2);

LOTUS_API lm_vec4 lm_new_vec4(float x, float y, float z, float w);
LOTUS_API lm_vec4 lm_scale_vec4(lm_vec4 v, float scale);
LOTUS_API lm_vec4 lm_add_vec4(lm_vec4 v1, lm_vec4 v2);
LOTUS_API lm_vec4 lm_sub_vec4(lm_vec4 v1, lm_vec4 v2);
LOTUS_API float lm_dot_vec4(lm_vec4 v1, lm_vec4 v2);
LOTUS_API lm_vec4 lm_norm_vec4(lm_vec4 v);

LOTUS_API lm_mat4 lm_identity();
LOTUS_API lm_mat4 lm_mul_mat4(lm_mat4 a, lm_mat4 b);
LOTUS_API lm_vec3 lm_mul_mat4_vec3(lm_mat4 m, lm_vec3 v);
LOTUS_API lm_mat4 lm_trans_mat4(float x, float y, float z);
LOTUS_API lm_mat4 lm_scale_mat4(float x, float y, float z);
LOTUS_API lm_mat4 lm_look_at(lm_vec3 eye, lm_vec3 center, lm_vec3 up);
LOTUS_API lm_mat4 lm_rot_mat4(float x, float y, float z, float angle);
LOTUS_API lm_mat4 lm_perspective(float fov, float aspect, float near, float far);
LOTUS_API lm_mat4 lm_ortho(float left, float right, float bottom, float top, float near, float far);

#endif