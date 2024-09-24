#include "../include/lotus_web.h"


void lotus_set_web_main(_lotus_web_main_ptr main) {
    #ifdef _LOTUS_WASM_
        emscripten_set_main_loop(main, 0, 1);
    #endif
}
