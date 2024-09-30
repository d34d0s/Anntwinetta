#pragma once

#include "attypes.h"

typedef atErrorType (*_process_prep_ptr)(void* d);
typedef atErrorType (*_process_main_ptr)(void* d);
typedef atErrorType (*_process_post_ptr)(void* d);

typedef struct ATprocess {
    int pid;
    void* data;
    _process_prep_ptr prep;
    _process_main_ptr main;
    _process_post_ptr post;
} ATprocess;

ATWIN_API atErrorType PROCESS_PREP_DEFAULT(void* d);
ATWIN_API atErrorType PROCESS_MAIN_DEFAULT(void* d);
ATWIN_API atErrorType PROCESS_POST_DEFAULT(void* d);

ATWIN_API ATprocess* atMakeProcess(void* d, _process_prep_ptr prep, _process_main_ptr main, _process_post_ptr post);
ATWIN_API atErrorType atDestroyProcess(ATprocess* p);
ATWIN_API atErrorType atRunProcess(ATprocess* p);
