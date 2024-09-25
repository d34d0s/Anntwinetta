#ifndef ANNT_TYPES_H
#define ANNT_TYPES_H

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

#ifdef _ANNT_WINDOWS_
    #ifdef _ANNT_EXPORT_
        #define ANNT_API __declspec(dllexport)
    #else
        #define ANNT_API __declspec(dllimport)
    #endif
#endif

#ifdef _ANNT_WASM_
    #include "../vendor/emscripten/emscripten.h"
    #define ANNT_API __attribute__((used))
#endif

#ifndef ANNT_API
    #define ANNT_API
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
#define at_is_nan(V) ((V) != (V))

// Helpful macro for casting one type to another
#define at_cast_t(A, B) ((A *)(B))

// Helpful macro for turning any given type into a const char* of itself
#define at_to_str(TYPE) ((const char *)#TYPE)

// Helper macro for quickly determining the size of an array
#define at_array_size(__ARR) sizeof(__ARR) / sizeof(__ARR[0])

// Helper macro for an in place for-range loop
#define at_for_range_i(__COUNT) for (uint32_t i = 0; i < __COUNT; ++i)

// Another helper macro for an in place for-range loop
#define at_for_range_j(__COUNT) for (uint32_t j = 0; j < __COUNT; ++j)

#define at_max(A, B) ((A) > (B) ? (A) : (B))

#define at_min(A, B) ((A) < (B) ? (A) : (B))

#define at_clamp(V, MIN, MAX) ((V) > (MAX) ? (MAX) : (V) < (MIN) ? (MIN) \
                                                                    : (V))

static void _at_log(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    printf("%s", "| ~Anntiwnetta~ | :: ");
    vprintf(message, args);
    printf("\n\n");
    va_end(args);
}

#define _at_log_init(MESSAGE, ...) \
    _at_log("|INIT| :: %s", ##__VA_ARGS__)

#define _at_log_exit(MESSAGE, ...) \
    _at_log("|EXIT| :: %s", ##__VA_ARGS__)

#define _at_log_info(MESSAGE, ...) \
    _at_log("|INFO| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _at_log_success(MESSAGE, ...) \
    _at_log("|SUCCESS| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _at_log_warning(MESSAGE, ...) \
    _at_log("|WARNING| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _at_log_error(MESSAGE, ...) \
    _at_log("|ERROR| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define _at_log_fatal(MESSAGE, ...) \
    _at_log("|FATAL| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)


#endif