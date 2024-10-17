#pragma once

#include "../atds.h"
#include "../attypes.h"
#include "../athelpers.h"

#include "../backend/GL/atGLAPI.h"

typedef struct ATuniformLayout {
    void* value;
    int location;
    const char* name;
} ATuniformLayout;

typedef struct ATshaderLayout {
    int idx;
    int* program;
    const char** vSrc;
    const char** fSrc;
    AThashmap** uniforms;
} ATshaderLayout;

typedef struct ATshaderData {
    int count;
    int* program;
    int* n_uniforms;
    const char** vSrc;
    const char** fSrc;
    AThashmap** uniforms;
} ATshaderData;

int _atSetShaderData(ATshaderData* d, const char* vertex, const char* fragment);
ATshaderLayout* _atGetShaderLayout(ATshaderData* d, int index);
void _atDestroyShaderLayout(ATshaderLayout* l);

ATerrorType _atSetShaderUniform(ATshaderData* d, int index, ATuniformType type, const char* name, void* value);
ATuniformLayout* _atGetShaderUniform(ATshaderData* d, int index, const char* name);
