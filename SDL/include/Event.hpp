#ifndef SDL_EVENT_HPP
#define SDL_EVENT_HPP

#include "types.hpp"
#include <SDL.h> // because of SDL_VERSION_ATLEAST Macro

#undef main

namespace sdl {
    struct KeyboardEvent {
        u8_t state;
        u8_t repeat;

        u32_t code;
        i32_t key;
        u16_t mod;
    };

    struct MouseMotionEvent {
        u32_t which;
        u32_t state;

        i32_t x;
        i32_t y;

        i32_t x_rel;
        i32_t y_rel;
    };

    struct MouseButtonEvent {
        u32_t which;
        u8_t button;

        u8_t state;
#if SDL_VERSION_ATLEAST(2, 0, 2)
        u8_t clicks;
#endif
        i32_t x;
        i32_t y;
    };

    struct MouseWheelEvent {
        u32_t which;

        i32_t x;
        i32_t y;
#if SDL_VERSION_ATLEAST(2, 0, 4)
        u32_t direction;
#endif
    };

    struct QuitEvent {  };

    struct WindowEvent {
        u8_t event;
        i32_t delta_x;
        i32_t delta_y;
    };

    struct Event {
        u32_t type;
        u32_t timestamp;
        u32_t windowID;

        union {
            WindowEvent window;
            KeyboardEvent key;
            MouseMotionEvent motion;
            MouseButtonEvent button;
            MouseWheelEvent wheel;
            QuitEvent quit;
        };
    };

    bool PollEvent(Event*);
}

#endif
