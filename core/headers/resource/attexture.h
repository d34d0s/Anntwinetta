#pragma once

#include "../atds.h"
#include "../attypes.h"
#include "../athelpers.h"

typedef struct ATtextureLayout {
    int count;
    char* src;
    char* title;
    int n_channels;
    int* dimensions;
} ATtextureLayout;

typedef struct ATtextureData {
    int count;
    ATarray* src;
    ATarray* title;
    ATarray* n_channels;
    ATarray* dimensions;
} ATtextureData;

void _atDestroyTextureData(ATtextureData* d);
ATerrorType _atInitTextureData(ATtextureData* d, int max);
