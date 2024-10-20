#include "../../headers/resource/atmaterial.h"

void _atDestroyMaterialData(ATmaterialData* d) {
    atDestroyArray(d->shader);
    d->count = 0;
    free(d);
}

ATerrorType _atInitMaterialData(ATmaterialData* d, int max) {
    d->count = 0;
    d->shader = atMakeArray(max, 250);
    return ERR_NONE;
}

int _atSetMaterialData(ATmaterialData* materialData, ATshaderData* shaderData, const char* vertex, const char* fragment) {
    if (!materialData || !shaderData) {
        return ERR_TYPE;
    }

    int materialIdx = materialData->count++;
    atInsertArray(
        materialData->shader,
        materialIdx,
        atMakeInt(_atSetShaderData(
            shaderData,
            vertex,
            fragment
        )
    ));

    return materialIdx;
}

void _atDestroyMaterialLayout(ATmaterialLayout* l) {
    l->idx = -1;
    l->shader = -1;
    l->uniforms = NULL;
    free(l);
}

ATmaterialLayout* _atGetMaterialLayout(ATmaterialData* materialData, ATshaderData* shaderData, int index) {
    if (!materialData || index < 0 || index >= materialData->count) {
        atLogError("invalid material index for layout");
        return atTypeCastPtr(ATmaterialLayout, ERR_TYPE);
    }

    ATmaterialLayout* l = (ATmaterialLayout*)malloc(sizeof(ATmaterialLayout));
    if (!l) {
        atLogError("failed to allocate material layout");
        return atTypeCastPtr(ATmaterialLayout, ERR_TYPE);
    }

    l->idx = index;
    l->shader = atQueryArrayInt(materialData->shader, index);
    l->uniforms = (AThashmap*)((ATvalue*)atQueryArray(shaderData->uniforms, index)->value);

    return l;
}