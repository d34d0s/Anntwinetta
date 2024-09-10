#ifndef LOTUSPROC_H
#define LOTUSPROC_H

#include "LotusECS.h"
#include "LotusMath.h"
#include "lotus_types.h"
#include "../../backend/headers/LotusGL.h"

#define LOTUS_MAX_DRAW_QUEUE 1024

typedef enum LotusDrawType {
    LOTUS_DRAW_MONO=0,
    LOTUS_DRAW_BATCH,
    LOTUS_DRAW_TYPE_COUNT
} LotusDrawType;

typedef struct LotusDrawCall {
    LotusDrawType type;
    unsigned int vao;
    unsigned int vbo;
    unsigned char nuniforms;
    unsigned short nvertices;
    LotusMaterial_itf* material;
} LotusDrawCall;

typedef struct LotusRenderer {
    GLFWwindow* ref;
    LMvec4 clearColor;
    LotusDrawCall* calls;
    unsigned long long ncalls;
    unsigned long long passes;
} LotusRenderer;

void _lotusInitRenderer(LotusRenderer* r, GLFWwindow* ref);
void _lotusPreProcessing(LotusRenderer* r);
void _lotusPostProcessing(LotusRenderer* r);

#endif