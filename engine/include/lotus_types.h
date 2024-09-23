#ifndef LOTUSTYPES_H
#define LOTUSTYPES_H

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

typedef enum error_t {
    ERR_NONE=0,
    ERR_TYPE,
    ERR_MALLOC,
    ERR_TYPES,
} error_t;

#ifdef _LOTUS_WINDOWS_
    #ifdef _LOTUS_EXPORT_
        #define LOTUS_API __declspec(dllexport)
    #else
        #define LOTUS_API __declspec(dllimport)
    #endif
#endif

#ifdef _LOTUS_WASM_
    #include "../vendor/emscripten/emscripten.h"
    #define LOTUS_API __attribute__((used))
#endif

#ifndef LOTUS_API
    #define LOTUS_API
#endif

typedef unsigned long EID_TYPE;
typedef unsigned char NID_TYPE;
typedef unsigned short CID_TYPE;

typedef unsigned char       b8;
typedef unsigned short      b16;
typedef unsigned long       b32;
typedef unsigned long long  b64;

#define BYTE1_MAX (0b1 << 4)      // 4bit  max (half byte: 15)
#define BYTE2_MAX (0b1 << 8)      // 8bit  max (1 bytes: 255)
#define BYTE4_MAX (0b1 << 16)     // 16bit max (2 bytes: 65,535)
#define BYTE8_MAX (1ULL << 32)    // 32bit max (4 bytes: 4,294,967,295)

// Helper macro for checking if a value is a number or not
#define lotusIsNAN(V) ((V) != (V))

// Helpful macro for casting one type to another
#define lotusCast_t(A, B) ((A *)(B))

// Helpful macro for turning any given type into a const char* of itself
#define lotusToStr(TYPE) ((const char *)#TYPE)

// Helper macro for quickly determining the size of an array
#define lotusArraySize(__ARR) sizeof(__ARR) / sizeof(__ARR[0])

// Helper macro for an in place for-range loop
#define lotusForRange_i(__COUNT) for (uint32_t i = 0; i < __COUNT; ++i)

// Another helper macro for an in place for-range loop
#define lotusForRange_j(__COUNT) for (uint32_t j = 0; j < __COUNT; ++j)

#define lotusMax(A, B) ((A) > (B) ? (A) : (B))

#define lotusMin(A, B) ((A) < (B) ? (A) : (B))

#define lotusClamp(V, MIN, MAX) ((V) > (MAX) ? (MAX) : (V) < (MIN) ? (MIN) \
                                                                    : (V))

static void _lotusLog(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    printf("%s", "|Lotus| :: ");
    vprintf(message, args);
    printf("\n\n");
    va_end(args);
}

#define _lotusLogInit(MESSAGE, ...) \
    _lotusLog("|INIT| :: %s", ##__VA_ARGS__)

#define _lotusLogExit(MESSAGE, ...) \
    _lotusLog("|EXIT| :: %s", ##__VA_ARGS__)

#define _lotusLogInfo(MESSAGE, ...) \
    _lotusLog("|INFO| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _lotusLogSuccess(MESSAGE, ...) \
    _lotusLog("|SUCCESS| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _lotusLogWarning(MESSAGE, ...) \
    _lotusLog("|WARNING| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _lotusLogError(MESSAGE, ...) \
    _lotusLog("|ERROR| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _lotusLogFatal(MESSAGE, ...) \
    _lotusLog("|FATAL| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)


#endif