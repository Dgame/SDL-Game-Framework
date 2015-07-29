#ifndef SDL_TEXTURE_HPP
#define SDL_TEXTURE_HPP

#include "types.hpp"

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Rect;

namespace sdl {
    struct Rect;
    struct Color;

    class Texture {
    public:
        explicit Texture(SDL_Texture*);
        Texture(const Texture&) = delete;
        virtual ~Texture();

        void query(u32_t*, u32_t*, u8_t* access = nullptr) const;

        SDL_Texture* get() const {
            return _tex;
        }

        void* lock(const Rect* area = nullptr, i32_t* pitch = nullptr) const;
        void unlock() const;

        void update(const void*, const Rect*, i32_t) const;

        void setColorMod(const Color&) const;
        Color getColorMod() const;

        void setOpcacity(u8_t) const;
        u8_t getOpcacity() const;

        void setBlendMode(u8_t) const;
        u8_t getBlendMode() const;

    private:
        SDL_Texture* _tex;
    };
}

#endif
