#ifndef LOTUSECS_H
#define LOTUSECS_H

#include "lotus_types.h"
#include "LotusMath.h"

#define LOTUS_ENTITY_MAX 65535

// Lotus Component Identifiers ( CID_MAX = 16 )
#define LotusMeshCID (1<<0)
#define LotusTextureCID (1<<1)
#define LotusMaterialCID (1<<2)
#define LotusTransformCID (1<<3)

typedef enum LOTUS_UNIFORM_TYPE {
    UTYPE_MAT4=0,
    UTYPE_VEC2,
    UTYPE_VEC3,
    UTYPE_VEC4,
    UTYPE_COUNT
} LOTUS_UNIFORM_TYPE;

typedef enum LOTUS_UNIFORM_INDEX {
    UMODEL_INDEX=0,
    UVIEW_INDEX,
    UPROJ_INDEX,
    UINDEX_COUNT
} LOTUS_UNIFORM_INDEX;

typedef struct LotusEntity {
    unsigned char state;    // state Bitfield   [quell, ...(NULL)]
    unsigned short EID;     // Entity Identifier
    unsigned short CID;     // Component Bitfield
} LotusEntity;

// COMPONENT INTERFACES
typedef struct LotusMesh_itf {
    float* verts;
    unsigned int vbo;
    unsigned int vao;
    unsigned short MID;
    unsigned short vsize;
    unsigned short nverts;
} LotusMesh_itf;

typedef struct LotusUniform_itf {
    void* value;
    const char* name;
    unsigned char utype;
    unsigned int location;
} LotusUniform_itf;

typedef struct LotusShader_itf {
    const char* vsrc;
    const char* fsrc;
    unsigned int program;
    LotusUniform_itf uniforms[16];
} LotusShader_itf;

typedef struct LotusMaterial_itf {
    float ambient;
    float diffuse;
    float specular;
    unsigned int MAID;       // materialID
    LotusShader_itf shader;
    unsigned int nuniforms;
} LotusMaterial_itf;

typedef struct LotusTransform_itf {
    LMmat4* model;
    LMvec3* scale;
    LMvec3* location;
    LMvec3* rotation;
} LotusTransform_itf;

// INTERNAL COMPONENT SoA STORES
typedef struct _LOTUS_MESH_INTERNAL {
    unsigned short _count;
    float** _verts;
    unsigned int* _vbo;
    unsigned int* _vao;
    unsigned short* _MID;
    unsigned short* _vsize;
    unsigned short* _nverts;
} _LOTUS_MESH_INTERNAL;
static _LOTUS_MESH_INTERNAL _LOTUS_MESH;

typedef struct _LOTUS_TEXTURE_INTERNAL {
    unsigned short _count;
} _LOTUS_TEXTURE_INTERNAL;
static _LOTUS_TEXTURE_INTERNAL _LOTUS_TEXTURE;

typedef struct _LOTUS_MATERIAL_INTERNAL {
    unsigned char _count;
    float _ambient[256];
    float _diffuse[256];
    float _specular[256];
    LotusShader_itf _shader[256];
    unsigned short _MAID[256];
    unsigned int _nuniforms[256];
    unsigned int _emap[LOTUS_ENTITY_MAX];    // maps EIDs -> MAIDs
} _LOTUS_MATERIAL_INTERNAL;
static _LOTUS_MATERIAL_INTERNAL _LOTUS_MATERIAL;

typedef struct _LOTUS_TRANSFORM_INTERNAL {
    unsigned short _count;
    LMmat4 _model[LOTUS_ENTITY_MAX];
    LMvec3 _scale[LOTUS_ENTITY_MAX];
    LMvec3 _location[LOTUS_ENTITY_MAX];
    LMvec3 _rotation[LOTUS_ENTITY_MAX];
} _LOTUS_TRANSFORM_INTERNAL;
static _LOTUS_TRANSFORM_INTERNAL _LOTUS_TRANSFORM;

typedef struct _LOTUS_ECS_INTERNAL {
    LotusEntity* _entities;
    unsigned short _count;     // number of active EIDs
    unsigned short _nquelled;    // number of quelled EIDs
    unsigned short* _quelled;    // array of quelled EIDs
} _LOTUS_ECS_INTERNAL;
static _LOTUS_ECS_INTERNAL _LOTUS_ECS;

unsigned short _lotusGetEntityCount(void);
LotusEntity** _lotusGetEntityArray(void);
unsigned short _lotusHashMesh(float* vertices, unsigned short nverts);

void _LOTUS_INIT_ECS(void);
void _LOTUS_QUELL_ENTITY(LotusEntity* e);

// Set A Component To An Entity's CID Bitfield
void lotusSetCID(LotusEntity* e, unsigned short CID_MASK);

// Remove A Component From An Entity's CID Bitfield
void lotusRemCID(LotusEntity* e, unsigned short CID_MASK);


// Lotus Shader/Uniform Management
void _lotusMakeShader(unsigned int* program, const char* vshader, const char* fshader);
void _lotusMakeUniform(LotusShader_itf* shader, unsigned char index, const char* name, unsigned char utype, void* value);
void _lotusSetUniformValue(LotusShader_itf* shader, unsigned char index, void* value);
void _lotusSendUniform(LotusShader_itf* shader, unsigned char index);

// Generate A New Entity ( EIDs Are Pooled )
LOTUS_API LotusEntity* lotusMakeEntity(void);

// Mark An Entity For Quelling ( deletion ) By Lotus Internal Cleanup
LOTUS_API void lotusQuellEntity(LotusEntity* e);

// Query A Component In An Entity's CID Bitfield
LOTUS_API unsigned char lotusQueryCID(LotusEntity* e, unsigned short CID_MASK);


// LOTUS MESH API
// Remove A Mesh Component From A Given Entity
LOTUS_API void lotusRemMesh(LotusEntity* e);

// Frees A Mesh Interface Returned From lotusGetMesh()
LOTUS_API void lotusReleaseMesh(LotusMesh_itf* m);

// Returns A Dynamically Allocated And Populated LotusMesh Interface Structure
LOTUS_API LotusMesh_itf* lotusGetMesh(LotusEntity* e);

// Set A Mesh Component To A Given Entity
LOTUS_API void lotusSetMesh(LotusEntity* e, float* verts, unsigned short nverts, unsigned char vColor);


// LOTUS MATERIAL API
LOTUS_API void lotusRemMaterial(LotusEntity* e);
LOTUS_API void lotusDelMaterial(unsigned char MAID);    // TODO: remove the material from any entities with it!
LOTUS_API void lotusReleaseMaterial(LotusMaterial_itf* m);
LOTUS_API unsigned char lotusGetMaterialID(LotusEntity* e);
LOTUS_API LotusMaterial_itf* lotusGetMaterial(LotusEntity* e);
LOTUS_API void lotusSetMaterial(LotusEntity* e, unsigned char MAID);
LOTUS_API void lotusSendUniform(unsigned char MAID, unsigned char uindex);
LOTUS_API void lotusSetUniform(unsigned char MAID, unsigned char uindex, void* uvalue);
LOTUS_API unsigned char lotusMakeMaterial(const char* vshader, const char* fshader, unsigned int nuniforms, const char** unames, unsigned int* utypes,  void** uvalues);


// LOTUS TRANSFORM API
LOTUS_API void lotusRemTransform(LotusEntity* e);
LOTUS_API void lotusReleaseTransform(LotusTransform_itf* t);
LOTUS_API LotusTransform_itf* lotusGetTransform(LotusEntity* e);
LOTUS_API void lotusSetTransform(LotusEntity* e, LMvec3 scale, LMvec3 rotation, LMvec3 location);

LOTUS_API void lotusSetTexture();

#endif