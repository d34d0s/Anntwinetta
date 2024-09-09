#ifndef LOTUSINPUT_H
#define LOTUSINPUT_H

#include "lotus_types.h"
#include "../vendor/GL/glfw3.h"

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

typedef struct LotusInputState {
    unsigned char current_keys[MAX_KEYS];
    unsigned char previous_keys[MAX_KEYS];
    unsigned char current_mouse_buttons[MAX_MOUSE_BUTTONS];
    unsigned char previous_mouse_buttons[MAX_MOUSE_BUTTONS];
} LotusInputState;
static LotusInputState lotusInputState;

typedef struct LotusClock {
    float delta;
    float current;
    float previous;
} LotusClock;

// WINDOW SPECIFIC EVENTS
void _lotusInitEvents(void);
void _lotusPollEvents(GLFWwindow* window);

// ENGINE CLOCK
LotusClock _lotusMakeClock(void);
void _lotusClockTick(LotusClock* clock);

// External Event/Input API
unsigned char _lotusIsKeyPressed(LotusKeyboardKey key);
unsigned char _lotusIsKeyTriggered(LotusKeyboardKey key);
unsigned char _lotusIsKeyReleased(LotusKeyboardKey key);
unsigned char _lotusIsMouseButtonPressed(LotusMouseButton button);
unsigned char _lotusIsMouseButtonTriggered(LotusMouseButton button);
unsigned char _lotusIsMouseButtonReleased(LotusMouseButton button);

#endif