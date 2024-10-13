#pragma once

#include "../atmath.h"
#include "../attypes.h"
#include "../athelpers.h"

typedef struct ATclock {
    float FPS;              // Current frames per second
    float TPF;              // Time per frame in milliseconds
    int maxFPS;             // Target maximum frames per second
    int last;               // Last update time in milliseconds
    int current;            // Current time in milliseconds
    float delta;            // Time since last frame in seconds
    float frames;           // Frames since last update
} ATclock;

ATclock _atMakeClock(float maxFPS);
void _atClockTick(ATclock* clock);
