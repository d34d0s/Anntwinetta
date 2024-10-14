#include "../../headers/resource/atclock.h"
#include "../../vendor/GLFW/glfw3.h"

ATclock _atMakeClock(void) {
    ATclock c = {
        .last=0.0f,
        .delta=0.0f,
        .current=glfwGetTime(),
    };return c;
}

void _atClockTick(ATclock* clock) {
    clock->current = glfwGetTime();
    clock->delta = clock->current - clock->last;
    clock->last = clock->current;
}
