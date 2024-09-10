#include "headers/LotusMaterialEXT.h"

static void* MVP_VOID_VALUES[3] = {NULL, NULL, NULL};
static const char* MVP_NAMES[3] = {"umodel", "uview", "uproj"};
static unsigned int MVP_TYPES[3] = {UTYPE_MAT4, UTYPE_MAT4, UTYPE_MAT4};

unsigned char LotusDefaultMaterial_001 (void) {
    return lotusMakeMaterial(
        vsrc001,
        fsrc001,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_002(void) {
    return lotusMakeMaterial(
        vsrc002,
        fsrc002,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}
