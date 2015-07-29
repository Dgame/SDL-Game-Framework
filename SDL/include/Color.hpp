#ifndef SDL_COLOR_HPP
#define SDL_COLOR_HPP

#include "types.hpp"

struct SDL_Color;
struct SDL_PixelFormat;

namespace sdl {
    struct Color {
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;

        u8_t red = 0;
        u8_t green = 0;
        u8_t blue = 0;
        u8_t alpha = 0;

        Color() = default;
        explicit Color(u8_t, u8_t, u8_t, u8_t a = 255);
        virtual ~Color() { }

        u32_t mapFor(const SDL_PixelFormat*) const;
        SDL_Color* copyInto(SDL_Color*) const;
    };

    SDL_Color* TryCopyInto(const Color*, SDL_Color*);
}

#endif
