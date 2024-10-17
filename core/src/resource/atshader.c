#include "../../headers/resource/atshader.h"

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

ATerrorType _atSetShaderUniform(ATshaderData* d, int index, ATuniformType type, const char* name, void* value) {
    if (index < 0 || index >= d->count) { return ERR_SHADER; }
    
    int n_uniforms = d->n_uniforms[index];
    if (n_uniforms+1 > 16) { atLogError("failed to set uniform %s | uniform max reached", name); return ERR_SHADER; }
    
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

ATuniformLayout* _atGetShaderUniform(ATshaderData* d, int index, const char* name) {
    if (index < 0 || index >= d->count) { return atTypeCastPtr(ATuniformLayout, ERR_SHADER); }
    
    AThashmap* uniforms = d->uniforms[index];

    ATuniformLayout* uniform = atGetHashmap(uniforms, name);
    if (!uniform) {
        atLogError("failed to get uniform %s | uniform not set", name);
        return atTypeCastPtr(ATuniformLayout,  ERR_SHADER);
    }; return uniform;
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
