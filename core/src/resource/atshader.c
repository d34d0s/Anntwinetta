#include "../../headers/resource/atshader.h"

void _atDestroyShaderData(ATshaderData* d) {
    free(d->vSrc);
    free(d->fSrc);
    free(d->program);
    free(d->n_uniforms);
    atForRangeI(d->count) {
        atDestroyHashmap(d->uniforms[i]);
    }; free(d->uniforms);
    
    d->count = 0;
    free(d);
}

ATerrorType _atInitShaderData(ATshaderData* d, int max) {
    d->count = 0;
    
    d->uniforms = (AThashmap**)malloc(max * sizeof(AThashmap*));
    if (!d->uniforms) {
        atLogError("failed to allocate shader data uniform hashmap array");
        return ERR_MALLOC;
    }

    if (atInitIntArray(&d->program, max, "shader data [program]")) {
        atLogError("failed to allocate shader data [program] array");
        return ERR_MALLOC;
    }

    if (atInitIntArray(&d->n_uniforms, max, "shader data [n uniforms]")) {
        atLogError("failed to allocate shader data [n uniforms] array");
        return ERR_MALLOC;
    }

    if (atInitConstCharPointerArray(&d->vSrc, max, 1024, "shader data [vSrc]")) {
        atLogError("failed to allocate shader data [vSrc] array");
        return ERR_MALLOC;
    }

    if (atInitConstCharPointerArray(&d->fSrc, max, 1024, "shader data [fSrc]")) {
        atLogError("failed to allocate shader data [fSrc] array");
        return ERR_MALLOC;
    }

    return ERR_NONE;
}

int _atSetShaderData(ATshaderData* d, const char* vertex, const char* fragment) {
    int index = d->count++;
    d->n_uniforms[index] = 0;
    d->vSrc[index] = vertex;
    d->fSrc[index] = fragment;
    d->uniforms[index] = atMakeHashmap(16);
    d->program[index] = atglMakeShader(
        vertex, 
        fragment
    ); return index;
}

ATerrorType _atMakeUniform(ATshaderData* d, int index, ATuniformType type, const char* name, void* value) {
    if (index < 0 || index >= d->count) { return ERR_SHADER; }
    
    int n_uniforms = d->n_uniforms[index];
    if (n_uniforms+1 > 16) {
        atLogError("failed to set uniform %s | uniform max reached", name);
        return ERR_SHADER;
    }
    
    int program = d->program[index];
    AThashmap* uniforms = d->uniforms[index];
    
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

    d->n_uniforms[index]++;

    return ERR_NONE;
}

ATerrorType _atSetUniform(ATshaderData* d, int index, ATuniformType type, const char* name, void* value) {
    if (index < 0 || index >= d->count) { return ERR_SHADER; }
    
    if (atSetHashmap(d->uniforms[index], name, value)) {
        atLogError("failed to set uniform %s | uniform max reached", name);
        return ERR_SHADER;
    }

    return ERR_NONE;
}

ATuniformLayout* _atGetUniformLayout(ATshaderData* d, int index, const char* name) {
    if (index < 0 || index >= d->count) { return atTypeCastPtr(ATuniformLayout, ERR_SHADER); }
    
    AThashmap* uniforms = d->uniforms[index];


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
    l->vSrc = &d->vSrc[index];
    l->fSrc = &d->fSrc[index];
    l->program = &d->program[index];
    l->uniforms = &d->uniforms[index];
    
    return l;
}

void _atDestroyShaderLayout(ATshaderLayout* l) {
    l->idx = 0;
    l->vSrc = NULL;
    l->fSrc = NULL;
    l->program = NULL;
    l->uniforms = NULL;
    free(l);
}

void _atDestroyUniformLayout(ATuniformLayout* l) {
    l->name = NULL;
    l->value = NULL;
    l->location = -1;
    free(l);
}
