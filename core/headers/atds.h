#pragma once

#include "attypes.h"
#include "athelpers.h"

typedef struct ATarray {
    int max;
    int count;
    void** arr;
} ATarray;

typedef struct ATkvPair {
    const char* k;
    void* v;
} ATkvPair;

typedef struct AThashmap {
    uint32_t max;
    uint32_t count;
    ATkvPair** map;
} AThashmap;

//dynamic array
ATWIN_API ATarray* atMakeArray(int max);
ATWIN_API void atDestroyArray(ATarray* inArr);
ATWIN_API ATerrorType atResizeArray(ATarray* inArr);
ATWIN_API void* atPopArray(ATarray* inArr, int index);
ATWIN_API ATerrorType atInsertArray(ATarray* inArr, int index, void* inData);


// hashmap
ATWIN_API void atDestroyHashmap(AThashmap* m);
ATWIN_API AThashmap* atMakeHashmap(uint32_t max);
ATWIN_API uint32_t atStringHash(const char* buffer);

ATWIN_API uint8_t atProbeHashmapF(AThashmap* m, uint32_t* kHash, const char* key);
ATWIN_API uint8_t atProbeHashmapR(AThashmap* m, uint32_t* kHash, const char* key);

ATWIN_API void* atGetHashmap(AThashmap* m, const char* key);
ATWIN_API ATerrorType atRemHashmap(AThashmap* m, const char* key);
ATWIN_API ATerrorType atSetHashmap(AThashmap* m, const char* key, void* value);


