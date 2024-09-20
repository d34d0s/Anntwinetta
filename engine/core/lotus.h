#pragma once

#include "lotus_types.h"

#ifdef _LOTUSWINDOWS_
    #include "../platform/windows/lotus_windows.h"
#endif

typedef struct _Lotus_Internal {
    char ver[100];
} _Lotus_Internal;
static _Lotus_Internal LOTUS;

LOTUSAPI void lotus_init(void);
LOTUSAPI void lotus_exit(void);
LOTUSAPI char* lotus_get_ver(void);
