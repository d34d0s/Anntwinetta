#ifndef LOTUSWEB_H
#define LOTUSWEB_H

#include "../../include/lotus_types.h"

#define lotus_web_wrapper(wl)   \
    void wl##_web() {           \
        wl((void*)0);           \
    }                           \

typedef void (*_lotus_web_main_ptr)(void);

// set a function matching the type interface to run as the browser's main procedure
LOTUS_API void lotus_set_web_main(_lotus_web_main_ptr main);


#endif