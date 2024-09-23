#ifndef LOTUS_H
#define LOTUS_H

#include "version.h"
#include "lotus_ds.h"
#include "lotus_ecs.h"
#include "lotus_math.h"
#include "lotus_proc.h"
#include "lotus_types.h"
#include "lotus_subsys.h"

#ifdef _LOTUS_WINDOWS_
    #include "../platform/include/lotus_windows.h"
#endif  // _LOTUS_WINDOWS_

#ifdef _LOTUS_GL_
    #include "../backend/include/lotus_gl.h"
#endif  // _LOTUS_GL_

#ifdef _LOTUS_WASM_
    #include "../vendor/emscripten/emscripten.h"
    #include "../backend/include/lotus_wgl.h"
#endif  // _LOTUS_WASM_

#ifdef _LOTUS_VK_
    #include "../backend/include/lotus_vk.h"
#endif  // _LOTUS_VK_

typedef struct _lotus_internal {
    char ver[100];
    #ifdef _LOTUS_GL_
        lotus_window_gl window;
    #endif
    #ifdef _LOTUS_VK_
        lotus_window_vk window;
    #endif
    struct subsys {
        lotus_render_subsys render_subsys;
    } subsys;
} _lotus_internal;
static _lotus_internal LOTUS;

LOTUS_API void lotus_init(void);
LOTUS_API void lotus_exit(void);
LOTUS_API char* lotus_get_ver(void);

// public subsystem API
LOTUS_API void lotus_render(lotus_draw_call dc);

#ifdef _LOTUS_GL_
    LOTUS_API void render_test_gl();

#endif  // _LOTUS_GL_ LOTUS_API 

#endif  // LOTUS_H