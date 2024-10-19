#pragma once

#include "../attypes.h"
#include "../athelpers.h"

typedef struct ATtextureLayout {
    int count;
    char** src;
    char** title;
    int* n_channels;
    int** dimensions;
} ATtextureLayout;

typedef struct ATtextureData {
    int count;
    char** src;
    char** title;
    int* n_channels;
    int** dimensions;
} ATtextureData;

void _atDestroyTextureData(ATtextureData* d);
ATerrorType _atInitTextureData(ATtextureData* d, int max);
