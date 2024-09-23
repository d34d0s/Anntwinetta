#include "../../../engine/core/lotus.h"

typedef struct entity_t {
    int eid;
    int cid_field;
} entity_t;

typedef enum comps {
    transform_comp=0b0,
    material_comp=0b10,
    n_comps
} comps;

typedef struct d_array {
    int c;
    void* arr;
} d_array;


bool has_comp(entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return 0;
    return e->cid_field & (0b1 << cid);
}

void set_comp(entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return;
    e->cid_field ^= 0b1 << cid;
}

void rem_comp(entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return;
    e->cid_field &= ~(0b1 << cid);
}

void main() {
    lotus_init();

    entity_t e = {0, 0};
    printf("entity struct size = %d\n", sizeof(e));

    set_comp(&e, transform_comp);
    set_comp(&e, material_comp);

    printf("has transform %d\n", has_comp(&e, transform_comp));

    rem_comp(&e, transform_comp);

    printf("has transform %d\n", has_comp(&e, transform_comp));

    lotus_exit();
}

