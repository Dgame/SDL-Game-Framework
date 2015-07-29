#include "Event.hpp"

namespace sdl {
    bool PollEvent(Event* event) {
        SDL_Event sdl_event;
        if (SDL_PollEvent(&sdl_event)) {
            event->type = sdl_event.type;

            switch (sdl_event.type) {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    event->timestamp = sdl_event.key.timestamp;
                    event->windowID = sdl_event.key.windowID;

                    event->key.state = sdl_event.key.state;
                    event->key.repeat = sdl_event.key.repeat;
                    event->key.code = sdl_event.key.keysym.scancode;
                    event->key.key = sdl_event.key.keysym.sym;
                    event->key.mod = sdl_event.key.keysym.mod;
                break;

                case SDL_MOUSEMOTION:
                    event->timestamp = sdl_event.motion.timestamp;
                    event->windowID = sdl_event.motion.windowID;

                    event->motion.which = sdl_event.motion.which;
                    event->motion.state = sdl_event.motion.state;

                    event->motion.x = sdl_event.motion.x;
                    event->motion.y = sdl_event.motion.y;
                    event->motion.x_rel = sdl_event.motion.xrel;
                    event->motion.y_rel = sdl_event.motion.yrel;
                break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    event->timestamp = sdl_event.button.timestamp;
                    event->windowID = sdl_event.button.windowID;

                    event->button.which = sdl_event.button.which;
                    event->button.button = sdl_event.button.button;
                    event->button.state = sdl_event.button.state;
#if SDL_VERSION_ATLEAST(2, 0, 2)
                    event->button.clicks = sdl_event.button.clicks;
#endif
                    event->button.x = sdl_event.button.x;
                    event->button.y = sdl_event.button.y;
                break;

                case SDL_MOUSEWHEEL:
                    event->timestamp = sdl_event.wheel.timestamp;
                    event->windowID = sdl_event.wheel.windowID;

                    event->wheel.which = sdl_event.wheel.which;
                    event->wheel.x = sdl_event.wheel.x;
                    event->wheel.y = sdl_event.wheel.y;
#if SDL_VERSION_ATLEAST(2, 0, 4)
                    event->wheel.direction = sdl_event.wheel.direction;
#endif
                break;

                case SDL_QUIT:
                    event->timestamp = sdl_event.quit.timestamp;
                    event->windowID = 0;
                break;

                case SDL_WINDOWEVENT:
                    event->timestamp = sdl_event.window.timestamp;
                    event->windowID = sdl_event.window.windowID;

                    event->window.event = sdl_event.window.event;
                    event->window.delta_x = sdl_event.window.data1;
                    event->window.delta_x = sdl_event.window.data2;
                break;
            }

            return true;
        }

        return false;
    }
}
