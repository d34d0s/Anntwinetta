#include "../../../engine/core/lotus.h"

bool log_proc(void* msg) {
    char* _msg = (char*) msg;
    printf("[ LOG ] | %s\n", _msg);
    return ERR_NONE;
}

typedef struct {
    float dx, dy;
    lm_vec2* vec;
} move_data;

bool proc_move_vec2(void* md) {
    move_data* _md = (move_data*) md;
    _md->vec->x += _md->dx;
    _md->vec->y += _md->dy;
    return ERR_NONE;
}

void main() {
    lotus_init();
    
    lm_vec2 my_vec = lm_new_vec2(0, 0);
    printf("vec coordinates pre process | %0.1f, %0.1f\n", my_vec.x, my_vec.y);
    
    data_layout(move_data, float dx; float dy; lm_vec2* vec);
    move_data.dx = 15.0f;
    move_data.dy = 30.0f;
    move_data.vec= &my_vec;
    proc_inplace(&move_data, proc_move_vec2, default_fallback);

    printf("vec coordinates post process | %0.1f, %0.1f\n", my_vec.x, my_vec.y);

    proc_t* console_out = new_proc(NULL, log_proc, default_fallback);
    console_out->main((void*)"hello, faraway!");
    console_out->main((void*)"nice to meet you!");

    lotus_exit();
}