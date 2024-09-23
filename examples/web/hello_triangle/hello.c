#include "../../../engine/include/lotus.h"

SDL_Event e;
bool quit = false;

void main_loop() {
    while( SDL_PollEvent( &e ) != 0 ) {
        if( e.type == SDL_QUIT ) { quit = true; }
    }
}

int main(void) {
    lotus_init();
    
    emscripten_set_main_loop(main_loop, 0, 1);
    
    lotus_exit();
    return 0;
}