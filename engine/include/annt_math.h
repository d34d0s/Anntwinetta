#ifndef ANNT_MATH_H
#define ANNT_MATH_H

#include "annt_types.h"

#define ANNT_PI       3.14159265358979323846   // pi

typedef struct at_vec2 {
    float x, y;
} at_vec2;

typedef struct at_vec2_i {
    b32 x, y;
} at_vec2_i;

typedef struct at_vec2_b {
    b8 x, y;
} at_vec2_b;

typedef struct at_vec3 {
    float x, y, z;
} at_vec3;

typedef struct at_vec3_i {
    b32 x, y, z;
} at_vec3_i;

typedef struct at_vec3_b {
    b8 x, y, z;
} at_vec3_b;

typedef struct at_vec4 {
    float x, y, z, w;
} at_vec4;

typedef struct at_vec4_i {
    b32 x, y, z, w;
} at_vec4_i;

typedef struct at_vec4_b {
    b8 x, y, z, w;
} at_vec4_b;

typedef struct at_mat4{
    float m[16];
} at_mat4;

ANNT_API float at_to_radians(float deg);

ANNT_API at_vec2 at_new_vec2(float x, float y);
ANNT_API at_vec2 at_scale_vec2(at_vec2 v, float scale);
ANNT_API at_vec2 at_add_vec2(at_vec2 v1, at_vec2 v2);
ANNT_API at_vec2 at_sub_vec2(at_vec2 v1, at_vec2 v2);
ANNT_API float at_dot_vec2(at_vec2 v1, at_vec2 v2);
ANNT_API at_vec2 at_norm_vec2(at_vec2 v);

ANNT_API at_vec3 at_new_vec3(float x, float y, float z);
ANNT_API at_vec3 at_scale_vec3(at_vec3 v, float scale);
ANNT_API at_vec3 at_add_vec3(at_vec3 v1, at_vec3 v2);
ANNT_API at_vec3 at_sub_vec3(at_vec3 v1, at_vec3 v2);
ANNT_API float at_dot_vec3(at_vec3 a, at_vec3 b);
ANNT_API at_vec3 at_norm_vec3(at_vec3 v);
ANNT_API at_vec3 at_cross_vec3(at_vec3 v1, at_vec3 v2);

ANNT_API at_vec4 at_new_vec4(float x, float y, float z, float w);
ANNT_API at_vec4 at_scale_vec4(at_vec4 v, float scale);
ANNT_API at_vec4 at_add_vec4(at_vec4 v1, at_vec4 v2);
ANNT_API at_vec4 at_sub_vec4(at_vec4 v1, at_vec4 v2);
ANNT_API float at_dot_vec4(at_vec4 v1, at_vec4 v2);
ANNT_API at_vec4 at_norm_vec4(at_vec4 v);

ANNT_API at_mat4 at_identity();
ANNT_API at_mat4 at_mul_mat4(at_mat4 a, at_mat4 b);
ANNT_API at_vec3 at_mul_mat4_vec3(at_mat4 m, at_vec3 v);
ANNT_API at_mat4 at_trans_mat4(float x, float y, float z);
ANNT_API at_mat4 at_scale_mat4(float x, float y, float z);
ANNT_API at_mat4 at_look_at(at_vec3 eye, at_vec3 center, at_vec3 up);
ANNT_API at_mat4 at_rot_mat4(float x, float y, float z, float angle);
ANNT_API at_mat4 at_perspective(float fov, float aspect, float near, float far);
ANNT_API at_mat4 at_ortho(float left, float right, float bottom, float top, float near, float far);

#endif