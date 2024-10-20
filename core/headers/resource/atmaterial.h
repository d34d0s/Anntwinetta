#pragma once

#include "../atds.h"
#include "../attypes.h"
#include "../athelpers.h"

#include "atshader.h"

typedef struct ATmaterialLayout {
    int idx;
    int shader;
    AThashmap* uniforms;
} ATmaterialLayout;

typedef struct ATmaterialData {
    int count;
    ATarray* shader;
} ATmaterialData;

void _atDestroyMaterialData(ATmaterialData* d);
ATerrorType _atInitMaterialData(ATmaterialData* d, int max);
int _atSetMaterialData(ATmaterialData* materialData, ATshaderData* shaderData, const char* vertex, const char* fragment);

void _atDestroyMaterialLayout(ATmaterialLayout* l);
ATmaterialLayout* _atGetMaterialLayout(ATmaterialData* materialData, ATshaderData* shaderData, int index);

