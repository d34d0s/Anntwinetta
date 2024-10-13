#include "../../headers/resource/atclock.h"
#include "../../vendor/GLFW/glfw3.h"

ATclock _atMakeClock(float maxFPS) {
    ATclock c = {
        .FPS=0.0f,
        .TPF=0.0f,
        .last=0.0f,
        .delta=0.0f,
        .frames=0.0f,
        .maxFPS = maxFPS,
        .current=glfwGetTime(),
    }; return c;
}

void _atClockTick(ATclock* clock) {
    clock->current = glfwGetTime();
    clock->delta = clock->current - clock->last;
    clock->last = clock->current;
}
