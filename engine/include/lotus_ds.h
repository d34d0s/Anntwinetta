#ifndef LOTUSDH_H
#define LOTUSDH_H

#include "lotus_types.h"

typedef struct darray_t {
    int max;
    int count;
    void** arr;
} darray_t;


LOTUS_API void* lotus_pop_darray(darray_t* d);
LOTUS_API bool lotus_full_darray(darray_t* d);
LOTUS_API bool lotus_append_darray(darray_t* d, void* v);
LOTUS_API bool lotus_resize_darray(int more, darray_t* d);
LOTUS_API darray_t lotus_new_darray(int max, int c_init, ...);

#endif