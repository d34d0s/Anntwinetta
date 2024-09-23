#ifndef LOTUSPROC_H
#define LOTUSPROC_H

#include "lotus_types.h"

typedef bool (*lotus_proc_main_ptr)(void*);
typedef void (*lotus_proc_fallback_ptr)(void*);

typedef struct lotus_proc_t {
    void* data;
    lotus_proc_main_ptr main;
    lotus_proc_fallback_ptr fallback;
} lotus_proc_t;

typedef struct lotus_seq_t {
    size_t count;
    lotus_proc_t** arr;
    lotus_proc_t* _proc;
} lotus_seq_t;

LOTUS_API void* lotus_get_proc_data(lotus_proc_t* p);
LOTUS_API void lotus_set_proc_data(lotus_proc_t* p, void* d);

LOTUS_API bool lotus_default_main(void* v);
LOTUS_API void lotus_default_fallback(void* v);
LOTUS_API bool lotus_default_seq_main(void* v);
LOTUS_API void lotus_default_seq_fallback(void* v);

LOTUS_API void lotus_del_proc(lotus_proc_t* proc);
LOTUS_API lotus_proc_t* lotus_new_proc(void* data, lotus_proc_main_ptr main, lotus_proc_fallback_ptr fallback);

LOTUS_API void lotus_del_seq(lotus_seq_t* seq);
LOTUS_API lotus_seq_t* lotus_new_seq(int count, ...);

#define lotus_data_layout(itf, ...) struct { __VA_ARGS__; } itf;

#define lotus_proc_inplace(d, m, f)                     \
    lotus_proc_t* _proc_ = lotus_new_proc(d, m, f);     \
    if (_proc_) {                                       \
        if(_proc_->main(_proc_->data)) {                \
            _proc_->fallback(_proc_->data);             \
        } lotus_del_proc(_proc_);                       \
    }

#define lotus_seq_inplace(c, ...)\
    lotus_seq_t* _seq_ = lotus_new_seq(c, __VA_ARGS__);         \
    if (_seq_) {                                                \
        if(_seq_->proc_->main(_seq_->proc_->data)) {            \
            _seq_->proc_->fallback(_seq_->proc_->data);         \
        } lotus_del_proc(_proc_);                               \
    }

#endif