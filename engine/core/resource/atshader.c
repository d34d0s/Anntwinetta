#include "../../headers/resource/atshader.h"

int _atSetShaderData(ATshaderData* d, const char* vertex, const char* fragment) {
    int index = d->count++;
    d->n_uniforms[index] = 0;
    d->vSrc[index] = vertex;
    d->fSrc[index] = fragment;
    d->program[index] = atglMakeShader(
        vertex, 
        fragment
    ); return index;
}

ATshaderLayout* _atGetShaderLayout(ATshaderData* d, int index) {
    if (index < 0 || index >= d->count) { return atTypeCastPtr(ATshaderLayout, ERR_MALLOC); }

    ATshaderLayout* l = (ATshaderLayout*)malloc(sizeof(ATshaderLayout));
    if (!l) {
        atLogError("failed to allocate shader layout | idx[%d]", index);
        return atTypeCastPtr(ATshaderLayout, ERR_MALLOC);
    }
    
    l->idx = index;
    l->vSrc = &d->vSrc[index];
    l->fSrc = &d->fSrc[index];
    l->program = &d->program[index];
    
    return l;
}

void _atDestroyShaderLayout(ATshaderLayout* l) {
    l->idx = 0;
    l->vSrc = NULL;
    l->fSrc = NULL;
    l->program = NULL;
    free(l);
}
