#include "../../headers/resource/atmesh.h"

void _atDestroyMeshData(ATmeshData* d) {
    d->count = 0;
    atDestroyArray(d->vbo);
    atDestroyArray(d->vao);
    atDestroyArray(d->n_verts);
    free(d);
}

ATerrorType _atInitMeshData(ATmeshData* d, int max) {
    d->count = 0;
    d->vbo = atMakeArray(max, 250);
    d->vao = atMakeArray(max, 250);
    d->n_verts = atMakeArray(max, 250);
    return ERR_NONE;
}

int _atSetMeshData(ATmeshData* d, int n_verts, float* vertices) {
    int index = d->count++;
    atInsertArray(d->n_verts, index, atMakeInt(n_verts));
    atInsertArray(d->vbo, index, atMakeInt(atglMakeVBO(n_verts, 3, vertices)));
    atInsertArray(d->vao, index, atMakeInt(atglMakeVAO(
        atQueryArrayInt(d->vbo, index),
        n_verts, 3
    ))); return index;
}

ATmeshLayout* _atGetMeshLayout(ATmeshData* d, int index) {
    if (index < 0 || index >= d->count) { return atTypeCastPtr(ATmeshLayout, ERR_MALLOC); }

    ATmeshLayout* l = (ATmeshLayout*)malloc(sizeof(ATmeshLayout));
    if (!l) {
        atLogError("failed to allocate mesh layout | idx[%d]", index);
        return atTypeCastPtr(ATmeshLayout, ERR_MALLOC);
    }
    
    l->idx = index;
    l->vao = atQueryArrayInt(d->vao, index);
    l->vbo = atQueryArrayInt(d->vbo, index);
    l->n_verts = atQueryArrayInt(d->n_verts, index);

    return l;
}

void _atDestroyMeshLayout(ATmeshLayout* l) {
    l->idx = -1;
    l->vbo = -1;
    l->vao = -1;
    l->n_verts = -1;
    free(l);
}