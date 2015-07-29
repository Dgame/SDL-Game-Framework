#ifndef SDL_SURFACE_HPP
#define SDL_SURFACE_HPP

#include <string>
#include "types.hpp"

struct SDL_Surface;
struct SDL_PixelFormat;

namespace sdl {
    struct Rect;
    struct Color;
    class Texture;
    class Renderer;

    class Surface {
    public:
        explicit Surface(u16_t, u16_t, u8_t);
        explicit Surface(void*, u16_t, u16_t, u8_t);
        explicit Surface(const std::string&);
        explicit Surface(SDL_Surface*);
        Surface(const Surface&);
        virtual ~Surface();

        Texture* asTextureOf(Renderer*) const;

        void saveToFile(const char*) const;
        void blit(const Surface&, Rect* dst = nullptr, const Rect* src = nullptr) const;

        u32_t width() const;
        u32_t height() const;

        void* pixels() const;
        SDL_PixelFormat* getFormat() const;

        SDL_Surface* get() const {
            return _srfc;
        }

        Surface convert(const SDL_PixelFormat*) const;
        void fill(const Color&, const Rect* dst = nullptr) const;

        void setColorKey(const Color&, bool) const;
        Color getColorKey() const;

        void setColorMod(const Color&) const;
        Color getColorMod() const;

        void setBlendMode(u8_t) const;
        u8_t getBlendMode() const;

    private:
        SDL_Surface* _srfc;
    };
}

#endif
