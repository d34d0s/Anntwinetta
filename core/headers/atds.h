#pragma once

#include "attypes.h"
#include "athelpers.h"

typedef enum ATvalueType {
    TYPE_NONE=0,
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_STRING,
    VALUE_TYPES
} ATvalueType;

typedef struct ATvalue {
    void* value;
    ATvalueType type;
} ATvalue;

typedef struct ATarray {
    int max;
    int count;
    int resize;
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

// dynamic value
ATWIN_API int atGetInt(ATvalue* v);
ATWIN_API char* atGetString(ATvalue* v);
ATWIN_API float atGetFloat(ATvalue* v);
ATWIN_API void atDestroyValue(ATvalue* v);
ATWIN_API ATvalue* atMakeInt(int value);
ATWIN_API ATvalue* atMakeFloat(float value);
ATWIN_API ATvalue* atMakeString(const char* value);

// dynamic array
ATWIN_API void atDestroyArray(ATarray* inArr);
ATWIN_API ATarray* atMakeArray(int max, int resize);
ATWIN_API ATerrorType atResizeArray(ATarray* inArr);
ATWIN_API ATvalue* atPopArray(ATarray* inArr, int index);
ATWIN_API int atQueryArrayInt(ATarray* inArr, int index);
ATWIN_API ATvalue* atQueryArray(ATarray* inArr, int index);
ATWIN_API float atQueryArrayFloat(ATarray* inArr, int index);
ATWIN_API char* atQueryArrayString(ATarray* inArr, int index);
ATWIN_API ATerrorType atInsertArray(ATarray* inArr, int index, ATvalue* value);
ATWIN_API ATerrorType atInsertArrayV(ATarray* inArr, int count, ATvalue** values);

// hashmap
ATWIN_API void atDestroyHashmap(AThashmap* m);
ATWIN_API AThashmap* atMakeHashmap(uint32_t max);
ATWIN_API uint32_t atStringHash(const char* buffer);

ATWIN_API uint8_t atProbeHashmapF(AThashmap* m, uint32_t* kHash, const char* key);
ATWIN_API uint8_t atProbeHashmapR(AThashmap* m, uint32_t* kHash, const char* key);

ATWIN_API void* atGetHashmap(AThashmap* m, const char* key);
ATWIN_API ATerrorType atRemHashmap(AThashmap* m, const char* key);
ATWIN_API ATerrorType atSetHashmap(AThashmap* m, const char* key, void* value);


