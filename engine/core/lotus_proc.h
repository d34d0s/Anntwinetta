#ifndef LOTUSPROC_H
#define LOTUSPROC_H

#include "lotus_types.h"

typedef bool (*proc_main_ptr)(void*);
typedef void (*proc_fallback_ptr)(void*);

typedef struct proc_t {
    void* data;
    proc_main_ptr main;
    proc_fallback_ptr fallback;
} proc_t;

typedef struct seq_t {
    size_t count;
    proc_t** arr;
    proc_t* _proc;
} seq_t;

LOTUS_API void* get_proc_data(proc_t* p);
LOTUS_API void set_proc_data(proc_t* p, void* d);

LOTUS_API bool default_main(void* v);
LOTUS_API void default_fallback(void* v);
LOTUS_API bool default_seq_main(void* v);
LOTUS_API void default_seq_fallback(void* v);

LOTUS_API void del_proc(proc_t* proc);
LOTUS_API proc_t* new_proc(void* data, proc_main_ptr main, proc_fallback_ptr fallback);

LOTUS_API void del_seq(seq_t* seq);
LOTUS_API seq_t* new_seq(int count, ...);

#define data_layout(itf, ...) struct { __VA_ARGS__; } itf;

#define proc_inplace(d, m, f)               \
    proc_t* _proc_ = new_proc(d, m, f);     \
    if (_proc_) {                           \
        if(_proc_->main(_proc_->data)) {   \
            _proc_->fallback(_proc_->data); \
        } del_proc(_proc_);                 \
    }

#define seq_inplace(c, ...)\
    seq_t* _seq_ = new_seq(c, __VA_ARGS__);             \
    if (_seq_) {                                        \
        if(_seq_->proc_->main(_seq_->proc_->data)) {   \
            _seq_->proc_->fallback(_seq_->proc_->data); \
        } del_proc(_proc_);                             \
    }

#endif