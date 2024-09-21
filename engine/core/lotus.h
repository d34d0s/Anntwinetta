#pragma once

#include "lotus_types.h"

#ifdef _LOTUS_WINDOWS_
    #include "../platform/windows/lotus_windows.h"
#endif  // _LOTUS_WINDOWS_

#ifdef _LOTUS_GL_
    #include "../backend/GL/lotus_gl.h"
#endif

#ifdef _LOTUS_VK_
    #include "../backend/VK/lotus_vk.h"
#endif

typedef struct _Lotus_Internal {
    char ver[100];
    #ifdef _LOTUS_GL_
        lotus_window_gl window;
    #endif
    #ifdef _LOTUS_VK_
        lotus_window_vk window;
    #endif
} _Lotus_Internal;
static _Lotus_Internal LOTUS;

LOTUS_API void lotus_init(void);
LOTUS_API void lotus_exit(void);
LOTUS_API char* lotus_get_ver(void);

#ifdef _LOTUS_GL_
    LOTUS_API void render_test_gl();

#endif