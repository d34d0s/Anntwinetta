#include "../include/lotus_ds.h"

bool lotus_full_darray(darray_t* d) { return (d->count >= d->max) ? 1 : 0; }
darray_t lotus_new_darray(int max, int c_init, ...) {
    darray_t d;
    d.arr = (void**)malloc(c_init*sizeof(void*));
    if (!d.arr) { return d; }
    d.count = c_init; d.max = max;

    va_list args;
    va_start(args, c_init);
    for (int v = 0; v < c_init; v++) {
        d.arr[v] = va_arg(args, void*);
    } va_end(args); return d;
}

bool lotus_resize_darray(int more, darray_t* d) {
    if (more > d->max || more <= 0) { return 1; }

    void** temp = (void**)realloc(d->arr, (d->count+more)*sizeof(void*));
    if (!temp) { return 1; }; d->arr = temp;

    return 0;
}
bool lotus_append_darray(darray_t* d, void* v) {
    if (d->count+1 > d->max || lotus_full_darray(d)) { return 1; }
    d->arr[d->count++] = v; return 0;
}
void* lotus_pop_darray(darray_t* d) {
    if ((d->count <= 0) | !d->arr) { return (void*)0; }
    void* v = d->arr[d->count-1];
    d->arr[--d->count] = (void*)0;
    
    void** temp = (void**)realloc(d->arr, d->count*sizeof(void*));
    if (temp) {
        d->arr = temp;
    } else{ return (void*)0; }
    
    return v;
}

