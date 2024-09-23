#include "../include/lotus_ecs.h"

bool lotus_has_comp(lotus_entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return 0;
    return e->cid_field & (0b1 << cid);
}

void lotus_set_comp(lotus_entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return;
    e->cid_field ^= 0b1 << cid;
}

void lotus_rem_comp(lotus_entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return;
    e->cid_field &= ~(0b1 << cid);
}

