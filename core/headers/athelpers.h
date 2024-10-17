#ifndef AT_HELPERS_H
#define AT_HELPERS_H

#include "attypes.h"

#define atInlineStruct(itf, ...) struct { __VA_ARGS__; } itf;

// Helper macro for checking if a value is a number or not
#define atIsNan(V) ((V) != (V))

// Helpful macro for casting one type to another
#define atTypeCast(T, V) ((T)V)
#define atTypeCastPtr(T, V) ((T*)V)

// Helpful macro for creating a pointer
#define atPointTo(A, P) (P=&A)

// Helpful macro for dereferencing a pointer
#define atDeRef(T, P) (*(T *)P)

// Helpful macro for turning a type into a const char* of itself
#define atToStr(TYPE) ((const char *)#TYPE)

// Helper macro for quickly determining the size of an array
#define atArraySize(__ARR) sizeof(__ARR) / sizeof(__ARR[0])

// Helper macros for an in place for-range loops
#define atForRangeI(__COUNT) for (uint32_t i = 0; i < __COUNT; ++i)
#define atForRangeJ(__COUNT) for (uint32_t j = 0; j < __COUNT; ++j)
#define atForRangeK(__COUNT) for (uint32_t k = 0; k < __COUNT; ++k)

#define atMax(A, B) ((A) > (B) ? (A) : (B))

#define atMin(A, B) ((A) < (B) ? (A) : (B))

#define atClamp(V, MIN, MAX) ((V) > (MAX) ? (MAX) : (V) < (MIN) ? (MIN) : (V))

typedef struct atImage {
    unsigned char* data;
    int width;
    int height;
    int channels;
} atImage;

ATWIN_API char *atReadFile(const char *path);

ATWIN_API int atInitIntArray(int** array, unsigned int size, const char* fieldName);
ATWIN_API int atInitIntPointerArray(int*** array, unsigned int size, unsigned int size2, const char* fieldName);

ATWIN_API int atInitUnsignedIntArray(unsigned int** array, unsigned int size, const char* fieldName);
ATWIN_API int atInitUnsignedIntPointerArray(unsigned int*** array, unsigned int size, unsigned int size2, const char* fieldName);

ATWIN_API int atInitCharArray(char** array, unsigned int size, const char* fieldName);
ATWIN_API int atInitCharPointerArray(char*** array, unsigned int size, unsigned int size2, const char* fieldName);

ATWIN_API int atInitConstCharArray(const char** array, unsigned int size, const char* fieldName);
ATWIN_API int atInitConstCharPointerArray(const char*** array, unsigned int size, unsigned int size2, const char* fieldName);

ATWIN_API int atInitVoidArray(void** array, unsigned int size, const char* fieldName);
ATWIN_API int atInitVoidPointerArray(void*** array, unsigned int size, unsigned int size2, const char* fieldName);

#endif