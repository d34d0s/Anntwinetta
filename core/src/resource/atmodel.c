#include "../../headers/resource/atmodel.h"

void _atDestroyModelData(ATmodelData* d) {
    d->count = 0;
    atDestroyArray(d->mesh);
    atDestroyArray(d->n_verts);
    atDestroyArray(d->material);
    free(d);
}

ATerrorType _atInitModelData(ATmodelData* d, int max) {
    if (!d || max <= 0) { return ERR_MALLOC; }
    d->count = 0;
    d->mesh = atMakeArray(max, 250);
    d->n_verts = atMakeArray(max, 250);
    d->material = atMakeArray(max, 250);
    return ERR_NONE;
}

int _atSetModelData(ATmodelData* modelData, ATmeshData* meshData, int n_verts, float* vertices) {
    int model_idx = modelData->count++;
    int mesh_idx =_atSetMeshData(meshData, n_verts, vertices);
    atInsertArray(modelData->material, model_idx, atMakeInt(-1));
    atInsertArray(modelData->mesh, model_idx, atMakeInt(mesh_idx));
    atInsertArray(modelData->n_verts, model_idx, atMakeInt(n_verts));
    return model_idx;
}

ATerrorType _atSetModelMaterial(ATmodelData* d, int modelID, int materialID) {
    if (modelID < 0 || modelID >= d->count) {
        return ERR_MODEL;
    }
    atInsertArray(d->material, modelID, atMakeInt(materialID));
    return ERR_NONE;
}

ATerrorType _atRemModelMaterial(ATmodelData* d, int modelID) {
    if (modelID < 0 || modelID >= d->count) {
        return ERR_MODEL;
    }
    atInsertArray(d->material, modelID, atMakeInt(-1));
    return ERR_NONE;
}

ATmodelLayout* _atGetModelLayout(ATmodelData* d, int idx) {
    if (!d || idx < 0 || idx >= d->count) {
        atLogError("invalid model index for layout");
        return atTypeCastPtr(ATmodelLayout, ERR_MALLOC);
    }

    ATmodelLayout* l = (ATmodelLayout*)malloc(sizeof(ATmodelLayout));
    if (!l) {
        atLogError("failed to allocate model layout");
        return atTypeCastPtr(ATmodelLayout, ERR_MALLOC);
    }

    l->idx = idx;
    l->mesh = atQueryArrayInt(d->mesh, idx);
    l->n_verts = atQueryArrayInt(d->n_verts, idx);
    l->material = atQueryArrayInt(d->material, idx);
    
    return l;
}

void _atDestroyModelLayout(ATmodelLayout* l) {
    l->idx = -1;
    l->mesh = -1;
    l->material = -1;
    l->n_verts = -1;
    free(l);
}

