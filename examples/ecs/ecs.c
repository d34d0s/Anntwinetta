#include "../../engine/include/anntwinetta.h"

void event_func(void) {
    at_events();
    if (at_is_key_pressed(at_keyboard.D)) printf("Pressing D\n");
    if (at_is_key_triggered(at_keyboard.A)) printf("Pressed A\n");
}

void render_func(void) {
    at_render(
       (at_draw_call){ .mode=DRAW_TRIANGLES }
    );
}

bool main_loop(void* _) {
    event_func();
    render_func();
    at_update();
    return 0;
}; at_web_wrapper(main_loop);

int main(void) {
    at_init();
    at_set_win_main(main_loop);
    at_set_web_main(main_loop_web);
    at_main();
    return 0;
}
