#include "../../../engine/include/lotus.h"

int main(int argc, char* argv[]) {
    lotus_init();
    SDL_Event e;
    bool quit = false;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) { quit = true; }
        }
        render_test_gl();
    } lotus_exit();
    return 0;
}