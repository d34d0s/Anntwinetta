#pragma once

#include "../attypes.h"
#include "../athelpers.h"

#include "../../vendor/SDL2/SDL.h"

#define MAX_MOUSE_BUTTONS 5
#define MAX_KEYBOARD_KEYS 282 // SDL's number of scancodes

// Event+Input Structures
typedef struct ATmouseButton {
    bool isPressed;  /** Indicates if the mouse button is currently pressed. */
    bool wasPressed; /** Indicates if the mouse button was pressed in the previous frame. */
    int scrollValue; /** The scroll value of the mouse wheel. */
} ATmouseButton;

typedef struct ATmouse {
    int LeftClick, RightClick, MiddleClick, X1, X2;
} ATmouse;


typedef struct ATkeyboardKey {
    bool isPressed;    /** Indicates if the key is currently pressed. */
    bool wasPressed;   /** Indicates if the key was pressed in the previous frame. */
    bool justReleased; /** Indicates if the key was released in the current frame. */
} ATkeyboardKey;

typedef struct ATkeyboard {
    int ESCAPE, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PRINTSCREEN, SCROLLLOCK, PAUSE,
        GRAVE, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0, MINUS, EQUALS, BACKSPACE,
        INSERT, HOME, PAGEUP, TAB, Q, W, E, R, T, Y, U, I, O, P, LEFTBRACKET, RIGHTBRACKET, BACKSLASH,
        DELETEKEY, END, PAGEDOWN, CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER,
        LEFTSHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RIGHTSHIFT, LEFTCTRL, LEFTALT,
        SPACE, RIGHTALT, RIGHTCTRL, UP, DOWN, LEFT, RIGHT, CONTEXT_MENU, POWER, VOLUME_UP,
        VOLUME_DOWN, MUTE, WWW, CALCULATOR, MY_COMPUTER, MAIL, MEDIA_SELECT, APP1, APP2;
} ATkeyboard;

static ATmouseButton atMouseState[MAX_MOUSE_BUTTONS] = {0};
static ATkeyboardKey atKeyboardState[MAX_KEYBOARD_KEYS] = {0};

typedef enum ATeventType {
    NONE_EVENT,
    KEYUP_EVENT,
    KEYDOWN_EVENT,
    MOUSEUP_EVENT,
    MOUSEDOWN_EVENT,
    MOUSEMOVE_EVENT,
    MOUSEWHEEL_EVENT,
    QUIT_EVENT=32787,
} ATeventType;

typedef struct ATeventData {
    int quit;
    SDL_Event* _sdlEvent;
    ATeventType type; /** Type of the event. */
    union data {
        struct key {
            int keyCode; /** Key code for keyboard events. */
        } key;
        struct mouseButton {
            int mouseX, mouseY; /** Mouse coordinates for mouse events. */
            int button;         /** Mouse button for mouse events. */
        } mouseButton;
        struct mouseWheel {
            int scrollDirection; /** Scroll direction for mouse wheel events. Positive is away from the user, negative is toward the user. */
        } mouseWheel;
        struct mouseMotion {
            int mouseX, mouseY; // Mouse position
            int relX, relY;     // Relative motion
        } mouseMotion;
    } data;
} ATeventData;

void _atSyncMouse();
void _atSyncKeyboard();
atErrorType _atPrepEvent(void* d);

atErrorType _atPrepEvent(void* d);
atErrorType _atMainEvent(void* d);
atErrorType _atPostEvent(void* d);


// public event+input API
static ATmouse atMouse = {
    SDL_BUTTON_LEFT,
    SDL_BUTTON_RIGHT,
    SDL_BUTTON_MIDDLE,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
};

static ATkeyboard atKeyboard = {
    SDL_SCANCODE_ESCAPE,
    SDL_SCANCODE_F1,
    SDL_SCANCODE_F2,
    SDL_SCANCODE_F3,
    SDL_SCANCODE_F4,
    SDL_SCANCODE_F5,
    SDL_SCANCODE_F6,
    SDL_SCANCODE_F7,
    SDL_SCANCODE_F8,
    SDL_SCANCODE_F9,
    SDL_SCANCODE_F10,
    SDL_SCANCODE_F11,
    SDL_SCANCODE_F12,
    SDL_SCANCODE_PRINTSCREEN,
    SDL_SCANCODE_SCROLLLOCK,
    SDL_SCANCODE_PAUSE,
    SDL_SCANCODE_GRAVE,
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_4,
    SDL_SCANCODE_5,
    SDL_SCANCODE_6,
    SDL_SCANCODE_7,
    SDL_SCANCODE_8,
    SDL_SCANCODE_9,
    SDL_SCANCODE_0,
    SDL_SCANCODE_MINUS,
    SDL_SCANCODE_EQUALS,
    SDL_SCANCODE_BACKSPACE,
    SDL_SCANCODE_INSERT,
    SDL_SCANCODE_HOME,
    SDL_SCANCODE_PAGEUP,
    SDL_SCANCODE_TAB,
    SDL_SCANCODE_Q,
    SDL_SCANCODE_W,
    SDL_SCANCODE_E,
    SDL_SCANCODE_R,
    SDL_SCANCODE_T,
    SDL_SCANCODE_Y,
    SDL_SCANCODE_U,
    SDL_SCANCODE_I,
    SDL_SCANCODE_O,
    SDL_SCANCODE_P,
    SDL_SCANCODE_LEFTBRACKET,
    SDL_SCANCODE_RIGHTBRACKET,
    SDL_SCANCODE_BACKSLASH,
    SDL_SCANCODE_DELETE,
    SDL_SCANCODE_END,
    SDL_SCANCODE_PAGEDOWN,
    SDL_SCANCODE_CAPSLOCK,
    SDL_SCANCODE_A,
    SDL_SCANCODE_S,
    SDL_SCANCODE_D,
    SDL_SCANCODE_F,
    SDL_SCANCODE_G,
    SDL_SCANCODE_H,
    SDL_SCANCODE_J,
    SDL_SCANCODE_K,
    SDL_SCANCODE_L,
    SDL_SCANCODE_SEMICOLON,
    SDL_SCANCODE_APOSTROPHE,
    SDL_SCANCODE_RETURN,
    SDL_SCANCODE_LSHIFT,
    SDL_SCANCODE_Z,
    SDL_SCANCODE_X,
    SDL_SCANCODE_C,
    SDL_SCANCODE_V,
    SDL_SCANCODE_B,
    SDL_SCANCODE_N,
    SDL_SCANCODE_M,
    SDL_SCANCODE_COMMA,
    SDL_SCANCODE_PERIOD,
    SDL_SCANCODE_SLASH,
    SDL_SCANCODE_RSHIFT,
    SDL_SCANCODE_LCTRL,
    SDL_SCANCODE_LALT,
    SDL_SCANCODE_SPACE,
    SDL_SCANCODE_RALT,
    SDL_SCANCODE_RCTRL,
    SDL_SCANCODE_UP,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
    SDL_SCANCODE_APPLICATION,
    SDL_SCANCODE_POWER,
    SDL_SCANCODE_VOLUMEUP,
    SDL_SCANCODE_VOLUMEDOWN,
    SDL_SCANCODE_MUTE,
    SDL_SCANCODE_WWW,
    SDL_SCANCODE_CALCULATOR,
    SDL_SCANCODE_COMPUTER,
    SDL_SCANCODE_MAIL,
    SDL_SCANCODE_MEDIASELECT,
    SDL_SCANCODE_APP1,
    SDL_SCANCODE_APP2
};

ATWIN_API bool atIsKeyPressed(int keyCode);
ATWIN_API bool atIsKeyReleased(int keyCode);
ATWIN_API bool atIsKeyTriggered(int keyCode);

ATWIN_API bool atIsMouseWheelScrolledUp();
ATWIN_API bool atIsMouseWheelScrolledDown();
ATWIN_API bool atIsMouseButtonPressed(int button);
ATWIN_API bool atIsMouseButtonTriggered(int button);
