#include "../../engine/include/lotus.h"

SDL_Event event;
bool main_loop(void* _) { 
    while( SDL_PollEvent( &event ) != 0 ) {
        if( event.type == SDL_QUIT ) { lotus_exit(); break; }
    }; lotus_render((lotus_draw_call){ .mode=DRAW_TRIANGLES });
    return 0;
}; lotus_web_wrapper(main_loop);

int main(void) {
    lotus_init();
    lotus_set_win_main(main_loop);
    lotus_set_web_main(main_loop_web);
    lotus_main();
    lotus_exit();
    return 0;
}