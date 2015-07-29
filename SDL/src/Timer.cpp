#include "Timer.hpp"

#include <SDL.h>

namespace sdl {
    Timer::Timer() : _start_ticks(0), _stop_ticks(0), _running(false) {
        
    }

    void Timer::start() {
        _start_ticks = _stop_ticks = SDL_GetTicks();
        _running = true;
    }

    void Timer::stop() {
        _stop_ticks = SDL_GetTicks();
        _running = false;
    }

    u32_t Timer::getTicks() const {
        if (_running)
            return SDL_GetTicks() - _start_ticks;
        return _start_ticks - _stop_ticks;
    }
}