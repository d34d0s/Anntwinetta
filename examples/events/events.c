#include "../../engine/include/lotus.h"

void event_func(void) {
    lotus_events();
    if (lotus_is_key_pressed(lotus_keyboard.D)) printf("Pressing D\n");
    if (lotus_is_key_triggered(lotus_keyboard.A)) printf("Pressed A\n");
}

void render_func(void) {
    lotus_render(
       (lotus_draw_call){ .mode=DRAW_TRIANGLES }
    );
}

bool main_loop(void* _) {
    event_func();
    render_func();
    lotus_update();
    return 0;
}; lotus_web_wrapper(main_loop);    // 

int main(void) {
    lotus_init();
    lotus_set_win_main(main_loop);
    lotus_set_web_main(main_loop_web);
    lotus_main();
    return 0;
}