#include "../headers/atds.h"

/*

DYNAMIC ARRAY

*/

ATarray* atMakeArray(int max) {
    ATarray* arr = (ATarray*)malloc(sizeof(ATarray));
    if (!arr) {
        atLogError("failed to allocate dynamic array");
        return atTypeCastPtr(ATarray, ERR_MALLOC);
    }

    arr->max = max;
    arr->count = 0;
    arr->arr = (void**)malloc(max*sizeof(void*));
    if (!arr->arr) {
        free(arr);
        atLogError("failed to allocate dynamic array");
        return atTypeCastPtr(ATarray, ERR_MALLOC);
    }; return arr;
}

void atDestroyArray(ATarray* inArr) {
    free(inArr->arr);
    inArr->arr = NULL;
    inArr->count = 0;
    inArr->max = 0;
    free(inArr);
}

atErrorType atResizeArray(ATarray* inArr) {
    int resize = 10;
    atErrorType err = ERR_NONE;
    
    void** temp = (void**)realloc(inArr->arr, inArr->max+resize * sizeof(void*));
    if (!temp) {
        err = ERR_MALLOC;
        return err;
    }
    
    inArr->max += resize;
    inArr->arr = temp;
    return err;
}

atErrorType atInsertArray(int index, ATarray* inArr, void* inData) {
    atErrorType err = ERR_NONE;
    if (!inArr || index < 0) { return err; }

    if (index > inArr->max || inArr->count+1 >= inArr->max) {
        atResizeArray(inArr);
    }

    inArr->arr[index] = inData;
    inArr->count++;
    return err;
}

void* atPopArray(int index, ATarray* inArr) {
    atErrorType err = ERR_NONE;
    if (!inArr || index > inArr->max || index > inArr->count) { return atTypeCastPtr(void, err); }

    void* value;
    if (index < 0) {
        value = inArr->arr[inArr->count-1];
    } else {
        value = inArr->arr[index];

        int remaining = inArr->count-(index+1);

        atForRangeI(remaining) {
            inArr->arr[index+i] = inArr->arr[index+i+1];
        }
    }
    
    inArr->arr[inArr->count-1] = NULL;
    inArr->count--;
    return value;
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

atErrorType atSetHashmap(AThashmap* m, const char* key, void* value) {
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

atErrorType atRemHashmap(AThashmap* m, const char* key) {
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
