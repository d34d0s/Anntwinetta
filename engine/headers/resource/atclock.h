#pragma once

#include "../atmath.h"
#include "../attypes.h"
#include "../athelpers.h"

typedef struct ATclock {
    float last;               // Last update time in milliseconds
    float current;            // Current time in milliseconds
    float delta;            // Time since last frame in milliseconds
} ATclock;

ATclock _atMakeClock(void);
void _atClockTick(ATclock* clock);
