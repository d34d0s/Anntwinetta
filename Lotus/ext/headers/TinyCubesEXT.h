// Tiny Cubes
// Voxel Meshing Extension For Lotus Engine

// from 3D voxel coords to 1D voxel array:
// vindex = vx + csidelen * vz + carea * vy

/*
    Coordinate-System

          +y     -z
           |    /
           |   /
           |  /
-x ------- | ------- +x
        /  |
      /    |
    /      |
  +z      -y

*/

#ifndef TINYCUBESEXT_H
#define TINYCUBESEXT_H

#include "../../core/headers/LotusECS.h"
#include "../../core/headers/LotusMath.h"
#include "../../backend/headers/LotusGL.h"
#include "../../core/headers/lotus_types.h"

#define voxel_t b8 // voxels are id's from 0-255

typedef struct TinyChunk {
    b32 area;
    b32 nverts;
    b32 volume;
    b32 sidelen;
    b8 materialID;
    voxel_t* voxels;
    LotusEntity* entity;
    unsigned int vbo, vao;
} TinyChunk;

#define tinyError _lotusLogError

// Internal API
void buildVoxels(TinyChunk* chunk);
void initChunk(TinyChunk* chunk, b32 sidelen);
void configureChunk(TinyChunk* chunk, b8* vData);
b8 isVoxelVoid(b8 x, b8 y, b8 z, const TinyChunk* chunk);

// External API
LOTUS_API void buildChunk(TinyChunk* chunk, b32 sidelen);

#endif