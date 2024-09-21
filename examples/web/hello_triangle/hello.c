#include "../../../engine/core/lotus.h"

SDL_Event e;
bool quit = false;

void main_loop() {
    while( SDL_PollEvent( &e ) != 0 ) {
        if( e.type == SDL_QUIT ) { quit = true; }
    }
    render_test_gl();
}

int main(int argc, char* argv[]) {
    lotus_init();
    emscripten_set_main_loop(main_loop, 0, 1);
    lotus_exit();
    return 0;
}