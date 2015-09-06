#ifndef SDL_TEXTURE_HPP
#define SDL_TEXTURE_HPP

#include <memory>

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
        Texture() = default;
        explicit Texture(SDL_Texture*, u32_t, u32_t);

        void query(u32_t*, u32_t*, u8_t* access = nullptr) const;

        SDL_Texture* raw() const {
            return _tex.get();
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

        u32_t width() const {
            return _width;
        }

        u32_t height() const {
            return _height;
        }

    private:
        std::shared_ptr<SDL_Texture> _tex;

        u32_t _width;
        u32_t _height;
    };
}

#endif
