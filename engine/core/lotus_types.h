#pragma once

#include "../vendor/SDL2/SDL.h"

#define LOTUS_KEEPALIVE __attribute__((used))

#ifdef _LOTUSWINDOWS_
    #ifdef _LOTUSEXPORT_
        #define LOTUSAPI __declspec(dllexport)
    #else
        #define LOTUSAPI __declspec(dllimport)
    #endif
#endif

#ifdef _LOTUSWASM_
    #define LOTUSAPI __attribute__((used))
#endif
