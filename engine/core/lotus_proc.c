#include "../include/lotus_proc.h"

/* DEFAULT CALLBACKS */
bool lotus_default_seq_main(void* v) {
    lotus_seq_t* s = (lotus_seq_t*) v;
    for (int p = 0; p < s->count; p++) {
        lotus_proc_t* _p = s->arr[p];
        if (_p->main(_p->data)) {
            _p->fallback(_p->data);
            return 1;
        }
    } return 0;
}

void lotus_default_seq_fallback(void* v) {
    printf("default seq fallback!\n");
    return;
}

bool lotus_default_main(void* v) {
    printf("default proc main!\n");
    return 0;
}

void lotus_default_fallback(void* v) {
    printf("default proc fallback!\n");
    return;
}

void lotus_del_proc(lotus_proc_t* proc) {
    if (!proc) return;
    proc->main = NULL;
    proc->data = NULL;
    proc->fallback = NULL;
    free(proc);
}

lotus_proc_t* lotus_new_proc(void* data, lotus_proc_main_ptr main, lotus_proc_fallback_ptr fallback) {
    lotus_proc_t* proc = (lotus_proc_t*)malloc(sizeof(lotus_proc_t));
    if (!proc) { return NULL; }
    proc->data = data;
    proc->main = (!main) ? lotus_default_main : main;
    proc->fallback = (!fallback) ? lotus_default_fallback : fallback;
    return proc;
}

void* lotus_get_proc_data(lotus_proc_t* p) { return p->data; }
void lotus_set_proc_data(lotus_proc_t* p, void* d) { p->data = d; }

// PROCESS SEQUENCE
void lotus_del_seq(lotus_seq_t* seq) {
    if (!seq) return;
    if (seq->count > 0) {
        for (int p = 0; p < seq->count; p++) {
            lotus_del_proc(seq->arr[p]);
        } seq->count = 0; seq->arr = NULL;
    } lotus_del_proc(seq->_proc);
    free(seq);
}

lotus_seq_t* lotus_new_seq(int count, ...) {
    lotus_seq_t* seq = (lotus_seq_t*)malloc(sizeof(lotus_seq_t));
    if (!seq) { return NULL; }
    
    seq->arr = (lotus_proc_t**)malloc(count*sizeof(lotus_proc_t*));
    if (!seq->arr) { free(seq); return NULL; }
    
    seq->count=0;
    va_list args;
    va_start(args, count);
    while (seq->count != count) {
        lotus_proc_t* out_proc = va_arg(args, lotus_proc_t*);
        if (!out_proc->main) break;
        seq->arr[seq->count++] = out_proc;
    } va_end(args);

    seq->_proc = lotus_new_proc(NULL, lotus_default_seq_main, lotus_default_seq_fallback);
    if (!seq->_proc) { free(seq); free(seq->arr); return NULL; }
    
    return seq;
};

