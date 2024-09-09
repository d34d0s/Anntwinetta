#include "headers/LotusVX.h"


LVXchunk lvxInitChunk(unsigned short size) {
    LVXchunk c = {.size=size, .area=size*size, .volume=(size*size)*size};
    c.voxels = malloc(sizeof(b16)*c.volume);
    if (!c.voxels) {
        printf("ERROR MALLOC FOR VOXEL ARRAY\n");
        return (LVXchunk){.size=-1, .area=-1, .volume=-1, .voxels=NULL};
    } return c;
}

void lvxFillChunk(LVXchunk* c) {
    for (int x = 0; x < c->size; x++) {
        for (int z = 0; z < c->size; z++) {
            for (int y = 0; y < c->size; y++) {
                c->voxels[x + c->size*z + c->area*y] = x;
            }
        }
    }
}

