#include "../../../engine/include/lotus.h"

void main() {
    lotus_init();
    printf("INIT OK\n");
    
    SDL_Event event;
    bool quit = false;

    lotus_entity_t e  = {10, 0};

    while(!quit) {
        while( SDL_PollEvent( &event ) != 0 ) {
            if( event.type == SDL_QUIT ) { quit = true; }
        }
        lotus_render((lotus_draw_call){ .mode=DRAW_TRIANGLES });
    } lotus_exit();
}

