#include "headers/LotusECS.h"
#include "../backend/headers/LotusGL.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/STB/stb_image.h"

// Lotus ECS Internal API
unsigned short _lotusGetEntityCount(void) { return _LOTUS_ECS._count; }
LotusEntity** _lotusGetEntityArray(void) { return &_LOTUS_ECS._entities; }
void lotusSetCID(LotusEntity* e, unsigned short CID_MASK) { e->CID |= CID_MASK; }
void lotusRemCID(LotusEntity* e, unsigned short CID_MASK) { e->CID &= ~CID_MASK; }

unsigned short _lotusHashMesh(float* verts, unsigned short nverts) {
    unsigned short hash = 0;
    for (int i = 0; i < nverts * 3; i++) {
        hash += verts[i];
        hash += i * 31 / (nverts+nverts); 
    } return hash;
}

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

void _lotusMakeUniform(LotusShader_itf* shader, unsigned char uindex, const char* uname, unsigned char utype, void* uvalue) {
    if (shader->program != -1) {
        shader->uniforms[uindex] = (LotusUniform_itf){.name=uname, .utype=utype, .value=uvalue, .location=glGetUniformLocation(shader->program, uname)};

        if (shader->uniforms[uindex].location == -1) {
            _lotusLogError("ERROR RETRIEVING UNIFORM LOCATION: RES[%d]", shader->uniforms[uindex].location); return;
        }
    } else _lotusLogError("ERROR IN SHADER COMPILATION/LINKING: PROGRAM[%d]\n", shader->program); return;

}

void _lotusSetUniformValue(LotusShader_itf* shader, unsigned char uindex, void* uvalue) {
    if (shader->program != -1) {
        glUseProgram(shader->program);
        LotusUniform_itf* uni = &shader->uniforms[uindex];
        if (uni->location != -1) {
            uni->value=uvalue;
        } else _lotusLogError("ERROR IN SHADER COMPILATION/LINKING: PROGRAM[%d]\n", shader->program); return;
    }
}

void _lotusSendUniform(LotusShader_itf* shader, unsigned char uindex) {
    if (shader->program != -1) {
        glUseProgram(shader->program);
        LotusUniform_itf* uni = &shader->uniforms[uindex];
        if (uni->value != NULL) {
            switch (uni->utype) {
                case UTYPE_MAT4:
                    glUniformMatrix4fv(uni->location, 1, GL_FALSE, uni->value);
                    break;
                case UTYPE_VEC2:
                    glUniform2fv(uni->location, 1, uni->value);
                    break;
                case UTYPE_VEC3:
                    glUniform3fv(uni->location, 1, uni->value);
                    break;
                case UTYPE_VEC4:
                    glUniform4fv(uni->location, 1, uni->value);
                    break;
                default: return; break;
            }
        }
    }
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
    _LOTUS_MESH._verts = (float**)malloc(LOTUS_ENTITY_MAX*sizeof(float*));
    if (!_LOTUS_MESH._verts) {
        _lotusLogError("Error Allocating Memory For Mesh Vertex Array");
        return;
    }

    _LOTUS_MESH._nverts = (unsigned short*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned short));
    if (!_LOTUS_MESH._nverts) {
        _lotusLogError("Error Allocating Memory For Mesh NVertex Array");
        free(_LOTUS_MESH._verts);
        return;
    }
    
    _LOTUS_MESH._vsize = (unsigned short*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned short));
    if (!_LOTUS_MESH._vsize) {
        _lotusLogError("Error Allocating Memory For Mesh Vertex Size Array");
        free(_LOTUS_MESH._nverts);
        free(_LOTUS_MESH._verts);
        return;
    }
    
    _LOTUS_MESH._MID = (unsigned short*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned short));
    if (!_LOTUS_MESH._MID) {
        _lotusLogError("Error Allocating Memory For Mesh MID Array");
        free(_LOTUS_MESH._verts);
        free(_LOTUS_MESH._nverts);
        return;
    }
    
    _LOTUS_MESH._vbo = (unsigned int*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned int));
    if (!_LOTUS_MESH._vbo) {
        _lotusLogError("Error Allocating Memory For Mesh VBO Array");
        free(_LOTUS_MESH._verts);
        free(_LOTUS_MESH._nverts);
        return;
    }
    
    _LOTUS_MESH._vao = (unsigned int*)malloc(LOTUS_ENTITY_MAX*sizeof(unsigned int));
    if (!_LOTUS_MESH._vao) {
        _lotusLogError("Error Allocating Memory For Mesh VAO Array");
        free(_LOTUS_MESH._verts);
        free(_LOTUS_MESH._nverts);
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
void lotusReleaseMesh(LotusMesh_itf* m) { free(m->verts); free(m); }
void lotusSetMesh(LotusEntity* e, float* verts, unsigned short nverts, unsigned char vColor, unsigned char vTexture) {
    if (_LOTUS_MESH._count+1 > LOTUS_ENTITY_MAX || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return; }
    unsigned short vsize = 3; // Number of floats per vertex
    vsize+=3*vColor;
    vsize+=2*vTexture;
    _LOTUS_MESH._count++;
    _LOTUS_MESH._vsize[e->EID] = vsize;
    _LOTUS_MESH._nverts[e->EID] = nverts;
    _LOTUS_MESH._MID[e->EID] = _lotusHashMesh(verts, nverts);
    _LOTUS_MESH._verts[e->EID] = (float*)malloc(nverts*vsize*sizeof(float));
    if (!_LOTUS_MESH._verts[e->EID]) {
        _lotusLogError("Error Allocating Space For Mesh Component Vertex Array");
        return;
    } memcpy(_LOTUS_MESH._verts[e->EID], verts, nverts*vsize*sizeof(float));
    _lotusMakeVBO(&_LOTUS_MESH._vbo[e->EID], vsize, nverts, verts);
    _lotusMakeVAO(&_LOTUS_MESH._vao[e->EID], &_LOTUS_MESH._vbo[e->EID]);
    _lotusConfigureVAO(&_LOTUS_MESH._vao[e->EID], vsize, vColor, vTexture);
    lotusSetCID(e, LotusMeshCID);
}

LotusMesh_itf* lotusGetMesh(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusMeshCID)) { return NULL; }
    LotusMesh_itf* m = (LotusMesh_itf*)malloc(sizeof(LotusMesh_itf));
    if (!m) {
        _lotusLogError("ERROR ALLOCATING SPACE FOR MESH INTERFACE");
        return NULL;
    }
    m->verts = malloc(sizeof(float)*_LOTUS_MESH._vsize[e->EID]*_LOTUS_MESH._nverts[e->EID]);
    if (!m->verts) {
        _lotusLogError("ERROR ALLOCATING SPACE FOR MESH INTERFACE VERTEX DATA ARRAY");
        free(m);
        return NULL;
    }
    memcpy(m->verts, _LOTUS_MESH._verts[e->EID], sizeof(float)*_LOTUS_MESH._vsize[e->EID]*_LOTUS_MESH._nverts[e->EID]);
    if (!m->verts) {
        _lotusLogError("ERROR COPYING MEMORY TO MESH INTERFACE VERTEX DATA ARRAY");
        free(m);
        return NULL;
    }
    m->MID = _LOTUS_MESH._MID[e->EID];
    m->vbo = _LOTUS_MESH._vbo[e->EID];
    m->vao = _LOTUS_MESH._vao[e->EID];
    m->vsize = _LOTUS_MESH._vsize[e->EID];
    m->nverts = _LOTUS_MESH._nverts[e->EID];
    return m;
}

void lotusRemMesh(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusMeshCID)) { return; }
    lotusRemCID(e, LotusMeshCID);
    _LOTUS_MESH._count--;
    _LOTUS_MESH._MID[e->EID] = -1;
    _LOTUS_MESH._vbo[e->EID] = -1;
    _LOTUS_MESH._vao[e->EID] = -1;
    _LOTUS_MESH._vsize[e->EID] = -1;
    _LOTUS_MESH._nverts[e->EID] = -1;
    _LOTUS_MESH._verts[e->EID] = NULL;
}


// MATERIAL COMPONENT
void lotusSetUniform(unsigned char MAID, unsigned char uindex, void* uvalue) {
    _lotusSetUniformValue(&_LOTUS_MATERIAL._shader[MAID], uindex, uvalue);
}

void lotusSendUniform(unsigned char MAID, unsigned char uindex) {
    _lotusSendUniform(&_LOTUS_MATERIAL._shader[MAID], uindex);
}


void lotusSetMaterial(LotusEntity* e, unsigned char MAID) {
    if (e->EID > LOTUS_ENTITY_MAX || e->EID < 0 || MAID < 0 || MAID > _LOTUS_MATERIAL._count) { return; }
    _LOTUS_MATERIAL._emap[e->EID] = MAID;
    lotusSetCID(e, LotusMaterialCID);
}

void lotusReleaseMaterial(LotusMaterial_itf* m) { free(m); }

unsigned char lotusGetMaterialID(LotusEntity* e) {
    if (e->EID > LOTUS_ENTITY_MAX || e->EID < 0 || !lotusQueryCID(e, LotusMaterialCID) || _LOTUS_MATERIAL._emap[e->EID] == -1) { return -1; }
    return _LOTUS_MATERIAL._emap[e->EID];
}

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

void lotusRemMaterial(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusMaterialCID) || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return; }
    _LOTUS_MATERIAL._emap[e->EID] = -1;
    lotusRemCID(e, LotusMaterialCID);
}

void lotusDelMaterial(unsigned char MAID) {
    if (_LOTUS_MATERIAL._count-1 > 0) { return; }
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
void lotusSetTexture(LotusEntity* e, unsigned int TEXID) {
    if (e->EID > LOTUS_ENTITY_MAX || e->EID < 0 || TEXID < 0 || TEXID > _LOTUS_TEXTURE._count) { return; }
    _LOTUS_TEXTURE._emap[e->EID] = TEXID;
    lotusSetCID(e, LotusTextureCID);
}

unsigned int lotusReleaseTexture(LotusTexture_itf* t) { free(t); }

unsigned int lotusGetTextureID(LotusEntity* e) {
    if (e->EID > LOTUS_ENTITY_MAX || e->EID < 0 || !lotusQueryCID(e, LotusTextureCID) || _LOTUS_TEXTURE._emap[e->EID] < 0 || _LOTUS_TEXTURE._emap[e->EID] > 1000) { return -1; }
    return _LOTUS_TEXTURE._emap[e->EID];
}

LotusTexture_itf* lotusGetTexture(LotusEntity* e) {
    unsigned int TEXID = lotusGetTextureID(e);
    if (TEXID == -1) { return NULL; }

    LotusTexture_itf* t = (LotusTexture_itf*)malloc(sizeof(LotusTexture_itf));
    if (!t) {
        _lotusLogError("Error Allocating Memory For LotusTexture Interface");
        return NULL;
    }

    t->raw = _LOTUS_TEXTURE._raw[TEXID];
    t->glid = _LOTUS_TEXTURE._glid[TEXID];
    t->TEXID = _LOTUS_TEXTURE._TEXID[TEXID];
    t->width = _LOTUS_TEXTURE._width[TEXID];
    t->height = _LOTUS_TEXTURE._height[TEXID];
    t->textype = _LOTUS_TEXTURE._textype[TEXID];
    t->nchannels = _LOTUS_TEXTURE._nchannels[TEXID];
    return t;
}

void lotusRemTexture(LotusEntity* e) {
    if (!lotusQueryCID(e, LotusTextureCID) || e->EID > LOTUS_ENTITY_MAX || e->EID < 0) { return; }
    _LOTUS_TEXTURE._emap[e->EID] = -1;
    lotusRemCID(e, LotusTextureCID);
}

void lotusDelTexture(unsigned int TEXID) {
    if (_LOTUS_TEXTURE._count-1 > 0) { return; }
    _LOTUS_TEXTURE._raw[TEXID] = NULL;
    _LOTUS_TEXTURE._glid[TEXID] = -1;
    _LOTUS_TEXTURE._TEXID[TEXID] = -1;
    _LOTUS_TEXTURE._width[TEXID] = -1;
    _LOTUS_TEXTURE._height[TEXID] = -1;
    _LOTUS_TEXTURE._textype[TEXID] = -1;
    _LOTUS_TEXTURE._nchannels[TEXID] = -1;
    _LOTUS_TEXTURE._count--;
}

unsigned int lotusMakeTexture(const char* srcpath, LOTUS_TEXTURE_TYPE textype) {
    if (_LOTUS_TEXTURE._count+1 > 1000) { return -1; }
    unsigned int TEXID = _LOTUS_TEXTURE._count;
    glGenTextures(1, &_LOTUS_TEXTURE._glid[TEXID]);
    glBindTexture(GL_TEXTURE_2D, _LOTUS_TEXTURE._glid[TEXID]);

    // TODO: configurable texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load tex2D with stb
    _LOTUS_TEXTURE._textype[TEXID] = textype;
    stbi_set_flip_vertically_on_load(true);
    _LOTUS_TEXTURE._raw[TEXID] = stbi_load(srcpath, &_LOTUS_TEXTURE._width[TEXID], &_LOTUS_TEXTURE._height[TEXID], &_LOTUS_TEXTURE._nchannels[TEXID], 0);
    if (_LOTUS_TEXTURE._raw[TEXID]) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _LOTUS_TEXTURE._width[TEXID], _LOTUS_TEXTURE._height[TEXID], 0, textype, GL_UNSIGNED_BYTE, _LOTUS_TEXTURE._raw[TEXID]);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
            _lotusLogError("Failed To Load Texture Data From:\t%s", srcpath); return -1;
    } stbi_image_free(_LOTUS_TEXTURE._raw[TEXID]); _LOTUS_TEXTURE._count++; return TEXID;
}

