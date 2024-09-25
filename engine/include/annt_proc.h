#ifndef ANNT_PROC_H
#define ANNT_PROC_H

#include "annt_types.h"

typedef bool (*at_proc_main_ptr)(void*);
typedef void (*at_proc_fallback_ptr)(void*);

typedef struct at_proc_t {
    void* data;
    at_proc_main_ptr main;
    at_proc_fallback_ptr fallback;
} at_proc_t;

typedef struct at_seq_t {
    size_t count;
    at_proc_t** arr;
    at_proc_t* _proc;
} at_seq_t;

ANNT_API void* at_get_proc_data(at_proc_t* p);
ANNT_API void at_set_proc_data(at_proc_t* p, void* d);

ANNT_API bool at_default_main(void* v);
ANNT_API void at_default_fallback(void* v);
ANNT_API bool at_default_seq_main(void* v);
ANNT_API void at_default_seq_fallback(void* v);

ANNT_API void at_del_proc(at_proc_t* proc);
ANNT_API at_proc_t* at_new_proc(void* data, at_proc_main_ptr main, at_proc_fallback_ptr fallback);

ANNT_API void at_del_seq(at_seq_t* seq);
ANNT_API at_seq_t* at_new_seq(int count, ...);

#define at_data_layout(itf, ...) struct { __VA_ARGS__; } itf;

#define at_proc_inplace(d, m, f)                     \
    at_proc_t* _proc_ = at_new_proc(d, m, f);     \
    if (_proc_) {                                       \
        if(_proc_->main(_proc_->data)) {                \
            _proc_->fallback(_proc_->data);             \
        } at_del_proc(_proc_);                       \
    }

#define at_seq_inplace(c, ...)\
    at_seq_t* _seq_ = at_new_seq(c, __VA_ARGS__);         \
    if (_seq_) {                                                \
        if(_seq_->proc_->main(_seq_->proc_->data)) {            \
            _seq_->proc_->fallback(_seq_->proc_->data);         \
        } at_del_proc(_proc_);                               \
    }

#endif