#ifndef LOTUSSUBSYS_H
#define LOTUSSUBSYS_H

#include "lotus_ecs.h"
#include "lotus_math.h"
#include "lotus_proc.h"
#include "lotus_types.h"

#include "../backend/include/lotus_gl.h"

#define DRAW_LINES                          0x0001
#define DRAW_POINTS                         0x0000
#define DRAW_TRIANGLES                      0x0004

typedef struct lotus_draw_call lotus_draw_call;
typedef struct lotus_render_subsys lotus_render_subsys;

struct lotus_draw_call {
    int mode;
    lotus_render_subsys* rsys;
};

struct lotus_render_subsys {
    struct state {
        int mode;
        int drawing;
        lm_vec3 ccolor;
    } state;
    lotus_proc_t* _proc;
    lotus_window_gl* window;
};

bool lotus_render_main(void*);
void lotus_render_fallback(void*);
bool lotus_init_render_subsys(int mode, lm_vec3 ccolor, lotus_render_subsys* rsys);

#endif