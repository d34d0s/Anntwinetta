#include "../include/annt_ecs.h"

bool at_has_component(at_entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return 0;
    return e->cid_field & (0b1 << cid);
}

void at_set_component(at_entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return;
    e->cid_field ^= 0b1 << cid;
}

void at_rem_component(at_entity_t* e, unsigned int cid) {
    if (e->eid < 0 || e->eid > BYTE8_MAX) return;
    e->cid_field &= ~(0b1 << cid);
}

