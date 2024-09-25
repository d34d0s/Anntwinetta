#include "../include/annt_web.h"


void at_set_web_main(_at_web_main_ptr main) {
    #ifdef _ANNT_WASM_
        emscripten_set_main_loop(main, 0, 1);
    #endif
}
