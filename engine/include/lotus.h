#ifndef LOTUS_H
#define LOTUS_H

#include "version.h"
#include "lotus_ds.h"
#include "lotus_ecs.h"
#include "lotus_math.h"
#include "lotus_proc.h"
#include "lotus_types.h"
#include "lotus_subsys.h"


#include "../platform/include/lotus_web.h"
#include "../platform/include/lotus_windows.h"

#ifdef _LOTUS_WINDOWS_
#endif  // _LOTUS_WINDOWS_

#ifdef _LOTUS_WASM_
    #include "../backend/include/lotus_wgl.h"
    #include "../vendor/emscripten/emscripten.h"
#endif  // _LOTUS_WASM_

#ifdef _LOTUS_GL_
    #include "../backend/include/lotus_gl.h"
#endif  // _LOTUS_GL_

#ifdef _LOTUS_VK_
    #include "../backend/include/lotus_vk.h"
#endif  // _LOTUS_VK_

typedef struct _lotus_internal {
    #ifdef _LOTUS_GL_
        lotus_window_gl window;
    #endif
    
    #ifdef _LOTUS_VK_
        lotus_window_vk window;
    #endif
    
    struct engine_state {
        char _win_quit;
    } engine_state;

    struct subsys {
        lotus_render_subsys render_subsys;
    } subsys;
    
    char ver[100];
    lotus_event_t* event;
    lotus_proc_t* _proc_main;
} _lotus_internal;
static _lotus_internal LOTUS;

// internal engine-level API
void _lotus_fallback(void*);


// public engine-level API
LOTUS_API void lotus_init(void);

/*
    - ON WINDOWS
        this function runs all core lotus engine procedures/sequences
        the user must call `lotus_set_main()` to set their code as the main procedure
        and then run the engine with `lotus_main()`

    - ON THE WEB
        nothing at the moment. feel free to omit from a web-based-build.
*/
LOTUS_API void lotus_main(void);

LOTUS_API void lotus_exit(void);
LOTUS_API char* lotus_get_ver(void);

// set a function matching the type interface to run as the windows main procedure
LOTUS_API void lotus_set_win_main(lotus_proc_main_ptr main);


// public subsystem API
LOTUS_API void lotus_events(void);
LOTUS_API void lotus_render(lotus_draw_call dc);
LOTUS_API void lotus_update(void);

#endif  // LOTUS_H