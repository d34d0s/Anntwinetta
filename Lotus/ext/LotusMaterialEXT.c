#include "headers/LotusMaterialEXT.h"

void lotusInitMaterialEXT(void) {
    static const char* MVP_NAMES[3] = {"umodel", "uview", "uproj"};
    static unsigned int MVP_TYPES[3] = {UTYPE_MAT4, UTYPE_MAT4, UTYPE_MAT4};
    static void* MVP_VOID_VALUES[3] = {NULL, NULL, NULL};
    LotusDefaultMaterial_001 = lotusMakeMaterial(
        vsrc001,
        fsrc001,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

