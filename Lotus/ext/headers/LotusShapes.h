// LOTUS DEFAULT-EXTENSION
// LotusShapesEXT provides simple default shape vertex-data, and vertex count for developers
// to set up some basic shapes in a simple manner.

#ifndef LOTUSSHAPESEXT_H
#define LOTUSSHAPESEXT_H

#include "../../engine/headers/core/LotusECS.h"
#include "../../engine/headers/core/lotus_types.h"

#define  LOTUS_VERTEX_MAX (1<<16)

// 2D Shapes
LOTUS_API void lotusQuadMesh(LotusEntity* e);
LOTUS_API void lotusCircleMesh(LotusEntity* e);
LOTUS_API void lotusLongQuadMesh(LotusEntity* e);
LOTUS_API void lotusTriangleMesh(LotusEntity* e);

// 3D Shapes
LOTUS_API void lotusCubeMesh(LotusEntity* e);
LOTUS_API void lotusConeMesh(LotusEntity* e);
LOTUS_API void lotusTorusMesh(LotusEntity* e);
LOTUS_API void lotusSphereMesh(LotusEntity* e);
LOTUS_API void lotusPyramidMesh(LotusEntity* e);
LOTUS_API void lotusCylinderMesh(LotusEntity* e);

#endif