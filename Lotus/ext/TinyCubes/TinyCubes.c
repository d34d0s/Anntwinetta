#include "../headers/TinyCubes.h"

static void* MVP_VOID_VALUES[3] = {NULL, NULL, NULL};
static const char* MVP_NAMES[3] = {"umodel", "uview", "uproj"};
static unsigned int MVP_TYPES[3] = {UTYPE_MAT4, UTYPE_MAT4, UTYPE_MAT4};

unsigned char tinyCubesMaterial(void) { return _tinyCubesMaterial_001; }

void initTinyCubes(void) {
    _tinyCubesMaterial_001 = lotusMakeMaterial(
        tinyCubesVSrc,
        tinyCubesFSrc,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

void initChunk(TinyChunk* chunk, b32 sidelen) {
    chunk->nverts = 0;
    chunk->sidelen = sidelen;
    chunk->entity = lotusMakeEntity();
    chunk->area = sidelen*sidelen;
    chunk->volume = chunk->area*sidelen;
    chunk->voxels = (b8*)malloc(sizeof(b8)*chunk->volume);
    if (!chunk->voxels) {
        tinyError("Failed to allocate memory for a chunk's voxel array!");
        return;
    }
}

void buildVoxels(TinyChunk* chunk) {
    for (b8 x = 0; x < chunk->sidelen; x++) {
        for (b8 z = 0; z < chunk->sidelen; z++) {
            for (b8 y = 0; y < chunk->sidelen; y++) {
                chunk->voxels[x + chunk->sidelen*z + chunk->area*y] = x+y+z;
            }
        }
    }
}

b8 isVoxelVoid(b8 x, b8 y, b8 z, const TinyChunk* chunk) {
    if (
        0 <= x &&
        x < chunk->sidelen &&
        0 <= y &&
        y < chunk->sidelen &&
        0 <= z &&
        z < chunk->sidelen
    ) { return (chunk->voxels[x + chunk->sidelen * z + chunk->area * y] > 0) ?  0 : 1; }
}

void configureChunk(TinyChunk* chunk, b8* vData) {
    glGenVertexArrays(1, &chunk->vao);
    glGenBuffers(1, &chunk->vbo);
    glBindVertexArray(chunk->vao);
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(b8) * chunk->volume * 18 * 5, vData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_UNSIGNED_BYTE, GL_FALSE, 5*sizeof(b8), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 1, GL_UNSIGNED_BYTE, GL_FALSE, 5*sizeof(b8), (void*)(3*sizeof(b8)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 1, GL_UNSIGNED_BYTE, GL_FALSE, 5*sizeof(b8), (void*)(4*sizeof(b8)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    
    // configure Chunk Entity Components
    lotusPushMesh(chunk->entity, chunk->nverts, 5, chunk->vbo, chunk->vao, vData);
    lotusSetMaterial(chunk->entity, tinyCubesMaterial());
    lotusSetTransform(
        chunk->entity,
        (LMvec3){1.0, 1.0, 1.0},
        (LMvec3){0.0, 0.0, 0.0},
        (LMvec3){0.0, 0.0, 0.0}
    ); free(vData);
}

void buildChunk(TinyChunk* chunk, b32 sidelen) {
    initChunk(chunk, sidelen); buildVoxels(chunk);
    b32 vDataIndex = 0;
    b8* vData = (b8*)malloc(sizeof(b8) * chunk->volume * 18 * 5);
    if (!vData) {
        printf("Failed to allocate memory for a chunk's vertex-data array!");
        free(chunk->voxels);
        chunk->sidelen = -1;
        chunk->volume = -1;
        chunk->area = -1;
        free(chunk);
        return;
    }

    for (b8 x = 0; x < sidelen; x ++) {
        for (b8 y = 0; y < sidelen; y ++) {
            for (b8 z = 0; z < sidelen; z ++) {
                b8 vtype = chunk->voxels[ x + chunk->sidelen * z + chunk->area * y ];
                if (vtype == 0) { continue; }

                if (isVoxelVoid(x, y+1, z, chunk)) {
                    LMvec3_byte topVertices[6] = {
                        (LMvec3_byte){x,   y+1,  z  },
                        (LMvec3_byte){x,   y+1,  z+1},
                        (LMvec3_byte){x+1, y+1,  z+1},
                        (LMvec3_byte){x,   y+1,  z  },
                        (LMvec3_byte){x+1, y+1,  z+1},
                        (LMvec3_byte){x+1, y+1,  z  }
                    };
                    for (b8 i = 0; i < 6; i++) {
                        chunk->nverts++;
                        b8 vface = 0;
                        vData[vDataIndex] = topVertices[i].x;       vDataIndex++;
                        vData[vDataIndex] = topVertices[i].y;       vDataIndex++;
                        vData[vDataIndex] = topVertices[i].z;       vDataIndex++;
                        vData[vDataIndex] = vtype;                  vDataIndex++;
                        vData[vDataIndex] = vface;                  vDataIndex++;
                    } 
                }
                
                if (isVoxelVoid(x, y-1, z, chunk)) {
                    LMvec3_byte bottomVertices[6] = {
                        (LMvec3_byte){x,   y,   z  },
                        (LMvec3_byte){x+1, y,   z+1},
                        (LMvec3_byte){x,   y,   z+1},
                        (LMvec3_byte){x,   y,   z  },
                        (LMvec3_byte){x+1, y,   z  },
                        (LMvec3_byte){x+1, y,   z+1}
                    };
                    for (b8 i = 0; i < 6; i++) {
                        chunk->nverts++;
                        b8 vface = 1;
                        vData[vDataIndex] = bottomVertices[i].x;   vDataIndex++;
                        vData[vDataIndex] = bottomVertices[i].y;   vDataIndex++;
                        vData[vDataIndex] = bottomVertices[i].z;   vDataIndex++;
                        vData[vDataIndex] = vtype;                 vDataIndex++;
                        vData[vDataIndex] = vface;                 vDataIndex++;
                    }
                }
                
                if (isVoxelVoid(x-1, y, z, chunk)) {
                    LMvec3_byte leftVertices[6] = {
                        (LMvec3_byte){x, y,   z  },
                        (LMvec3_byte){x, y+1, z+1},
                        (LMvec3_byte){x, y+1, z  },
                        (LMvec3_byte){x, y,   z  },
                        (LMvec3_byte){x, y,   z+1},
                        (LMvec3_byte){x, y+1, z+1}
                    };
                    for (b8 i = 0; i < 6; i++) {
                        chunk->nverts++;
                        b8 vface = 2;
                        vData[vDataIndex] = leftVertices[i].x;   vDataIndex++;
                        vData[vDataIndex] = leftVertices[i].y;   vDataIndex++;
                        vData[vDataIndex] = leftVertices[i].z;   vDataIndex++;
                        vData[vDataIndex] = vtype;               vDataIndex++;
                        vData[vDataIndex] = vface;               vDataIndex++;
                    }
                }
                                
                if (isVoxelVoid(x+1, y, z, chunk)) {
                    LMvec3_byte rightVertices[6] = {
                        (LMvec3_byte){x+1, y,   z  },
                        (LMvec3_byte){x+1, y+1, z  },
                        (LMvec3_byte){x+1, y+1, z+1},
                        (LMvec3_byte){x+1, y,   z  },
                        (LMvec3_byte){x+1, y+1, z+1},
                        (LMvec3_byte){x+1, y,   z+1}
                    };
                    for (b8 i = 0; i < 6; i++) {
                        chunk->nverts++;
                        b8 vface = 3;
                        vData[vDataIndex] = rightVertices[i].x;   vDataIndex++;
                        vData[vDataIndex] = rightVertices[i].y;   vDataIndex++;
                        vData[vDataIndex] = rightVertices[i].z;   vDataIndex++;
                        vData[vDataIndex] = vtype;                vDataIndex++;
                        vData[vDataIndex] = vface;                vDataIndex++;
                    }
                }
                
                if (isVoxelVoid(x, y, z-1, chunk)) {
                    LMvec3_byte backVertices[6] = {
                        (LMvec3_byte){x,   y,   z  },
                        (LMvec3_byte){x,   y+1, z  },
                        (LMvec3_byte){x+1, y+1, z  },
                        (LMvec3_byte){x,   y,   z  },
                        (LMvec3_byte){x+1, y+1, z  },
                        (LMvec3_byte){x+1, y,   z  }
                    };
                    for (b8 i = 0; i < 6; i++) {
                        chunk->nverts++;
                        b8 vface = 4;
                        vData[vDataIndex] = backVertices[i].x;   vDataIndex++;
                        vData[vDataIndex] = backVertices[i].y;   vDataIndex++;
                        vData[vDataIndex] = backVertices[i].z;   vDataIndex++;
                        vData[vDataIndex] = vtype;               vDataIndex++;
                        vData[vDataIndex] = vface;               vDataIndex++;
                    }
                }
                
                if (isVoxelVoid(x, y, z+1, chunk)) {
                    LMvec3_byte frontVertices[6] = {
                        (LMvec3_byte){x,   y,   z+1},
                        (LMvec3_byte){x+1, y+1, z+1},
                        (LMvec3_byte){x,   y+1, z+1},
                        (LMvec3_byte){x,   y,   z+1},
                        (LMvec3_byte){x+1, y,   z+1},
                        (LMvec3_byte){x+1, y+1, z+1}
                    };
                    for (b8 i = 0; i < 6; i++) {
                        chunk->nverts++;
                        b8 vface = 5;
                        vData[vDataIndex] = frontVertices[i].x;   vDataIndex++;
                        vData[vDataIndex] = frontVertices[i].y;   vDataIndex++;
                        vData[vDataIndex] = frontVertices[i].z;   vDataIndex++;
                        vData[vDataIndex] = vtype;                vDataIndex++;
                        vData[vDataIndex] = vface;                vDataIndex++;
                    }
                }
            }
        }
    }
    configureChunk(chunk, vData);
}

void main() {}
