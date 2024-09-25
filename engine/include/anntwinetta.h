#ifndef ANNTWINETTA_H
#define ANNTWINETTA_H

#include "version.h"
#include "annt_ds.h"
#include "annt_ecs.h"
#include "annt_math.h"
#include "annt_proc.h"
#include "annt_types.h"
#include "annt_subsys.h"


#include "../platform/include/annt_web.h"
#include "../platform/include/annt_windows.h"

#ifdef _ANNT_WINDOWS_
#endif  // _ANNT_WINDOWS_

#ifdef _ANNT_WASM_
    #include "../backend/include/annt_wgl.h"
    #include "../vendor/emscripten/emscripten.h"
#endif  // _ANNT_WASM_

#ifdef _ANNT_GL_
    #include "../backend/include/annt_gl.h"
#endif  // _ANNT_GL_

#ifdef _ANNT_VK_
    #include "../backend/include/annt_vk.h"
#endif  // _ANNT_VK_

typedef struct _ANNT_internal {
    #ifdef _ANNT_GL_
        at_window_gl window;
    #endif
    
    #ifdef _ANNT_VK_
        at_window_vk window;
    #endif
    
    struct ecs {
        at_darray_t entity_arr;
    } ecs;

    struct engine_state {
        char _win_quit;
    } engine_state;

    struct subsys {
        at_render_subsys render_subsys;
    } subsys;
    
    char ver[100];
    at_event_t* event;
    at_proc_t* _proc_main;
} _ANNT_internal;
static _ANNT_internal ANNT;

// internal engine-level API
void _at_fallback(void*);


// public engine-level API
ANNT_API void at_init(void);

/*
    - ON WINDOWS
        this function runs all core anntwinetta procedures/sequences
        the user must call `at_set_main()` to set their code as the main procedure
        and then run the engine with `at_main()`

    - ON THE WEB
        nothing at the moment. feel free to omit from a web-based-build.
*/
ANNT_API void at_main(void);

ANNT_API void at_exit(void);
ANNT_API char* at_get_ver(void);

// set a function matching the type interface to run as the windows main procedure
ANNT_API void at_set_win_main(at_proc_main_ptr main);


// public subsystem API
ANNT_API void at_events(void);
ANNT_API void at_render(at_draw_call dc);
ANNT_API void at_update(void);

#endif  // at_H