#include "headers/LotusMaterialEXT.h"

static void* MVP_VOID_VALUES[3] = {NULL, NULL, NULL};
static const char* MVP_NAMES[3] = {"umodel", "uview", "uproj"};
static unsigned int MVP_TYPES[3] = {UTYPE_MAT4, UTYPE_MAT4, UTYPE_MAT4};

unsigned char LotusDefaultMaterial_MVP (void) {
    return lotusMakeMaterial(
        vsrcMVP,
        fsrcMVP,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_MVPC (void) {
    return lotusMakeMaterial(
        vsrcMVPC,
        fsrcMVPC,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_MVPT (void) {
    return lotusMakeMaterial(
        vsrcMVPT,
        fsrcMVPT,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_MVPN (void) {
    return lotusMakeMaterial(
        vsrcMVPCT,
        fsrcMVPCT,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_MVPCT(void) {
    return lotusMakeMaterial(
        vsrcMVPCT,
        fsrcMVPCT,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_MVPCN(void) {
    return lotusMakeMaterial(
        vsrcMVPCT,
        fsrcMVPCT,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_MVPTN(void) {
    return lotusMakeMaterial(
        vsrcMVPCT,
        fsrcMVPCT,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}

unsigned char LotusDefaultMaterial_MVPCTN(void) {
    return lotusMakeMaterial(
        vsrcMVPCT,
        fsrcMVPCT,
        3,
        MVP_NAMES,
        MVP_TYPES,
        MVP_VOID_VALUES
    );
}
