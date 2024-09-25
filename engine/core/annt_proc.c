#include "../include/annt_proc.h"

/* DEFAULT CALLBACKS */
bool at_default_seq_main(void* v) {
    at_seq_t* s = (at_seq_t*) v;
    for (int p = 0; p < s->count; p++) {
        at_proc_t* _p = s->arr[p];
        if (_p->main(_p->data)) {
            _p->fallback(_p->data);
            return 1;
        }
    } return 0;
}

void at_default_seq_fallback(void* v) {
    printf("default seq fallback!\n");
    return;
}

bool at_default_main(void* v) {
    printf("default proc main!\n");
    return 0;
}

void at_default_fallback(void* v) {
    printf("default proc fallback!\n");
    return;
}

void at_del_proc(at_proc_t* proc) {
    if (!proc) return;
    proc->main = NULL;
    proc->data = NULL;
    proc->fallback = NULL;
    free(proc);
}

at_proc_t* at_new_proc(void* data, at_proc_main_ptr main, at_proc_fallback_ptr fallback) {
    at_proc_t* proc = (at_proc_t*)malloc(sizeof(at_proc_t));
    if (!proc) { return NULL; }
    proc->data = data;
    proc->main = (!main) ? at_default_main : main;
    proc->fallback = (!fallback) ? at_default_fallback : fallback;
    return proc;
}

void* at_get_proc_data(at_proc_t* p) { return p->data; }
void at_set_proc_data(at_proc_t* p, void* d) { p->data = d; }

// PROCESS SEQUENCE
void at_del_seq(at_seq_t* seq) {
    if (!seq) return;
    if (seq->count > 0) {
        for (int p = 0; p < seq->count; p++) {
            at_del_proc(seq->arr[p]);
        } seq->count = 0; seq->arr = NULL;
    } at_del_proc(seq->_proc);
    free(seq);
}

at_seq_t* at_new_seq(int count, ...) {
    at_seq_t* seq = (at_seq_t*)malloc(sizeof(at_seq_t));
    if (!seq) { return NULL; }
    
    seq->arr = (at_proc_t**)malloc(count*sizeof(at_proc_t*));
    if (!seq->arr) { free(seq); return NULL; }
    
    seq->count=0;
    va_list args;
    va_start(args, count);
    while (seq->count != count) {
        at_proc_t* out_proc = va_arg(args, at_proc_t*);
        if (!out_proc->main) break;
        seq->arr[seq->count++] = out_proc;
    } va_end(args);

    seq->_proc = at_new_proc(NULL, at_default_seq_main, at_default_seq_fallback);
    if (!seq->_proc) { free(seq); free(seq->arr); return NULL; }
    
    return seq;
};

