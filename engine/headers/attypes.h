#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED
#include "../vendor/SDL2/SDL.h"

#ifdef _ATWIN_WINDOWS_
    #ifdef _ATWIN_EXPORT_
        #define ATWIN_API __declspec(dllexport)
    #else
        #define ATWIN_API __declspec(dllimport)
    #endif
#else
    #ifdef _ATWIN_WEB_
        #include "../vendor/emscripten/emscripten.h"
        #define ATWIN_API __attribute__((used))
    #else 
        #define ATWIN_API
    #endif
#endif

#ifdef _ATWIN_WINDOWS_
    #define atMainLoop(logic)       \
        while (atRunning()) {       \
            logic                   \
        }; atExit();
#else
    #ifdef _ATWIN_WEB_
        #define atMainLoop(logic)       \
            void mainLoop(void) {       \
                logic                   \
            }; emscripten_set_main_loop(mainLoop);
    #else
        #define atMainLoop(logic)
    #endif
#endif

#define NOVALUE -1

typedef unsigned char       b8;
typedef unsigned short      b16;
typedef unsigned long       b32;
typedef unsigned long long  b64;

#define BYTE1_MAX (0b1 << 4)      // 4bit  max (half byte: 15)
#define BYTE2_MAX (0b1 << 8)      // 8bit  max (1 bytes: 255)
#define BYTE4_MAX (0b1 << 16)     // 16bit max (2 bytes: 65,535)
#define BYTE8_MAX (1ULL << 32)    // 32bit max (4 bytes: 4,294,967,295)

typedef enum atErrorType {
    ERR_NONE=0,
    ERR_INIT,
    ERR_TYPE,
    ERR_DRAW,
    ERR_MALLOC,
    ERR_SHADER,
    ERR_PROCESS,
    ERR_TYPES,
} atErrorType;

static void atLog(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    printf("%s", "| ~Anntwinetta~ | :: ");
    vprintf(message, args);
    printf("\n\n");
    va_end(args);
}

#define atLogInit(MESSAGE, ...) \
    atLog("|INIT| :: %s", ##__VA_ARGS__)

#define atLogExit(MESSAGE, ...) \
    atLog("|EXIT| :: %s", ##__VA_ARGS__)

#define atLogInfo(MESSAGE, ...) \
    atLog("|INFO| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define atLogSuccess(MESSAGE, ...) \
    atLog("|SUCCESS| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define atLogWarning(MESSAGE, ...) \
    atLog("|WARNING| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define atLogError(MESSAGE, ...) \
    atLog("|ERROR| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define atLogFatal(MESSAGE, ...) \
    atLog("|FATAL| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

