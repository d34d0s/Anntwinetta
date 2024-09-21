#include "../../core/lotus_math.h"
#include "../../core/lotus_types.h"
#include "../../vendor/SDL2/SDL_vulkan.h"

typedef struct lotus_window_vk {
    b8* title;
    b8 is_open;
    lm_vec2_i size;
    SDL_Window* _sdl_win;
} lotus_window_vk;

LOTUS_API b8 lotus_init_vk( lotus_window_vk* w );
