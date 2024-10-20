#include "../../headers/resource/atshader.h"

void _atDestroyShaderData(ATshaderData* d) {
    atDestroyArray(d->vSrc);
    atDestroyArray(d->fSrc);
    atDestroyArray(d->program);
    atDestroyArray(d->uniforms);
    atDestroyArray(d->n_uniforms);
    d->count = 0;
    free(d);
}

ATerrorType _atInitShaderData(ATshaderData* d, int max) {
    d->count = 0;
    d->vSrc = atMakeArray(max, 250);
    d->fSrc = atMakeArray(max, 250);
    d->program = atMakeArray(max, 250);
    d->uniforms = atMakeArray(max, 250);
    d->n_uniforms = atMakeArray(max, 250);
    return ERR_NONE;
}

int _atSetShaderData(ATshaderData* d, const char* vertex, const char* fragment) {
    int index = d->count++;
    atInsertArray(d->uniforms, index, atMakeValue(TYPE_HASHMAP, atMakeHashmap(16)));
    atInsertArray(d->n_uniforms, index, atMakeInt(0));
    atInsertArray(d->vSrc, index, atMakeString(vertex));
    atInsertArray(d->fSrc, index, atMakeString(fragment));
    atInsertArray(d->program, index, atMakeInt(atglMakeShader(
        vertex, 
        fragment
    ))); return index;
}

ATerrorType _atMakeUniform(ATshaderData* d, int index, ATuniformType type, const char* name, void* value) {
    if (index < 0 || index >= d->count) { return ERR_SHADER; }
    
    int n_uniforms = atQueryArrayInt(d->n_uniforms, index);
    if (n_uniforms+1 > 16) {
        atLogError("failed to set uniform %s | uniform max reached", name);
        return ERR_SHADER;
    }
    
    int program = atQueryArrayInt(d->program, index);
    AThashmap* uniforms = (AThashmap*)((ATvalue*)atQueryArray(d->uniforms, index)->value);
    
    ATuniformLayout* uniform = (ATuniformLayout*)malloc(sizeof(ATuniformLayout));
    if (!uniform) {
        atLogError("failed to allocate uniform %s\'s layout", name);
        return ERR_MALLOC;
    }

    uniform->name = name;
    uniform->value = value;
    uniform->location = atglGetUniformLocation(program, name);
    atglSetUniformValue(type, program, uniform->location, uniform->value);

    atSetHashmap(uniforms, name, uniform);

    atInsertArray(d->n_uniforms, index, atMakeInt(0));

    return ERR_NONE;
}

ATerrorType _atSetUniform(ATshaderData* d, int index, ATuniformType type, const char* name, void* value) {
    if (index < 0 || index >= d->count) { return ERR_SHADER; }
    
    ATuniformLayout* uniform = _atGetUniformLayout(d, index, name);
    uniform->value = value;

    AThashmap* uniforms = (AThashmap*)((ATvalue*)atQueryArray(d->uniforms, index)->value);
    if (atSetHashmap(uniforms, name, uniform)) {
        atLogError("failed to set uniform %s | uniform max reached", name);
        return ERR_SHADER;
    }

    return ERR_NONE;
}

ATuniformLayout* _atGetUniformLayout(ATshaderData* d, int index, const char* name) {
    if (index < 0 || index >= d->count) { return atTypeCastPtr(ATuniformLayout, ERR_SHADER); }
    
    AThashmap* uniforms = (AThashmap*)((ATvalue*)atQueryArray(d->uniforms, index)->value);

    ATuniformLayout* uniform = (ATuniformLayout*)malloc(sizeof(ATuniformLayout));
    if (!uniform) {
        atLogError("failed to allocate uniform layout");
        return atTypeCastPtr(ATuniformLayout,  ERR_MALLOC);
    }
    
    ATuniformLayout* uniformPtr = atGetHashmap(uniforms, name);
    if (!uniformPtr) {
        atLogError("failed to get uniform %s | uniform not set", name);
        free(uniform);
        return atTypeCastPtr(ATuniformLayout,  ERR_SHADER);
    };
    
    uniform->name = uniformPtr->name;
    uniform->value = uniformPtr->value;
    uniform->location = uniformPtr->location;

    return uniform;
}

ATshaderLayout* _atGetShaderLayout(ATshaderData* d, int index) {
    if (index < 0 || index >= d->count) { return atTypeCastPtr(ATshaderLayout, ERR_SHADER); }

    ATshaderLayout* l = (ATshaderLayout*)malloc(sizeof(ATshaderLayout));
    if (!l) {
        atLogError("failed to allocate shader layout | idx[%d]", index);
        return atTypeCastPtr(ATshaderLayout, ERR_SHADER);
    }
    l->idx = index;
    l->vSrc = atQueryArrayString(d->vSrc, index);
    l->fSrc = atQueryArrayString(d->fSrc, index);
    l->program = atQueryArrayInt(d->program, index);
    l->uniforms = (AThashmap*)((ATvalue*)atQueryArray(d->uniforms, index)->value);
    return l;
}

void _atDestroyShaderLayout(ATshaderLayout* l) {
    l->idx = 0;
    l->vSrc = NULL;
    l->fSrc = NULL;
    l->program = -1;
    l->uniforms = NULL;
    free(l);
}

void _atDestroyUniformLayout(ATuniformLayout* l) {
    l->name = NULL;
    l->value = NULL;
    l->location = -1;
    free(l);
}
