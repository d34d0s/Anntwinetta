#include "lotus_proc.h"

/* DEFAULT CALLBACKS */
bool default_seq_main(void* v) {
    seq_t* s = (seq_t*) v;
    for (int p = 0; p < s->count; p++) {
        proc_t* _p = s->arr[p];
        if (_p->main(_p->data)) {
            _p->fallback(_p->data);
            return 1;
        }
    } return 0;
}

void default_seq_fallback(void* v) {
    printf("default seq fallback!\n");
    return;
}

bool default_main(void* v) {
    printf("default proc main!\n");
    return 0;
}

void default_fallback(void* v) {
    printf("default proc fallback!\n");
    return;
}

void del_proc(proc_t* proc) {
    if (!proc) return;
    proc->main = NULL;
    proc->data = NULL;
    proc->fallback = NULL;
    free(proc);
}

proc_t* new_proc(void* data, proc_main_ptr main, proc_fallback_ptr fallback) {
    proc_t* proc = (proc_t*)malloc(sizeof(proc_t));
    if (!proc) { return NULL; }
    proc->data = data;
    proc->main = (!main) ? default_main : main;
    proc->fallback = (!fallback) ? default_fallback : fallback;
    return proc;
}

void* get_proc_data(proc_t* p) { return p->data; }
void set_proc_data(proc_t* p, void* d) { p->data = d; }

// PROCESS SEQUENCE
void del_seq(seq_t* seq) {
    if (!seq) return;
    if (seq->count > 0) {
        for (int p = 0; p < seq->count; p++) {
            del_proc(seq->arr[p]);
        } seq->count = 0; seq->arr = NULL;
    } del_proc(seq->_proc);
    free(seq);
}

seq_t* new_seq(int count, ...) {
    seq_t* seq = (seq_t*)malloc(sizeof(seq_t));
    if (!seq) { return NULL; }
    
    seq->arr = (proc_t**)malloc(count*sizeof(proc_t*));
    if (!seq->arr) { free(seq); return NULL; }
    
    seq->count=0;
    va_list args;
    va_start(args, count);
    while (seq->count != count) {
        proc_t* out_proc = va_arg(args, proc_t*);
        if (!out_proc->main) break;
        seq->arr[seq->count++] = out_proc;
    } va_end(args);

    seq->_proc = new_proc(NULL, default_seq_main, default_seq_fallback);
    if (!seq->_proc) { free(seq); free(seq->arr); return NULL; }
    
    return seq;
};

