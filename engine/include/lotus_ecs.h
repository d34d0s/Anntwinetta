#ifndef LOTUSECS_H
#define LOTUSECS_H

#include "lotus_types.h"

typedef struct lotus_entity_t {
    int eid;
    int cid_field;
} lotus_entity_t;

typedef enum lotus_components {
    null_c=0b0000,
    mesh_c=0b0001,
    texture_c=0b0010,
    material_c=0b0011,
    transform_c=0b0100,
    num_components
} lotus_components;

typedef struct lotus_mesh_itf {
    const unsigned int* id;
    const unsigned int* vbo;
    const unsigned int* ebo;
    const unsigned int* vao;
    const unsigned int* n_verts;
} lotus_mesh_itf;

typedef struct lotus_texture_itf {
    const unsigned int* id;
} lotus_texture_itf;

typedef struct lotus_material_itf {
    const unsigned int* id;
} lotus_material_itf;

typedef struct lotus_transform_itf {
    const unsigned int* id;
} lotus_transform_itf;


LOTUS_API bool lotus_has_comp(lotus_entity_t* e, unsigned int cid);
LOTUS_API void lotus_set_comp(lotus_entity_t* e, unsigned int cid);
LOTUS_API void lotus_rem_comp(lotus_entity_t* e, unsigned int cid);

#endif