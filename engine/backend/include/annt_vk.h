#include "../../include/annt_math.h"
#include "../../include/annt_types.h"
#include "../../vendor/SDL2/SDL_vulkan.h"

typedef struct at_window_vk {
    b8* title;
    b8 is_open;
    at_vec2_i size;
    SDL_Window* _sdl_win;
} at_window_vk;

ANNT_API b8 at_init_vk( at_window_vk* w );
