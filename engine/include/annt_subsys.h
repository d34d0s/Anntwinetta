#ifndef ANNT_SUBSYS_H
#define ANNT_SUBSYS_H

#include "annt_ecs.h"
#include "annt_math.h"
#include "annt_proc.h"
#include "annt_types.h"
#include "annt_events.h"

#include "../backend/include/annt_gl.h"

#define DRAW_LINES                          0x0001
#define DRAW_POINTS                         0x0000
#define DRAW_TRIANGLES                      0x0004

typedef struct at_draw_call at_draw_call;
typedef struct at_render_subsys at_render_subsys;

struct at_draw_call {
    int mode;
    at_render_subsys* rsys;
};

struct at_render_subsys {
    struct state {
        int mode;
        int drawing;
        at_vec3 ccolor;
    } state;
    at_proc_t* _proc;
    at_window_gl* window;
};

// Render SubSystem
bool at_render_main(void*);
void at_render_fallback(void*);
bool at_init_render_subsys(int mode, at_vec3 ccolor, at_render_subsys* rsys);

// Event SubSystem

/**
 * @brief Polls an SDL event and populates the provided lotus Event structure accordingly.
 *
 * @param engine Pointer your lotus Engine structure.
 * @return true if an event was polled and processed, false otherwise.
 */

bool at_events_main(void*);

void at_events_fallback(void*);

#endif