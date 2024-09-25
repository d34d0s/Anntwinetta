#ifndef ANNT_WEB_H
#define ANNT_WEB_H

#include "../../include/annt_types.h"

#define at_web_wrapper(wl)   \
    void wl##_web() {           \
        wl((void*)0);           \
    }                           \

typedef void (*_at_web_main_ptr)(void);

// set a function matching the type interface to run as the browser's main procedure
ANNT_API void at_set_web_main(_at_web_main_ptr main);


#endif