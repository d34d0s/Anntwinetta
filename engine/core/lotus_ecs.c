#include "../include/lotus_ecs.h"

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

