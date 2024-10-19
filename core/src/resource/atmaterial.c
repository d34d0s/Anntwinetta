#include "../../headers/resource/atmaterial.h"

void _atDestroyMaterialData(ATmaterialData* d) {
    free(d->shader);

    atForRangeI(d->count) {
        atDestroyHashmap(d->uniforms[i]);
    }; d->count = 0;
    
    free(d);
}

ATerrorType _atInitMaterialData(ATmaterialData* d, int max) {
    d->count = 0;

    atInitIntArray(&d->shader, max, "material data shader index array");
    if (!d->shader) {
        atLogError("failed to allocate material data shader index array");
        return ERR_MALLOC;
    }

    d->uniforms = (AThashmap**)malloc(max * sizeof(AThashmap*));
    if (!d->uniforms) {
        atLogError("failed to allocate material data uniform array");
        return ERR_MALLOC;
    }

    return ERR_NONE;
}

int _atSetMaterialData(ATmaterialData* materialData, ATshaderData* shaderData, const char* vertex, const char* fragment) {
    if (!materialData || !shaderData) {
        return ERR_TYPE;
    }

    int materialIdx = materialData->count++;
    materialData->uniforms[materialIdx] = atMakeHashmap(16);
    materialData->shader[materialIdx] = _atSetShaderData(
        shaderData,
        vertex,
        fragment
    );

    return materialIdx;
}

void _atDestroyMaterialLayout(ATmaterialLayout* l) {
    l->idx = -1;
    l->shader = NULL;
    l->uniforms = NULL;
    free(l);
}

ATmaterialLayout* _atGetMaterialLayout(ATmaterialData* d, int index) {
    if (!d || index < 0 || index >= d->count) {
        atLogError("invalid material index for layout");
        return atTypeCastPtr(ATmaterialLayout, ERR_TYPE);
    }

    ATmaterialLayout* l = (ATmaterialLayout*)malloc(sizeof(ATmaterialLayout));
    if (!l) {
        atLogError("failed to allocate material layout");
        return atTypeCastPtr(ATmaterialLayout, ERR_TYPE);
    }

    l->idx = index;
    l->shader = &d->shader[index];
    l->uniforms = &d->uniforms[index];

    return l;
}