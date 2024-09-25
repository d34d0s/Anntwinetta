#ifndef ANNT_DH_H
#define ANNT_DH_H

#include "annt_types.h"

typedef struct at_darray_t {
    int max;
    int count;
    void** arr;
} at_darray_t;


ANNT_API void* at_pop_darray(at_darray_t* d);
ANNT_API bool at_full_darray(at_darray_t* d);
ANNT_API bool at_append_darray(at_darray_t* d, void* v);
ANNT_API bool at_resize_darray(int more, at_darray_t* d);
ANNT_API at_darray_t at_new_darray(int max, int c_init, ...);

#endif