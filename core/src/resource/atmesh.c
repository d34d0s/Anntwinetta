#include "../../headers/resource/atmesh.h"

void _atDestroyMeshData(ATmeshData* d) {
    d->count = 0;
    free(d->vbo);
    free(d->vao);
    free(d->n_verts);
    free(d);
}

ATerrorType _atInitMeshData(ATmeshData* d, int max) {
    d->count = 0;
    
    if (atInitIntArray(&d->vbo, max, "mesh data [vbo]")) {
        atLogError("failed to allocate mesh data [vbo] array");
        return ERR_MALLOC;
    }

    if (atInitIntArray(&d->vao, max, "mesh data [vao]")) {
        atLogError("failed to allocate mesh data [vao] array");
        return ERR_MALLOC;
    }

    if (atInitIntArray(&d->n_verts, max, "mesh data [n verts]")) {
        atLogError("failed to allocate mesh data [n verts] array");
        return ERR_MALLOC;
    }

    return ERR_NONE;
}

int _atSetMeshData(ATmeshData* d, int n_verts, float* vertices) {
    int index = d->count++;
    d->n_verts[index] = n_verts;    
    d->vbo[index] = atglMakeVBO(n_verts, 3, vertices);
    d->vao[index] = atglMakeVAO(
        d->vbo[index],
        n_verts, 3
    ); return index;
}

ATmeshLayout* _atGetMeshLayout(ATmeshData* d, int index) {
    if (index < 0 || index >= d->count) { return atTypeCastPtr(ATmeshLayout, ERR_MALLOC); }

    ATmeshLayout* l = (ATmeshLayout*)malloc(sizeof(ATmeshLayout));
    if (!l) {
        atLogError("failed to allocate mesh layout | idx[%d]", index);
        return atTypeCastPtr(ATmeshLayout, ERR_MALLOC);
    }
    
    l->idx = index;
    l->vbo = &d->vbo[index];
    l->vao = &d->vao[index];
    l->n_verts = &d->n_verts[index];

    return l;
}

void _atDestroyMeshLayout(ATmeshLayout* l) {
    l->idx = -1;
    l->vbo = NULL;
    l->vao = NULL;
    l->n_verts = NULL;
    free(l);
}