#ifndef ANNT_EVENTS_H
#define ANNT_EVENTS_H

#include "annt_types.h"

#include "../vendor/SDL2/SDL.h"

#define MAX_MOUSE_BUTTONS 5
#define MAX_KEYBOARD_KEYS 282 // SDL's number of scancodes

// Event Structures
/**
 * @brief Structure representing the state of a key on the keyboard.
 */
typedef struct at_keyboard_key {
    bool isPressed;    /**< Indicates if the key is currently pressed. */
    bool wasPressed;   /**< Indicates if the key was pressed in the previous frame. */
    bool justReleased; /**< Indicates if the key was released in the current frame. */
} at_keyboard_key;

/**
 * @brief Structure representing the state of a mouse button.
 */
typedef struct at_mouse_button {
    bool isPressed;  /**< Indicates if the mouse button is currently pressed. */
    bool wasPressed; /**< Indicates if the mouse button was pressed in the previous frame. */
    int scrollValue; /**< The scroll value of the mouse wheel. */
} at_mouse_button;
/**
 * @brief Enum representing various types of events.
 */
typedef enum at_event_type {
    at_quit_event,
    at_none_event,
    at_key_up_event,
    at_key_down_event,
    at_mouse_wheel_event,
    at_mouse_motion_event,
    at_mouse_button_up_event,
    at_controller_stick_event,
    at_mouse_button_down_event,
    at_controller_button_up_event,
    at_controller_button_down_event
    // at_quit_event=32787
} at_event_type;

/**
 * @brief Struct representing mouse buttons.
 */
typedef struct at_mouse_buttons {
    int LeftClick, RightClick, MiddleClick, X1, X2;
} at_mouse_buttons;

/**
 * @brief Struct representing keyboard keys.
 */
typedef struct at_keyboard_keys {
    int ESCAPE, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PRINTSCREEN, SCROLLLOCK, PAUSE,
        GRAVE, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0, MINUS, EQUALS, BACKSPACE,
        INSERT, HOME, PAGEUP, TAB, Q, W, E, R, T, Y, U, I, O, P, LEFTBRACKET, RIGHTBRACKET, BACKSLASH,
        DELETEKEY, END, PAGEDOWN, CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER,
        LEFTSHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RIGHTSHIFT, LEFTCTRL, LEFTALT,
        SPACE, RIGHTALT, RIGHTCTRL, UP, DOWN, LEFT, RIGHT, CONTEXT_MENU, POWER, VOLUME_UP,
        VOLUME_DOWN, MUTE, WWW, CALCULATOR, MY_COMPUTER, MAIL, MEDIA_SELECT, APP1, APP2;
} at_keyboard_keys;

/**
 * @brief Struct representing an event.
 */
typedef struct at_event_t {
    SDL_Event event;
    at_event_type type; /**< Type of the event. */
    union data {
        struct key {
            int keyCode; /**< Key code for keyboard events. */
        } key;
        struct mouseButton {
            int mouseX, mouseY; /**< Mouse coordinates for mouse events. */
            int button;         /**< Mouse button for mouse events. */
        } mouseButton;
        struct mouseWheel {
            int scrollDirection; /**< Scroll direction for mouse wheel events. Positive is away from the user, negative is toward the user. */
        } mouseWheel;
        struct mouseMotion {
            int mouseX, mouseY; // Mouse position
            int relX, relY;     // Relative motion
        } mouseMotion;
        struct controller {
            int controllerIndex;
            int controllerButton;
        } controller;
    } data;
} at_event_t;


// Clock for managing frame timing and FPS
typedef struct at_clock {
   float FPS;           // Current frames per second
   int maxFPS;          // Target maximum frames per second
   float TPF;           // Time per frame in milliseconds
   int lastTime;        // Last update time in milliseconds
   float deltaTime;     // Time since last frame in seconds
   float frameCount;    // Frames since last update
   int currentTime;     // Current time in milliseconds
} at_clock;

static at_mouse_button at_mouse_state[MAX_MOUSE_BUTTONS] = {0};
static at_keyboard_key at_keyboard_state[MAX_KEYBOARD_KEYS] = {0};

static at_mouse_buttons at_mouse = {
    SDL_BUTTON_LEFT,
    SDL_BUTTON_RIGHT,
    SDL_BUTTON_MIDDLE,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
};

static at_keyboard_keys at_keyboard = {
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
    SDL_SCANCODE_APP2};

/**
 * @brief Updates the keyboard state based on the events polled.
 *
 * @param engine Pointer to your lotus Engine structure.
 */
void at_update_keyboard_state();

/**
 * @brief Updates the mouse button state based on the events polled.
 *
 * @param engine Pointer to your lotus Engine structure.
 */
void at_update_mouse_button_state();

/**
 * @brief Allocates memory for a lotus Event structure and returns a pointer to it.
 *
 * @return Pointer to the newly allocated lotus Event structure.
 */
at_event_t *at_make_event_structure();

/**
 * @brief Checks if a key is triggered (pressed) in the current frame.
 *
 * @param keyCode The SDL keycode of the key to check.
 * @return true if the key is triggered, false otherwise.
 */
ANNT_API bool at_is_key_triggered(int keyCode);

/**
 * @brief Checks if a key is currently pressed.
 *
 * @param engine Pointer to your lotus Engine structure.
 * @param keyCode The SDL keycode of the key to check.
 * @return true if the key is currently pressed, false otherwise.
 */
ANNT_API bool at_is_key_pressed(int keyCode);

/**
 * @brief Checks if a key is currently released.
 *
 * @param engine Pointer to your lotus Engine structure.
 * @param keyCode The SDL keycode of the key to check.
 * @return true if the key is currently released, false otherwise.
 */
ANNT_API bool at_is_key_released(int keyCode);

/**
 * @brief Checks if a mouse button is triggered (pressed) in the current frame.
 *
 * @param button The SDL button index of the mouse button to check.
 * @return true if the mouse button is triggered, false otherwise.
 */
ANNT_API bool at_is_mouse_button_triggered(int button);

/**
 * @brief Checks if a mouse button is down (held) in the current frame.
 *
 * @param button The SDL button index of the mouse button to check.
 * @return true if the mouse button is triggered, false otherwise.
 */
ANNT_API bool at_is_mouse_button_pressed(int button);

/**
 * @brief Checks if the mouse wheel has been scrolled up.
 *
 * @return true if the mouse wheel has been scrolled up, false otherwise.
 */
ANNT_API bool at_is_mouse_wheel_scrolled_up();

/**
 * @brief Checks if the mouse wheel has been scrolled down.
 *
 * @return true if the mouse wheel has been scrolled down, false otherwise.
 */
ANNT_API bool at_is_mouse_wheel_scrolled_down();


#endif