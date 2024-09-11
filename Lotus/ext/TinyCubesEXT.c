#include "headers/TinyCubesEXT.h"
#include "headers/LotusMaterialEXT.h"

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
    for (int vx = 0; vx < chunk->sidelen; vx++) {
        for (int vz = 0; vz < chunk->sidelen; vz++) {
            for (int vy = 0; vy < chunk->sidelen; vy++) {
                chunk->voxels[vx + chunk->sidelen*vz + chunk->area*vy] = 1;
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
    ) { return (chunk->voxels[x + chunk->sidelen * z + chunk->area * y]) ?  0 : 1; }
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
    
    // configure Chunk Entity Components
    lotusPushMesh(chunk->entity, chunk->nverts, 5, chunk->vbo, chunk->vao, vData);
    lotusSetMaterial(chunk->entity, LotusDefaultMaterial_MVP());
    lotusSetTransform(
        chunk->entity,
        (LMvec3){1.0, 1.0, 1.0},
        (LMvec3){0.0, 0.0, 0.0},
        (LMvec3){0.0, 0.0, 0.0}
    );

    free(vData);
}

void buildChunk(TinyChunk* chunk, b32 sidelen) {
    initChunk(chunk, sidelen); buildVoxels(chunk);
    b32 vDataIndex = 0;
    b8* vData = (b8*)malloc(sizeof(b8) * chunk->volume * 18 * 5);
    if (!vData) {
        tinyError("Failed to allocate memory for a chunk's vertex-data array!");
        free(chunk->voxels);
        chunk->sidelen = -1;
        chunk->volume = -1;
        chunk->area = -1;
        free(chunk);
        return;
    }

    for (int x = 0; x < sidelen; x ++) {
        for (int y = 0; y < sidelen; y ++) {
            for (int z = 0; z < sidelen; z ++) {
                b8 vtype = chunk->voxels[ x + chunk->sidelen * z + chunk->area * y ];
                if (vtype == 0) { continue; }

                if (isVoxelVoid(x, y+1, z, chunk)) {
                    LMvec3_i topVertices[6] = {
                        (LMvec3_i){x,   y+1,  z  },
                        (LMvec3_i){x,   y+1,  z+1},
                        (LMvec3_i){x+1, y+1,  z+1},
                        (LMvec3_i){x,   y+1,  z  },
                        (LMvec3_i){x+1, y+1,  z+1},
                        (LMvec3_i){x+1, y+1,  z  }
                    };
                    for (int i = 0; i < 6; i++) {
                        chunk->nverts++;
                        vData[vDataIndex] = topVertices[i].x;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = topVertices[i].y;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = topVertices[i].z;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = vtype;              vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = 0;                  vDataIndex=vDataIndex+=1;
                    }
                }
                
                if (isVoxelVoid(x, y-1, z, chunk)) {
                    LMvec3_i bottomVertices[6] = {
                        (LMvec3_i){x,   y,   z  },
                        (LMvec3_i){x+1, y,   z+1},
                        (LMvec3_i){x,   y,   z+1},
                        (LMvec3_i){x,   y,   z  },
                        (LMvec3_i){x+1, y,   z  },
                        (LMvec3_i){x+1, y,   z+1}
                    };
                    for (int i = 0; i < 6; i++) {
                        chunk->nverts++;
                        vData[vDataIndex] = bottomVertices[i].x;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = bottomVertices[i].y;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = bottomVertices[i].z;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = vtype;              vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = 1;                  vDataIndex=vDataIndex+=1;
                    }
                }
                
                if (isVoxelVoid(x-1, y, z, chunk)) {
                    LMvec3_i leftVertices[6] = {
                        (LMvec3_i){x, y,   z  },
                        (LMvec3_i){x, y+1, z+1},
                        (LMvec3_i){x, y+1, z  },
                        (LMvec3_i){x, y,   z  },
                        (LMvec3_i){x, y,   z+1},
                        (LMvec3_i){x, y+1, z+1}
                    };
                    for (int i = 0; i < 6; i++) {
                        chunk->nverts++;
                        vData[vDataIndex] = leftVertices[i].x;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = leftVertices[i].y;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = leftVertices[i].z;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = vtype;              vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = 2;                  vDataIndex=vDataIndex+=1;
                    }
                }
                                
                if (isVoxelVoid(x+1, y, z, chunk)) {
                    LMvec3_i rightVertices[6] = {
                        (LMvec3_i){x+1, y,   z  },
                        (LMvec3_i){x+1, y+1, z  },
                        (LMvec3_i){x+1, y+1, z+1},
                        (LMvec3_i){x+1, y,   z  },
                        (LMvec3_i){x+1, y+1, z+1},
                        (LMvec3_i){x+1, y,   z+1}
                    };
                    for (int i = 0; i < 6; i++) {
                        chunk->nverts++;
                        vData[vDataIndex] = rightVertices[i].x;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = rightVertices[i].y;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = rightVertices[i].z;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = vtype;              vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = 3;                  vDataIndex=vDataIndex+=1;
                    }
                }
                
                if (isVoxelVoid(x, y, z-1, chunk)) {
                    LMvec3_i backVertices[6] = {
                        (LMvec3_i){x,   y,   z  },
                        (LMvec3_i){x,   y+1, z  },
                        (LMvec3_i){x+1, y+1, z  },
                        (LMvec3_i){x,   y,   z  },
                        (LMvec3_i){x+1, y+1, z  },
                        (LMvec3_i){x+1, y,   z  }
                    };
                    for (int i = 0; i < 6; i++) {
                        chunk->nverts++;
                        vData[vDataIndex] = backVertices[i].x;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = backVertices[i].y;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = backVertices[i].z;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = vtype;              vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = 4;                  vDataIndex=vDataIndex+=1;
                    }
                }
                
                if (isVoxelVoid(x, y, z+1, chunk)) {
                    LMvec3_i frontVertices[6] = {
                        (LMvec3_i){x,   y,   z+1},
                        (LMvec3_i){x+1, y+1, z+1},
                        (LMvec3_i){x,   y+1, z+1},
                        (LMvec3_i){x,   y,   z+1},
                        (LMvec3_i){x+1, y,   z+1},
                        (LMvec3_i){x+1, y+1, z+1}
                    };
                    for (int i = 0; i < 6; i++) {
                        chunk->nverts++;
                        vData[vDataIndex] = frontVertices[i].x;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = frontVertices[i].y;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = frontVertices[i].z;   vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = vtype;              vDataIndex=vDataIndex+=1;
                        vData[vDataIndex] = 5;                  vDataIndex=vDataIndex+=1;
                    }
                }
            }
        }
    } configureChunk(chunk, vData);
}

