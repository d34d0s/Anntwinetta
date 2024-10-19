#include "../headers/atds.h"

/*

DYNAMIC VALUES

*/

int atGetInt(ATvalue* v) {
    return *(int*)v->value;
}

char* atGetString(ATvalue* v) {
    return (char*)v->value;
}

float atGetFloat(ATvalue* v) {
    return *(float*)v->value;
}

void atDestroyValue(ATvalue* v) {
    v->type = TYPE_NONE;
    free(v->value);
    free(v);
}

ATvalue* atMakeInt(int value) {
    ATvalue* v = (ATvalue*)malloc(sizeof(ATvalue));
    if (!v) {
        atLogError("failed to allocate dynamic value");
        return atTypeCastPtr(ATvalue, ERR_MALLOC);
    }

    v->type = TYPE_INT;
    
    v->value = (int*)malloc(sizeof(int));
    if (!v->value) {
        atLogError("failed to allocate integer");
        v->value = NULL;
        return v;
    }; *(int*)v->value = value;
    
    return v;
}

ATvalue* atMakeFloat(float value) {
    ATvalue* v = (ATvalue*)malloc(sizeof(ATvalue));
    if (!v) {
        atLogError("failed to allocate dynamic value");
        return atTypeCastPtr(ATvalue, ERR_MALLOC);
    }

    v->type = TYPE_FLOAT;
    
    v->value = (float*)malloc(sizeof(float));
    if (!v->value) {
        atLogError("failed to allocate float");
        v->value = NULL;
        return v;
    }; *(float*)v->value = value;
    
    return v;
}

ATvalue* atMakeString(const char* value) {
    ATvalue* v = (ATvalue*)malloc(sizeof(ATvalue));
    if (!v) {
        atLogError("failed to allocate dynamic value");
        return atTypeCastPtr(ATvalue, ERR_MALLOC);
    }

    v->type = TYPE_STRING;
    v->value = strdup(value);
    return v;
}


/*

DYNAMIC ARRAY

*/

ATarray* atMakeArray(int max, int resize) {
    ATarray* arr = (ATarray*)malloc(sizeof(ATarray));
    if (!arr) {
        atLogError("failed to allocate dynamic array");
        return atTypeCastPtr(ATarray, ERR_MALLOC);
    }

    arr->count = 0;
    arr->max = max;
    arr->resize = resize;

    arr->arr = (void**)malloc(max*sizeof(void*));
    if (!arr->arr) {
        free(arr);
        atLogError("failed to allocate dynamic array");
        return atTypeCastPtr(ATarray, ERR_MALLOC);
    }; return arr;
}

void atDestroyArray(ATarray* inArr) {
    // free associated data
    atForRangeI(inArr->count) {
        atDestroyValue(inArr->arr[i]);
    };  free(inArr->arr);
    inArr->resize = 0;
    inArr->count = 0;
    inArr->max = 0;
    free(inArr);
}

ATerrorType atResizeArray(ATarray* inArr) {
    ATerrorType err = ERR_NONE;
    
    void** temp = (void**)realloc(inArr->arr, inArr->max+inArr->resize * sizeof(void*));
    if (!temp) {
        err = ERR_MALLOC;
        return err;
    }
    
    inArr->max += inArr->resize;
    inArr->arr = temp;
    return err;
}

ATerrorType atInsertArray(ATarray* inArr, int index, ATvalue* value) {
    ATerrorType err = ERR_NONE;
    if (!inArr || index < 0) { return err; }

    if (index >= inArr->max || inArr->count == inArr->max) {
        err = atResizeArray(inArr);
    }

    if (!err) {
        inArr->arr[index] = value;
        inArr->count++;
    }; return err;
}

ATerrorType atInsertArrayV(ATarray* inArr, int count, ATvalue** values) {
    ATerrorType err = ERR_NONE;
    if (inArr->count + count >= inArr->max || inArr->count == inArr->max) {
        err = atResizeArray(inArr);
    }
    if (!err) {
        for (int i = 0; i < count; i++) {
            inArr->arr[inArr->count] = values[i];
            inArr->count++;
        }
    }; return err;
}

ATvalue* atPopArray(ATarray* inArr, int index) {
    ATerrorType err = ERR_NONE;
    
    if (!inArr || index >= inArr->max) {
        return atTypeCastPtr(void, err);
    }

    void* value = inArr->arr[index];

    for (int i = index; i < inArr->count-1; i++) {
        inArr->arr[i] = inArr->arr[i + 1];
    };inArr->arr[inArr->count-1] = NULL;
    
    inArr->count--;
    return value;
}

ATvalue* atQueryArray(ATarray* inArr, int index) {
    ATerrorType err = ERR_NONE;
    
    if (!inArr || index >= inArr->max) {
        return atTypeCastPtr(void, err);
    }
    
    return inArr->arr[index];
}

int atQueryArrayInt(ATarray* inArr, int index) {
    return atGetInt(atQueryArray(inArr, index));
}

float atQueryArrayFloat(ATarray* inArr, int index) {
    return atGetFloat(atQueryArray(inArr, index));
}

char* atQueryArrayString(ATarray* inArr, int index) {
    return atGetString(atQueryArray(inArr, index));
}

/*

HASHMAP

*/
uint32_t atStringHash(const char* buffer) {
    uint32_t res = 0;
    size_t size = strlen(buffer);
    atForRangeI(size) {
        res+=(uint32_t)buffer[i]*31;
    }; return res;
}

AThashmap* atMakeHashmap(uint32_t max) {
    AThashmap* m = (AThashmap*)malloc(sizeof(AThashmap));
    if (!m) {
        atLogError("failed to allocate hashmap");
        return atTypeCastPtr(AThashmap, ERR_MALLOC);
    }

    m->max = max;
    m->count = 0;

    m->map = (ATkvPair**)calloc(max, sizeof(ATkvPair*));
    if (!m->map) {
        free(m);
        atLogError("failed to allocate hashmap array");
        return atTypeCastPtr(AThashmap, ERR_MALLOC);
    }

    return m;
}

void atDestroyHashmap(AThashmap* m) {
    m->max = 0;
    m->count = 0;
    for (uint32_t i = 0; i < m->max; i++) {
        if (m->map[i]) {
            free(m->map[i]);
        }
    } free(m->map); free(m);
}


uint8_t atProbeHashmapF(AThashmap* m, uint32_t* kHash, const char* key) {
    uint8_t match = 0;
    ATkvPair* kvp = m->map[*kHash];
    
    for (uint32_t i = *kHash+1; i < m->max; i++) {
        kvp = m->map[i];
        if (key == NULL) {
            if (!kvp) {
                match = 1;
                *kHash = i;
                break;
            } else continue;
        } else {
            if (kvp && !strcmp(key, kvp->k)) {
                *kHash = i;
                match = 1;
                break;
            } else continue;
        }
    } return match;
}

uint8_t atProbeHashmapR(AThashmap* m, uint32_t* kHash, const char* key) {
    uint8_t match = 0;
    ATkvPair* kvp = m->map[*kHash];
    
    for (uint32_t i = *kHash-1; i > 0; i--) {
        kvp = m->map[i];
        if (key == NULL) {
            if (!kvp) {
                match = 1;
                *kHash = i;
                break;
            } else continue;
        } else {
            if (kvp && !strcmp(key, kvp->k)) {
                match = 1;
                *kHash = i;
                break;
            } else continue;
        }
    } return match;
}


void* atGetHashmap(AThashmap* m, const char* key) {
    if (!key) { return atTypeCastPtr(void, ERR_PROCESS); }

    uint32_t kHash = atStringHash(key) % m->max;
    ATkvPair* kvp = m->map[kHash];

    if (kvp && strcmp(key, kvp->k)) {
        uint8_t match = 0;

        // forward probing
        match = atProbeHashmapF(m, &kHash, key);

        // reverse probing
        if (!match) {
            match = atProbeHashmapR(m, &kHash, key);
        }
        
        if (!match) {
            atLogError("probing error | key [%s] is not set", key);
            return atTypeCastPtr(void, ERR_PROCESS);
        }
        
        kvp = m->map[kHash];
    }; return kvp->v;
}

ATerrorType atSetHashmap(AThashmap* m, const char* key, void* value) {
    if (!key || !value || m->count+1 > m->max) { return ERR_PROCESS; }

    uint32_t kHash = atStringHash(key) % m->max;
    ATkvPair* kvp = m->map[kHash];

    // resolve collisions with open addressing + linear probing
    if (kvp) {
        if (!strcmp(key, kvp->k)) {
            m->map[kHash]->v = value;
            return ERR_NONE;        
        }

        uint8_t set = 0;
        
        // forward probing
        set = atProbeHashmapF(m, &kHash, NULL);

        // reverse probing
        if (!set) set = atProbeHashmapR(m, &kHash, NULL);

        if (!set) {
            atLogError("probing error | key[%s]", key);
            return ERR_MALLOC;
        }
    }

    m->map[kHash] = (ATkvPair*)malloc(sizeof(ATkvPair));
    m->map[kHash]->k = strdup(key);
    m->map[kHash]->v = value;
    m->count++;
    return ERR_NONE;
}

ATerrorType atRemHashmap(AThashmap* m, const char* key) {
    if (!key) { return ERR_PROCESS; }

    uint32_t kHash = atStringHash(key) % m->max;
    ATkvPair* kvp = m->map[kHash];

    if (kvp && strcmp(key, kvp->k)) {
        uint8_t match = 0;

        // forward probing
        match = atProbeHashmapF(m, &kHash, key);

        // reverse probing
        if (!match) {
            match = atProbeHashmapR(m, &kHash, key);
        }
        
        if (!match) {
            atLogError("probing error | key [%s] is not set", key);
            return ERR_MALLOC;
        }
        
        kvp = m->map[kHash];
    };

    free(m->map[kHash]);
    m->map[kHash] = NULL;
    return ERR_NONE;
}
