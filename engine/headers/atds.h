#pragma once

#include "attypes.h"
#include "athelpers.h"

typedef struct ATarray {
    int max;
    int count;
    void** arr;
} ATarray;

typedef struct ATkvPair {
    uint8_t* k;
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
ATWIN_API atErrorType atResizeArray(ATarray* inArr);
ATWIN_API void* atPopArray(int index, ATarray* inArr);
ATWIN_API atErrorType atInsertArray(int index, ATarray* inArr, void* inData);


// hashmap
ATWIN_API void atDestroyHashmap(AThashmap* m);
ATWIN_API AThashmap* atMakeHashmap(uint32_t max);
ATWIN_API uint32_t atStringHash(uint8_t* buffer);

ATWIN_API uint8_t atProbeHashmapF(AThashmap* m, uint32_t* kHash, const char* key);
ATWIN_API uint8_t atProbeHashmapR(AThashmap* m, uint32_t* kHash, const char* key);

ATWIN_API void* atGetHashmap(AThashmap* m, uint8_t* key);
ATWIN_API atErrorType atRemHashmap(AThashmap* m, uint8_t* key);
ATWIN_API atErrorType atSetHashmap(AThashmap* m, uint8_t* key, void* value);


