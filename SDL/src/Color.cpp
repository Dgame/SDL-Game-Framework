#include "Color.hpp"
#include <SDL.h>

namespace sdl {
    const Color Color::Black(0, 0, 0);
    const Color Color::White(255, 255, 255);
    const Color Color::Red(255, 0, 0);
    const Color Color::Green(0, 255, 0);
    const Color Color::Blue(0, 0, 255);
    const Color Color::Yellow(0, 255, 255);

    Color::Color(u8_t r, u8_t g, u8_t b, u8_t a) : red(r), green(g), blue(b), alpha(a) {

    }

    u32_t Color::mapFor(const SDL_PixelFormat* fmt) const {
        if (!fmt)
            return 0;
        return SDL_MapRGBA(fmt, this->red, this->green, this->blue, this->alpha);
    }

    SDL_Color* Color::copyInto(SDL_Color* col) const {
        if (col) {
            col->r = this->red;
            col->g = this->green;
            col->b = this->blue;
            col->a = this->alpha;
        }

        return col;
    }

    SDL_Color* TryCopyInto(const Color* col, SDL_Color* sdl_col) {
        if (col)
            return col->copyInto(sdl_col);
        return nullptr;
    }
}
