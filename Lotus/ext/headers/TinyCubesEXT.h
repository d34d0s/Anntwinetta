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
static unsigned char _tinyCubesMaterial_001;

static const char *tinyCubesVSrc = "#version 430 core\n"
    "layout (location = 0) in vec3 vLocation;\n"
    "layout (location = 1) in int vtype;\n"
    "layout (location = 2) in int vface;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "out vec3 voxColor;\n"
    "vec3 hash31(int p) {\n"
    "   vec3 p3 = fract(vec3(p * 21.2) * vec3(0.1031, 0.1030, 0.0973));\n"
    "   p3 += dot(p3, p3.yzx + 33.33);\n"
    "   return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05;\n"
    "}\n"
    "void main() {\n"
    "   voxColor = hash31(vtype);\n"
    "   gl_Position = uproj * uview * umodel * vec4(vLocation, 1.0);\n"
    "}\n";

static const char *tinyCubesFSrc = "#version 430 core\n"
    "out vec4 FragColor;\n"
    "in vec3 voxColor;\n"
    "void main() {\n"
    "   FragColor = vec4(voxColor, 1.0);\n"
    "}\n";


void buildVoxels(TinyChunk* chunk);
void initChunk(TinyChunk* chunk, b32 sidelen);
void configureChunk(TinyChunk* chunk, b8* vData);
b8 isVoxelVoid(b8 x, b8 y, b8 z, const TinyChunk* chunk);

// External API
LOTUS_API void initTinyCubes(void);
LOTUS_API unsigned char tinyCubesMaterial(void);
LOTUS_API void buildChunk(TinyChunk* chunk, b32 sidelen);

#endif