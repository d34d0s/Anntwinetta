#pragma once

#include "../attypes.h"
#include "../athelpers.h"

#include "atmesh.h"

typedef struct ATmodelLayout {
    int idx;
    int* mesh;
    int* n_verts;
    int* material;
} ATmodelLayout;

typedef struct ATmodelData {
    int count;
    int* mesh;
    int* n_verts;
    int* material;
} ATmodelData;

void _atDestroyModelData(ATmodelData* modelData);
ATerrorType _atInitModelData(ATmodelData* d, int max);
ATerrorType _atSetModelMaterial(ATmodelData* d, int modelID, int materialID);
ATerrorType _atRemModelMaterial(ATmodelData* d, int modelID, int materialID);
int _atSetModelData(ATmodelData* modelData, ATmeshData* meshData, int n_verts, float* vertices);

void _atDestroyModelLayout(ATmodelLayout* l);
ATmodelLayout* _atGetModelLayout(ATmodelData* modelData, int idx);