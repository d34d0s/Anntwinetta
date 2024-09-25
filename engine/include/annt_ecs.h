#ifndef ANNT_ECS_H
#define ANNT_ECS_H

#include "annt_types.h"

typedef struct at_entity_t {
    int eid;
    char tag[100];
    int cid_field;
} at_entity_t;

typedef enum at_components {
    null_c=0b0000,
    mesh_c=0b0001,
    texture_c=0b0010,
    material_c=0b0011,
    transform_c=0b0100,
    num_components
} at_components;

typedef struct at_mesh_itf {
    const unsigned int* id;
    const unsigned int* vbo;
    const unsigned int* ebo;
    const unsigned int* vao;
    const unsigned int* n_verts;
} at_mesh_itf;

typedef struct at_texture_itf {
    const unsigned int* id;
} at_texture_itf;

typedef struct at_material_itf {
    const unsigned int* id;
} at_material_itf;

typedef struct at_transform_itf {
    const unsigned int* id;
} at_transform_itf;

ANNT_API at_entity_t* at_new_entity(char* tag, ...);

ANNT_API bool at_has_component(at_entity_t* e, unsigned int cid);
ANNT_API void at_set_component(at_entity_t* e, unsigned int cid);
ANNT_API void at_rem_component(at_entity_t* e, unsigned int cid);

#endif