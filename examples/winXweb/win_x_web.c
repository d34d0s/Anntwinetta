#include "../../engine/include/anntwinetta.h"

SDL_Event event;
bool main_loop(void* _) { 
    while( SDL_PollEvent( &event ) != 0 ) {
        if( event.type == SDL_QUIT ) { at_exit(); break; }
    }; at_render((at_draw_call){ .mode=DRAW_TRIANGLES });
    return 0;
}; at_web_wrapper(main_loop);

int main(void) {
    at_init();
    at_set_win_main(main_loop);
    at_set_web_main(main_loop_web);
    at_main();
    at_exit();
    return 0;
}