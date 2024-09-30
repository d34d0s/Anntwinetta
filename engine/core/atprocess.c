#include "../headers/atprocess.h"

atErrorType PROCESS_PREP_DEFAULT(void* d) { return ERR_NONE; }
atErrorType PROCESS_MAIN_DEFAULT(void* d) { return ERR_NONE; }
atErrorType PROCESS_POST_DEFAULT(void* d) { return ERR_NONE; }

ATprocess* atMakeProcess(void* d, _process_prep_ptr prep, _process_main_ptr main, _process_post_ptr post) {
    static int n_process = 0;
    
    ATprocess* p = (ATprocess*)malloc(sizeof(ATprocess));
    if (!p) {
        atLogError("failed to allocate process");
        return (void*)ERR_MALLOC;
    }

    p->data=d;
    p->prep=prep;
    p->main=main;
    p->post=post;
    p->pid=n_process++;

    return p;
}

atErrorType atDestroyProcess(ATprocess* p) {
    p->data=NULL;
    p->prep=NULL;
    p->main=NULL;
    p->post=NULL;
    p->pid=-1;
    free(p);
}

atErrorType atRunProcess(ATprocess* p) {
    int err = p->prep(p->data);
    if (err) { atLogError("process 'prep' failed to run | aborting process"); return err; }

    err = p->main(p->data);
    if (err) { atLogError("process 'main' failed to run | aborting process"); return err; }

    err = p->post(p->data);
    if (err) { atLogError("process 'post' failed to run | aborting process"); return err; }

    return err;
}
