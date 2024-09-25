#include "../../engine/include/anntwinetta.h"

void event_func(void) {
    at_events();    // Call Anntwinetta's event procedure
    if (at_is_key_pressed(at_keyboard.D)) printf("Pressing D\n");
    if (at_is_key_triggered(at_keyboard.A)) printf("Pressed A\n");
}

void render_func(void) {
    // Anntwinetta's render procedure acts on a data-layout called a 'draw-call'
    // more on that in the docs
    at_render(
       (at_draw_call){ .mode=DRAW_TRIANGLES }
    );
}

bool main_loop(void* _) {
    event_func();
    render_func();
    at_update();    // Anntwinetta's subsystems need certain state to be update/refreshed
    return 0;
}; at_web_wrapper(main_loop);

int main(void) {
    at_init();  // Initialize Anntwinetta
 
    // Anntwinetta's main procedure,
    // implement this as you please, but do...
    // NOTE THE TYPE INTERFACES THAT MUST BE MATCHED FOR BOTH
    // WINDOWS AND WEB MAIN FUNCIONS:
    // Web Main Function Signature: void web_main(void)
    // Windows Main Function Signature: bool win_main(void*)
    at_set_win_main(main_loop);
    at_set_web_main(main_loop_web);
    at_main();
    return 0;
}