#pragma once

#include "../attypes.h"
#include "../athelpers.h"

#include "../../backend/headers/atGLAPI.h"

typedef struct ATshaderLayout {
    int idx;
    int* program;
    const char** vSrc;
    const char** fSrc;
} ATshaderLayout;

typedef struct ATshaderData {
    // TODO: Uniform hashmap!
    int count;
    int* program;
    int* n_uniforms;
    const char** vSrc;
    const char** fSrc;
} ATshaderData;

int _atSetShaderData(ATshaderData* d, const char* vertex, const char* fragment);
ATshaderLayout* _atGetShaderLayout(ATshaderData* d, int index);
void _atDestroyShaderLayout(ATshaderLayout* l);

