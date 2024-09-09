#pragma once

// voxel data layout
// x y z vxID faceID aoID flipID
// unsigned short x, y, z; // 0b1000 * 3
// unsigned char vxID;    // 0b1000
// unsigned char faceID:4;    // 0b100
// unsigned char aoID:2;
// unsigned char flipID:1;

#include "lotus_types.h"

typedef struct LVXchunk {
    b16 size;
    b16 area;
    b16 volume;
    b16 *voxels;
} LVXchunk;

LVXchunk lvxInitChunk(unsigned short size);
void lvxFillChunk(LVXchunk* c);

