#pragma once

#include "attypes.h"

typedef ATerrorType (*_process_prep_ptr)(void* d);
typedef ATerrorType (*_process_main_ptr)(void* d);
typedef ATerrorType (*_process_post_ptr)(void* d);

typedef struct ATprocess {
    int pid;
    void* data;
    _process_prep_ptr prep;
    _process_main_ptr main;
    _process_post_ptr post;
} ATprocess;

ATWIN_API ATerrorType PROCESS_PREP_DEFAULT(void* d);
ATWIN_API ATerrorType PROCESS_MAIN_DEFAULT(void* d);
ATWIN_API ATerrorType PROCESS_POST_DEFAULT(void* d);

ATWIN_API ATprocess* atMakeProcess(void* d, _process_prep_ptr prep, _process_main_ptr main, _process_post_ptr post);
ATWIN_API ATerrorType atDestroyProcess(ATprocess* p);
ATWIN_API ATerrorType atRunProcess(ATprocess* p);
