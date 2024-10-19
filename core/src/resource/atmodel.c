#include "../../headers/resource/atmodel.h"

void _atDestroyModelData(ATmodelData* d) {
    d->count = 0;
    free(d->mesh);
    free(d->material);
    free(d->n_verts);
    free(d);
}

ATerrorType _atInitModelData(ATmodelData* d, int max) {
    if (!d || max <= 0) { return ERR_MALLOC; }

    d->count = 0;

    if (atInitIntArray(&d->mesh, max, "model data mesh index array")) {
        atLogError("failed to initialize model data mesh index array");
        return ERR_MALLOC;
    }

    if (atInitIntArray(&d->material, max, "model data material index array")) {
        atLogError("failed to initialize model data material index array");
        return ERR_MALLOC;
    }

    if (atInitIntArray(&d->n_verts, max, "model data mesh index array")) {
        atLogError("failed to initialize model data vertex count array");
        return ERR_MALLOC;
    }

    return ERR_NONE;
}

int _atSetModelData(ATmodelData* modelData, ATmeshData* meshData, int n_verts, float* vertices) {
    int model_idx = modelData->count++;
    int mesh_idx =_atSetMeshData(meshData, n_verts, vertices);
    
    modelData->material[model_idx] = -1;
    modelData->mesh[model_idx] = mesh_idx;
    modelData->n_verts[model_idx] = n_verts;

    return model_idx;
}

ATerrorType _atSetModelMaterial(ATmodelData* d, int modelID, int materialID) {
    if (modelID < 0 || modelID >= d->count) {
        return ERR_MODEL;
    }
    d->material[modelID] = materialID;
    return ERR_NONE;
}

ATerrorType _atRemModelMaterial(ATmodelData* d, int modelID, int materialID) {
    if (modelID < 0 || modelID >= d->count) {
        return ERR_MODEL;
    }
    d->material[modelID] = -1;
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
    l->mesh = &d->mesh[l->idx];
    l->material = &d->material[l->idx];
    l->n_verts = &d->n_verts[l->idx];
    
    return l;
}

void _atDestroyModelLayout(ATmodelLayout* l) {
    l->idx = -1;
    l->mesh = NULL;
    l->material = NULL;
    l->n_verts = NULL;
    free(l);
}

