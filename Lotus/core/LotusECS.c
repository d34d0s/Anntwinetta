#include "headers/LotusECS.h"
#include "../backend/headers/LotusGL.h"


// Lotus ECS Internal API
unsigned short _lotusGetEntityCount(void) { return _LOTUS_ECS._count; }
LotusEntity** _lotusGetEntityArray(void) { return &_LOTUS_ECS._entities; }
void lotusSetCID(LotusEntity* e, unsigned short CID_MASK) { e->CID |= CID_MASK; }
void lotusRemCID(LotusEntity* e, unsigned short CID_MASK) { e->CID &= ~CID_MASK; }

unsigned short _lotusHashMesh(float* vertices, unsigned short nvertices) {
    unsigned short hash = 0;
    for (int i = 0; i < nvertices * 3; i++) {
        hash += vertices[i];
        hash += i * 31 / (nvertices+nvertices); 
    } return hash;
}

void _LOTUS_QUELL_ENTITY(LotusEntity* e) {
    if (e->state & (1<<0)) {
        _LOTUS_ECS._quelled[_LOTUS_ECS._nquelled] = e->EID;
        _LOTUS_ECS._count--; _LOTUS_ECS._nquelled++;
        
        // remove components
        if (lotusQueryCID(e, LotusMeshCID)) { lotusRemMesh(e); }
        
        // shift entity array
        _LOTUS_ECS._entities[e->EID] = (LotusEntity){.EID=-1, .CID=-1, .state=-1};
        for (int i = e->EID; i < _LOTUS_ECS._count; i++) {
            _LOTUS_ECS._entities[i] = _LOTUS_ECS._entities[i+1];
            _LOTUS_ECS._entities[i].EID = i;
        } _LOTUS_ECS._entities[_LOTUS_ECS._count-1].EID = -1;  // handle "orphaned" entity
        e->EID = -1;
        e->CID = -1;
    }
}

void _LOTUS_INIT_MESH(void) {
    _LOTUS_MESH._count=0;
    _LOTUS_MESH._vertices = (float**)malloc(LOTUS_ENTITY_MAX*sizeof(float*));
    if (!_LOTUS_MESH._vertices) {
        _lotusLogError("Error Allocating Memory For Mesh Vertex Array");
        return;
    }

    _LOTUS_MESH._nvertices = (unsigned short*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned short));
    if (!_LOTUS_MESH._nvertices) {
        _lotusLogError("Error Allocating Memory For Mesh NVertex Array");
        free(_LOTUS_MESH._vertices);
        return;
    }
    
    _LOTUS_MESH._MID = (unsigned short*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned short));
    if (!_LOTUS_MESH._MID) {
        _lotusLogError("Error Allocating Memory For Mesh MID Array");
        free(_LOTUS_MESH._vertices);
        free(_LOTUS_MESH._nvertices);
        return;
    }
    
    _LOTUS_MESH._vbo = (unsigned int*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned int));
    if (!_LOTUS_MESH._vbo) {
        _lotusLogError("Error Allocating Memory For Mesh VBO Array");
        free(_LOTUS_MESH._vertices);
        free(_LOTUS_MESH._nvertices);
        return;
    }
    
    _LOTUS_MESH._vao = (unsigned int*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned int));
    if (!_LOTUS_MESH._vao) {
        _lotusLogError("Error Allocating Memory For Mesh VAO Array");
        free(_LOTUS_MESH._vertices);
        free(_LOTUS_MESH._nvertices);
        free(_LOTUS_MESH._vbo);
        return;
    }
}

void _LOTUS_INIT_ECS(void) {
    _LOTUS_ECS._count=0;
    _LOTUS_ECS._nquelled=0;
    
    _LOTUS_ECS._quelled=(unsigned short*)malloc(sizeof(unsigned short)*LOTUS_ENTITY_MAX);
    if (!_LOTUS_ECS._quelled) {
        _lotusLogError("Error Allocating Space For Lotus ECS Internal Quelled EID Array");
        return;
    } 
    
    _LOTUS_ECS._entities=(LotusEntity*)malloc(sizeof(LotusEntity)*LOTUS_ENTITY_MAX);
    if (!_LOTUS_ECS._entities) {
        _lotusLogError("Error Allocating Space For Lotus ECS Internal Entity Array");
        return;
    }
    
    _LOTUS_INIT_MESH();
    memset(_LOTUS_MATERIAL._emap, -1, sizeof(unsigned int)*LOTUS_ENTITY_MAX);
    _LOTUS_TEXTURE._count=0; _LOTUS_TRANSFORM._count=0;
}


// Lotus ECS External API
LotusEntity* lotusMakeEntity(void) {
    unsigned short EID;
    if (_LOTUS_ECS._count+1 > LOTUS_ENTITY_MAX) {
        _lotusLogError("Lotus Entity Max Reached!"); return NULL;
    }
   
    if (_LOTUS_ECS._nquelled <= 0) {
        EID = _LOTUS_ECS._count++;
    } else {
        EID = _LOTUS_ECS._quelled[_LOTUS_ECS._nquelled-1];
        _LOTUS_ECS._count++; _LOTUS_ECS._nquelled--;
    }

    if (EID < LOTUS_ENTITY_MAX) {
        _LOTUS_ECS._entities[EID] = (LotusEntity){.EID=EID, .CID=0};
    } else {
        _LOTUS_ECS._entities[EID] = (LotusEntity){.EID=-1, .CID=-1} ;
    } return &_LOTUS_ECS._entities[EID];
}
void lotusQuellEntity(LotusEntity* e) {
    if (e->state & (1<<0)) { return; }
    e->state |= (1<<0);
    _LOTUS_QUELL_ENTITY(e);
}
unsigned char lotusQueryCID(LotusEntity* e, unsigned short CID_MASK) {
    return (e->CID & CID_MASK) ? 1 : 0;
}


// MESH COMPONENT
void lotusReleaseMesh(LotusMesh_itf* m) { free(m->vertices); free(m); }
void lotusSetMesh(LotusEntity* e, float* vertices, unsigned short nvertices) {
    if (_LOTUS_MESH._count+1 > LOTUS_ENTITY_MAX || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return; }
    _LOTUS_MESH._count++;
    _LOTUS_MESH._nvertices[e->EID] = nvertices;
    _LOTUS_MESH._MID[e->EID] = _lotusHashMesh(vertices, nvertices);
    _LOTUS_MESH._vertices[e->EID] = (float*)malloc(nvertices*3*sizeof(float));
    if (!_LOTUS_MESH._vertices[e->EID]) {
        _lotusLogError("Error Allocating Space For Mesh Component Vertex Array");
        return;
    } memcpy(_LOTUS_MESH._vertices[e->EID], vertices, nvertices*3*sizeof(float));
    _lotusMakeVBO(&_LOTUS_MESH._vbo[e->EID], _LOTUS_MESH._vertices[e->EID], nvertices);
    _lotusMakeVAO(&_LOTUS_MESH._vao[e->EID], &_LOTUS_MESH._vbo[e->EID]);
    _lotusConfigureVAO(&_LOTUS_MESH._vao[e->EID]);
    lotusSetCID(e, LotusMeshCID);
}

LotusMesh_itf* lotusGetMesh(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusMeshCID)) { return NULL; }
    LotusMesh_itf* m = (LotusMesh_itf*)malloc(sizeof(LotusMesh_itf));
    if (!m) {
        _lotusLogError("ERROR ALLOCATING SPACE FOR MESH INTERFACE");
        return NULL;
    }
    m->vertices = malloc(sizeof(float)*3*_LOTUS_MESH._nvertices[e->EID]);
    if (!m->vertices) {
        _lotusLogError("ERROR ALLOCATING SPACE FOR MESH INTERFACE VERTEX DATA ARRAY");
        free(m);
        return NULL;
    }
    memcpy(m->vertices, _LOTUS_MESH._vertices[e->EID], sizeof(float)*3*_LOTUS_MESH._nvertices[e->EID]);
    if (!m->vertices) {
        _lotusLogError("ERROR COPYING MEMORY TO MESH INTERFACE VERTEX DATA ARRAY");
        free(m);
        return NULL;
    }
    m->MID = _LOTUS_MESH._MID[e->EID];
    m->vbo = _LOTUS_MESH._vbo[e->EID];
    m->vao = _LOTUS_MESH._vao[e->EID];
    m->nvertices = _LOTUS_MESH._nvertices[e->EID];
    return m;
}

void lotusRemMesh(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusMeshCID)) { return; }
    lotusRemCID(e, LotusMeshCID);
    _LOTUS_MESH._count--;
    _LOTUS_MESH._MID[e->EID] = -1;
    _LOTUS_MESH._vbo[e->EID] = -1;
    _LOTUS_MESH._vao[e->EID] = -1;
    _LOTUS_MESH._nvertices[e->EID] = -1;
    _LOTUS_MESH._vertices[e->EID] = NULL;
}


// MATERIAL COMPONENT
void _lotusMakeShader(unsigned int* program, const char* vshader, const char* fshader) {
    *program = glCreateProgram();
    
    unsigned int _vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vshader, 1, &vshader, NULL);
    glCompileShader(_vshader);
    
    int vsuccess;
    glGetShaderiv(_vshader, GL_COMPILE_STATUS, &vsuccess);
    if (!vsuccess) {
        char infoLog[512];
        glGetShaderInfoLog(_vshader, 512, NULL, infoLog);
        printf("ERROR::VERTEX_SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }
    
    unsigned int _fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fshader, 1, &fshader, NULL);
    glCompileShader(_fshader);
    
    int fsuccess;
    glGetShaderiv(_fshader, GL_COMPILE_STATUS, &fsuccess);
    if (!fsuccess) {
        char infoLog[512];
        glGetShaderInfoLog(_fshader, 512, NULL, infoLog);
        printf("ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }

    glAttachShader(*program, _vshader);
    glAttachShader(*program, _fshader);
    glLinkProgram(*program);

    int success;
    glGetProgramiv(*program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(*program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    } glDeleteShader(_vshader); glDeleteShader(_fshader);
}

void _lotusMakeUniform(LotusShader_itf* shader, unsigned char index, const char* name, unsigned char utype, void* value) {
    if (shader->program != -1) {
        shader->uniforms[index] = (LotusUniform_itf){.name=name, .utype=utype, .value=value, .location=glGetUniformLocation(shader->program, name)};

        if (shader->uniforms[index].location == -1) {
            _lotusLogError("ERROR RETRIEVING UNIFORM LOCATION: RES[%d]", shader->uniforms[index].location); return;
        }
    } else _lotusLogError("ERROR IN SHADER COMPILATION/LINKING: PROGRAM[%d]\n", shader->program); return;

}

void _lotusSetUniformValue(LotusShader_itf* shader, unsigned char index, void* value) {
    if (shader->program != -1) {
        glUseProgram(shader->program);
        LotusUniform_itf* uni = &shader->uniforms[index];
        if (uni->location != -1) {
            uni->value=value;
        } else _lotusLogError("ERROR IN SHADER COMPILATION/LINKING: PROGRAM[%d]\n", shader->program); return;
    }
}

void _lotusSendUniform(LotusShader_itf* shader, unsigned char index) {
    if (shader->program != -1) {
        glUseProgram(shader->program);
        LotusUniform_itf* uni = &shader->uniforms[index];
        if (uni->value != NULL) {
            switch (uni->utype) {
                case UTYPE_MAT4:
                    glUniformMatrix4fv(uni->location, 1, GL_FALSE, uni->value);
                    break;
                default: return; break;
            }
        }
    }
}

unsigned char lotusMakeMaterial(const char* vshader, const char* fshader, unsigned int nuniforms, const char** unames, unsigned int* utypes,  void** uvalues) {
    if (_LOTUS_MATERIAL._count+1 > (1 << 8)-1) { return -1; }
    unsigned char MAID = _LOTUS_MATERIAL._count;
    _LOTUS_MATERIAL._MAID[MAID] = MAID;
    _LOTUS_MATERIAL._ambient[MAID] = 1.0f;
    _LOTUS_MATERIAL._diffuse[MAID] = 1.0f;
    _LOTUS_MATERIAL._specular[MAID] = 1.0f;
    _LOTUS_MATERIAL._shader[MAID].vsrc = vshader;
    _LOTUS_MATERIAL._shader[MAID].fsrc = fshader;
    _lotusMakeShader(&_LOTUS_MATERIAL._shader[MAID].program, vshader, fshader);
    if (nuniforms > 0 && nuniforms < 17) {
        // TODO: retrieve uview, and uproj from LotusCamera
        _LOTUS_MATERIAL._nuniforms[MAID] = nuniforms;
        for (int i = 0; i < nuniforms; i++) {
            _lotusMakeUniform(&_LOTUS_MATERIAL._shader[MAID], i, unames[i], utypes[i], uvalues[i]);
            _lotusSendUniform(&_LOTUS_MATERIAL._shader[MAID], i);
        }
    }
    _LOTUS_MATERIAL._count++; return MAID;
}

void lotusSetMaterial(LotusEntity* e, unsigned char MAID) {
    if (e->EID > LOTUS_ENTITY_MAX || e->EID < 0 || MAID < 0 || MAID > _LOTUS_MATERIAL._count) { return; }
    _LOTUS_MATERIAL._emap[e->EID] = MAID;
    lotusSetCID(e, LotusMaterialCID);
}

void lotusReleaseMaterial(LotusMaterial_itf* m) { free(m); }
LotusMaterial_itf* lotusGetMaterial(LotusEntity* e) {
    unsigned char MAID = lotusGetMaterialID(e);
    if (MAID == -1) { return NULL; }
    
    LotusMaterial_itf* m = (LotusMaterial_itf*)malloc(sizeof(LotusMaterial_itf));
    if (!m) {
        _lotusLogError("Error Allocating Space For Material Component Interface");
        return NULL;
    }

    m->MAID = MAID;
    m->shader = _LOTUS_MATERIAL._shader[m->MAID];
    m->ambient = _LOTUS_MATERIAL._ambient[m->MAID];
    m->diffuse = _LOTUS_MATERIAL._diffuse[m->MAID];
    m->specular = _LOTUS_MATERIAL._specular[m->MAID];
    m->nuniforms = _LOTUS_MATERIAL._nuniforms[m->MAID];
    return m;
}

unsigned char lotusGetMaterialID(LotusEntity* e) {
    if (e->EID > LOTUS_ENTITY_MAX || e->EID < 0 || !lotusQueryCID(e, LotusMaterialCID) || _LOTUS_MATERIAL._emap[e->EID] == -1) { return -1; }
    return _LOTUS_MATERIAL._emap[e->EID];
}

void lotusRemMaterial(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusMaterialCID) || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return; }
    _LOTUS_MATERIAL._emap[e->EID] = -1;
    lotusRemCID(e, LotusMaterialCID);
}

void lotusDelMaterial(unsigned char MAID) {
    if (_LOTUS_MATERIAL._count+1 > (1 << 8)-1) { return; }
    _LOTUS_MATERIAL._ambient[MAID] = -1;
    _LOTUS_MATERIAL._diffuse[MAID] = -1;
    _LOTUS_MATERIAL._specular[MAID] = -1;
    _LOTUS_MATERIAL._shader[MAID].vsrc = NULL;
    _LOTUS_MATERIAL._shader[MAID].fsrc = NULL;
    _LOTUS_MATERIAL._shader[MAID].program = -1;

    unsigned int nuniforms = _LOTUS_MATERIAL._nuniforms[MAID];
    if (nuniforms > 0 && nuniforms < 17) {
        for (int i = 0; i < nuniforms; i++) {
            _LOTUS_MATERIAL._shader[MAID].uniforms[i] = (LotusUniform_itf){.location=-1, .utype=-1, .value=NULL, .name=NULL};
        }
    } _LOTUS_MATERIAL._count--;
}


// TRANSFORM COMPONENT
void lotusSetTransform(LotusEntity* e, LMvec3 scale, LMvec3 rotation, LMvec3 location) {
    if (_LOTUS_TRANSFORM._count+1 > LOTUS_ENTITY_MAX || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return; }
    _LOTUS_TRANSFORM._count++;
    _LOTUS_TRANSFORM._scale[e->EID] = scale;
    _LOTUS_TRANSFORM._location[e->EID] = location;
    _LOTUS_TRANSFORM._rotation[e->EID] = rotation;
    _LOTUS_TRANSFORM._model[e->EID] = lmIdentity();
    lotusSetCID(e, LotusTransformCID);
}

void lotusReleaseTransform(LotusTransform_itf* t) { free(t); }
LotusTransform_itf* lotusGetTransform(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusTransformCID) || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return NULL; }
    LotusTransform_itf* t = (LotusTransform_itf*)malloc(sizeof(LotusTransform_itf));
    if (!t) {
        _lotusLogError("Error Allocating Space For LotusTransform Interface");
        return NULL;
    }
    t->model = &_LOTUS_TRANSFORM._model[e->EID];
    t->scale = &_LOTUS_TRANSFORM._scale[e->EID];
    t->location = &_LOTUS_TRANSFORM._location[e->EID];
    t->rotation = &_LOTUS_TRANSFORM._rotation[e->EID];
    return t;
}

void lotusRemTransform(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusTransformCID) || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return; }
    _LOTUS_TRANSFORM._count--;
    _LOTUS_TRANSFORM._model[e->EID] = (LMmat4){-1};
    _LOTUS_TRANSFORM._scale[e->EID] = (LMvec3){-1};
    _LOTUS_TRANSFORM._location[e->EID] = (LMvec3){-1};
    _LOTUS_TRANSFORM._rotation[e->EID] = (LMvec3){-1};
    lotusRemCID(e, LotusTransformCID);
}


// TEXTURE COMPONENT
void lotusSetTexture() {

}
