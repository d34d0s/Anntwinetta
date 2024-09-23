#ifndef LOTUSECS_H
#define LOTUSECS_H

#include "lotus_types.h"

typedef struct entity_t {
    int eid;
    int cid_field;
} entity_t;

typedef enum components {
    null_c=0b0000,
    mesh_c=0b0001,
    texture_c=0b0010,
    material_c=0b0011,
    transform_c=0b0100,
    num_components
} components;

typedef struct mesh_itf {
    const unsigned int* id;
    const unsigned int* vbo;
    const unsigned int* ebo;
    const unsigned int* vao;
    const unsigned int* n_verts;
} mesh_itf;

typedef struct texture_itf {
    const unsigned int* id;
} texture_itf;

typedef struct material_itf {
    const unsigned int* id;
} material_itf;

typedef struct transform_itf {
    const unsigned int* id;
} transform_itf;


LOTUS_API bool has_comp(entity_t* e, unsigned int cid);
LOTUS_API void set_comp(entity_t* e, unsigned int cid);
LOTUS_API void rem_comp(entity_t* e, unsigned int cid);

#endif