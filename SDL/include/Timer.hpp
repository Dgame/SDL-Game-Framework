#ifndef SDL_TIMER_HPP
#define SDL_TIMER_HPP

#include "types.hpp"

namespace sdl {
    class Timer {
    public:
        Timer();
        virtual ~Timer() { }

        void start();
        void stop();

        u32_t getTicks() const;

    private:
        u32_t _start_ticks;
        u32_t _stop_ticks;

        bool _running;
    };
}

#endif
